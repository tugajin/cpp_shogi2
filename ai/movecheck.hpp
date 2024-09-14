#ifndef __MOVECHECK_HPP__
#define __MOVECHECK_HPP__

#include "game.hpp"
#include "movelist.hpp"
#include "attack.hpp"
#include "movedrop.hpp"

namespace gen {

template<Color turn, bool has_pawn, bool has_lance, bool has_knight, int hand_num> void drop_check_moves_square(game::Position &pos, movelist::MoveList &ml, const Piece pieces[],const Square sq, const Square king_sq){
    const auto rank = sq_rank(sq);
    const auto delta = king_sq - sq;
    if (has_pawn) {
        constexpr auto cp = turn == BLACK ? BLACK_PAWN : WHITE_PAWN;
        /*if ((turn == BLACK && rank == RANK_1) || (turn == WHITE && rank == RANK_9)) {
        } else*/ if(pos.exists_pawn(turn,sq_file(sq))) {
        } else if (attack::pseudo_attack(cp,delta)) {
            //pseudo_attackのおかげでRANK_1 or 9は来ないはず
            ASSERT2((turn == BLACK && rank != RANK_1) || (turn == WHITE && rank != RANK_9),{
                Tee<<"drop pawn error\n";
                Tee<<pos<<std::endl;
                Tee<<sq<<std::endl;
            });
            if (!is_mate_with_pawn_drop<turn>(sq,pos)) {
                ml.add(move(sq,PAWN));
            }
        }
    }
    if (has_lance) {
        constexpr auto cp = turn == BLACK ? BLACK_LANCE : WHITE_LANCE;
        /*if ((turn == BLACK && rank == RANK_1) || (turn == WHITE && rank == RANK_9)) {
        } else*/ if (attack::pseudo_attack(cp,delta)){
            //pseudo_attackのおかげでRANK_1 or 9は来ないはず
            ASSERT2((turn == BLACK && rank != RANK_1) || (turn == WHITE && rank != RANK_9),{
                Tee<<"drop lance error\n";
                Tee<<pos<<std::endl;
                Tee<<sq<<std::endl;
            });
            ml.add(move(sq,LANCE));
        }
    }
    if (has_knight) {
        constexpr auto cp = turn == BLACK ? BLACK_KNIGHT : WHITE_KNIGHT;
        /*if ((turn == BLACK && rank < RANK_3) || (turn == WHITE && rank > RANK_7)) {
        } else if (attack::pseudo_attack(cp,delta)){
        } else*/ {
            //チェック済のはず
            ASSERT2(attack::pseudo_attack(cp,delta),{
                Tee<<"drop knight error\n";
                Tee<<pos<<std::endl;
                Tee<<sq<<std::endl;
            });
            ASSERT2((turn == BLACK && rank >= RANK_3) || (turn == WHITE && rank <= RANK_7),{
                Tee<<"drop knight error2\n";
                Tee<<pos<<std::endl;
                Tee<<sq<<std::endl;
            });
            ml.add(move(sq,KNIGHT));
        }
    }
    switch(hand_num) {
        case 4: {
            const auto cp = color_piece(pieces[3],turn);
            if (attack::pseudo_attack(cp,delta)) {
                ml.add(move(sq,pieces[3]));
            }
            [[fallthrough]];  // フォールスルーを明示
        }
        case 3: {
            const auto cp = color_piece(pieces[2],turn);
            if (attack::pseudo_attack(cp,delta)) {
                ml.add(move(sq,pieces[2]));
            }
            [[fallthrough]];  // フォールスルーを明示
        }
        case 2: {
            const auto cp = color_piece(pieces[1],turn);
            if (attack::pseudo_attack(cp,delta)) {
                ml.add(move(sq,pieces[1]));
            }
            [[fallthrough]];  // フォールスルーを明示
        }
        case 1:{
            const auto cp = color_piece(pieces[0],turn);
            if (attack::pseudo_attack(cp,delta)) {
                ml.add(move(sq,pieces[0]));
            }
            [[fallthrough]];  // フォールスルーを明示
        } 
        case 0:break;
        default:
            ASSERT2(false,{ Tee<<hand_num<<std::endl; });
            break;
    }
}
template<Color turn> 
    inline void add_check_move_to_dir(movelist::MoveList &ml, const Square from, const Square to, const bool to_prom, const Square king_sq, const ColorPiece move_flag, const game::Position &pos) {
    const auto from_cp = pos.square(from);
    const auto to_cp = pos.square(to);
    const auto delta = to - from;
    const auto check_delta = king_sq - to;
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
                if (attack::pseudo_attack(from_cp,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                    ml.add(move(from,to));
                }
                break;
            }
            case BLACK_PAWN: 
            case WHITE_PAWN: {
                if (attack::pseudo_attack(from_cp,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                    ml.add(move(from,to));
                }
                if (to_prom) {
                    const auto from_cp2 = prom(from_cp);
                    if (attack::pseudo_attack(from_cp2,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to,true));
                    }
                }
                break;
            }
            case BLACK_LANCE: {
                const auto rank = sq_rank(to);
                if (rank > RANK_3) {
                    if (attack::pseudo_attack(from_cp,check_delta) /* && !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to));
                    }
                } else if (rank <= RANK_2) {
                    if (attack::pseudo_attack(from_cp,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to));
                    }
                    const auto from_cp2 = prom(from_cp);
                    if (attack::pseudo_attack(from_cp2,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to,true));
                    }
                } else {
                    if (attack::pseudo_attack(from_cp,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to));
                    }
                    const auto from_cp2 = prom(from_cp);
                    if (attack::pseudo_attack(from_cp2,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to));
                    }
                }
                break;
            }
            case WHITE_LANCE: {
                const auto rank = sq_rank(to);
                if (rank < RANK_7) {
                   if (attack::pseudo_attack(from_cp,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to));
                    }
                } else if (rank >= RANK_8) {
                    if (attack::pseudo_attack(from_cp,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to));
                    }
                    const auto from_cp2 = prom(from_cp);
                    if (attack::pseudo_attack(from_cp2,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to,true));
                    }
                } else {
                    if (attack::pseudo_attack(from_cp,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to));
                    }
                    const auto from_cp2 = prom(from_cp);
                    if (attack::pseudo_attack(from_cp2,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to,true));
                    }
                }
                break;
            }
            case BLACK_SILVER: 
            case WHITE_SILVER: 
            case BLACK_ROOK:
            case BLACK_BISHOP: 
            case WHITE_ROOK:
            case WHITE_BISHOP: {
                if (attack::pseudo_attack(from_cp,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                    ml.add(move(from,to));
                }
                if (from_prom || to_prom) {
                    const auto from_cp2 = prom(from_cp);
                    if (attack::pseudo_attack(from_cp2,check_delta) /*&& !attack::is_discover(from,to,opp,pos)*/) {
                        ml.add(move(from,to,true));
                    }
                }
                break;
            }
            case BLACK_KNIGHT:
            case WHITE_KNIGHT:
            case BLACK_KING:
            case WHITE_KING:
                break;
            default:
                ASSERT(false);
            break;
        }
    }
}

template<Color turn, bool is_prom> inline void add_check_move_to_dir_knight(movelist::MoveList &ml, const Square to, const Square inc, const Square king_sq, const game::Position &pos, const ColorPiece move_flag) {
    Square from = to - inc;
    ASSERT2(int(from) >= 0,{
        Tee<<pos<<std::endl;
        Tee<<to<<std::endl;
    });

    const auto from_cp = pos.square(from);
    const auto to_cp = pos.square(to);
    const auto delta = to - from;
    const auto check_delta = king_sq - to;

    if (piece_color(from_cp) == turn 
    && attack::can_move(to_cp,move_flag) 
    && attack::pseudo_attack(from_cp,delta)
    && !attack::is_discover(from,to,turn,pos)) {
        if (turn == BLACK) {
            //if (!attack::is_discover(from,to,opp,pos)) {
            {
                constexpr auto cp = is_prom ? BLACK_PKNIGHT : BLACK_KNIGHT;
                if (attack::pseudo_attack(cp,check_delta)) {
                    ml.add(move(from,to,is_prom));
                }
            }
        } else {
            //if (!attack::is_discover(from,to,opp,pos)) {
            {
                constexpr auto cp = is_prom ? WHITE_PKNIGHT : WHITE_KNIGHT;
                if (attack::pseudo_attack(cp,check_delta)) {
                    ml.add(move(from,to,is_prom));
                }
            } 
        }
    }
}
template<Color turn> 
    void gen_check_moves_dir(game::Position &pos, movelist::MoveList &ml, const Square to, const Square inc, const Square king_sq, const ColorPiece move_flag) {
    Square from;
    for (from = to - inc; pos.square(from) == COLOR_EMPTY; from -= inc) {;}
    if (color_is_eq(turn,pos.square(from))) {
        add_check_move_to_dir<turn>(ml,from,to,sq_is_prom<turn>(to),king_sq,move_flag,pos);
    }
}
template<Color turn,bool has_knight> 
    void gen_check_moves_dir_knight(game::Position &pos, movelist::MoveList &ml, const Square inc, const Square king_sq, ColorPiece move_flag) {
    Square to = king_sq - inc;
    const auto rank = sq_rank(to);
    if (turn == BLACK && rank >= RANK_3) {
        add_check_move_to_dir_knight<turn,false>(ml,to,INC_KNIGHT_LEFTUP,king_sq,pos,move_flag);
        add_check_move_to_dir_knight<turn,false>(ml,to,INC_KNIGHT_RIGHTUP,king_sq,pos,move_flag);
        if (pos.square(to) == COLOR_EMPTY) {
            drop_check_moves_square<turn,false,false,has_knight,0>(pos,ml,nullptr,to,king_sq);
        }
    } else if (turn == WHITE && rank <= RANK_7) {
        add_check_move_to_dir_knight<turn,false>(ml,to,INC_KNIGHT_LEFTDOWN,king_sq,pos,move_flag);
        add_check_move_to_dir_knight<turn,false>(ml,to,INC_KNIGHT_RIGHTDOWN,king_sq,pos,move_flag);
        if (pos.square(to) == COLOR_EMPTY) {
            drop_check_moves_square<turn,false,false,has_knight,0>(pos,ml,nullptr,to,king_sq);
        }
    }
}

template<Color turn> inline void add_check_lance_move(movelist::MoveList &ml, const Square sq, const Square king_sq, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    Square to = sq + inc;
    if (attack::is_discover(sq,to,turn,pos)) { return; }
    for (; pos.square(to) == COLOR_EMPTY; to += inc) {
        const auto rank = sq_rank(to);
        const auto delta = king_sq - to;
        if (turn == BLACK) {
            if (rank == RANK_1) {
                if (!attack::pseudo_attack(color_piece(PLANCE,turn),delta)) { 
                    ml.add(move(sq,to,true));
                }
            } else if (rank == RANK_2 || rank == RANK_3) {
                if (!attack::pseudo_attack(color_piece(PLANCE,turn),delta)) { 
                    ml.add(move(sq,to,true));
                }
                if (!attack::pseudo_attack(color_piece(LANCE,turn),delta)) { 
                    ml.add(move(sq,to));
                }
            } else {
                if (!attack::pseudo_attack(color_piece(LANCE,turn),delta)) { 
                    ml.add(move(sq,to));
                }
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
                if (!attack::pseudo_attack(color_piece(PLANCE,turn),delta)) { 
                    ml.add(move(sq,to,true));
                }
            } else if (rank == RANK_7 || rank == RANK_8) {
                if (!attack::pseudo_attack(color_piece(PLANCE,turn),delta)) { 
                    ml.add(move(sq,to,true));
                }
                if (!attack::pseudo_attack(color_piece(LANCE,turn),delta)) { 
                    ml.add(move(sq,to));
                }
            } else {
                if (!attack::pseudo_attack(color_piece(LANCE,turn),delta)) { 
                    ml.add(move(sq,to));
                }
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

template<Color turn> inline void add_check_knight_move(movelist::MoveList &ml, const Square sq, const Square inc, const Square king_sq, const ColorPiece move_flag, const game::Position &pos) {
    const auto to = sq + inc;
    if (attack::can_move(pos.square(to),move_flag)) {
        if (attack::is_discover(sq,to,turn,pos)) { return; }
        const auto delta =  king_sq - to;
        const auto rank = sq_rank(to);
        if (turn == BLACK) {
            if (rank > RANK_3) {
                if (!attack::pseudo_attack(color_piece(KNIGHT,turn),delta)) { 
                    ml.add(move(sq,to));
                }
            } else if (rank <= RANK_2) {
                if (!attack::pseudo_attack(color_piece(PKNIGHT,turn),delta)) { 
                    ml.add(move(sq,to,true));
                }
            } else if (rank == RANK_3) {
                if (!attack::pseudo_attack(color_piece(KNIGHT,turn),delta)) { 
                    ml.add(move(sq,to));
                }
                if (!attack::pseudo_attack(color_piece(PKNIGHT,turn),delta)) { 
                    ml.add(move(sq,to,true));
                }
            }
        } else {
            if (rank < RANK_7) {
                if (!attack::pseudo_attack(color_piece(KNIGHT,turn),delta)) { 
                    ml.add(move(sq,to));
                }
            } else if (rank >= RANK_8) {
                if (!attack::pseudo_attack(color_piece(PKNIGHT,turn),delta)) { 
                    ml.add(move(sq,to,true));
                }
            } else if (rank == RANK_7) {
                if (!attack::pseudo_attack(color_piece(KNIGHT,turn),delta)) { 
                    ml.add(move(sq,to));
                }
                if (!attack::pseudo_attack(color_piece(PKNIGHT,turn),delta)) { 
                    ml.add(move(sq,to,true));
                }
            }
        }
    }
}

template<Color turn> inline void add_check_silver_move(movelist::MoveList &ml, const Square sq, const Square inc, const Square king_sq, const ColorPiece move_flag, const game::Position &pos) {
    const auto to = sq + inc;
    if (attack::can_move(pos.square(to),move_flag)) {
        if (attack::is_discover(sq,to,turn,pos)) { return; }
        const auto delta =  king_sq - to;
        if (!attack::pseudo_attack(color_piece(SILVER,turn),delta)) { 
            ml.add(move(sq,to));
        }
        const auto prom_from = sq_is_prom<turn>(sq);
        const auto prom_to = sq_is_prom<turn>(to);
        if (prom_from || prom_to) {
            if (!attack::pseudo_attack(color_piece(PSILVER,turn),delta)) {
                ml.add(move(sq,to,true));
            }
        }
    }
}

template<Color turn, Piece pc>inline void add_check_gold_move(movelist::MoveList &ml, const Square sq, const Square inc, const Square king_sq, const ColorPiece move_flag, const game::Position &pos) {
    const auto to = sq + inc;
    if (attack::can_move(pos.square(to),move_flag)) {
        if (attack::is_discover(sq,to,turn,pos)) { return; }
        const auto delta =  king_sq - to;
        if (attack::pseudo_attack(color_piece(pc,turn),delta)) { return; }
        ml.add(move(sq,to));
    }
}

inline void add_check_king_move(movelist::MoveList &ml, const Square sq, const Square inc, const Square king_sq, const ColorPiece move_flag, const game::Position &pos) {
    const auto to = sq + inc;
    if (attack::can_move(pos.square(to),move_flag)) {
        const auto opp = change_turn(pos.turn());
        if (attack::is_attacked(pos,to,opp)) { return; }
        ml.add(move(sq,to));
    }
}

template<Color turn, Piece pc> inline void add_check_slider_move(movelist::MoveList &ml, const Square sq, const Square king_sq, const Square inc, const ColorPiece move_flag, const game::Position &pos) {
    static_assert(pc == ROOK || pc == BISHOP);
    const auto prom_from = sq_is_prom<turn>(sq);
    Square to = sq + inc;
    if (attack::is_discover(sq,to,turn,pos)) { return; }

    for (; pos.square(to) == COLOR_EMPTY; to += inc) {
        const auto delta =  king_sq - to;
        if (attack::pseudo_attack(color_piece(pc,turn),delta)) { continue; }
        const auto prom_to = sq_is_prom<turn>(to);
        if ((prom_from || prom_to)) {
            if (!attack::pseudo_attack(color_piece(prom(pc),turn),delta)) { 
                ml.add(move(sq,to,true));
            }
        }
        ml.add(move(sq,to));
    }
    if (attack::can_move(pos.square(to),move_flag)) {
        const auto delta =  king_sq - to;
        const auto prom_to = sq_is_prom<turn>(to);
        if ((prom_from || prom_to)) {
            if (!attack::pseudo_attack(color_piece(prom(pc),turn),delta)) { 
                ml.add(move(sq,to,true));
            }
        }
        if (!attack::pseudo_attack(color_piece(pc,turn),delta)) { 
            ml.add(move(sq,to));
        }

    }
}

template<Color turn, Piece pc>inline void add_check_slider2_move(movelist::MoveList &ml, const Square sq, const Square inc, const Square king_sq, const ColorPiece move_flag, const game::Position &pos) {
    Square to = sq + inc;
    if (attack::is_discover(sq,to,turn,pos)) { return; }
    
    for (; pos.square(to) == COLOR_EMPTY; to += inc) {
        const auto delta =  king_sq - to;
        if (!attack::pseudo_attack(color_piece(pc,turn),delta)) {
            ml.add(move(sq,to));
        }
    }
    if (attack::can_move(pos.square(to),move_flag)) {
        const auto delta =  king_sq - to;
        if (!attack::pseudo_attack(color_piece(pc,turn),delta)) {
            ml.add(move(sq,to));
        }
    }
}

template<Color turn, Square inc> inline void gen_discover_check_moves_dir(const game::Position &pos, movelist::MoveList &ml,const Square from, const Square king_sq, ColorPiece move_flag){
    const auto cp = pos.square(from);
    if (turn == BLACK) {
        if (false) {
        } else if (cp == COLOR_EMPTY) {
        } else if (cp == BLACK_PAWN) {
            const auto to = from + INC_UP;
            if (!attack::can_move(pos.square(to),move_flag)) { return; }
            if (pos.square(to+INC_UP) == WHITE_KING) { return; }
            if (inc == INC_UP || inc == INC_DOWN) { return; }
            if (attack::is_discover(from,to,turn,pos)) { return; }
            //const auto prom = sq_is_prom(to,turn);
            //ml.add(move(sq,to,prom));
            const auto rank = sq_rank(to);
            if (rank == RANK_1) {
                ml.add(move(from,to,true));
            } else if (rank == RANK_2 || rank == RANK_3) {
                ml.add(move(from,to,true));
                ml.add(move(from,to,false));
            } else {
                ml.add(move(from,to,false));
            }
        } else if (cp == BLACK_LANCE) {
            if (inc == INC_UP || inc == INC_DOWN) { return; }
            add_check_lance_move<turn>(ml,from,INC_UP,king_sq,move_flag,pos);
        } else if (cp == BLACK_KNIGHT) {
            add_check_knight_move<turn>(ml,from,INC_KNIGHT_LEFTUP,king_sq,move_flag,pos);
            add_check_knight_move<turn>(ml,from,INC_KNIGHT_RIGHTUP,king_sq,move_flag,pos);
        } else if (cp == BLACK_SILVER) {
            if (inc != INC_UP && inc != INC_DOWN) { 
                add_check_silver_move<turn>(ml,from,INC_UP,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_silver_move<turn>(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_silver_move<turn>(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFTDOWN && inc != INC_RIGHTUP) {
                add_check_silver_move<turn>(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_silver_move<turn>(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
        } else if (cp == BLACK_GOLD 
                || cp == BLACK_PPAWN 
                || cp == BLACK_PLANCE 
                || cp == BLACK_PKNIGHT 
                || cp == BLACK_PSILVER) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_gold_move<turn,GOLD>(ml,from,INC_UP,king_sq,move_flag,pos);
                add_check_gold_move<turn,GOLD>(ml,from,INC_DOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_gold_move<turn,GOLD>(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_gold_move<turn,GOLD>(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_gold_move<turn,GOLD>(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_gold_move<turn,GOLD>(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        } else if (cp == BLACK_KING) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_king_move(ml,from,INC_UP,king_sq,move_flag,pos);
                add_check_king_move(ml,from,INC_DOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_king_move(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_king_move(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_king_move(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_king_move(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_king_move(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_king_move(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        } else if (cp == BLACK_ROOK) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_slider_move<turn,ROOK>(ml,from,INC_UP,king_sq,move_flag,pos);
                add_check_slider_move<turn,ROOK>(ml,from,INC_DOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_slider_move<turn,ROOK>(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_slider_move<turn,ROOK>(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        } else if (cp == BLACK_BISHOP) {
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_slider_move<turn,BISHOP>(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_slider_move<turn,BISHOP>(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_slider_move<turn,BISHOP>(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_slider_move<turn,BISHOP>(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
        } else if (cp == BLACK_PROOK) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_slider2_move<turn,PROOK>(ml,from,INC_UP,king_sq,move_flag,pos);
                add_check_slider2_move<turn,PROOK>(ml,from,INC_DOWN,king_sq,move_flag,pos);

            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_gold_move<turn,PROOK>(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_gold_move<turn,PROOK>(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_gold_move<turn,PROOK>(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_gold_move<turn,PROOK>(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_slider2_move<turn,PROOK>(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_slider2_move<turn,PROOK>(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        } else if (cp == BLACK_PBISHOP) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_gold_move<turn,PBISHOP>(ml,from,INC_UP,king_sq,move_flag,pos);
                add_check_gold_move<turn,PBISHOP>(ml,from,INC_DOWN,king_sq,move_flag,pos);

            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_slider2_move<turn,PBISHOP>(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_slider2_move<turn,PBISHOP>(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_slider2_move<turn,PBISHOP>(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_slider2_move<turn,PBISHOP>(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_gold_move<turn,PBISHOP>(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_gold_move<turn,PBISHOP>(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        }
    } else {
        if (false) {
        } else if (cp == COLOR_EMPTY) {
        } else if (cp == WHITE_PAWN) {
            const auto to = from + INC_DOWN;
            if (!attack::can_move(pos.square(to),move_flag)) { return; }
            if (pos.square(to+INC_DOWN) == BLACK_KING) { return; }
            if (attack::is_discover(from,to,turn,pos)) { return; }
            if (inc == INC_UP || inc == INC_DOWN) { return; }

            //const auto prom = sq_is_prom(to,turn);
            //ml.add(move(sq,to,prom));
            const auto rank = sq_rank(to);
            if (rank == RANK_9) {
                ml.add(move(from,to,true));
            } else if (rank == RANK_7 || rank == RANK_8) {
                ml.add(move(from,to,true));
                ml.add(move(from,to,false));
            } else {
                ml.add(move(from,to,false));
            }
        } else if (cp == WHITE_LANCE) {
            if (inc == INC_UP || inc == INC_DOWN) { return; }
            add_check_lance_move<turn>(ml,from,INC_DOWN,king_sq,move_flag,pos);
        } else if (cp == WHITE_KNIGHT) {
            add_check_knight_move<turn>(ml,from,INC_KNIGHT_LEFTDOWN,king_sq,move_flag,pos);
            add_check_knight_move<turn>(ml,from,INC_KNIGHT_RIGHTDOWN,king_sq,move_flag,pos);
        } else if (cp == WHITE_SILVER) {
            if (inc != INC_UP && inc != INC_DOWN) { 
                add_check_silver_move<turn>(ml,from,INC_DOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_silver_move<turn>(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_silver_move<turn>(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFTDOWN && inc != INC_RIGHTUP) {
                add_check_silver_move<turn>(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_silver_move<turn>(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
        } else if (cp == WHITE_GOLD 
                || cp == WHITE_PPAWN 
                || cp == WHITE_PLANCE 
                || cp == WHITE_PKNIGHT 
                || cp == WHITE_PSILVER) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_gold_move<turn,GOLD>(ml,from,INC_DOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_gold_move<turn,GOLD>(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_gold_move<turn,GOLD>(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_gold_move<turn,GOLD>(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_gold_move<turn,GOLD>(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        } else if (cp == WHITE_KING) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_king_move(ml,from,INC_UP,king_sq,move_flag,pos);
                add_check_king_move(ml,from,INC_DOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_king_move(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_king_move(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_king_move(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_king_move(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_king_move(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_king_move(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        } else if (cp == WHITE_ROOK) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_slider_move<turn,ROOK>(ml,from,INC_UP,king_sq,move_flag,pos);
                add_check_slider_move<turn,ROOK>(ml,from,INC_DOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_slider_move<turn,ROOK>(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_slider_move<turn,ROOK>(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        } else if (cp == WHITE_BISHOP) {
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_slider_move<turn,BISHOP>(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_slider_move<turn,BISHOP>(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_slider_move<turn,BISHOP>(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_slider_move<turn,BISHOP>(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
        } else if (cp == WHITE_PROOK) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_slider2_move<turn,PROOK>(ml,from,INC_UP,king_sq,move_flag,pos);
                add_check_slider2_move<turn,PROOK>(ml,from,INC_DOWN,king_sq,move_flag,pos);

            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_gold_move<turn,PROOK>(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_gold_move<turn,PROOK>(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_gold_move<turn,PROOK>(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_gold_move<turn,PROOK>(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_slider2_move<turn,PROOK>(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_slider2_move<turn,PROOK>(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        } else if (cp == WHITE_PBISHOP) {
            if (inc != INC_UP && inc != INC_DOWN) {
                add_check_gold_move<turn,PBISHOP>(ml,from,INC_UP,king_sq,move_flag,pos);
                add_check_gold_move<turn,PBISHOP>(ml,from,INC_DOWN,king_sq,move_flag,pos);

            }
            if (inc != INC_LEFTUP && inc != INC_RIGHTDOWN) {
                add_check_slider2_move<turn,PBISHOP>(ml,from,INC_LEFTUP,king_sq,move_flag,pos);
                add_check_slider2_move<turn,PBISHOP>(ml,from,INC_RIGHTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_RIGHTUP && inc != INC_LEFTDOWN) {
                add_check_slider2_move<turn,PBISHOP>(ml,from,INC_RIGHTUP,king_sq,move_flag,pos);
                add_check_slider2_move<turn,PBISHOP>(ml,from,INC_LEFTDOWN,king_sq,move_flag,pos);
            }
            if (inc != INC_LEFT && inc != INC_RIGHT) {
                add_check_gold_move<turn,PBISHOP>(ml,from,INC_LEFT,king_sq,move_flag,pos);
                add_check_gold_move<turn,PBISHOP>(ml,from,INC_RIGHT,king_sq,move_flag,pos);
            }
        }
    }
}
    
template<Color turn, bool has_pawn, bool has_lance,int hand_num, Square inc> 
    void gen_check_moves_to(game::Position &pos, movelist::MoveList &ml, const Square king_sq, const Piece pieces[], const ColorPiece move_flag) {
    Square to;
    auto distance = 0;
    constexpr auto opp = change_turn(turn);
    for (to = king_sq - inc; pos.square(to) == COLOR_EMPTY; to -= inc, distance++) {
        drop_check_moves_square<turn,has_pawn,has_lance,false,hand_num>(pos,ml,pieces,to,king_sq);
        gen_check_moves_dir<turn>(pos,ml,to,INC_UP,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_LEFTUP,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_RIGHTUP,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_LEFT,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_RIGHT,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_LEFTDOWN,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_DOWN,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_RIGHTDOWN,king_sq,move_flag);
        const auto rank = sq_rank(to);
        //桂成の王手
        if (turn == BLACK && rank <= RANK_3 && distance == 0 && inc != INC_LEFTDOWN && inc != INC_RIGHTDOWN) {
            add_check_move_to_dir_knight<turn,true>(ml,to,INC_KNIGHT_LEFTUP,king_sq,pos,move_flag);
            add_check_move_to_dir_knight<turn,true>(ml,to,INC_KNIGHT_RIGHTUP,king_sq,pos,move_flag);
        } else if (turn == WHITE && rank >= RANK_7 && distance == 0 && inc != INC_LEFTUP && inc != INC_RIGHTUP) {
            add_check_move_to_dir_knight<turn,true>(ml,to,INC_KNIGHT_LEFTDOWN,king_sq,pos,move_flag);
            add_check_move_to_dir_knight<turn,true>(ml,to,INC_KNIGHT_RIGHTDOWN,king_sq,pos,move_flag);
        }
    }
    //駒を取りながら王手
    if (color_is_eq(opp,pos.square(to))) {
        gen_check_moves_dir<turn>(pos,ml,to,INC_UP,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_LEFTUP,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_RIGHTUP,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_LEFT,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_RIGHT,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_LEFTDOWN,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_DOWN,king_sq,move_flag);
        gen_check_moves_dir<turn>(pos,ml,to,INC_RIGHTDOWN,king_sq,move_flag);
        const auto rank = sq_rank(to);
        //桂成の王手
        if (turn == BLACK && rank <= RANK_3 && distance == 0 && inc != INC_LEFTDOWN && inc != INC_RIGHTDOWN) {
            add_check_move_to_dir_knight<turn,true>(ml,to,INC_KNIGHT_LEFTUP,king_sq,pos,move_flag);
            add_check_move_to_dir_knight<turn,true>(ml,to,INC_KNIGHT_RIGHTUP,king_sq,pos,move_flag);
        } else if (turn == WHITE && rank >= RANK_7 && distance == 0 && inc != INC_LEFTUP && inc != INC_RIGHTUP) {
            add_check_move_to_dir_knight<turn,true>(ml,to,INC_KNIGHT_LEFTDOWN,king_sq,pos,move_flag);
            add_check_move_to_dir_knight<turn,true>(ml,to,INC_KNIGHT_RIGHTDOWN,king_sq,pos,move_flag);
        }
    } else if (color_is_eq(turn,pos.square(to))) {
        //空き王手
        const auto from = to;
        //背後に飛び駒があるかチェック
        Square slider_sq;
        for(slider_sq = from - inc; pos.square(slider_sq) == COLOR_EMPTY; slider_sq -= inc) {;}
        const auto slider_cp = pos.square(slider_sq);
        if (color_is_eq(turn,slider_cp) && attack::pseudo_slider_attack(slider_cp, king_sq - slider_sq)) {
            gen_discover_check_moves_dir<turn,inc>(pos,ml,from,king_sq,move_flag);
        }
    }
}

template<Color turn, bool has_pawn, bool has_lance, bool has_knight, int hand_num> 
    void gen_check_moves(game::Position &pos, movelist::MoveList &ml, const Piece pieces[], const ColorPiece move_flag) {
    const auto opp = change_turn(turn);
    const auto king_sq = pos.king_sq(opp);
    gen_check_moves_to<turn,has_pawn,has_lance,hand_num,INC_UP>(pos,ml,king_sq,pieces,move_flag);
    gen_check_moves_to<turn,has_pawn,has_lance,hand_num,INC_LEFTUP>(pos,ml,king_sq,pieces,move_flag);
    gen_check_moves_to<turn,has_pawn,has_lance,hand_num,INC_RIGHTUP>(pos,ml,king_sq,pieces,move_flag);
    gen_check_moves_to<turn,has_pawn,has_lance,hand_num,INC_LEFT>(pos,ml,king_sq,pieces,move_flag);
    gen_check_moves_to<turn,has_pawn,has_lance,hand_num,INC_RIGHT>(pos,ml,king_sq,pieces,move_flag);
    gen_check_moves_to<turn,has_pawn,has_lance,hand_num,INC_DOWN>(pos,ml,king_sq,pieces,move_flag);
    gen_check_moves_to<turn,has_pawn,has_lance,hand_num,INC_LEFTDOWN>(pos,ml,king_sq,pieces,move_flag);
    gen_check_moves_to<turn,has_pawn,has_lance,hand_num,INC_RIGHTDOWN>(pos,ml,king_sq,pieces,move_flag);
    //桂不成の王手
    if (turn == BLACK && sq_rank(king_sq) <= RANK_7) {
        gen_check_moves_dir_knight<turn,has_knight>(pos,ml, INC_KNIGHT_LEFTUP,king_sq,move_flag);
        gen_check_moves_dir_knight<turn,has_knight>(pos,ml, INC_KNIGHT_RIGHTUP,king_sq,move_flag);
    } else if(turn == WHITE && sq_rank(king_sq) >= RANK_3){
        gen_check_moves_dir_knight<turn,has_knight>(pos,ml, INC_KNIGHT_LEFTDOWN,king_sq,move_flag);
        gen_check_moves_dir_knight<turn,has_knight>(pos,ml, INC_KNIGHT_RIGHTDOWN,king_sq,move_flag);
    }
}
template<Color turn> void gen_check_moves(game::Position &pos, movelist::MoveList &ml) {
    const auto move_flag = (turn == BLACK) ? ColorPiece(BLACK_FLAG | COLOR_WALL_FLAG) : ColorPiece(WHITE_FLAG | COLOR_WALL_FLAG);
    const auto hand = pos.hand(turn);
    Piece pieces[4] = {};
    auto hand_num = 0;

#define ADD_HAND(param0,param1,param2) do {\
    switch(hand_num) {\
        case 0: gen_check_moves<turn,param0,param1,param2,0>(pos,ml,pieces,move_flag); break;\
        case 1: gen_check_moves<turn,param0,param1,param2,1>(pos,ml,pieces,move_flag); break;\
        case 2: gen_check_moves<turn,param0,param1,param2,2>(pos,ml,pieces,move_flag); break;\
        case 3: gen_check_moves<turn,param0,param1,param2,3>(pos,ml,pieces,move_flag); break;\
        case 4: gen_check_moves<turn,param0,param1,param2,4>(pos,ml,pieces,move_flag); break;\
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
void gen_check_moves(game::Position &pos, movelist::MoveList &ml) {
    (pos.turn() == BLACK) ? gen_check_moves<BLACK>(pos,ml) : gen_check_moves<WHITE>(pos,ml);
}
}
#endif