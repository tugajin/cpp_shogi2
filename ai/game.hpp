#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "common.hpp"
#include "util.hpp"
#include "movelist.hpp"
namespace game {
class Position;
}
namespace hash {
Key hash_key(const game::Position &pos);
}
namespace sfen{
std::string out_sfen(const game::Position &pos);
}

bool move_is_ok(const Move m, const game::Position &pos); 

namespace game {

extern Key g_key_history[1][1024];

class Position {
public:
    Position() {}
    Position(const ColorPiece pieces[], const Hand hand[], const Color turn);
    bool is_lose();
    bool is_win() const;
    bool is_draw(int max_num = 4) const {
        if (this->ply_ >= 400) {
            return true;
        }
        return false;
        const auto curr_key = game::g_key_history[0][this->ply_];
        auto num = 0;
        for (auto ply = this->ply_ - 4; ply >= 0; ply -= 2) {
            const auto prev_key = game::g_key_history[0][ply];
            if (curr_key == prev_key) {
                if ((++num) >= max_num) {
                    return true;
                }
            }
        }
        return false;
    }
    bool is_done() {
        return (this->is_lose() || this->is_draw());
    }
    Color turn() const {
        return this->turn_;
    }
    ColorPiece square(const Square sq) const {
        ASSERT(sq >= SQ_BEGIN);
        ASSERT(sq < SQ_END);
        return this->square_[sq];
    }
    void set_square(const Square sq, const ColorPiece cp) {
        ASSERT(sq >= SQ_BEGIN);
        ASSERT(sq < SQ_END);
        this->square_[sq] = cp;
    }
    Hand hand(const Color c) const {
        ASSERT(color_is_ok(c));
        return this->hand_[c];
    }
    bool is_ok() const;
    std::string str() const;
    Square king_sq (const Color c) const {
        return this->king_sq_[c];
    }
	friend std::ostream& operator<<(std::ostream& os, const Position& pos) {
        os << pos.str();
		return os;
	}
    Position next(const Move action) const;
    void dump() const;
    Key history() const {
        return game::g_key_history[0][this->ply_];
    }
    Key history(const int ply) const {
        return game::g_key_history[0][ply];
    }
    int ply() const {
        return this->ply_;
    }
    bool exists_pawn(const Color c, const File f) const {
        return this->exist_pawn_[c] & (1 << f);
    }
    Position mirror() const;
    Position rotate() const;
    void next_quick(const Square to, const ColorPiece cp);
    void prev_quick(const Square to);
private:
    ColorPiece square_[SQ_END];//どんな駒が存在しているか？
    Hand hand_[COLOR_SIZE];
    uint16 exist_pawn_[COLOR_SIZE];//2歩用の配列
    Square king_sq_[COLOR_SIZE];//王の場所
    int ply_;
    Color turn_;
    void quiet_move_piece(const Square from, const Square to, ColorPiece color_piece);
    void put_piece(const Square sq, const ColorPiece color_piece);
    void remove_piece(const Square sq, const ColorPiece color_piece);
};

Position::Position(const ColorPiece pieces[], const Hand hand[], const Color turn) {
   REP(i, SQ_END) {
        this->square_[i] = sq_is_ok(static_cast<Square>(i)) ? COLOR_EMPTY : COLOR_WALL;
    }
    REP_COLOR(col) {
        this->exist_pawn_[col] = 0;
    }
    this->ply_ = 0;
    REP(i, SQUARE_SIZE) {
        if (pieces[i] != COLOR_EMPTY) {
            this->put_piece(SQUARE_INDEX[i], pieces[i]);
        } else {
            this->square_[SQUARE_INDEX[i]] = COLOR_EMPTY;
        }
    }
    this->hand_[BLACK] = hand[BLACK];
    this->hand_[WHITE] = hand[WHITE];
    this->turn_ = turn;
    ASSERT2(this->is_ok(),{
        Tee<<*this<<std::endl;
        this->dump();
    })
}

void Position::put_piece(const Square sq, const ColorPiece color_piece) {
    ASSERT2(sq_is_ok(sq),{ Tee<<"sq:"<<sq<<std::endl; });
    ASSERT(color_piece != COLOR_EMPTY);
    const auto col = piece_color(color_piece);
    const auto pc = to_piece(color_piece);
    this->square_[sq] = color_piece;
    if (pc == PAWN) {
        ASSERT((this->exist_pawn_[col] & (1 << sq_file(sq))) == 0);
        this->exist_pawn_[col] ^= (1 << sq_file(sq));
    } else if (pc == KING) {
        this->king_sq_[col] = sq;
    }
}

std::string Position::str() const {
    std::string ret = "手番:" + color_str(this->turn()) + " hash:" + to_string(this->history()) + " ply:" + to_string(this->ply_) + "\n";
    ret += sfen::out_sfen(*this)+"\n";
    ret += "後手:" + hand_str(this->hand_[WHITE]) + "\n";
    for(auto *p = SQUARE_INDEX; *p != SQ_WALL; ++p) {
        const auto color_piece = this->square_[*p];
        const auto col = piece_color(color_piece);
        const auto piece = to_piece(color_piece);
        if (piece == EMPTY) {
            ret += " ";
        } else if (col == BLACK) {
            ret += "^";
        } else {
            ret += "v";
        }
        ret += piece_str(piece);
        if (sq_file(*p) == FILE_1) { ret += "\n"; }
    }
    ret += "先手:" + hand_str(this->hand_[BLACK]) ;
    return ret;
}

bool Position::is_ok() const {
    if (this->turn() != BLACK && this->turn() != WHITE) {
#if DEBUG
                Tee<<"error turn\n";
#endif
        return false;
    }
    if (this->ply_ < 0 || this->ply_ > 1024) {
#if DEBUG
                Tee<<"error history\n";
#endif
        return false;
    }
    // double pawn
    uint16 found_pawn[COLOR_SIZE] = {0, 0};
    REP_FILE(file) {
        REP_RANK(rank) {
            const auto sq = ::square(file, rank);
            const auto color_piece = this->square(sq);
            const auto piece = to_piece(color_piece);
            const auto color = piece_color(color_piece);
            if (piece == PAWN) {
                found_pawn[color] |= (1 << sq_file(sq));
            }
        }
    }
    REP_COLOR(c) {
        if (found_pawn[c] != this->exist_pawn_[c]) {
#if DEBUG
        Tee<<"double pawn error\n";
        Tee<<c<<std::endl;
#endif
            return false;
        }
    }
    
    if (!hand_is_ok(this->hand_[BLACK])) {
#if DEBUG
        Tee<<"error black hand\n";
#endif
        return false;
    } 
    if (!hand_is_ok(this->hand_[WHITE])) {
#if DEBUG
        Tee<<"error white hand\n";
#endif
        return false;
    } 

    return true;
}

Position Position::next(const Move action) const {
    ASSERT2(this->is_ok(),{
        Tee<<"prev_next\n";
        Tee<<this->str()<<std::endl;
        Tee<<move_str(action)<<std::endl;
    });
    ASSERT2(move_is_ok(action, *this), {
        Tee<< "prev move error\n";
        Tee<<this->str()<<std::endl;
        Tee<<move_str(action)<<std::endl;
    });
    Position next_pos = *this;
    const auto turn = next_pos.turn();
    const auto opp = change_turn(turn);
    if (move_is_drop(action)) {
        const auto piece = move_piece(action);
        const auto to = move_to(action);
        next_pos.square_[to] = color_piece(piece,turn);
        next_pos.hand_[turn] = dec_hand(next_pos.hand_[turn], piece);
        if (piece == PAWN) {
            ASSERT(!(next_pos.exist_pawn_[turn] & (1 << sq_file(to))));
            next_pos.exist_pawn_[turn] ^= (1 << sq_file(to));
        }
    } else {
        const auto from = move_from(action);
        const auto to = move_to(action);
        const auto src_color_piece = next_pos.square(from);
        auto dst_color_piece = src_color_piece;
        const auto captured_color_piece = next_pos.square(to);
        const auto src_piece = to_piece(src_color_piece);

        if (captured_color_piece != COLOR_EMPTY) {
            next_pos.hand_[turn] = inc_hand(next_pos.hand_[turn], unprom(to_piece(captured_color_piece)));
            const auto captured_piece = to_piece(captured_color_piece);
            if (captured_piece == PAWN) {
                ASSERT(next_pos.exist_pawn_[opp] & (1 << sq_file(to)));
                next_pos.exist_pawn_[opp] ^= (1 << sq_file(to));
            }
        } 
        if (move_is_prom(action)) {
            const auto dst_piece = prom(src_piece);
            dst_color_piece = color_piece(dst_piece, turn);
            if (src_piece == PAWN) {
                ASSERT(next_pos.exist_pawn_[turn] & (1 << sq_file(from)));
                next_pos.exist_pawn_[turn] ^= (1 << sq_file(from));
            }
        } 
        next_pos.square_[from] = COLOR_EMPTY;
        next_pos.square_[to] = dst_color_piece;
        if (src_piece == KING) {
            next_pos.king_sq_[turn] = to;
        }
    }
    ++next_pos.ply_;
    next_pos.turn_ = change_turn(turn);
    //game::g_key_history[0][next_pos.ply_]= hash::hash_key(next_pos);
    ASSERT2(next_pos.is_ok(),{
        //Tee<<"prev\n";
        //Tee<<*this<<std::endl;
        Tee<<"after next\n";
        Tee<<next_pos<<std::endl;
        Tee<<move_str(action)<<std::endl;
        next_pos.dump();
    });
    ASSERT2(!next_pos.is_win(),{
        //Tee<<"prev\n";
        //Tee<<*this<<std::endl;
        Tee<<"evasion error\n";
        Tee<<*this<<std::endl;
        Tee<<move_str(action)<<std::endl;
        next_pos.dump();
    });
    return next_pos;
}


void Position::dump() const {
    Tee<<"dump:\n";
    Tee<<"square\n";
    REP(sq, SQ_END) {
        if (sq % 8 == 0) { Tee<<"\n";}
        Tee<<padding_str(to_string(static_cast<int>(this->square_[sq])),5)+",";
    }
    Tee<<"black_hand:"<<static_cast<int>(this->hand_[BLACK])<<std::endl;
    Tee<<"white_hand:"<<static_cast<int>(this->hand_[WHITE])<<std::endl;

    Tee<<"double pawn:"<<this->exist_pawn_[BLACK]<<std::endl;
    Tee<<"double pawn:"<<this->exist_pawn_[WHITE]<<std::endl;
}

Position Position::mirror() const {
    Position pos;
    return pos;
}

Position Position::rotate() const {
    Position pos;
    return pos;
}

void init() {
    REP(i, 1024) {
        game::g_key_history[0][i] = Key(0);
    }
}

}
bool move_is_ok(const Move m, const game::Position &pos) {
    const auto to = move_to(m);
    if (!sq_is_ok(to)) {
        return false;
    }
    if (move_is_drop(m)) {
        const auto piece = move_piece(m);
        if (!piece_is_ok(piece)) {
            return false;
        }
        if (piece == KING 
        || piece == PPAWN 
        || piece == PLANCE 
        || piece == PKNIGHT 
        || piece == PSILVER 
        || piece == PBISHOP 
        || piece == PROOK) {
            return false;
        }
        if (pos.square(to) != COLOR_EMPTY) {
            return false;
        }
        if (piece == PAWN) {
            const auto rank = sq_rank(to);
            if (pos.turn() == BLACK && rank == RANK_1) {
                return false;
            }
            if (pos.turn() == WHITE && rank == RANK_9) {
                return false;
            }
            if (pos.exists_pawn(pos.turn(), sq_file(to))) {
                return false;
            }
        }
        if (piece == LANCE) {
            const auto rank = sq_rank(to);
            if (pos.turn() == BLACK && rank == RANK_1) {
                return false;
            }
            if (pos.turn() == WHITE && rank == RANK_9) {
                return false;
            }
        }
        if (piece == KNIGHT) {
            const auto rank = sq_rank(to);
            if (pos.turn() == BLACK && (rank == RANK_1 || rank == RANK_2)) {
                return false;
            }
            if (pos.turn() == WHITE && (rank == RANK_9 || rank == RANK_8)) {
                return false;
            }
        }
    } else {
        const auto from = move_from(m);
        const auto prom = move_is_prom(m);
        const auto color_piece = pos.square(from);
        const auto color = piece_color(color_piece);
        const auto piece = to_piece(color_piece);
        if (!sq_is_ok(from)) {
            return false;
        }
        if (!sq_is_ok(to)) {
            return false;
        }
        if (color != pos.turn()) {
            return false;
        }
        if (prom) {
            if (piece == GOLD 
            || piece == KING 
            || piece == PPAWN 
            || piece == PLANCE 
            || piece == PKNIGHT 
            || piece == PSILVER 
            || piece == PBISHOP 
            || piece == PROOK) {
                return false;
            }
        } 
        const auto cap = pos.square(to);
        if (cap != COLOR_EMPTY) {
            const auto cap_color = piece_color(cap);
            if (cap_color == pos.turn()) {
                return false;
            }
            const auto piece = to_piece(cap);
            if (piece == KING) {
                return false;
            }
        }
    }
    return true;
}

#endif