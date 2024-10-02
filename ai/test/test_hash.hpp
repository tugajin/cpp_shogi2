#ifndef __TEST_HASH_HPP__
#define __TEST_HASH_HPP__

#include "../common.hpp"
#include "../util.hpp"
#include "../game.hpp"
#include "../matesearch.hpp"
#include "../attack.hpp"
#include "../pnsearch.hpp"

namespace test {
void test_hash() {
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        hand[0] = inc_hand(hand[0],GOLD);
        hand[1] = inc_hand(hand[1],GOLD);
        auto pos = game::Position(pieces,hand,BLACK);
        Tee<<pos<<std::endl;

        auto pos2 = pos.next(move(SQ_45,GOLD));
        ASSERT(pos.is_ok());
        ASSERT(pos2.is_ok());
        Tee<<pos<<std::endl;
        Tee<<pos2<<std::endl;


        auto pos3 = pos2.next(move(SQ_66,GOLD));
        ASSERT(pos3.is_ok());

    }
   {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);
        Tee<<pos<<std::endl;

        auto pos2 = pos.next(move(SQ_59,SQ_58));
        ASSERT(pos.is_ok());
        ASSERT(pos2.is_ok());
        Tee<<pos<<std::endl;
        Tee<<pos2<<std::endl;
        auto pos3 = pos2.next(move(SQ_53,SQ_52));
        ASSERT(pos3.is_ok());

    }
   {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BPS, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, WGO, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);
        Tee<<pos<<std::endl;

        auto pos2 = pos.next(move(SQ_59,SQ_58));
        ASSERT(pos.is_ok());
        ASSERT(pos2.is_ok());
        Tee<<pos<<std::endl;
        Tee<<pos2<<std::endl;
        auto pos3 = pos2.next(move(SQ_53,SQ_42));
        Tee<<pos3<<std::endl;
        auto pos4 = pos3.next(move(SQ_11,GOLD));
        Tee<<pos4<<std::endl;
    }
   {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, BPA, 
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);
        Tee<<pos<<std::endl;

        auto pos2 = pos.next(move(SQ_12,SQ_11,true));
        ASSERT(pos.is_ok());
        ASSERT(pos2.is_ok());
        Tee<<pos<<std::endl;
        Tee<<pos2<<std::endl;

    }
}
}

#endif