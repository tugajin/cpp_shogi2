#ifndef __MOVEDROP_HPP__
#define __MOVEDROP_HPP__

#include "game.hpp"
#include "movelist.hpp"
#include "attack.hpp"

namespace gen {

template<Color turn, bool has_pawn, bool has_lance, bool has_knight, int hand_num> void drop_moves_square(game::Position &pos, movelist::MoveList &ml, const Piece pieces[],const Square sq){
    const auto rank = sq_rank(sq);
    if (has_pawn) {
        if ((turn == BLACK && rank == RANK_1) || (turn == WHITE && rank == RANK_9)) {
        } else if (pos.exists_pawn(turn,sq_file(sq))){
        } else if (is_mate_with_pawn_drop<turn>(sq,pos)) {
        } else {
            ml.add(move(sq,PAWN));
        }
    }
    if (has_lance) {
        if ((turn == BLACK && rank == RANK_1) || (turn == WHITE && rank == RANK_9)) {
        } else {
            ml.add(move(sq,LANCE));
        }
    }
    if (has_knight) {
        if ((turn == BLACK && rank < RANK_3) || (turn == WHITE && rank > RANK_7)) {
        } else {
            ml.add(move(sq,KNIGHT));
        }
    }
    switch(hand_num) {
        case 4: 
            ml.add(move(sq,pieces[3]));
             /* Falls through. */
        case 3: 
            ml.add(move(sq,pieces[2]));
             /* Falls through. */
        case 2: 
            ml.add(move(sq,pieces[1]));
             /* Falls through. */
        case 1: 
            ml.add(move(sq,pieces[0]));
            /* Falls through. */
        case 0:break;
        default:
            ASSERT2(false,{ Tee<<hand_num<<std::endl; });
            break;
    }
}
}
#endif