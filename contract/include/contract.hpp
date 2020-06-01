#pragma once

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
      private:
      const symbol eos_symbol;

      public:
         using contract::contract;
         
         factfinder(name receiver, name code, datastream<const char *> ds) : 
            contract(receiver, code, ds),
            eos_symbol("SYS", 4){

               index_table indicies( get_self(), get_first_receiver().value );
               indicies.emplace(get_self(), [&]( auto& s ) {
                  s.vote_index = 0;
                  s.message_index = 0;
               });
            }

         [[eosio::action]]
         void post( const name& poster, const std::string& message ) {
            require_auth( poster );

            check( is_account( poster ), "poster account does not exist" );

            index_table indicies( get_self(), get_first_receiver().value );
            index i = indicies.get(0);
            // TODO NEED TO UPDATE INDEX

            message_table messages( get_self(), get_first_receiver().value );

            time_point current_time = current_time_point();

            messages.emplace( poster, [&]( auto& s ) {
               s.poster = poster;
               s.message = message;
               s.message_id    = i.message_index + 1;
               s.post_time     = current_time;
               s.staked_true   = 0;
               s.staked_false  = 0;
            });

         }

         [[eosio::action]]
         void castvote( const name& voter, const uint64_t& message_id, const asset& amount, const bool& is_true ) {
            require_auth( voter );
            check( is_account( voter ), "voter account does not exist" );

            

            /*
            message_table messages;
            auto message = messages.find(message_id);

            if (message == messages.end()) {
               check(false, "message does not exist");
            }

            check(isActive(message), "voting is over");

            */
            /*
            action{
               permission_level{get_self(), "active"_n},
               "eosio.token"_n,
               "transfer"_n,
               std::make_tuple(owner, get_self() hodl_it->funds, std::string("Staking Tokens for Voting"))
            }.send();
            */
         };

         [[eosio::action]]
         void withdraw( const uint64_t& vote_id ) {
            

            /*
            action{
               permission_level{get_self(), "active"_n},
               "eosio.token"_n,
               "transfer"_n,
               std::make_tuple(get_self(),  hodl_it->funds, std::string("Staking Tokens for Voting"))
            }.send();
            */
         }

         using post_action = eosio::action_wrapper<"post"_n, &factfinder::post>;
         using castvote_action = eosio::action_wrapper<"castvote"_n, &factfinder::castvote>;
         using withdraw_action = eosio::action_wrapper<"withdraw"_n, &factfinder::withdraw>;
      private:
         struct [[eosio::table]] vote {
            asset    balance;
            name     voter;
            uint64_t vote_on;
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

            uint64_t primary_key()const { return 0; }
         };

         typedef eosio::multi_index< "messages"_n, message > message_table;
         typedef eosio::multi_index< "votes"_n, vote > vote_table;
         typedef eosio::multi_index< "indecies"_n, index > index_table;


         bool is_active(const message& msg) {
            return (msg.post_time + time_point(seconds(SECONDS_VOTING_LASTS))) < eosio::current_time_point();
         }
   };

}