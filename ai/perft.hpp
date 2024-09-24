#ifndef __PERFT_HPP__
#define __PERFT_HPP__

#include <climits>
#include "game.hpp"
#include "common.hpp"
//#include "movelegal.hpp"
#include "movegen.hpp"
#include "movecheck.hpp"
#include "mate1.hpp"
#include "mate3.hpp"

namespace search {


template<Color turn> uint64 perft(game::Position &pos, const int depth) {

    ASSERT2(pos.is_ok(),{
        Tee<<"perft error\n";
        Tee<<pos<<std::endl;
    })
    if (depth < 0) {
        movelist::MoveList ml;
        if (attack::in_checked(pos)) {
            gen::gen_evasion_moves<turn>(pos,ml);
        } else {
            gen::gen_moves<turn>(pos,ml);
        }
        //std::cout<<sfen::out_sfen(pos)<<":"<<ml.len()<<std::endl;
        return 1;
    }
    movelist::MoveList ml;
    if (attack::in_checked(pos)) {
        gen::gen_evasion_moves<turn>(pos,ml);
    } else {
        gen::gen_moves<turn>(pos,ml);
        movelist::MoveList ml2;
        movelist::MoveList ml3;
        gen::gen_check_moves(pos,ml2);
        gen::gen_check_moves_debug(pos,ml3);
        if (ml2.len() != ml3.len()) {
            Tee<<pos<<std::endl<<std::endl;
            Tee<<"check\n";
            Tee<<ml2<<std::endl;
            Tee<<"check debug\n";
            Tee<<ml3<<std::endl;
            ASSERT(false);
        }
        const auto mv = mate1::mate1<turn>(pos);
        movelist::MoveList ml4;
        mate3::mate1_debug(pos,ml4);
        if (mv == MOVE_NONE && ml4.len() == 0) {

        } else if (mv == MOVE_NONE && ml4.len() != 0) {
            Tee<<pos<<std::endl;
            Tee<<"mate1 error1\n";
            Tee<<move_str(mv)<<std::endl;
            Tee<<ml4<<std::endl;
            ASSERT(false);
        } else if (!ml4.contain(mv)) {
            Tee<<pos<<std::endl;
            Tee<<"mate1 error2\n";
            Tee<<move_str(mv)<<std::endl;
            Tee<<ml4<<std::endl;
            ASSERT(false);
        }
    }
    //std::cout<<sfen::out_sfen(pos)<<":"<<ml.len()<<std::endl;
    //Tee<<ml<<std::endl;
    const auto len = ml.len();
    uint64 num = 0ull;
    REP(i,len) {
        const auto mv = ml[i];
        auto next_pos = pos.next(mv);
        num += perft<change_turn(turn)>(next_pos,depth-1);
    }
    return num;
}
uint64 perft(game::Position &pos, const int depth) {
    return pos.turn() == BLACK ? perft<BLACK>(pos,depth) : perft<WHITE>(pos,depth);
}
}
#endif