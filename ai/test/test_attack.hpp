#ifndef __TEST_ATTACK_HPP__
#define __TEST_ATTACK_HPP__

#include "../common.hpp"
#include "../util.hpp"
#include "../game.hpp"
#include "../movegen.hpp"
#include "../attack.hpp"

namespace test {
void test_attack() {
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, BRO, 
            CEM, CEM, CEM, WKN, WKI, WKN, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BGO, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, WPA, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);
        Tee<<pos<<std::endl;
        ASSERT(gen::is_mate_with_pawn_drop<BLACK>(SQ_53,pos));
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, BRO, 
            CEM, CEM, CEM, WSI, WKI, WKN, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BGO, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, WPA, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);
        Tee<<pos<<std::endl;
        ASSERT(!gen::is_mate_with_pawn_drop<BLACK>(SQ_53,pos));
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, BRO, 
            BRO, CEM, CEM, WSI, WKI, WKN, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BGO, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, WPA, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);
        Tee<<pos<<std::endl;
        ASSERT(gen::is_mate_with_pawn_drop<BLACK>(SQ_53,pos));
    }
}
}
#endif