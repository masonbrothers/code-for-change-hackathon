#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

#include <eosio/system.hpp>

#include <string>

#define SECONDS_VOTING_LASTS 60

namespace eosiosystem {
   class system_contract;
}

namespace eosio {
   using std::string;

   class [[eosio::contract("factfinder")]] factfinder : public contract {
      public:
         using contract::contract;
         
         factfinder(name receiver, name code, datastream<const char *> ds) : 
            contract(receiver, code, ds),
            eos_symbol("SYS", 4){

               
            }

         [[eosio::action]]
         void init() {
            index_table indicies( get_self(), get_first_receiver().value );
            auto i = indicies.find(0);
            check(i == indicies.end(), "Contract has already been initialized");
            indicies.emplace(get_self(), [&]( auto& s ) {
                s.vote_index = 0;
                s.message_index = 0;
                s.only = 0;
            });
         }
        

        /**
          * Post message from poster
          * @param poster - the account to post from,
          * @param message - the message to be posted,
          */
         [[eosio::action]]
         void post( const name& poster, const std::string& message ) {
            require_auth( poster );
            check( is_account( poster ), "poster account does not exist" );

            index_table indicies( get_self(), get_first_receiver().value );
            auto i = indicies.find(0);
            check(i != indicies.end(), "Contract has not been initialized please call init");
            
            message_table messages( get_self(), get_first_receiver().value );

            time_point current_time = current_time_point();

            messages.emplace( poster, [&]( auto& s ) {
               s.poster = poster;
               s.message = message;
               s.message_id    = i->message_index + 1;
               s.post_time     = current_time;
               s.staked_true   = 0;
               s.staked_false  = 0;
            });

            indicies.modify(i, get_self(), [&]( auto& s ) {
               s.message_index = i->message_index + 1;
            });
         }

         [[eosio::on_notify("eosio.token::transfer")]]
         void castvote( const name& voter, const name& receiver, const asset& amount, const std::string& memo ) {
            check(memo.length() >= 2, "memo must be t/f then message_id example t1");
            
            check(memo.at(0) == 't' || memo.at(0) == 'f', "memo must start with t or f");
            const bool is_true = memo.at(0) == 't';

            const uint64_t message_id = std::atoi(memo.substr(1).c_str());
            
            require_auth( voter );
            check( is_account( voter ), "voter account does not exist" );

            check(receiver == get_self() && voter != get_self(), "This is not the correct function");

            index_table indicies( get_self(), get_first_receiver().value );
            auto i = indicies.find(0);
            check(i != indicies.end(), "Contract has not been initialized please call init");
            
            message_table messages( get_self(), get_first_receiver().value );
            auto msg = messages.find(message_id);
            
            check(msg != messages.end(), "message does not exist");

            check(is_active(msg), "voting is over");
            check(amount.amount > 0, "amount must be positive");
            check(amount.symbol == eos_symbol, "only SYS tokens are accepted");
            
            vote_table votes( get_self(), get_first_receiver().value );
            
            votes.emplace(get_self(), [&](auto &s) {
               s.amount = amount;
               s.voter = voter;
               s.vote_on = message_id;
               s.is_true = is_true;
               s.vote_id = i->vote_index + 1;
            });

            indicies.modify(i, get_self(), [&]( auto& s ) {
               s.vote_index = i->vote_index + 1;
            });

            if (is_true) {
               messages.modify(msg, get_self(), [&](auto &s) {
                  s.staked_true += amount.amount;
               });
            } else {
               messages.modify(msg, get_self(), [&](auto &s) {
                  s.staked_false += amount.amount;
               });
            }
            
         };

         [[eosio::action]]
         void withdraw( const uint64_t& vote_id ) {
            index_table indicies( get_self(), get_first_receiver().value );
            auto i = indicies.find(0);
            check(i != indicies.end(), "Contract has not been initialized please call init");

            vote_table votes( get_self(), get_first_receiver().value );
            auto v = votes.find(vote_id);

            check(v != votes.end(), "vote_id is not a cast vote");

            require_auth(v->voter);

            message_table messages( get_self(), get_first_receiver().value );
            auto msg = messages.find(v->vote_on);
            
            check(msg != messages.end(), "message does not exist");

            check(!is_active(msg), "cannot withdraw as voting is not over");
            
            check(v->is_true == (msg->staked_true > msg->staked_false), "stake lost as consensus determined opposite of vote");

            action{
               permission_level{get_self(), "active"_n},
               "eosio.token"_n,
               "transfer"_n,
               std::make_tuple(get_self(), v->voter, v->amount, std::string("Return Staked Tokens from Voting"))
            }.send();
         };

         using init_action = eosio::action_wrapper<"init"_n, &factfinder::init>;
         using post_action = eosio::action_wrapper<"post"_n, &factfinder::post>;
         using castvote_action = eosio::action_wrapper<"castvote"_n, &factfinder::castvote>;
         using withdraw_action = eosio::action_wrapper<"withdraw"_n, &factfinder::withdraw>;
         
      private:   
         const symbol eos_symbol;

         struct [[eosio::table]] vote {
            asset    amount;
            name     voter;
            uint64_t vote_on;
            bool     is_true;
            uint64_t vote_id;
            uint64_t primary_key()const { return vote_id; }
         };

         struct [[eosio::table]] message {
            name        poster;
            std::string message;
            uint64_t    message_id;
            time_point  post_time;
            uint64_t    staked_true;
            uint64_t    staked_false;

            uint64_t primary_key()const { return message_id; }
         };

         struct [[eosio::table]] index {
            uint64_t vote_index;
            uint64_t message_index;
            uint64_t only;
            uint64_t primary_key()const { return only; }
         };

         typedef eosio::multi_index< "messages"_n, message > message_table;
         typedef eosio::multi_index< "votes"_n, vote > vote_table;
         typedef eosio::multi_index< "indecies"_n, index > index_table;


         static bool is_active(const message_table::const_iterator& msg) {
            return (msg->post_time + time_point(seconds(SECONDS_VOTING_LASTS))) < eosio::current_time_point();
         }
   };

}
