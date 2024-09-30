#ifndef __MATE1_HPP__
#define __MATE1_HPP__

#include "game.hpp"
#include "movelist.hpp"
#include "attack.hpp"

#define DEBUG_MATE 0

namespace mate1 {

template<Color turn, Square king_nei_inc, Square inc>
    Move mate1_to_pos_knight(game::Position &pos,const Square to, const Square king_sq) {
        ASSERT(to != king_sq);
        ASSERT2(gen::is_knight_inc(inc) || inc == INC_NONE,{
            Tee<<"mate1_to_pos_knight error:"<<inc<<std::endl;
        });
        if (inc == INC_NONE) {
            constexpr auto next_inc = attack::dir10<turn,king_nei_inc>();
            if (next_inc == INC_NONE) {
                return MOVE_NONE;
            }
            const auto new_to = king_sq - next_inc;
            return mate1_to_drop<turn,ROOK,next_inc>(pos,new_to,king_sq);
        }
        if (gen::is_knight_inc(king_nei_inc)) { //不成の王手
            if (turn == BLACK && sq_rank(to) > RANK_7) {
                goto next_phase;
            } else if (turn == WHITE && sq_rank(to) < RANK_3) {
                goto next_phase;
            }
        } else {//成の王手
            if (!sq_is_prom<turn>(to)) {
                goto next_phase;
            }
        }
        {
            Square from = to - inc;
            const auto from_cp = pos.square(from);
            if ((turn == BLACK && from_cp == BLACK_KNIGHT) || (turn == WHITE && from_cp == WHITE_KNIGHT)) {
                if (attack::is_discover(from,to,turn,pos)) {
                    goto next_phase;
                }
                const auto delta2 = king_sq - to;
                const auto org_from = pos.square(from);
                // 玉の八近傍なので成での王手
                if (!gen::is_knight_inc(king_nei_inc)) {
                    const auto from_cp2 = prom(from_cp);
                    if (!attack::pseudo_attack(from_cp2,delta2)) {
                        goto next_phase;
                    }
                    pos.set_square(from,COLOR_EMPTY);
                    if (gen::is_mate_quick<turn,false>(from,to,from_cp2,pos)) {
                        pos.set_square(from,org_from);
                        return move(from,to,true);
                    } 
                    pos.set_square(from,org_from);
                }
                else {
                    /*if (!attack::pseudo_attack(from_cp,delta2)) {
                        goto next_phase;
                    }*/
                    ASSERT2(attack::pseudo_attack(from_cp,delta2),{
                        Tee<<pos<<std::endl;
                        Tee<<from<<std::endl;
                        Tee<<to<<std::endl;
                        Tee<<delta2<<std::endl;
                    })
                    pos.set_square(from,COLOR_EMPTY);
                    if (gen::is_mate_quick<turn,false>(from,to,from_cp,pos)) {
                        pos.set_square(from,org_from);
                        return move(from,to);
                    }
                    pos.set_square(from,org_from);
                } 
            }
        }
        next_phase:
        {
            constexpr auto next_inc = attack::dir10<turn,inc>();
            ASSERT(gen::is_knight_inc(next_inc) || next_inc == INC_NONE);
            return mate1_to_pos_knight<turn,king_nei_inc,next_inc>(pos,to,king_sq);
        }
}
template<Color turn, Square king_nei_inc, Square inc>
    Move mate1_to_pos(game::Position &pos,const Square to, const Square king_sq, const ColorPiece move_flag) {

        //戻ってしまうので無し
        if (king_nei_inc == invert_inc(inc)) {
            goto next_phase;
        }
        ASSERT(to != king_sq);
        if (!attack::can_move(pos.square(to),move_flag)) {
            constexpr auto next_inc = attack::dir10<turn,king_nei_inc>();
            return mate1_to<turn,next_inc>(pos,king_sq);
        }
        if (gen::is_knight_inc(king_nei_inc)) {
            constexpr auto new_inc = gen::is_knight_inc(inc) ? inc :
                                     turn == BLACK ? INC_KNIGHT_LEFTUP : INC_KNIGHT_LEFTDOWN;
            return mate1_to_pos_knight<turn,king_nei_inc,new_inc>(pos,to,king_sq);
        }
        if (gen::is_knight_inc(inc)) {
            return mate1_to_pos_knight<turn,king_nei_inc,inc>(pos,to,king_sq);
        }
        {
            Square from;
            for (from = to - inc; pos.square(from) == COLOR_EMPTY; from -= inc) {;}
            const auto from_cp = pos.square(from);
            if (!color_is_eq(turn,from_cp)) {
                goto next_phase;
            }
            switch(from_cp) {
                case BLACK_PAWN:
                case WHITE_PAWN: {
                    const auto delta = to - from;
                    if (!attack::pseudo_attack(from_cp,delta)) {   
                        goto next_phase;
                    }
                    if (attack::is_discover(from,to,turn,pos)) {
                        goto next_phase;
                    }

                    const auto delta2 = king_sq - to;
                    const auto org_from = pos.square(from);

                    if (sq_is_prom<turn>(to)) {
                        const auto from_cp2 = prom(from_cp);
                        if (!attack::pseudo_attack(from_cp2,delta2)) {
                            goto next_phase;
                        }
                        pos.set_square(from,COLOR_EMPTY);
                        if (gen::is_mate_quick<turn,false>(from,to,from_cp2,pos)) {
                            pos.set_square(from,org_from);
                            return move(from,to,true);
                        }
                        pos.set_square(from,org_from);
                    } else {
                        if (!attack::pseudo_attack(from_cp,delta2)) {
                            goto next_phase;
                        }
                        pos.set_square(from,COLOR_EMPTY);
                        if (gen::is_mate_quick<turn,false>(from,to,from_cp,pos)) {
                            pos.set_square(from,org_from);
                            return move(from,to);
                        }
                        pos.set_square(from,org_from);
                    } 
                    pos.set_square(from,org_from);
                    break;
                }
                case BLACK_LANCE:
                case WHITE_LANCE:
                case BLACK_KNIGHT:
                case WHITE_KNIGHT: {
                    const auto delta = to - from;
                    if (!attack::pseudo_attack(from_cp,delta)) {   
                        goto next_phase;
                    }
                    if (attack::is_discover(from,to,turn,pos)) {
                        goto next_phase;
                    }

                    const auto delta2 = king_sq - to;
                    const auto org_from = pos.square(from);

                    if (sq_is_prom<turn>(to)) {
                        const auto from_cp2 = prom(from_cp);
                        if (attack::pseudo_attack(from_cp2,delta2)) {
                            pos.set_square(from,COLOR_EMPTY);
                            if (gen::is_mate_quick<turn,false>(from,to,from_cp2,pos)) {
                                pos.set_square(from,org_from);
                                return move(from,to,true);
                            }
                            pos.set_square(from,org_from);
                        }
                    } 
                    if (!attack::pseudo_attack(from_cp,delta2)) {
                        goto next_phase;
                    }
                    pos.set_square(from,COLOR_EMPTY);
                    if (gen::is_mate_quick<turn,false>(from,to,from_cp,pos)) {
                        pos.set_square(from,org_from);
                        return move(from,to);
                    }
                    pos.set_square(from,org_from);
                    break;
                }
                case BLACK_SILVER:
                case WHITE_SILVER: {
                    const auto delta = to - from;
                    if (!attack::pseudo_attack(from_cp,delta)) {   
                        goto next_phase;
                    }
                    if (attack::is_discover(from,to,turn,pos)) {
                        goto next_phase;
                    }

                    const auto delta2 = king_sq - to;
                    const auto org_from = pos.square(from);

                    if (sq_is_prom<turn>(from) || sq_is_prom<turn>(to)) {
                        const auto from_cp2 = prom(from_cp);
                        if (attack::pseudo_attack(from_cp2,delta2)) {
                            pos.set_square(from,COLOR_EMPTY);
                            if (gen::is_mate_quick<turn,false>(from,to,from_cp2,pos)) {
                                pos.set_square(from,org_from);
                                return move(from,to,true);
                            }
                            pos.set_square(from,org_from);
                        }
                    } 
                    if (!attack::pseudo_attack(from_cp,delta2)) {
                        goto next_phase;
                    }
                    pos.set_square(from,COLOR_EMPTY);
                    if (gen::is_mate_quick<turn,false>(from,to,from_cp,pos)) {
                        pos.set_square(from,org_from);
                        return move(from,to);
                    }
                    pos.set_square(from,org_from);
                    break;
                }
                case BLACK_ROOK:
                case WHITE_ROOK: 
                case BLACK_BISHOP:
                case WHITE_BISHOP: {
                    const auto delta = to - from;
                    if (!attack::pseudo_attack(from_cp,delta)) {   
                        goto next_phase;
                    }
                    if (attack::is_discover(from,to,turn,pos)) {
                        goto next_phase;
                    }

                    const auto delta2 = king_sq - to;
                    const auto org_from = pos.square(from);

                    if (sq_is_prom<turn>(from) || sq_is_prom<turn>(to)) {
                        const auto from_cp2 = prom(from_cp);
                        if (!attack::pseudo_attack(from_cp2,delta2)) {
                            goto next_phase;
                        }
                        pos.set_square(from,COLOR_EMPTY);
                        if (gen::is_mate_quick<turn,false>(from,to,from_cp2,pos)) {
                            pos.set_square(from,org_from);
                            return move(from,to,true);
                        }
                        pos.set_square(from,org_from);
                    } else {
                        if (!attack::pseudo_attack(from_cp,delta2)) {
                            goto next_phase;
                        }
                        pos.set_square(from,COLOR_EMPTY);
                        if (gen::is_mate_quick<turn,false>(from,to,from_cp,pos)) {
                            pos.set_square(from,org_from);
                            return move(from,to);
                        }
                        pos.set_square(from,org_from);
                    } 
                    break;
                }
                case BLACK_GOLD:
                case WHITE_GOLD: 
                case BLACK_PPAWN:
                case WHITE_PPAWN:
                case BLACK_PLANCE:
                case WHITE_PLANCE:
                case BLACK_PKNIGHT:
                case WHITE_PKNIGHT:
                case BLACK_PSILVER:
                case WHITE_PSILVER: 
                case BLACK_PROOK:
                case WHITE_PROOK:
                case BLACK_PBISHOP:
                case WHITE_PBISHOP: {
                    const auto delta = to - from;
                    if (!attack::pseudo_attack(from_cp,delta)) {   
                        goto next_phase;
                    }
                    const auto delta2 = king_sq - to;
                    if (!attack::pseudo_attack(from_cp,delta2)) {
                        goto next_phase;
                    }
                    if (attack::is_discover(from,to,turn,pos)) {
                        goto next_phase;
                    }
                    const auto org_from = pos.square(from);
                    pos.set_square(from,COLOR_EMPTY);
                    if (gen::is_mate_quick<turn,false>(from,to,from_cp,pos)) {
                        pos.set_square(from,org_from);
                        return move(from,to);
                    }
                    pos.set_square(from,org_from);
                    break;
                }
                default:
                break;
            }
        }
        next_phase:
        constexpr auto next_inc = attack::dir10<turn,inc>();
        return mate1_to_pos<turn,king_nei_inc,next_inc>(pos,to,king_sq,move_flag);
}

template<Color turn, Piece pc, Square inc>
    Move mate1_to_drop(game::Position &pos,const Square to, const Square king_sq) {
          
        if (pc == EMPTY || pos.square(to) != COLOR_EMPTY) {
            const auto new_to = king_sq - inc;
            const auto move_flag = (turn == BLACK) ? ColorPiece(BLACK_FLAG | COLOR_WALL_FLAG) : ColorPiece(WHITE_FLAG | COLOR_WALL_FLAG);
            return mate1_to_pos<turn,inc,INC_UP>(pos,new_to,king_sq,move_flag);
        }

        const auto hand = pos.hand(turn);
        if (!has_piece(hand,pc)) {
            goto next_phase;
        }

        switch(pc) {
            case ROOK: {
                if (inc != INC_LEFT 
                && inc != INC_RIGHT 
                && inc != INC_UP 
                && inc != INC_DOWN) {
                    goto next_phase;
                }
                break;
            }
            case BISHOP: {
                if (inc != INC_LEFTUP 
                && inc != INC_RIGHTUP 
                && inc != INC_LEFTDOWN 
                && inc != INC_RIGHTDOWN) {
                    goto next_phase;
                }
                break;
            }
            case GOLD: {
                if (turn == BLACK) {
                    if (inc != INC_LEFT 
                    && inc != INC_RIGHT 
                    && inc != INC_UP 
                    && inc != INC_DOWN
                    && inc != INC_LEFTUP
                    && inc != INC_RIGHTUP) {
                        goto next_phase;
                    }
                    if (inc == INC_DOWN) {
                        if (has_piece(hand,ROOK)) {
                            goto next_phase;
                        }
                    }
                } else {
                    if (inc != INC_LEFT 
                    && inc != INC_RIGHT 
                    && inc != INC_UP 
                    && inc != INC_DOWN
                    && inc != INC_LEFTDOWN
                    && inc != INC_RIGHTDOWN) {
                        goto next_phase;
                    }
                    if (inc == INC_UP) {
                        if (has_piece(hand,ROOK)) {
                            goto next_phase;
                        }
                    }
                }

                if (gen::is_knight_inc(inc)) {
                    goto next_phase;
                }
                break;
            }
            case SILVER: {
                if (inc == INC_LEFT || inc == INC_RIGHT) {
                    goto next_phase;
                }
                if (has_piece(hand,GOLD) && has_piece(hand,BISHOP)) {
                    goto next_phase;
                }
                if (turn == BLACK) {
                    if (inc == INC_DOWN) {
                        goto next_phase;
                    }
                    if (inc == INC_LEFTDOWN 
                    || inc == INC_RIGHTDOWN) {
                        if (has_piece(hand,BISHOP)) {
                            goto next_phase;
                        }
                    }
                } else {
                    if (inc == INC_UP) {
                        goto next_phase;
                    }
                    if (inc == INC_LEFTUP 
                    || inc == INC_RIGHTUP) {
                        if (has_piece(hand,BISHOP)) {
                            goto next_phase;
                        }
                    }
                }

                if (gen::is_knight_inc(inc)) {
                    goto next_phase;
                }
                break;
            }
            case KNIGHT: {
                if (turn == BLACK) {
                    if (inc != INC_KNIGHT_LEFTUP && inc != INC_KNIGHT_RIGHTUP) {
                        goto next_phase;
                    }
                } else {
                    if (inc != INC_KNIGHT_LEFTDOWN && inc != INC_KNIGHT_RIGHTDOWN) {
                        goto next_phase;
                    }
                }
                break;
            }
            case LANCE: {
                if (turn == BLACK) {
                    if (inc != INC_UP) {
                        goto next_phase;
                    }
                } else {
                    if (inc != INC_DOWN) {
                        goto next_phase;
                    }
                }
                if (has_piece(hand,ROOK)) {
                    goto next_phase;
                }
                break;
            }
            default:
            ASSERT(false);
            break;
        }
        {
            const auto to_cp = color_piece(pc,turn);
            if (gen::is_mate_quick<turn,true>(SQ_END,to,to_cp,pos)) {
                return move(to,pc);
            }
        }
        next_phase:
        constexpr auto next_pc =   (pc == ROOK)   ? BISHOP
                            : (pc == BISHOP) ? GOLD
                            : (pc == GOLD)   ? SILVER
                            : (pc == SILVER) ? KNIGHT
                            : (pc == KNIGHT) ? LANCE : EMPTY;

        return mate1_to_drop<turn,next_pc,inc>(pos,to,king_sq);
}

template<Color turn,Square inc> 
    Move mate1_to(game::Position &pos, const Square king_sq) {
    if (inc == INC_NONE) {
        return MOVE_NONE;
    }
    constexpr auto opp = change_turn(turn);
    const auto to = king_sq - inc;
    const auto to_cp = pos.square(to);
    if (to_cp == COLOR_EMPTY) {
        //王手→駒移動王手でチェック
        return mate1_to_drop<turn,ROOK,inc>(pos,to,king_sq);
    }//駒移動王手だけチェック
    else if (color_is_eq(opp,to_cp)) {
       return mate1_to_drop<turn,EMPTY,inc>(pos,to,king_sq);
    } else {
        constexpr auto next_inc = attack::dir10<turn,inc>();
        return mate1_to<turn,next_inc>(pos,king_sq);
    }
}

template<Color turn> Move mate1(game::Position &pos) {
    constexpr auto opp = change_turn(turn);
    const auto king_sq = pos.king_sq(opp);
    return mate1_to<turn,INC_UP>(pos,king_sq);
}

Move mate1(game::Position &pos) {
    return pos.turn() == BLACK ? mate1<BLACK>(pos) : mate1<WHITE>(pos);
}
}
#endif