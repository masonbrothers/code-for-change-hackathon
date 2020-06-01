#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   class [[eosio::contract("eosio.token")]] token : public contract {
      public:
         using contract::contract;
         
         [[eosio::action]]
         void post( const name& poster, const std::string& message, const asset& amount, const int64_t& reply_id ) {
            require_auth( poster );

            check( is_account( poster ), "poster account does not exist" );

            auto sym_code_raw = symbol.code().raw();
            stats statstable( get_self(), sym_code_raw );
            const auto& st = statstable.get( sym_code_raw, "symbol does not exist" );
            check( st.supply.symbol == symbol, "symbol precision mismatch" );

            accounts acnts( get_self(), owner.value );
            auto it = acnts.find( sym_code_raw );
            if( it == acnts.end() ) {
               acnts.emplace( poster, [&]( auto& a ){
               a.balance = asset{0, symbol};
               });
            }

            action{
               permission_level{get_self(), "active"_n},
               get_self(),
               "vote"_n,
               std::make_tuple(poster, message_id, amount, true)
            }.send();
         }

         [[eosio::action]]
         void vote( const name& voter, const asset& amount, const bool& is_true ) {
            require_auth( voter );
            check( is_account( voter ), "voter account does not exist" );

            accounts stakes( get_self(),  );
            auto it = acnts.find( sym_code_raw );
            if( it == acnts.end() ) {
               acnts.emplace( poster, [&]( auto& a ){
               a.balance = asset{0, symbol};
               });
            }

            action{
               permission_level{get_self(), "active"_n},
               "eosio.token"_n,
               "transfer"_n,
               std::make_tuple(owner, get_self() hodl_it->funds, std::string("Staking Tokens for Voting"))
            }.send();
         };

         [[eosio::action]]
         void solidify( const uint64_t& id ) {

            check(now() > the_party, "Hold your horses");
         }

         void withdraw( const uint64_t& vote_id )

         using post_action = eosio::action_wrapper<"post"_n, &token::post>;
         using vote_action = eosio::action_wrapper<"vote"_n, &token::vote>;
         using solidify_action = eosio::action_wrapper<"solidify"_n, &token::solidify>;
      private:
         struct [[eosio::table]] vote {
            asset    balance;
            name     voter;
            uint64_t vote_on;
            uint64_t vote_id;
            uint64_t primary_key()const { return vote_id; }
         };

         struct [[eosio::table]] message {
            name     poster;
            std::string message;
            uint64_t message_id;
            uint64_t reply_to;
            uint32_t post_time;
            uint64_t staked_true;
            uint64_t staked_false;



            uint64_t primary_key()const { return message_id; }
         };

         typedef eosio::multi_index< "messages"_n, account > messages;
         typedef eosio::multi_index< "stakes"_n, stake > stakes;
   };

}