#ifndef __MOVEGEN_HPP__
#define __MOVEGEN_HPP__

#include "game.hpp"
#include "movelist.hpp"
#include "attack.hpp"
#include "movedrop.hpp"

namespace gen {

template<Color turn> inline void add_lance_move(movelist::MoveList &ml, const Square sq, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    Square to = sq + inc;
    if (attack::is_discover(sq,to,turn,pos)) { return; }
    for (; pos.square(to) == COLOR_EMPTY; to += inc) {
        
        const auto rank = sq_rank(to);
        if (turn == BLACK) {
            if (rank == RANK_1) {
                ml.add(move(sq,to,true));
            } else if (rank == RANK_2 || rank == RANK_3) {
                ml.add(move(sq,to,true));
                ml.add(move(sq,to,false));
            } else {
                ml.add(move(sq,to));
            }
            // if (rank > RANK_3) {
            //     ml.add(move(sq,to));
            // } else if (rank <= RANK_2) {
            //     ml.add(move(sq,to,true));
            // } else {
            //     ml.add(move(sq,to,true));
            //     ml.add(move(sq,to,false));
            // }
        } else {
            // if (rank < RANK_7) {
            //     ml.add(move(sq,to));
            // } else if (rank >= RANK_8) {
            //     ml.add(move(sq,to,true));
            // } else {
            //     ml.add(move(sq,to,true));
            //     ml.add(move(sq,to,false));
            // }
            if (rank == RANK_9) {
                ml.add(move(sq,to,true));
            } else if (rank == RANK_7 || rank == RANK_8) {
                ml.add(move(sq,to,true));
                ml.add(move(sq,to,false));
            } else {
                ml.add(move(sq,to));
            }
        }
    }
    if (attack::can_move(pos.square(to),move_flag)) {
        const auto rank = sq_rank(to);
        if (turn == BLACK) {
            // if (rank > RANK_3) {
            //     ml.add(move(sq,to));
            // } else if (rank <= RANK_2) {
            //     ml.add(move(sq,to,true));
            // } else if (rank == RANK_3) {
            //     ml.add(move(sq,to,true));
            //     ml.add(move(sq,to,false));
            // }
            if (rank == RANK_1) {
                ml.add(move(sq,to,true));
            } else if (rank == RANK_2 || rank == RANK_3) {
                ml.add(move(sq,to,true));
                ml.add(move(sq,to,false));
            } else {
                ml.add(move(sq,to));
            }
        } else {
            // if (rank < RANK_7) {
            //     ml.add(move(sq,to));
            // } else if (rank >= RANK_8) {
            //     ml.add(move(sq,to,true));
            // } else if (rank == RANK_7) {
            //     ml.add(move(sq,to,true));
            //     ml.add(move(sq,to,false));
            // }
            if (rank == RANK_9) {
                ml.add(move(sq,to,true));
            } else if (rank == RANK_7 || rank == RANK_8) {
                ml.add(move(sq,to,true));
                ml.add(move(sq,to,false));
            } else {
                ml.add(move(sq,to));
            }
        }
    }
}

template<Color turn> inline void add_knight_move(movelist::MoveList &ml, const Square sq, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    const auto to = sq + inc;
    if (attack::can_move(pos.square(to),move_flag)) {
        if (attack::is_discover(sq,to,turn,pos)) { return; }
        const auto rank = sq_rank(to);
        if (turn == BLACK) {
            if (rank > RANK_3) {
                ml.add(move(sq,to));
            } else if (rank <= RANK_2) {
                ml.add(move(sq,to,true));
            } else if (rank == RANK_3) {
                ml.add(move(sq,to,true));
                ml.add(move(sq,to,false));
            }
        } else {
            if (rank < RANK_7) {
                ml.add(move(sq,to));
            } else if (rank >= RANK_8) {
                ml.add(move(sq,to,true));
            } else if (rank == RANK_7) {
                ml.add(move(sq,to,true));
                ml.add(move(sq,to,false));
            }
        }
    }
}

template<Color turn> inline void add_silver_move(movelist::MoveList &ml, const Square sq, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    const auto to = sq + inc;
    if (attack::can_move(pos.square(to),move_flag)) {
        if (attack::is_discover(sq,to,turn,pos)) { return; }
        ml.add(move(sq,to));
        const auto prom_from = sq_is_prom<turn>(sq);
        const auto prom_to = sq_is_prom<turn>(to);
        if (prom_from || prom_to) {
            ml.add(move(sq,to,true));
        }
    }
}

inline void add_gold_move(movelist::MoveList &ml, const Square sq, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    const auto to = sq + inc;
    const auto turn = pos.turn();
    if (attack::can_move(pos.square(to),move_flag)) {
        if (attack::is_discover(sq,to,turn,pos)) { return; }
        ml.add(move(sq,to));
    }
}

inline void add_king_move(movelist::MoveList &ml, const Square sq, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    const auto to = sq + inc;
    if (attack::can_move(pos.square(to),move_flag)) {
        const auto opp = change_turn(pos.turn());
        if (attack::is_attacked(pos,to,opp)) { return; }
        ml.add(move(sq,to));
    }
}

template<Color turn> inline void add_slider_move(movelist::MoveList &ml, const Square sq, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    const auto prom_from = sq_is_prom<turn>(sq);
    Square to = sq + inc;
    if (attack::is_discover(sq,to,turn,pos)) { return; }
    for (; pos.square(to) == COLOR_EMPTY; to += inc) {
        const auto prom_to = sq_is_prom<turn>(to);
        if ((prom_from || prom_to)) {
            ml.add(move(sq,to,true));
        }
        ml.add(move(sq,to,false));
    }
    if (attack::can_move(pos.square(to),move_flag)) {
        const auto prom_to = sq_is_prom<turn>(to);
        if ((prom_from || prom_to)) {
            ml.add(move(sq,to,true));
        }
        ml.add(move(sq,to,false));
    }
}

inline void add_slider2_move(movelist::MoveList &ml, const Square sq, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    Square to = sq + inc;
    const auto turn = pos.turn();
    if (attack::is_discover(sq,to,turn,pos)) { return; }
    for (; pos.square(to) == COLOR_EMPTY; to += inc) {
        ml.add(move(sq,to));
    }
    if (attack::can_move(pos.square(to),move_flag)) {
        ml.add(move(sq,to));
    }
}

template<Color turn>void pos_moves_square(const game::Position &pos, movelist::MoveList &ml, const ColorPiece move_flag, const Square sq) {
    const auto cp = pos.square(sq);
    if (turn == BLACK) {
        if (false) {
        } else if (cp == COLOR_EMPTY) {
        } else if (cp == BLACK_PAWN) {
            const auto to = sq + INC_UP;
            if (!attack::can_move(pos.square(to),move_flag)) { return; }
            if (attack::is_discover(sq,to,turn,pos)) { return; }
            //const auto prom = sq_is_prom(to,turn);
            //ml.add(move(sq,to,prom));
            const auto rank = sq_rank(to);
            if (rank == RANK_1) {
                ml.add(move(sq,to,true));
            } else if (rank == RANK_2 || rank == RANK_3) {
                ml.add(move(sq,to,true));
                ml.add(move(sq,to,false));
            } else {
                ml.add(move(sq,to,false));
            }
        } else if (cp == BLACK_LANCE) {
            add_lance_move<turn>(ml,sq,INC_UP,move_flag,pos);
        } else if (cp == BLACK_KNIGHT) {
            add_knight_move<turn>(ml,sq,INC_KNIGHT_LEFTUP,move_flag,pos);
            add_knight_move<turn>(ml,sq,INC_KNIGHT_RIGHTUP,move_flag,pos);
        } else if (cp == BLACK_SILVER) {
            add_silver_move<turn>(ml,sq,INC_LEFTUP,move_flag,pos);
            add_silver_move<turn>(ml,sq,INC_UP,move_flag,pos);
            add_silver_move<turn>(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_silver_move<turn>(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_silver_move<turn>(ml,sq,INC_RIGHTDOWN,move_flag,pos);
        } else if (cp == BLACK_GOLD 
                || cp == BLACK_PPAWN 
                || cp == BLACK_PLANCE 
                || cp == BLACK_PKNIGHT 
                || cp == BLACK_PSILVER) {
            add_gold_move(ml,sq,INC_LEFTUP,move_flag,pos);
            add_gold_move(ml,sq,INC_UP,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_gold_move(ml,sq,INC_LEFT,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHT,move_flag,pos);
            add_gold_move(ml,sq,INC_DOWN,move_flag,pos);
        } else if (cp == BLACK_KING) {
            add_king_move(ml,sq,INC_LEFTUP,move_flag,pos);
            add_king_move(ml,sq,INC_UP,move_flag,pos);
            add_king_move(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_king_move(ml,sq,INC_LEFT,move_flag,pos);
            add_king_move(ml,sq,INC_RIGHT,move_flag,pos);
            add_king_move(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_king_move(ml,sq,INC_DOWN,move_flag,pos);
            add_king_move(ml,sq,INC_RIGHTDOWN,move_flag,pos);
        } else if (cp == BLACK_ROOK) {
            add_slider_move<turn>(ml,sq,INC_UP,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_LEFT,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_RIGHT,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_DOWN,move_flag,pos);
        } else if (cp == BLACK_BISHOP) {
            add_slider_move<turn>(ml,sq,INC_LEFTUP,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_RIGHTDOWN,move_flag,pos);
        } else if (cp == BLACK_PROOK) {
            add_slider2_move(ml,sq,INC_UP,move_flag,pos);
            add_slider2_move(ml,sq,INC_LEFT,move_flag,pos);
            add_slider2_move(ml,sq,INC_RIGHT,move_flag,pos);
            add_slider2_move(ml,sq,INC_DOWN,move_flag,pos);
            add_gold_move(ml,sq,INC_LEFTUP,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_gold_move(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHTDOWN,move_flag,pos);
        } else if (cp == BLACK_PBISHOP) {
            add_slider2_move(ml,sq,INC_LEFTUP,move_flag,pos);
            add_slider2_move(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_slider2_move(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_slider2_move(ml,sq,INC_RIGHTDOWN,move_flag,pos);
            add_gold_move(ml,sq,INC_UP,move_flag,pos);
            add_gold_move(ml,sq,INC_LEFT,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHT,move_flag,pos);
            add_gold_move(ml,sq,INC_DOWN,move_flag,pos);
        }
    } else {
        if (false) {
        } else if (cp == COLOR_EMPTY) {
        } else if (cp == WHITE_PAWN) {
            const auto to = sq + INC_DOWN;
            if (!attack::can_move(pos.square(to),move_flag)) { return; }
            if (attack::is_discover(sq,to,turn,pos)) { return; }
            //const auto prom = sq_is_prom(to,turn);
            //ml.add(move(sq,to,prom));
            const auto rank = sq_rank(to);
            if (rank == RANK_9) {
                ml.add(move(sq,to,true));
            } else if (rank == RANK_7 || rank == RANK_8) {
                ml.add(move(sq,to,true));
                ml.add(move(sq,to,false));
            } else {
                ml.add(move(sq,to,false));
            }
        } else if (cp == WHITE_LANCE) {
            add_lance_move<turn>(ml,sq,INC_DOWN,move_flag,pos);
        } else if (cp == WHITE_KNIGHT) {
            add_knight_move<turn>(ml,sq,INC_KNIGHT_LEFTDOWN,move_flag,pos);
            add_knight_move<turn>(ml,sq,INC_KNIGHT_RIGHTDOWN,move_flag,pos);
        } else if (cp == WHITE_SILVER) {
            add_silver_move<turn>(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_silver_move<turn>(ml,sq,INC_DOWN,move_flag,pos);
            add_silver_move<turn>(ml,sq,INC_RIGHTDOWN,move_flag,pos);
            add_silver_move<turn>(ml,sq,INC_LEFTUP,move_flag,pos);
            add_silver_move<turn>(ml,sq,INC_RIGHTUP,move_flag,pos);
        } else if (cp == WHITE_GOLD 
                || cp == WHITE_PPAWN 
                || cp == WHITE_PLANCE 
                || cp == WHITE_PKNIGHT 
                || cp == WHITE_PSILVER) {
            add_gold_move(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_gold_move(ml,sq,INC_DOWN,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHTDOWN,move_flag,pos);
            add_gold_move(ml,sq,INC_LEFT,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHT,move_flag,pos);
            add_gold_move(ml,sq,INC_UP,move_flag,pos);
        } else if (cp == WHITE_KING) {
            add_king_move(ml,sq,INC_LEFTUP,move_flag,pos);
            add_king_move(ml,sq,INC_UP,move_flag,pos);
            add_king_move(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_king_move(ml,sq,INC_LEFT,move_flag,pos);
            add_king_move(ml,sq,INC_RIGHT,move_flag,pos);
            add_king_move(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_king_move(ml,sq,INC_DOWN,move_flag,pos);
            add_king_move(ml,sq,INC_RIGHTDOWN,move_flag,pos);
        } else if (cp == WHITE_ROOK) {
            add_slider_move<turn>(ml,sq,INC_UP,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_LEFT,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_RIGHT,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_DOWN,move_flag,pos);
        } else if (cp == WHITE_BISHOP) {
            add_slider_move<turn>(ml,sq,INC_LEFTUP,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_slider_move<turn>(ml,sq,INC_RIGHTDOWN,move_flag,pos);
        } else if (cp == WHITE_PROOK) {
            add_slider2_move(ml,sq,INC_UP,move_flag,pos);
            add_slider2_move(ml,sq,INC_LEFT,move_flag,pos);
            add_slider2_move(ml,sq,INC_RIGHT,move_flag,pos);
            add_slider2_move(ml,sq,INC_DOWN,move_flag,pos);
            add_gold_move(ml,sq,INC_LEFTUP,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_gold_move(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHTDOWN,move_flag,pos);
        } else if (cp == WHITE_PBISHOP) {
            add_slider2_move(ml,sq,INC_LEFTUP,move_flag,pos);
            add_slider2_move(ml,sq,INC_RIGHTUP,move_flag,pos);
            add_slider2_move(ml,sq,INC_LEFTDOWN,move_flag,pos);
            add_slider2_move(ml,sq,INC_RIGHTDOWN,move_flag,pos);
            add_gold_move(ml,sq,INC_UP,move_flag,pos);
            add_gold_move(ml,sq,INC_LEFT,move_flag,pos);
            add_gold_move(ml,sq,INC_RIGHT,move_flag,pos);
            add_gold_move(ml,sq,INC_DOWN,move_flag,pos);
        }
    }
}
template<Color turn, bool has_pawn, bool has_lance, bool has_knight, int hand_num> 
    void gen_moves(game::Position &pos, movelist::MoveList &ml, const Piece pieces[], const ColorPiece move_flag) {
    for(auto *p = SQUARE_INDEX; *p != SQ_WALL; ++p) {
        const auto sq = *p;
        const auto dst = pos.square(sq);
        if (dst == COLOR_EMPTY) {
            if (has_pawn || has_lance || has_knight || hand_num > 0) {
                drop_moves_square<turn,has_pawn,has_lance,has_knight,hand_num>(pos,ml,pieces,sq);
            }
        } else {
            pos_moves_square<turn>(pos,ml,move_flag,sq);
        }
    }
}
template<Color turn> void gen_moves(game::Position &pos, movelist::MoveList &ml) {
    const auto move_flag = (turn == BLACK) ? ColorPiece((BLACK_FLAG | COLOR_WALL_FLAG)) : ColorPiece((WHITE_FLAG | COLOR_WALL_FLAG));
    const auto hand = pos.hand(turn);
    Piece pieces[4] = {};
    auto hand_num = 0;

#define ADD_HAND(param0,param1,param2) do {\
    switch(hand_num) {\
        case 0: gen_moves<turn,param0,param1,param2,0>(pos,ml,pieces,move_flag); break;\
        case 1: gen_moves<turn,param0,param1,param2,1>(pos,ml,pieces,move_flag); break;\
        case 2: gen_moves<turn,param0,param1,param2,2>(pos,ml,pieces,move_flag); break;\
        case 3: gen_moves<turn,param0,param1,param2,3>(pos,ml,pieces,move_flag); break;\
        case 4: gen_moves<turn,param0,param1,param2,4>(pos,ml,pieces,move_flag); break;\
        default: ASSERT(false); break;\
    }\
}while(0)

    if (has_piece(hand,SILVER)) {
        pieces[hand_num++] = SILVER;
    }
    if (has_piece(hand,GOLD)) {
        pieces[hand_num++] = GOLD;
    }
    if (has_piece(hand,BISHOP)) {
        pieces[hand_num++] = BISHOP;
    }
    if (has_piece(hand,ROOK)) {
        pieces[hand_num++] = ROOK;
    }
    if (has_piece(hand,PAWN)) {
        if (has_piece(hand,LANCE)) {
            if (has_piece(hand,KNIGHT)) {
                ADD_HAND(true,true,true);
            } else {
                ADD_HAND(true,true,false);
            }
        } else {
            if (has_piece(hand,KNIGHT)) {
                ADD_HAND(true,false,true);
            } else {
                ADD_HAND(true,false,false);
            }
        }
    } else {
        if (has_piece(hand,LANCE)) {
            if (has_piece(hand,KNIGHT)) {
                ADD_HAND(false,true,true);
            } else {
                ADD_HAND(false,true,false);
            }
        } else {
            if (has_piece(hand,KNIGHT)) {
                ADD_HAND(false,false,true);
            } else {
                ADD_HAND(false,false,false);
            }
        }
    }
#undef ADD_HAND
}

void gen_moves(game::Position &pos, movelist::MoveList &ml) {
    (pos.turn() == BLACK) ? gen_moves<BLACK>(pos,ml) : gen_moves<WHITE>(pos,ml);
}
void gen_check_moves_debug(game::Position &pos, movelist::MoveList &ml) {
    movelist::MoveList ml2;
    gen_moves(pos,ml2);
    REP(i,ml2.len()) {
        const auto m = ml2[i];
        auto pos2 = pos.next(m);
        if (attack::in_checked(pos2)) {
            ml.add(m);
        }
    }    
}
}
#endif