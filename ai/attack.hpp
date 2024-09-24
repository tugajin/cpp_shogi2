#ifndef __ATTACK_HPP__
#define __ATTACK_HPP__

#include "game.hpp"

namespace attack {

inline Square delta_inc_line(const Square delta) {
    ASSERT(delta + DELTA_OFFSET >= 0);
    ASSERT(delta + DELTA_OFFSET < DELTA_NB);
    return g_delta_inc_line[DELTA_OFFSET + delta];
}

inline ColorPiece delta_flag_all(const Square delta) {
    ASSERT2(delta + DELTA_OFFSET >= 0,{ Tee<<delta<<std::endl; });
    ASSERT2(delta + DELTA_OFFSET < DELTA_NB,{Tee<<delta<<std::endl;});
    return g_delta_flag_all[DELTA_OFFSET + delta];
}
inline ColorPiece delta_flag_slider(const Square delta) {
    ASSERT2(delta + DELTA_OFFSET >= 0,{ Tee<<delta<<std::endl; });
    ASSERT2(delta + DELTA_OFFSET < DELTA_NB,{Tee<<delta<<std::endl;});
    return g_delta_flag_slider[DELTA_OFFSET + delta];
}

inline bool line_is_empty(const Square from, const Square to, const game::Position &pos) {
    const auto inc = delta_inc_line(to - from);
    ASSERT(inc != INC_NONE);
    Square sq;
    for (sq = from + inc; sq != to; sq += inc) {
        if (pos.square(sq) != COLOR_EMPTY) {
            return false;
        }
    }
    ASSERT(sq == to);
    return true;
}

inline bool pseudo_attack(const ColorPiece p, const Square delta) {
    return (delta_flag_all(delta) & p) != 0;
}

inline bool pseudo_slider_attack(const ColorPiece p, const Square delta) {
    return (delta_flag_slider(delta) & p) != 0;
}

inline bool slider_attack(const Square from ,const Square to, const ColorPiece cp, const game::Position &pos) {
    const auto delta = to - from;
    return (pseudo_attack(cp, delta) && line_is_empty(from, to, pos));
}

class Checker {
public:
    int checker_num;
    Square checker_from[2];
    Square checker_inc[2];
    void set(const Square inc, const Square to_sq, const Color opp, const game::Position &pos) {
        Square from_sq;
        for(from_sq = to_sq - inc; pos.square(from_sq) == COLOR_EMPTY; from_sq -= inc) {;}
        const auto checker_color_piece = pos.square(from_sq);
        const auto checker_delta = to_sq - from_sq;
        if (piece_color(checker_color_piece) == opp && pseudo_attack(checker_color_piece,checker_delta)) {
            this->checker_from[this->checker_num] = from_sq;
            if (pseudo_slider_attack(checker_color_piece,checker_delta)) {
                this->checker_inc[this->checker_num++] = inc;
            } else {
                this->checker_inc[this->checker_num++] = INC_NONE;
            }
        }
    }
    void set_knight(const Square inc, const Square to_sq, const Color opp, const game::Position &pos) {
        Square from_sq = to_sq - inc; 
        const auto checker_color_piece = pos.square(from_sq);
        const auto checker_piece = to_piece(checker_color_piece);
        if (color_is_eq(opp,checker_color_piece) && checker_piece == KNIGHT) {
            this->checker_from[this->checker_num] = from_sq;
            this->checker_inc[this->checker_num++] = INC_NONE;
        } 
    }
    Checker(const game::Position &pos) {
        this->checker_from[0] =  this->checker_from[1] = SQ_END;
        this->checker_inc[0] = this->checker_inc[1] = INC_NONE;
        this->checker_num = 0;

        const auto turn = pos.turn();
        const auto opp = change_turn(turn);
        const auto to_sq = pos.king_sq(turn);
        this->set(INC_UP, to_sq, opp, pos);
        this->set(INC_LEFTUP, to_sq, opp, pos);
        this->set(INC_RIGHTUP, to_sq, opp, pos);
        this->set(INC_LEFT, to_sq, opp, pos);
        this->set(INC_RIGHT, to_sq, opp, pos);
        this->set(INC_LEFTDOWN, to_sq, opp, pos);
        this->set(INC_RIGHTDOWN, to_sq, opp, pos);
        this->set(INC_DOWN, to_sq, opp, pos);
        if (opp == BLACK) {
            this->set_knight(INC_KNIGHT_LEFTUP, to_sq, opp, pos);
            this->set_knight(INC_KNIGHT_RIGHTUP, to_sq, opp, pos);
        } else {
            this->set_knight(INC_KNIGHT_LEFTDOWN, to_sq, opp, pos);
            this->set_knight(INC_KNIGHT_RIGHTDOWN, to_sq, opp, pos);
        }
        if (this->checker_inc[1] != INC_NONE) {
            const auto tmp = this->checker_inc[0];
            this->checker_inc[0] = this->checker_inc[1];
            this->checker_inc[1] = tmp;
            const auto tmp2 = this->checker_from[0];
            this->checker_from[0] = this->checker_from[1];
            this->checker_from[1] = tmp2;
            
        }
    }
};


inline bool is_attacked_dir(const game::Position &pos, const Square sq, const Square inc, const Color turn) {
    Square attacker_sq;
    for(attacker_sq = sq - inc; pos.square(attacker_sq) == COLOR_EMPTY; attacker_sq -= inc) {;}
    const auto delta = sq - attacker_sq;
    const auto p = pos.square(attacker_sq);
    return (color_is_eq(turn,p) && pseudo_attack(p,delta));
}
inline bool is_attacked_knight_dir(const game::Position &pos, const Square sq, const Square inc, const Color turn) {
    Square attacker_sq = sq - inc; 
    const auto p = pos.square(attacker_sq);
    const auto delta = sq - attacker_sq;
    return (color_is_eq(turn,p) && pseudo_attack(p,delta));
}

bool is_attacked(const game::Position &pos, const Square sq, const Color turn) {
    if (false) {
    }else if (is_attacked_dir(pos,sq,INC_UP,turn)) {
        return true;
    } else if (is_attacked_dir(pos,sq,INC_LEFTUP,turn)) {
        return true;
    } else if (is_attacked_dir(pos,sq,INC_RIGHTUP,turn)) {
        return true;
    } else if (is_attacked_dir(pos,sq,INC_LEFT,turn)) {
        return true;
    } else if (is_attacked_dir(pos,sq,INC_RIGHT,turn)) {
        return true;
    } else if (is_attacked_dir(pos,sq,INC_DOWN,turn)) {
        return true;
    } else if (is_attacked_dir(pos,sq,INC_LEFTDOWN,turn)) {
        return true;
    } else if (is_attacked_dir(pos,sq,INC_RIGHTDOWN,turn)) {
        return true;
    } else if (turn == BLACK && is_attacked_dir(pos,sq,INC_KNIGHT_LEFTUP,turn)) {
        return true;
    } else if (turn == BLACK && is_attacked_dir(pos,sq,INC_KNIGHT_RIGHTUP,turn)) {
        return true;
    } else if (turn == WHITE && is_attacked_dir(pos,sq,INC_KNIGHT_LEFTDOWN,turn)) {
        return true;
    } else if (turn == WHITE && is_attacked_dir(pos,sq,INC_KNIGHT_RIGHTDOWN,turn)) {
        return true;
    } else {
        return false;
    }
}

inline bool in_checked(const game::Position &pos) {
    return is_attacked(pos,pos.king_sq(pos.turn()),change_turn(pos.turn()));
}

inline bool can_move(const ColorPiece p, const int move_flag) {
    return (p & move_flag) == 0;
}

inline bool is_pinned(const Square sq, const Color me, const game::Position &pos) {
    const auto king_sq = pos.king_sq(me);
    // 玉とsqの間に何もないか？
    const auto inc_king = attack::delta_inc_line(king_sq - sq);
    if (inc_king == INC_NONE) { return false; }
    Square pseudo_king_sq;
    for (pseudo_king_sq = sq + inc_king; pos.square(pseudo_king_sq) == COLOR_EMPTY; pseudo_king_sq += inc_king) {;}
    if (pseudo_king_sq != king_sq) { return false; }

    // sqと飛び駒の間に何もないか？
    const auto inc_slider = static_cast<Square>(-inc_king);
    Square slider_sq;
    for(slider_sq = sq + inc_slider; pos.square(slider_sq) == COLOR_EMPTY; slider_sq += inc_slider) {;}
    const auto slider_cp = pos.square(slider_sq);
    const auto opp = change_turn(me);
    return color_is_eq(opp,slider_cp) && attack::pseudo_slider_attack(slider_cp, sq - slider_sq);
}

inline bool is_discover(const Square from, const Square to, const Color turn, const game::Position &pos) {
    const auto king_sq = pos.king_sq(turn);
    if (attack::delta_inc_line(king_sq - from) != attack::delta_inc_line(king_sq - to)) {
        return is_pinned(from,turn,pos);
    }
    return false;
}

template<Square inc> constexpr Square dir8() {
    return (inc == INC_UP) ? INC_DOWN:
           (inc == INC_DOWN) ? INC_LEFT:
           (inc == INC_LEFT) ? INC_RIGHT:
           (inc == INC_RIGHT) ? INC_LEFTUP:
           (inc == INC_LEFTUP) ? INC_RIGHTDOWN:
           (inc == INC_RIGHTDOWN) ? INC_LEFTDOWN:
           (inc == INC_LEFTDOWN) ? INC_RIGHTUP: INC_NONE;
}

template<Color turn, Square inc> constexpr Square dir10() {
    if (turn == BLACK) {
        return (inc == INC_UP) ? INC_DOWN:
            (inc == INC_DOWN) ? INC_LEFT:
            (inc == INC_LEFT) ? INC_RIGHT:
            (inc == INC_RIGHT) ? INC_LEFTUP:
            (inc == INC_LEFTUP) ? INC_RIGHTDOWN:
            (inc == INC_RIGHTDOWN) ? INC_LEFTDOWN:
            (inc == INC_LEFTDOWN) ? INC_RIGHTUP:
            (inc == INC_RIGHTUP) ? INC_KNIGHT_LEFTUP:
            (inc == INC_KNIGHT_LEFTUP) ? INC_KNIGHT_RIGHTUP:INC_NONE;
    } else {
        return (inc == INC_UP) ? INC_DOWN:
            (inc == INC_DOWN) ? INC_LEFT:
            (inc == INC_LEFT) ? INC_RIGHT:
            (inc == INC_RIGHT) ? INC_LEFTUP:
            (inc == INC_LEFTUP) ? INC_RIGHTDOWN:
            (inc == INC_RIGHTDOWN) ? INC_LEFTDOWN:
            (inc == INC_LEFTDOWN) ? INC_RIGHTUP:
            (inc == INC_RIGHTUP) ? INC_KNIGHT_LEFTDOWN:
            (inc == INC_KNIGHT_LEFTDOWN) ? INC_KNIGHT_RIGHTDOWN: INC_NONE;
    }
}
void init() {

    REP(i, 16) {
        g_piece_color_piece[BLACK][i] = g_piece_color_piece[WHITE][i] = 0ull;
    }

    g_piece_color_piece[BLACK][PAWN] = BLACK_PAWN;
    g_piece_color_piece[BLACK][LANCE] = BLACK_LANCE;
    g_piece_color_piece[BLACK][KNIGHT] = BLACK_KNIGHT;
    g_piece_color_piece[BLACK][SILVER] = BLACK_SILVER;
    g_piece_color_piece[BLACK][BISHOP] = BLACK_BISHOP;
    g_piece_color_piece[BLACK][ROOK] = BLACK_ROOK;
    g_piece_color_piece[BLACK][GOLD] = BLACK_GOLD;
    g_piece_color_piece[BLACK][KING] = BLACK_KING;
    g_piece_color_piece[BLACK][PPAWN] = BLACK_PPAWN;
    g_piece_color_piece[BLACK][PLANCE] = BLACK_PLANCE;
    g_piece_color_piece[BLACK][PKNIGHT] = BLACK_PKNIGHT;
    g_piece_color_piece[BLACK][PSILVER] = BLACK_PSILVER;
    g_piece_color_piece[BLACK][PBISHOP] = BLACK_PBISHOP;
    g_piece_color_piece[BLACK][PROOK] = BLACK_PROOK;

    g_piece_color_piece[WHITE][PAWN] = WHITE_PAWN;
    g_piece_color_piece[WHITE][LANCE] = WHITE_LANCE;
    g_piece_color_piece[WHITE][KNIGHT] = WHITE_KNIGHT;
    g_piece_color_piece[WHITE][SILVER] = WHITE_SILVER;
    g_piece_color_piece[WHITE][BISHOP] = WHITE_BISHOP;
    g_piece_color_piece[WHITE][ROOK] = WHITE_ROOK;
    g_piece_color_piece[WHITE][GOLD] = WHITE_GOLD;
    g_piece_color_piece[WHITE][KING] = WHITE_KING;
    g_piece_color_piece[WHITE][PPAWN] = WHITE_PPAWN;
    g_piece_color_piece[WHITE][PLANCE] = WHITE_PLANCE;
    g_piece_color_piece[WHITE][PKNIGHT] = WHITE_PKNIGHT;
    g_piece_color_piece[WHITE][PSILVER] = WHITE_PSILVER;
    g_piece_color_piece[WHITE][PBISHOP] = WHITE_PBISHOP;
    g_piece_color_piece[WHITE][PROOK] = WHITE_PROOK;

    REP(i, DELTA_NB) {
        g_delta_inc_line[i] = INC_NONE;
        g_delta_flag_all[i] = COLOR_EMPTY;
        g_delta_flag_slider[i] = COLOR_EMPTY;
    }

    const ColorPiece flags[] =        { UP_FLAG, LEFTUP_FLAG, LEFT_FLAG, LEFTDOWN_FLAG, 
                                        DOWN_FLAG, RIGHTDOWN_FLAG, RIGHT_FLAG, RIGHTUP_FLAG }; 
    const ColorPiece slider_flags[] = { SLIDER_UP_FLAG, SLIDER_LEFTUP_FLAG, SLIDER_LEFT_FLAG, SLIDER_LEFTDOWN_FLAG, 
                                        SLIDER_DOWN_FLAG, SLIDER_RIGHTDOWN_FLAG, SLIDER_RIGHT_FLAG, SLIDER_RIGHTUP_FLAG }; 
    const Square incs[] =             { INC_UP, INC_LEFTUP, INC_LEFT, INC_LEFTDOWN, 
                                        INC_DOWN, INC_RIGHTDOWN, INC_RIGHT, INC_RIGHTUP };
    REP(dir, 8) {
        auto inc = incs[dir];
        auto delta = inc;
        g_delta_flag_all[DELTA_OFFSET + delta] = flags[dir];
        //壁までいくことがあるので、9回実施
        REP(num, 9){
            ASSERT2(DELTA_OFFSET + delta >= 0,{
                Tee<<num<<std::endl;
                Tee<<delta<<std::endl;
            });
            g_delta_flag_all[DELTA_OFFSET + delta] = static_cast<ColorPiece>(
                                                    static_cast<int>(g_delta_flag_all[DELTA_OFFSET + delta]) | 
                                                    static_cast<int>(slider_flags[dir])
                                                );
            g_delta_flag_slider[DELTA_OFFSET + delta] = slider_flags[dir];
            g_delta_inc_line[DELTA_OFFSET + delta] = inc;
            delta += inc;
        }
    }

    auto delta = INC_KNIGHT_LEFTUP;
    g_delta_flag_all[DELTA_OFFSET + delta] = BLACK_KNIGHT_FLAG;
    delta = INC_KNIGHT_RIGHTUP;
    g_delta_flag_all[DELTA_OFFSET + delta] = BLACK_KNIGHT_FLAG;

    delta = INC_KNIGHT_LEFTDOWN;
    g_delta_flag_all[DELTA_OFFSET + delta] = WHITE_KNIGHT_FLAG;
    delta = INC_KNIGHT_RIGHTDOWN;
    g_delta_flag_all[DELTA_OFFSET + delta] = WHITE_KNIGHT_FLAG; 

    ASSERT(g_delta_flag_all[DELTA_OFFSET + INC_UP] == (UP_FLAG | SLIDER_UP_FLAG));
    ASSERT(g_delta_flag_all[DELTA_OFFSET + INC_DOWN] == (DOWN_FLAG | SLIDER_DOWN_FLAG));
    ASSERT(g_delta_flag_all[DELTA_OFFSET + INC_LEFTUP] == (LEFTUP_FLAG | SLIDER_LEFTUP_FLAG));
    ASSERT(g_delta_flag_all[DELTA_OFFSET + INC_LEFTDOWN] == (LEFTDOWN_FLAG | SLIDER_LEFTDOWN_FLAG));
    ASSERT(g_delta_flag_all[DELTA_OFFSET + INC_LEFT] == (LEFT_FLAG | SLIDER_LEFT_FLAG));
    ASSERT(g_delta_flag_all[DELTA_OFFSET + INC_RIGHT] == (RIGHT_FLAG | SLIDER_RIGHT_FLAG));
    ASSERT(g_delta_flag_all[DELTA_OFFSET + INC_RIGHTUP] == (RIGHTUP_FLAG | SLIDER_RIGHTUP_FLAG));
    ASSERT(g_delta_flag_all[DELTA_OFFSET + INC_RIGHTDOWN] == (RIGHTDOWN_FLAG| SLIDER_RIGHTDOWN_FLAG));

}

}
namespace game {
bool Position::is_win() const {
    const auto me = this->turn();
    const auto opp = change_turn(me);
    return attack::is_attacked(*this, this->king_sq(opp), me);
}
}
namespace gen {

constexpr bool is_knight_inc(const Square inc) {
    return (inc == INC_KNIGHT_LEFTDOWN 
         || inc == INC_KNIGHT_LEFTUP 
         || inc == INC_KNIGHT_RIGHTDOWN 
         || inc == INC_KNIGHT_RIGHTUP);
}

template<Color turn, Square inc> bool can_capture_checker(const Square drop_sq, const game::Position &pos) {
    if (is_knight_inc(inc)) {
        return can_capture_checker_knight<turn,inc>(drop_sq,pos);
    }
    Square from;
    for (from = drop_sq - inc; pos.square(from) == COLOR_EMPTY; from -= inc) {;}
    const auto from_cp = pos.square(from);
    const auto from_pc = to_piece(from_cp);
    if (color_is_eq(turn, from_cp) 
    && from_pc != KING
    && attack::pseudo_attack(from_cp, drop_sq - from) 
    && !attack::is_discover(from, drop_sq, turn, pos)) {
        return true;
    }
    constexpr auto next_inc = attack::dir10<turn,inc>();
    return can_capture_checker<turn,next_inc>(drop_sq,pos);
}

template<Color turn, Square inc> bool can_capture_checker_knight(const Square drop_sq, const game::Position &pos) {
    if (inc == INC_NONE) {
        return false;
    }
    Square from = drop_sq - inc;
    const auto from_cp = pos.square(from);
    const auto from_piece = to_piece(from_cp);
    if (color_is_eq(turn, from_cp) 
    && from_piece == KNIGHT
    && !attack::is_discover(from, drop_sq, turn, pos)) {
        return true;
    }
    constexpr auto next_inc = attack::dir10<turn,inc>();
    return can_capture_checker_knight<turn,next_inc>(drop_sq,pos);
}
template<Square inc> bool can_escape_king(const Square king_sq, const ColorPiece move_flag, const Color me, const game::Position &pos) {
    if (inc == INC_NONE) {
        return false;
    }
    const auto to = king_sq - inc;
    if (attack::can_move(pos.square(to), move_flag)) { 
        if (!attack::is_attacked(pos, to, me)) {
            return true;
        }
    }
    constexpr auto next_inc = attack::dir8<inc>();
    return can_escape_king<next_inc>(king_sq,move_flag,me,pos);
}

// turnは王手してる側
template<Color checker_turn, bool is_drop>
bool is_mate_quick(const Square from, const Square checker_sq, ColorPiece to_cp, game::Position &pos) {

    constexpr auto me = checker_turn;
    constexpr auto opp = change_turn(me);
    const auto org_cp = pos.square(checker_sq);
    const auto king_sq = pos.king_sq(opp);
    // 置く
    pos.set_square(checker_sq, to_cp);

    ASSERT2(attack::is_attacked(pos,pos.king_sq(change_turn(checker_turn)),checker_turn),{
        Tee<<pos<<std::endl;
        Tee<<checker_sq<<std::endl;
    });

    // capture attacker
    if (is_drop) {
        if (can_capture_checker<change_turn(checker_turn),INC_UP>(checker_sq, pos)) {
            pos.set_square(checker_sq, org_cp);
            return false;
        } 
    } else {
        if (attack::is_discover(from,checker_sq,opp,pos)) {
        } else {
            if (can_capture_checker<change_turn(checker_turn),INC_UP>(checker_sq, pos)) {
                pos.set_square(checker_sq, org_cp);
                return false;
            } 
        }
    } 
    const auto move_flag = (opp == BLACK) ? ColorPiece(BLACK_FLAG | COLOR_WALL_FLAG) : ColorPiece(WHITE_FLAG | COLOR_WALL_FLAG);

    // escape king
    pos.set_square(king_sq,COLOR_EMPTY);
    if (can_escape_king<INC_UP>(king_sq, move_flag, me, pos)){
        pos.set_square(checker_sq, org_cp);
        constexpr auto king_cp = checker_turn == BLACK ? WHITE_KING : BLACK_KING;
        pos.set_square(king_sq,king_cp);
        return false;
    }
    pos.set_square(checker_sq, org_cp);
    constexpr auto king_cp = checker_turn == BLACK ? WHITE_KING : BLACK_KING;
    pos.set_square(king_sq,king_cp);
    return true;
}
// turnは王手してる側
template<Color checker_turn>
bool is_mate_with_pawn_drop(const Square drop_sq, game::Position &pos) {
    constexpr auto me = checker_turn;
    constexpr auto opp = change_turn(me);
    const auto king_sq = (me == BLACK) ? drop_sq + INC_UP : drop_sq + INC_DOWN;

    if (pos.king_sq(opp) != king_sq) {
        return false;
    }
    constexpr auto cp = color_piece<PAWN,checker_turn>();
    return is_mate_quick<checker_turn,true>(SQ_END,drop_sq,cp,pos);
}
}
namespace attack {
inline void test_attack() {
   
}
}
#endif