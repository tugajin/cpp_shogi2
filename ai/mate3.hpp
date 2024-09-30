#ifndef __MATE3_HPP__
#define __MATE3_HPP__

#include "game.hpp"
#include "movelist.hpp"
#include "attack.hpp"
#include "movecheck.hpp"
#include "moveevasion.hpp"

#define DEBUG_MATE 0

namespace mate3 {
bool is_neighbor(const Square sq0, const Square sq1) {
    const Square dir[] = {INC_DOWN, INC_UP, INC_LEFT, INC_RIGHT, INC_LEFTUP, INC_RIGHTUP, INC_LEFTDOWN, INC_RIGHTDOWN, INC_KNIGHT_LEFTDOWN, INC_KNIGHT_LEFTUP, INC_KNIGHT_RIGHTDOWN, INC_KNIGHT_RIGHTUP};
    REP(i, 12) {
        if (sq0 + dir[i] == sq1) {
            return true;
        }
    }
    return false;
}
void mate1_debug(game::Position &pos, movelist::MoveList &ml) {
    movelist::MoveList ml2;
    gen::gen_check_moves(pos,ml2);
    if (ml2.len() == 0) {
        return ;
    }
    const auto opp = change_turn(pos.turn());
    const auto king_sq = pos.king_sq(opp);

    for (auto i = 0; i < ml2.len(); i++) {
        const auto to = move_to(ml2[i]);
        if (!is_neighbor(to,king_sq)) {
            continue;
        }
        if (!move_is_drop(ml2[i])) {
            auto cp = pos.square(move_from(ml2[i]));
            if (move_is_prom(ml2[i])) {
                cp = prom(cp);
            }
            const auto delta = king_sq - to;
            if (!attack::pseudo_attack(cp,delta)) {
                continue;;
            }
        }
        auto pos2 = pos.next(ml2[i]);
        movelist::MoveList ml3;
        gen::gen_evasion_moves(pos2,ml3);
        if (ml3.len() == 0) {
            ml.add(ml2[i]);
        }
    }
}

}
#endif