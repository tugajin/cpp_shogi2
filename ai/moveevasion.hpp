#ifndef __MOVEEVASION_HPP__
#define __MOVEEVASION_HPP__

#include "game.hpp"
#include "movelist.hpp"
#include "attack.hpp"
#include "movedrop.hpp"

namespace gen {

namespace evasion {
    enum EvasionDirType {
        EVASION_SKIP_UPDOWN,
        EVASION_SKIP_LEFTRIGHT,
        EVASION_SKIP_LEFTUPRIGHTDOWN,
        EVASION_SKIP_RIGHTUPLEFTDOWN,
        EVASION_ALL,
    };
}

inline void add_evasion_king_move(movelist::MoveList &ml, const Square sq, const Square inc, const ColorPiece move_flag, const game::Position &pos, const Color opp) {
    const auto to = sq + inc;
    if (attack::can_move(pos.square(to),move_flag) && !attack::is_attacked(pos,to,opp)) {
        ml.add(move(sq,to));
    }
}
template<Color turn> inline void add_evasion_move_to_dir(movelist::MoveList &ml, const Square to, const bool to_prom, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    Square from;
    for (from = to - inc; pos.square(from) == COLOR_EMPTY; from -= inc) {;}
    const auto from_cp = pos.square(from);
    const auto to_cp = pos.square(to);
    const auto delta = to - from;
    if (piece_color(from_cp) == turn 
    && attack::can_move(to_cp,move_flag) 
    && attack::pseudo_attack(from_cp,delta)
    && !attack::is_discover(from,to,turn,pos)) {
        const auto from_prom = sq_is_prom<turn>(from);
        switch(from_cp) {
            case BLACK_GOLD:
            case BLACK_PPAWN:
            case BLACK_PLANCE:
            case BLACK_PKNIGHT:
            case BLACK_PSILVER:
            case BLACK_PBISHOP:
            case BLACK_PROOK:
            case WHITE_GOLD:
            case WHITE_PPAWN:
            case WHITE_PLANCE:
            case WHITE_PKNIGHT:
            case WHITE_PSILVER:
            case WHITE_PBISHOP:
            case WHITE_PROOK: {
                ml.add(move(from,to));
                break;
            }
            case BLACK_PAWN: {
                //ml.add(move(from,to,to_prom));
                const auto rank = sq_rank(to);
                if (rank == RANK_1) {
                    ml.add(move(from,to,true));
                } else if (rank == RANK_2 || rank == RANK_3) {
                    ml.add(move(from,to,true));
                    ml.add(move(from,to,false));
                } else {
                    ml.add(move(from,to,false));
                }
                break;
            }
            case WHITE_PAWN: {
                //ml.add(move(from,to,to_prom));
                const auto rank = sq_rank(to);
                if (rank == RANK_9) {
                    ml.add(move(from,to,true));
                } else if (rank == RANK_7 || rank == RANK_8) {
                    ml.add(move(from,to,true));
                    ml.add(move(from,to,false));
                } else {
                    ml.add(move(from,to,false));
                }
                break;
            }
            case BLACK_LANCE: {
                const auto rank = sq_rank(to);
                // if (rank > RANK_3) {
                //     ml.add(move(from,to));
                // } else if (rank <= RANK_2) {
                //     ml.add(move(from,to,true));
                // } else {
                //     ml.add(move(from,to,true));
                //     ml.add(move(from,to));
                // }
                if (rank == RANK_1) {
                    ml.add(move(from,to,true));
                } else if (rank == RANK_2 || rank == RANK_3) {
                    ml.add(move(from,to,true));
                    ml.add(move(from,to,false));
                } else {
                    ml.add(move(from,to));
                }
                break;
            }
            case WHITE_LANCE: {
                const auto rank = sq_rank(to);
                // if (rank < RANK_7) {
                //     ml.add(move(from,to));
                // } else if (rank >= RANK_8) {
                //     ml.add(move(from,to,true));
                // } else {
                //     ml.add(move(from,to,true));
                //     ml.add(move(from,to));
                // }
                if (rank == RANK_9) {
                    ml.add(move(from,to,true));
                } else if (rank == RANK_7 || rank == RANK_8) {
                    ml.add(move(from,to,true));
                    ml.add(move(from,to,false));
                } else {
                    ml.add(move(from,to));
                }
                break;
            }
            case BLACK_SILVER: 
            case WHITE_SILVER: 
            case BLACK_ROOK:
            case BLACK_BISHOP: 
            case WHITE_ROOK:
            case WHITE_BISHOP: {
                if ((from_prom || to_prom)) {
                    ml.add(move(from,to,(from_prom || to_prom)));
                }
                ml.add(move(from,to));
                break;
            }
            case BLACK_KING:
            case WHITE_KING:
                break;
            default:
                ASSERT(false);
            break;
        }
    }
}
template<Color turn> inline void add_evasion_move_to_dir_knight(movelist::MoveList &ml, const Square to, const Square inc, const game::Position &pos) {
    Square from = to - inc;
    if (pos.square(from) == BLACK_KNIGHT 
    && turn == BLACK
    && !attack::is_discover(from,to,turn,pos)) {
        const auto rank = sq_rank(to);
        if (rank > RANK_3) {
            ml.add(move(from,to));
        } else if (rank <= RANK_2) {
            ml.add(move(from,to,true));
        } else {
            ml.add(move(from,to,true));
            ml.add(move(from,to));
        }
    } else if (pos.square(from) == WHITE_KNIGHT 
            && turn == WHITE
            && !attack::is_discover(from,to,turn,pos)) {
        const auto rank = sq_rank(to);
        if (rank < RANK_7) {
            ml.add(move(from,to));
        } else if (rank >= RANK_8) {
            ml.add(move(from,to,true));
        } else {
            ml.add(move(from,to,true));
            ml.add(move(from,to));
        }
    }
}
template<Color turn,evasion::EvasionDirType type>inline void add_evasion_move_to(movelist::MoveList &ml, const Square to, const bool to_prom, const ColorPiece move_flag, const game::Position &pos) {
    if (type != evasion::EVASION_SKIP_UPDOWN) {
        add_evasion_move_to_dir<turn>(ml,to,to_prom,INC_UP,move_flag,pos);
        add_evasion_move_to_dir<turn>(ml,to,to_prom,INC_DOWN,move_flag,pos);
    }
    if (type != evasion::EVASION_SKIP_LEFTUPRIGHTDOWN) {
        add_evasion_move_to_dir<turn>(ml,to,to_prom,INC_LEFTUP,move_flag,pos);
        add_evasion_move_to_dir<turn>(ml,to,to_prom,INC_RIGHTDOWN,move_flag,pos);
    }
    if (type != evasion::EVASION_SKIP_LEFTRIGHT) {
        add_evasion_move_to_dir<turn>(ml,to,to_prom,INC_LEFT,move_flag,pos);
        add_evasion_move_to_dir<turn>(ml,to,to_prom,INC_RIGHT,move_flag,pos);
    }
    if (type != evasion::EVASION_SKIP_RIGHTUPLEFTDOWN) {
        add_evasion_move_to_dir<turn>(ml,to,to_prom,INC_LEFTDOWN,move_flag,pos);
        add_evasion_move_to_dir<turn>(ml,to,to_prom,INC_RIGHTUP,move_flag,pos);
    }
    if (turn == BLACK) {
        add_evasion_move_to_dir_knight<turn>(ml,to, INC_KNIGHT_LEFTUP, pos);
        add_evasion_move_to_dir_knight<turn>(ml,to, INC_KNIGHT_RIGHTUP, pos);
    } else {
        add_evasion_move_to_dir_knight<turn>(ml,to, INC_KNIGHT_LEFTDOWN, pos);
        add_evasion_move_to_dir_knight<turn>(ml,to, INC_KNIGHT_RIGHTDOWN, pos);
    }

}
template<Color turn, bool has_pawn, bool has_lance, bool has_knight, int hand_num, evasion::EvasionDirType type> 
    inline void add_aigoma_moves(game::Position &pos, movelist::MoveList &ml, const Square sq, const Square inc, const ColorPiece move_flag, const Piece pieces[]) {
    //合い駒
    for (auto to = sq + inc; pos.square(to) == COLOR_EMPTY; to += inc) {
        const auto to_prom = sq_is_prom<turn>(to);
        add_evasion_move_to<turn,type>(ml,to,to_prom,move_flag,pos);
        if (has_pawn || has_knight || has_lance || hand_num > 0) {
            drop_moves_square<turn,has_pawn,has_lance,has_knight,hand_num>(pos,ml,pieces,to);
        }
    }
}
template<Color turn, bool has_pawn, bool has_lance, bool has_knight, int hand_num> void gen_evasion_moves(game::Position &pos, movelist::MoveList &ml,  const Piece pieces[]) {
    const auto me = turn;
    const auto opp = change_turn(me);
    const auto king_sq = pos.king_sq(me);
    const auto move_flag = (me == BLACK) ? ColorPiece(BLACK_FLAG | COLOR_WALL_FLAG) : ColorPiece(WHITE_FLAG | COLOR_WALL_FLAG);
    attack::Checker checker(pos);
    ASSERT2(checker.checker_num !=0,{
        Tee<<pos<<std::endl;
    });
    //王が逃げる手
    if (checker.checker_inc[0] != INC_DOWN && checker.checker_inc[1] != INC_DOWN) {
        add_evasion_king_move(ml,king_sq,INC_DOWN,move_flag,pos,opp);
    }
    if (checker.checker_inc[0] != INC_RIGHTDOWN && checker.checker_inc[1] != INC_RIGHTDOWN) {
        add_evasion_king_move(ml,king_sq,INC_RIGHTDOWN,move_flag,pos,opp);
    }
    if (checker.checker_inc[0] != INC_LEFTDOWN && checker.checker_inc[1] != INC_LEFTDOWN) {
        add_evasion_king_move(ml,king_sq,INC_LEFTDOWN,move_flag,pos,opp);
    }
    if (checker.checker_inc[0] != INC_RIGHT && checker.checker_inc[1] != INC_RIGHT) {
        add_evasion_king_move(ml,king_sq,INC_RIGHT,move_flag,pos,opp);
    }
    if (checker.checker_inc[0] != INC_LEFT && checker.checker_inc[1] != INC_LEFT) {
        add_evasion_king_move(ml,king_sq,INC_LEFT,move_flag,pos,opp);
    }
    if (checker.checker_inc[0] != INC_RIGHTUP && checker.checker_inc[1] != INC_RIGHTUP) {
        add_evasion_king_move(ml,king_sq,INC_RIGHTUP,move_flag,pos,opp);
    }
    if (checker.checker_inc[0] != INC_LEFTUP && checker.checker_inc[1] != INC_LEFTUP) {
        add_evasion_king_move(ml,king_sq,INC_LEFTUP,move_flag,pos,opp);
    }
    if (checker.checker_inc[0] != INC_UP && checker.checker_inc[1] != INC_UP) {
        add_evasion_king_move(ml,king_sq,INC_UP,move_flag,pos,opp);
    }
    if (checker.checker_num == 2) {
        return;
    }
    //王手駒を取る
    auto to = checker.checker_from[0];
    auto to_prom = sq_is_prom<turn>(to);
    add_evasion_move_to<turn,evasion::EVASION_ALL>(ml,to,to_prom,move_flag,pos);
    //合い駒
    switch (checker.checker_inc[0]) {
        case INC_UP:
        case INC_DOWN:
            add_aigoma_moves<turn,has_pawn,has_lance,has_knight,hand_num,evasion::EVASION_SKIP_UPDOWN>(pos,ml,to,checker.checker_inc[0],move_flag,pieces);
            break;
        case INC_LEFTUP:
        case INC_RIGHTDOWN:
            add_aigoma_moves<turn,has_pawn,has_lance,has_knight,hand_num,evasion::EVASION_SKIP_LEFTUPRIGHTDOWN>(pos,ml,to,checker.checker_inc[0],move_flag,pieces);
            break;
        case INC_RIGHTUP:
        case INC_LEFTDOWN:
            add_aigoma_moves<turn,has_pawn,has_lance,has_knight,hand_num,evasion::EVASION_SKIP_RIGHTUPLEFTDOWN>(pos,ml,to,checker.checker_inc[0],move_flag,pieces);
            break;
        case INC_LEFT:
        case INC_RIGHT:
            add_aigoma_moves<turn,has_pawn,has_lance,has_knight,hand_num,evasion::EVASION_SKIP_LEFTRIGHT>(pos,ml,to,checker.checker_inc[0],move_flag,pieces);
            break;
        case INC_NONE:
            break;
        default:
            ASSERT(false);
        break;
    }

}

template<Color turn> void gen_evasion_moves(game::Position &pos, movelist::MoveList &ml) {

    const auto hand = pos.hand(turn);
    Piece pieces[4] = {};
    auto hand_num = 0;

#define ADD_HAND(param0,param1,param2) do {\
    switch(hand_num) {\
        case 0: gen_evasion_moves<turn,param0,param1,param2,0>(pos,ml,pieces); break;\
        case 1: gen_evasion_moves<turn,param0,param1,param2,1>(pos,ml,pieces); break;\
        case 2: gen_evasion_moves<turn,param0,param1,param2,2>(pos,ml,pieces); break;\
        case 3: gen_evasion_moves<turn,param0,param1,param2,3>(pos,ml,pieces); break;\
        case 4: gen_evasion_moves<turn,param0,param1,param2,4>(pos,ml,pieces); break;\
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
void gen_evasion_moves(game::Position &pos, movelist::MoveList &ml) {
    (pos.turn() == BLACK) ? gen_evasion_moves<BLACK>(pos,ml) : gen_evasion_moves<WHITE>(pos,ml);
}
}
#endif