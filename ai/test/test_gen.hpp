#ifndef __TEST_GEN_HPP__
#define __TEST_GEN_HPP__

#include "../common.hpp"
#include "../util.hpp"
#include "../game.hpp"
#include "../movegen.hpp"
#include "../moveevasion.hpp"
#include "../movecheck.hpp"
#include "../sfen.hpp"
#include "../perft.hpp"

namespace test {
uint32 test_gen2(const std::string sfen_str) {
    auto pos = sfen::sfen(sfen_str);
    movelist::MoveList ml;
    if (attack::in_checked(pos)) {
        gen::gen_evasion_moves(pos,ml);
    } else {
        gen::gen_moves(pos,ml);
    }
    return ml.len();
}
void test_gen() {
    for(uint64 i = 0;;i++) {
        //Tee<<i<<"\r";
        auto pos = sfen::hirate();
        //auto pos = sfen::sfen("nn1sks3/G3rP2s/pp3g1s1/1g7/PPpP2p1p/3B2PL1/N2L2K1P/L1P+bG4/2R5L w PN5p 140");
        while (true) {
            if (pos.ply() > 1000) {
                break;
            }
            Tee<<pos<<std::endl;
            movelist::MoveList ml;
            if (attack::in_checked(pos)) {
                gen::gen_evasion_moves(pos,ml);
            } else {
                gen::gen_moves(pos,ml);
            }
            if (ml.len() == 0) {
                break;
            }
            Tee<<search::perft(pos,1)<<std::endl;
            const auto mv = ml[my_rand(ml.len())];
            //Tee<<move_str(mv)<<std::endl;
            pos = pos.next(mv);
        }
    }
}
}
#endif