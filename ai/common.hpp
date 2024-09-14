#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "util.hpp"
/*
  0   1   2   3    4    5    6    7    8    9   10   11   12  13  14  15
 16  17  18  19   20   21   22   23   24   25   26   27   28  29  30  31
 32  33  34  35  v36  v37  v38  v39  v40  v41  v42  v43  v44  45  46  47
 48  49  50  51  v52  v53  v54  v55  v56  v57  v58  v59  v60  61  62  63
 64  65  66  67  v68  v69  v70  v71  v72  v73  v74  v75  v76  77  78  79
 80  81  82  83  v84  v85  v86  v87  v88  v89  v90  v91  v92  93  94  95
 96  97  98  99 v100 v101 v102 v103 v104 v105 v106 v107 v108 109 110 111
112 113 114 115 v116 v117 v118 v119 v120 v121 v122 v123 v124 125 126 127
128 129 130 131 v132 v133 v134 v135 v136 v137 v138 v139 v140 141 142 143
144 145 146 147 v148 v149 v150 v151 v152 v153 v154 v155 v156 157 158 159
160 161 162 163 v164 v165 v166 v167 v168 v169 v170 v171 v172 173 174 175
176 177 178 179  180  181  182  183  184  185  186  187  188 189 190 191
192 193 194 195  196  197  198  199  200  201  202  203  204 205 206 207
208 209 210 211  212  213  214  215  216  217  218  219  220 221 222 223
224 225 226 227  228  229  230  231  232  233  234  235  236 237 238 239
240 241 242 243  244  245  246  247  248  249  250  251  252 253 254 255

*/


constexpr inline int SQUARE_SIZE = 81;
constexpr inline int DIR_SIZE = 8;

#define REP(i,e) for (auto i = 0; (i) < (e); ++(i))
#define REP_FILE(i) for (auto i = FILE_9; (i) < FILE_SIZE; ++(i)) 
#define REP_RANK(i) for (auto i = RANK_1; (i) < RANK_SIZE; ++(i)) 
#define REP_COLOR(i) for (auto i = BLACK; (i) < COLOR_SIZE; ++(i)) 
#define REP_PIECE(i) for (auto i = PAWN; (i) <= PROOK; ++(i)) 

typedef uint64 Key;

enum Move : int {
    MOVE_NONE = -1
};

enum Color : int {
    BLACK = 0, WHITE = 1, COLOR_SIZE = 2, COLOR_NONE = 3,
};

enum File : int {
    FILE_1 = 8, 
    FILE_2 = 7, 
    FILE_3 = 6, 
    FILE_4 = 5, 
    FILE_5 = 4, 
    FILE_6 = 3, 
    FILE_7 = 2, 
    FILE_8 = 1, 
    FILE_9 = 0, 
    FILE_SIZE = 9,
};

enum Rank : int {
    RANK_1 = 0,
    RANK_2 = 1,
    RANK_3 = 2,
    RANK_4 = 3,
    RANK_5 = 4,
    RANK_6 = 5,
    RANK_7 = 6,
    RANK_8 = 7,
    RANK_9 = 8,
    RANK_SIZE = 9,
};

enum Square : int {
    SQ_BEGIN = 0,
    SQ_11 = 44,
    SQ_12 = 60,
    SQ_13 = 76,
    SQ_14 = 92,
    SQ_15 = 108,
    SQ_16 = 124,
    SQ_17 = 140,
    SQ_18 = 156,
    SQ_19 = 172,

    SQ_21 = 43,
    SQ_22 = 59,
    SQ_23 = 75,
    SQ_24 = 91,
    SQ_25 = 107,
    SQ_26 = 123,
    SQ_27 = 139,
    SQ_28 = 155,
    SQ_29 = 171,
    
    SQ_31 = 42,
    SQ_32 = 58,
    SQ_33 = 74,
    SQ_34 = 90,
    SQ_35 = 106,
    SQ_36 = 122,
    SQ_37 = 138,
    SQ_38 = 154,
    SQ_39 = 170,

    SQ_41 = 41,
    SQ_42 = 57,
    SQ_43 = 73,
    SQ_44 = 89,
    SQ_45 = 105,
    SQ_46 = 121,
    SQ_47 = 137,
    SQ_48 = 153,
    SQ_49 = 169,

    SQ_51 = 40,
    SQ_52 = 56,
    SQ_53 = 72,
    SQ_54 = 88,
    SQ_55 = 104,
    SQ_56 = 120,
    SQ_57 = 136,
    SQ_58 = 152,
    SQ_59 = 168,

    SQ_61 = 39,
    SQ_62 = 55,
    SQ_63 = 71,
    SQ_64 = 87,
    SQ_65 = 103,
    SQ_66 = 119,
    SQ_67 = 135,
    SQ_68 = 151,
    SQ_69 = 167,

    SQ_71 = 38,
    SQ_72 = 54,
    SQ_73 = 70,
    SQ_74 = 86,
    SQ_75 = 102,
    SQ_76 = 118,
    SQ_77 = 134,
    SQ_78 = 150,
    SQ_79 = 166,

    SQ_81 = 37,
    SQ_82 = 53,
    SQ_83 = 69,
    SQ_84 = 85,
    SQ_85 = 101,
    SQ_86 = 117,
    SQ_87 = 133,
    SQ_88 = 149,
    SQ_89 = 165,

    SQ_91 = 36,
    SQ_92 = 52,
    SQ_93 = 68,
    SQ_94 = 84,
    SQ_95 = 100,
    SQ_96 = 116,
    SQ_97 = 132,
    SQ_98 = 148,
    SQ_99 = 164,
    
    SQ_END = 256,
    SQ_WALL = -1,
    INC_UP = -16,
    INC_DOWN = 16,
    INC_LEFT = -1,
    INC_RIGHT = 1,
    INC_LEFTUP = -17,
    INC_RIGHTUP = -15,
    INC_LEFTDOWN = 15,
    INC_RIGHTDOWN = 17,
    INC_KNIGHT_LEFTUP = -33,
    INC_KNIGHT_RIGHTUP = -31,
    INC_KNIGHT_LEFTDOWN = 31,
    INC_KNIGHT_RIGHTDOWN = 33,
    INC_NONE = 0,
};

static constexpr int INC_OFFSET = INC_KNIGHT_RIGHTDOWN;
static constexpr int INC_MAX = 1 + INC_OFFSET * 2;

enum Piece : int {
    PROM_FLAG = 1 << 3,
    EMPTY = 0,
    PAWN = 1,
    LANCE = 2,
    KNIGHT = 3,
    SILVER = 4,
    BISHOP = 5,
    ROOK = 6,
    GOLD = 7,
    KING = 8, 
    PPAWN   =   PAWN | PROM_FLAG,
    PLANCE  =  LANCE | PROM_FLAG,
    PKNIGHT = KNIGHT | PROM_FLAG,
    PSILVER = SILVER | PROM_FLAG,
    PBISHOP = BISHOP | PROM_FLAG,
    PROOK   =   ROOK | PROM_FLAG,
    PIECE_END = 16,
};

enum ColorPiece : int {
    BLACK_FLAG = 1 << 5,
    WHITE_FLAG = 1 << 6,
    COLOR_WALL_FLAG = 1 << 7,
    UP_FLAG = 1 << 8,
    DOWN_FLAG = 1 << 9,
    LEFT_FLAG = 1 << 10,
    RIGHT_FLAG = 1 << 11,
    LEFTUP_FLAG = 1 << 12,
    LEFTDOWN_FLAG = 1 << 13,
    RIGHTUP_FLAG = 1 << 14,
    RIGHTDOWN_FLAG = 1 << 15,
    SLIDER_UP_FLAG = 1 << 16,
    SLIDER_DOWN_FLAG = 1 << 17,
    SLIDER_LEFT_FLAG = 1 << 18,
    SLIDER_RIGHT_FLAG = 1 << 19,
    SLIDER_LEFTUP_FLAG = 1 << 20,
    SLIDER_LEFTDOWN_FLAG = 1 << 21,
    SLIDER_RIGHTUP_FLAG = 1 << 22,
    SLIDER_RIGHTDOWN_FLAG = 1 << 23,
    BLACK_KNIGHT_FLAG = 1 << 24,
    WHITE_KNIGHT_FLAG = 1 << 25,

    X_FLAGS           = LEFTUP_FLAG | LEFTDOWN_FLAG | RIGHTDOWN_FLAG | RIGHTUP_FLAG,
    PLUS_FLAGS        = UP_FLAG | LEFT_FLAG | DOWN_FLAG | RIGHT_FLAG,
    SLIDER_X_FLAGS    = SLIDER_LEFTUP_FLAG | SLIDER_LEFTDOWN_FLAG | SLIDER_RIGHTDOWN_FLAG | SLIDER_RIGHTUP_FLAG,
    SLIDER_PLUS_FLAGS = SLIDER_UP_FLAG | SLIDER_LEFT_FLAG | SLIDER_DOWN_FLAG | SLIDER_RIGHT_FLAG,
    KING_FLAGS        = X_FLAGS | PLUS_FLAGS,

    BLACK_PAWN        = PAWN | BLACK_FLAG | UP_FLAG,
    BLACK_LANCE       = LANCE | BLACK_FLAG | SLIDER_UP_FLAG, 
    BLACK_KNIGHT      = KNIGHT | BLACK_FLAG | BLACK_KNIGHT_FLAG, 
    BLACK_SILVER      = SILVER | BLACK_FLAG | UP_FLAG | X_FLAGS, 
    BLACK_GOLDS       = BLACK_FLAG | PLUS_FLAGS | LEFTUP_FLAG | RIGHTUP_FLAG,
    BLACK_GOLD        = GOLD | BLACK_GOLDS, 
    BLACK_KING        = KING | BLACK_FLAG | KING_FLAGS,
    BLACK_BISHOP      = BISHOP | BLACK_FLAG | SLIDER_X_FLAGS,
    BLACK_ROOK        = ROOK | BLACK_FLAG | SLIDER_PLUS_FLAGS,
    BLACK_PPAWN       = PPAWN | BLACK_GOLDS,
    BLACK_PLANCE      = PLANCE | BLACK_GOLDS,
    BLACK_PKNIGHT     = PKNIGHT | BLACK_GOLDS,
    BLACK_PSILVER     = PSILVER | BLACK_GOLDS,
    BLACK_PBISHOP     = PBISHOP | BLACK_BISHOP | PLUS_FLAGS,
    BLACK_PROOK       = PROOK | BLACK_ROOK | X_FLAGS,

    WHITE_PAWN        = PAWN | WHITE_FLAG | DOWN_FLAG, 
    WHITE_LANCE       = LANCE | WHITE_FLAG | SLIDER_DOWN_FLAG, 
    WHITE_KNIGHT      = KNIGHT | WHITE_FLAG | WHITE_KNIGHT_FLAG, 
    WHITE_SILVER      = SILVER | WHITE_FLAG | DOWN_FLAG | X_FLAGS, 
    WHITE_GOLDS       = WHITE_FLAG | LEFTDOWN_FLAG | RIGHTDOWN_FLAG | PLUS_FLAGS,
    WHITE_GOLD        = GOLD | WHITE_GOLDS, 
    WHITE_KING        = KING | WHITE_FLAG | KING_FLAGS,
    WHITE_BISHOP      = BISHOP | WHITE_FLAG | SLIDER_X_FLAGS ,
    WHITE_ROOK        = ROOK | WHITE_FLAG | SLIDER_PLUS_FLAGS ,
    WHITE_PPAWN       = PPAWN | WHITE_GOLDS,
    WHITE_PLANCE      = PLANCE | WHITE_GOLDS,
    WHITE_PKNIGHT     = PKNIGHT | WHITE_GOLDS,
    WHITE_PSILVER     = PSILVER | WHITE_GOLDS,
    WHITE_PBISHOP     = PBISHOP | WHITE_BISHOP | PLUS_FLAGS,
    WHITE_PROOK       = PROOK | WHITE_ROOK | X_FLAGS,
    COLOR_EMPTY = EMPTY,
    COLOR_WALL = COLOR_WALL_FLAG,
    COLOR_PIECE_END = (WHITE_KNIGHT_FLAG << 1) - 1,

    CEM = COLOR_EMPTY,//短縮形
    BPA = BLACK_PAWN,
    BLA = BLACK_LANCE,
    BKN = BLACK_KNIGHT,
    BSI = BLACK_SILVER,
    BBI = BLACK_BISHOP,
    BRO = BLACK_ROOK,
    BGO = BLACK_GOLD,
    BKI = BLACK_KING,
    BPP = BLACK_PPAWN,
    BPL = BLACK_PLANCE,
    BPK = BLACK_PKNIGHT,
    BPS = BLACK_PSILVER,
    BPB = BLACK_PBISHOP,
    BPR = BLACK_PROOK,
    WPA = WHITE_PAWN,
    WLA = WHITE_LANCE,
    WKN = WHITE_KNIGHT,
    WSI = WHITE_SILVER,
    WBI = WHITE_BISHOP,
    WRO = WHITE_ROOK,
    WGO = WHITE_GOLD,
    WKI = WHITE_KING,
    WPP = WHITE_PPAWN,
    WPL = WHITE_PLANCE,
    WPK = WHITE_PKNIGHT,
    WPS = WHITE_PSILVER,
    WPB = WHITE_PBISHOP,
    WPR = WHITE_PROOK,
};

Color& operator++(Color& org) {
  org = static_cast<Color>(org + 1);
  return org;
}

Piece& operator++(Piece& org) {
  org = static_cast<Piece>(org + 1);
  return org;
}
File& operator++(File& org) {
  org = static_cast<File>(org + 1);
  return org;
}
Rank& operator++(Rank& org) {
  org = static_cast<Rank>(org + 1);
  return org;
}

constexpr Square operator+(Square l, Square r) {
  return static_cast<Square>(static_cast<int>(l) + static_cast<int>(r));
}
constexpr Square operator-(Square l, Square r) {
  return static_cast<Square>(static_cast<int>(l) - static_cast<int>(r));
}
constexpr Square& operator += (Square& lhs, const int rhs) { 
    return lhs  = static_cast<Square>(static_cast<int>(lhs) + rhs); 
} 
constexpr Square& operator += (Square& lhs, const Square rhs) { 
    return lhs += static_cast<int>(rhs); 
} 
constexpr Square& operator -= (Square& lhs, const int rhs) { 
    return lhs  = static_cast<Square>(static_cast<int>(lhs) - rhs); 
} 
constexpr Square& operator -= (Square& lhs, const Square rhs) { 
    return lhs -= static_cast<int>(rhs); 
} 
/*
    .... .... .... .... .... .... ...x xxxx pawn
    .... .... .... .... .... ...x xx.. .... lance
    .... .... .... .... ...x xx.. .... .... knight
    .... .... .... ...x xx.. .... .... .... silver
    .... .... .... xx.. .... .... .... .... bishop
    .... .... .xx. .... .... .... .... .... rook
    .... .xxx .... .... .... .... .... .... gold
    
*/
constexpr inline int HAND_SHIFT[] = {0, 0, 6, 10, 14, 18, 21, 24};

enum Hand : int { 
    HAND_NONE = 0 << HAND_SHIFT[0],
    HAND_PAWN = 1ul << HAND_SHIFT[1],
    HAND_LANCE = 1ul << HAND_SHIFT[2],
    HAND_KNIGHT = 1ul << HAND_SHIFT[3],
    HAND_SILVER = 1ul << HAND_SHIFT[4],
    HAND_BISHOP = 1ul << HAND_SHIFT[5],
    HAND_ROOK = 1ul << HAND_SHIFT[6],
    HAND_GOLD = 1ul << HAND_SHIFT[7],
};

constexpr inline int HAND_INC[] = {0, HAND_PAWN, HAND_LANCE, HAND_KNIGHT, HAND_SILVER, HAND_BISHOP, HAND_ROOK, HAND_GOLD };
constexpr inline int HAND_BITS[] = {0, 0x1f , 0x7 , 0x7 , 0x7 , 0x3 , 0x3 , 0x7  };
constexpr inline int HAND_MASK[] = {HAND_BITS[0] << HAND_SHIFT[0], HAND_BITS[1] << HAND_SHIFT[1], HAND_BITS[2] << HAND_SHIFT[2], HAND_BITS[3] << HAND_SHIFT[3], HAND_BITS[4] << HAND_SHIFT[4], HAND_BITS[5] << HAND_SHIFT[5], HAND_BITS[6] << HAND_SHIFT[6], HAND_BITS[7] << HAND_SHIFT[7] };
constexpr inline Square SQUARE_INDEX[] = { 
    SQ_91, SQ_81, SQ_71, SQ_61, SQ_51, SQ_41, SQ_31, SQ_21, SQ_11,
    SQ_92, SQ_82, SQ_72, SQ_62, SQ_52, SQ_42, SQ_32, SQ_22, SQ_12,
    SQ_93, SQ_83, SQ_73, SQ_63, SQ_53, SQ_43, SQ_33, SQ_23, SQ_13,
    SQ_94, SQ_84, SQ_74, SQ_64, SQ_54, SQ_44, SQ_34, SQ_24, SQ_14, 
    SQ_95, SQ_85, SQ_75, SQ_65, SQ_55, SQ_45, SQ_35, SQ_25, SQ_15, 
    SQ_96, SQ_86, SQ_76, SQ_66, SQ_56, SQ_46, SQ_36, SQ_26, SQ_16, 
    SQ_97, SQ_87, SQ_77, SQ_67, SQ_57, SQ_47, SQ_37, SQ_27, SQ_17, 
    SQ_98, SQ_88, SQ_78, SQ_68, SQ_58, SQ_48, SQ_38, SQ_28, SQ_18, 
    SQ_99, SQ_89, SQ_79, SQ_69, SQ_59, SQ_49, SQ_39, SQ_29, SQ_19, 
    SQ_WALL
};

extern uint64 g_piece_color_piece[COLOR_SIZE][PIECE_END];

static constexpr inline int DELTA_OFFSET = 280;
//static constexpr inline int DELTA_NB = DELTA_OFFSET * 2 + 1;
static constexpr inline int DELTA_NB = 1ull << 9;

extern Square g_delta_inc_line[DELTA_NB];
extern ColorPiece g_delta_flag_all[DELTA_NB];
extern ColorPiece g_delta_flag_slider[DELTA_NB];

inline std::string color_str(const Color c) {
    return c == BLACK ? "先手" : "後手";
}
std::ostream& operator<<(std::ostream& os, const Color c) {
    os << color_str(c);
    return os;
}
inline constexpr Color change_turn(const Color turn) {
    return static_cast<Color>(static_cast<int>(turn) ^ 1);
}

inline constexpr Square invert_inc(const Square inc) {
    return static_cast<Square>(-static_cast<int>(inc));
}

inline constexpr Square square(const File f, const Rank r) {
    return static_cast<Square>(f + (r * 16) + 36);
}

inline constexpr Rank sq_rank(const Square sq) {
    return static_cast<Rank>((sq-36) >> 4);
}

inline constexpr File sq_file(const Square sq) {
    return static_cast<File>((sq-36) & 0xf);
}

inline Square invert_sq(const Square sq) {
    return Square(172) - sq + Square(36);
}

inline Square mirror_sq(const Square sq) {
    auto file = sq_file(sq);
    auto rank = sq_rank(sq);
    file = static_cast<File>(static_cast<int>(FILE_SIZE) - 1 - static_cast<int>(file));
    return square(file, rank);
}

inline int sq_to_index_debug(const Square sq) {
    REP(i,SQUARE_SIZE) {
        if (SQUARE_INDEX[i] == sq) {
            return i;
        }
    }
    return -1;
}
inline int sq_to_index(const Square sq) {
    const auto f = sq_file(sq);
    const auto r = sq_rank(sq);
    //https://www.wdic.org/w/TECH/%E3%83%93%E3%83%83%E3%83%88%E3%82%B7%E3%83%95%E3%83%88
    const auto index = f + (r<<3) + r;// f + r*3
    ASSERT(sq_to_index_debug(sq)==index);
    return index;
}

inline constexpr Hand inc_hand(const Hand h, const Piece p) {
    ASSERT2(p == PAWN || p == LANCE || p == KNIGHT || p == SILVER || p == GOLD || p == BISHOP || p == ROOK,{
        Tee<<p<<std::endl;
    });
    return static_cast<Hand>(h + HAND_INC[p]);
}

inline constexpr Hand dec_hand(const Hand h, const Piece p) {
    ASSERT2(p == PAWN || p == LANCE || p == KNIGHT || p == SILVER || p == GOLD || p == BISHOP || p == ROOK,{
        Tee<<p<<std::endl;
    });
    return static_cast<Hand>(h - HAND_INC[p]);
}

inline constexpr bool has_piece(const Hand h, const Piece p) {
    ASSERT2(p == PAWN || p == LANCE || p == KNIGHT || p == SILVER || p == GOLD || p == BISHOP || p == ROOK,{
        Tee<<p<<std::endl;
    });
    return (h & HAND_MASK[p]) != 0;
}

inline constexpr int num_piece(const Hand h, const Piece p) {
    ASSERT2(p == PAWN || p == LANCE || p == KNIGHT || p == SILVER || p == GOLD || p == BISHOP || p == ROOK,{
        Tee<<p<<std::endl;
    });
    return (h >> HAND_SHIFT[p]) & HAND_BITS[p];
}

inline constexpr Move move(const Square from, const Square to, bool prom = false) {
    return static_cast<Move>(
        (static_cast<int>(prom) << 17) | (from << 8) | to
    );
}

inline constexpr Move move(const Square to, const Piece p) {
    return static_cast<Move>(
       (1ul << 18) | (p << 8) | (to)
    );
}

inline constexpr Square move_from(const Move m) {
    return static_cast<Square>((m >> 8) & 0xFF);
}

inline constexpr Square move_to(const Move m) {
    return static_cast<Square>(m & 0xFF);
}

inline constexpr Piece move_piece(const Move m) {
    return static_cast<Piece>((m >> 8) & 0x1F);
}

inline constexpr bool move_is_drop(const Move m) {
    return (m & (1ul << 18)) != 0;
}

inline constexpr bool move_is_prom(const Move m) {
    return (m & (1 << 17)) != 0;
}

inline ColorPiece color_piece(const Piece p, const Color c) {
    return static_cast<ColorPiece>(g_piece_color_piece[c][p]);
}

inline constexpr Piece to_piece(const ColorPiece p) {
    return static_cast<Piece>(p & 0x1F);
}

inline constexpr Piece prom(const Piece p) {
    ASSERT(p != GOLD);
    ASSERT(p != KING);
    ASSERT(p != EMPTY);
    return static_cast<Piece>(p | PROM_FLAG);
}

inline constexpr Piece unprom(const Piece p) {
    ASSERT(p != EMPTY);
    return static_cast<Piece>(p & (~PROM_FLAG));
}

inline constexpr Color piece_color(const ColorPiece p) {
    return static_cast<Color>((p >> 6) & 0x1);
}

inline ColorPiece prom(const ColorPiece cp) {
    const auto color = piece_color(cp);
    const auto pc = to_piece(cp);
    const auto ppc = prom(pc);
    return color_piece(ppc, color);
}

inline bool color_is_eq(const Color c, const ColorPiece cp) {
    static constexpr ColorPiece flag[] = { BLACK_FLAG, WHITE_FLAG };
    return (flag[c] & cp) != 0;
}

inline bool can_prom(const ColorPiece cp) {
    switch (cp) {
        case BLACK_PAWN:
        case BLACK_LANCE:
        case BLACK_KNIGHT:
        case BLACK_SILVER:
        case BLACK_BISHOP:
        case BLACK_ROOK:
        case WHITE_PAWN:
        case WHITE_LANCE:
        case WHITE_KNIGHT:
        case WHITE_SILVER:
        case WHITE_BISHOP:
        case WHITE_ROOK:
            return false;
        default:
            return true;
    }
}

inline bool piece_is_slider(const Piece pc) {
    switch (pc) {
        case LANCE:
        case BISHOP:
        case ROOK:
        case PBISHOP:
        case PROOK:
            return true;
        default:
            return false;
    }
}

inline bool sq_is_ok(const Square sq) {
    for(auto *p = SQUARE_INDEX; *p != SQ_WALL; ++p) {
        if (*p == sq) {
            return true;
        }
    }
    return false;
}

constexpr inline bool sq_is_prom(const Square sq, const Color c) {
    const auto rank = sq_rank(sq);
    return (c == BLACK) ? (rank <= RANK_3) : (rank >= RANK_7);
}

template<Color c> bool sq_is_prom(const Square sq) {
    const auto rank = sq_rank(sq);
    return (c == BLACK) ? (rank <= RANK_3) : (rank >= RANK_7);
}

inline bool piece_is_ok(const Piece p) {
    return (p == PAWN    || 
            p == LANCE   ||
            p == KNIGHT  ||
            p == SILVER  || 
            p == GOLD    || 
            p == BISHOP  || 
            p == ROOK    ||
            p == KING    ||
            p == PPAWN   || 
            p == PLANCE  || 
            p == PKNIGHT || 
            p == PSILVER || 
            p == PBISHOP || 
            p == PROOK);
}

inline bool color_is_ok(const Color c) {
    return (c == BLACK || c == WHITE);
}

inline bool move_is_ok(const Move m) {
    if (move_is_drop(m)) {
        const auto piece = move_piece(m);
        const auto to = move_to(m);
        return piece_is_ok(piece) && sq_is_ok(to);
    } else {
        const auto from = move_from(m);
        const auto to = move_to(m);
        return sq_is_ok(from) && sq_is_ok(to);
    }
}

inline bool hand_is_ok(const Hand h) {
    static constexpr Hand HAND_MAX = static_cast<Hand>(0x76DDDDF);
    return h >= HAND_NONE && h <= HAND_MAX;
}

static inline std::string PIECE_STR[] = {"・","歩","香","桂","銀","角","飛","金","玉","と","杏","圭","全","馬","龍"};

inline std::string piece_str(const Piece p) {
    return PIECE_STR[p];
}

inline std::string hand_str(const Hand h) {
    std::string ret = "";
    REP(i, num_piece(h, PAWN)) {
        ret += piece_str(PAWN);
    }
    REP(i, num_piece(h, LANCE)) {
        ret += piece_str(LANCE);
    }
    REP(i, num_piece(h, KNIGHT)) {
        ret += piece_str(KNIGHT);
    }
    REP(i, num_piece(h, SILVER)) {
        ret += piece_str(SILVER);
    }
    REP(i, num_piece(h, GOLD)) {
        ret += piece_str(GOLD);
    }
    REP(i, num_piece(h, BISHOP)) {
        ret += piece_str(BISHOP);
    }
    REP(i, num_piece(h, ROOK)) {
        ret += piece_str(ROOK);
    }
    if (ret == "") {
        return "持ち駒なし";
    } else {
        return ret;
    }
}


inline std::string sq_str(const Square sq) {
    static const std::string file_str[] = {"９","８","７","６","５","４","３","２","１"};
    static const std::string rank_str[] = {"一","二","三","四","五","六","七","八","九"};
    if (!sq_is_ok(sq)) {
        return "error_sq:" + to_string(int(sq));
    }
    const auto file = sq_file(sq);
    const auto rank = sq_rank(sq);
    return file_str[file] + rank_str[rank];
}

inline std::string move_str(const Move m) {
    std::string ret = "";
    if (m == MOVE_NONE) {
        ret += "MOVE_NONE";
    } else if (move_is_drop(m)) {
        ret +="★ " + sq_str(move_to(m))+piece_str(move_piece(m));
    } else {
        ret +=sq_str(move_from(m)) + sq_str(move_to(m));
        if (move_is_prom(m)) { ret += "成"; } 
    }
    ret += "(" + to_string(static_cast<int>(m)) + ")";
    return ret;
}


void check_mode() {
#if DEBUG
    Tee<<"debug mode\n";
#elif NDEBUG
    Tee<<"release mode\n";
#else
    Tee<<"unknown mode\n";
#endif
}


#endif
