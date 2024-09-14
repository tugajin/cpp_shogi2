#ifndef __TEST_COMMON_HPP__
#define __TEST_COMMON_HPP__

#include "../common.hpp"
#include "../util.hpp"

namespace test {
void test_hand(const Piece piece, const int num) {
    auto hand = HAND_NONE;
    ASSERT(!has_piece(hand,piece));
    REP(i, num) {
        hand = inc_hand(hand,piece);
        ASSERT(has_piece(hand,piece));
        ASSERT2(num_piece(hand,piece) == (i+1),{
            Tee<<num_piece(hand,piece)<<std::endl;
            Tee<<i+1<<std::endl;
        });
    }
    REP(i, num) {
        hand = dec_hand(hand,piece);
        if (i != (num-1)) {
            ASSERT(has_piece(hand,piece));
        }
        ASSERT2(num_piece(hand,piece) == (num-i-1),{
            Tee<<num_piece(hand,piece)<<std::endl;
            Tee<<(num-i-1)<<std::endl;
        });
    }
    ASSERT(!has_piece(hand,piece));
}
void test_sq() {
    auto sq = SQUARE_INDEX;
    auto index = 0;
    REP_RANK(rank) {
        REP_FILE(file) {
            ASSERT2(*sq == square(file,rank),{
                Tee<<file<<":"<<rank<<std::endl;
                Tee<<*sq<<std::endl;
                Tee<<square(file,rank)<<std::endl;
            });
            ASSERT2(sq_rank(*sq) == rank,{
                Tee<<*sq<<std::endl;
                Tee<<sq_rank(*sq)<<std::endl;
                Tee<<rank<<std::endl;
            });
            ASSERT2(sq_file(*sq) == file,{
                Tee<<*sq<<std::endl;
                Tee<<sq_file(*sq)<<std::endl;
                Tee<<file<<std::endl;
            });
            ASSERT2(sq_to_index(*sq) == index,{
                Tee<<*sq<<std::endl;
                Tee<<index<<std::endl;
                Tee<<sq_to_index(*sq)<<std::endl;
            });
            sq++;
            index++;
        }
    }
}
void test_move() {
    auto mv = move(SQ_19,SQ_18);
    ASSERT(move_from(mv) == SQ_19);
    ASSERT(move_to(mv) == SQ_18);
    ASSERT(!move_is_drop(mv));
    ASSERT(!move_is_prom(mv));

    mv = move(SQ_19,SQ_18,true);
    ASSERT(move_from(mv) == SQ_19);
    ASSERT(move_to(mv) == SQ_18);
    ASSERT(!move_is_drop(mv));
    ASSERT(move_is_prom(mv));
    
    mv = move(SQ_19,PAWN);
    ASSERT(move_to(mv) == SQ_19);
    ASSERT(move_piece(mv) == PAWN);
    ASSERT(move_is_drop(mv));
    ASSERT(!move_is_prom(mv));

    mv = move(SQ_11,ROOK);
    ASSERT(move_to(mv) == SQ_11);
    ASSERT(move_piece(mv) == ROOK);
    ASSERT(move_is_drop(mv));
    ASSERT(!move_is_prom(mv));
}
void test_common() {
    ASSERT(change_turn(BLACK) == WHITE);
    ASSERT(change_turn(WHITE) == BLACK);
    test_sq();
    test_move();
    test_hand(PAWN,18);
    test_hand(LANCE,4);
    test_hand(KNIGHT,4);
    test_hand(SILVER,4);
    test_hand(GOLD,4);
    test_hand(BISHOP,2);
    test_hand(ROOK,2);

    ASSERT(prom(PAWN) == PPAWN);
    ASSERT(prom(LANCE) == PLANCE);
    ASSERT(prom(KNIGHT) == PKNIGHT);
    ASSERT(prom(SILVER) == PSILVER);
    ASSERT(prom(BISHOP) == PBISHOP);
    ASSERT(prom(ROOK) == PROOK);
    ASSERT(unprom(PAWN) == PAWN);
    ASSERT(unprom(LANCE) == LANCE);
    ASSERT(unprom(KNIGHT) == KNIGHT);
    ASSERT(unprom(SILVER) == SILVER);
    ASSERT(unprom(GOLD) == GOLD);
    ASSERT(unprom(BISHOP) == BISHOP);
    ASSERT(unprom(ROOK) == ROOK);

    ASSERT(unprom(PPAWN) == PAWN);
    ASSERT(unprom(PLANCE) == LANCE);
    ASSERT(unprom(PKNIGHT) == KNIGHT);
    ASSERT(unprom(PSILVER) == SILVER);
    ASSERT(unprom(PBISHOP) == BISHOP);
    ASSERT(unprom(PROOK) == ROOK);

    ASSERT(color_piece(PAWN,BLACK) == BLACK_PAWN);
    ASSERT(color_piece(LANCE,BLACK) == BLACK_LANCE);
    ASSERT(color_piece(KNIGHT,BLACK) == BLACK_KNIGHT);
    ASSERT(color_piece(SILVER,BLACK) == BLACK_SILVER);
    ASSERT(color_piece(GOLD,BLACK) == BLACK_GOLD);
    ASSERT(color_piece(BISHOP,BLACK) == BLACK_BISHOP);
    ASSERT(color_piece(ROOK,BLACK) == BLACK_ROOK);
    ASSERT(color_piece(KING,BLACK) == BLACK_KING);
    
    ASSERT(color_piece(PPAWN,BLACK) == BLACK_PPAWN);
    ASSERT(color_piece(PLANCE,BLACK) == BLACK_PLANCE);
    ASSERT(color_piece(PKNIGHT,BLACK) == BLACK_PKNIGHT);
    ASSERT(color_piece(PSILVER,BLACK) == BLACK_PSILVER);
    ASSERT(color_piece(PBISHOP,BLACK) == BLACK_PBISHOP);
    ASSERT(color_piece(PROOK,BLACK) == BLACK_PROOK);
    
    ASSERT(color_piece(PAWN,WHITE) == WHITE_PAWN);
    ASSERT(color_piece(LANCE,WHITE) == WHITE_LANCE);
    ASSERT(color_piece(KNIGHT,WHITE) == WHITE_KNIGHT);
    ASSERT(color_piece(SILVER,WHITE) == WHITE_SILVER);
    ASSERT2(color_piece(GOLD,WHITE) == WHITE_GOLD,{
        Tee<<color_piece(GOLD,WHITE)<<";"<<WHITE_GOLD<<std::endl;
    });
    ASSERT(color_piece(BISHOP,WHITE) == WHITE_BISHOP);
    ASSERT(color_piece(ROOK,WHITE) == WHITE_ROOK);
    ASSERT(color_piece(KING,WHITE) == WHITE_KING);
    
    ASSERT(color_piece(PPAWN,WHITE) == WHITE_PPAWN);
    ASSERT(color_piece(PLANCE,WHITE) == WHITE_PLANCE);
    ASSERT(color_piece(PKNIGHT,WHITE) == WHITE_PKNIGHT);
    ASSERT2(color_piece(PSILVER,WHITE) == WHITE_PSILVER,{
        Tee<<color_piece(PSILVER,WHITE)<<":"<<WHITE_PSILVER<<std::endl;
    });
    ASSERT(color_piece(PBISHOP,WHITE) == WHITE_PBISHOP);
    ASSERT(color_piece(PROOK,WHITE) == WHITE_PROOK);

    ASSERT(to_piece(WHITE_PAWN) == PAWN);
    ASSERT(to_piece(WHITE_LANCE) == LANCE);
    ASSERT(to_piece(WHITE_KNIGHT) == KNIGHT);
    ASSERT(to_piece(WHITE_SILVER) == SILVER);
    ASSERT(to_piece(WHITE_GOLD) == GOLD);
    ASSERT(to_piece(WHITE_KING) == KING);
    ASSERT(to_piece(WHITE_BISHOP) == BISHOP);
    ASSERT(to_piece(WHITE_ROOK) == ROOK);
    ASSERT(to_piece(WHITE_PPAWN) == PPAWN);
    ASSERT(to_piece(WHITE_PLANCE) == PLANCE);
    ASSERT(to_piece(WHITE_PKNIGHT) == PKNIGHT);
    ASSERT(to_piece(WHITE_PSILVER) == PSILVER);
    ASSERT(to_piece(WHITE_PBISHOP) == PBISHOP);
    ASSERT(to_piece(WHITE_PROOK) == PROOK);

    ASSERT(to_piece(BLACK_PAWN) == PAWN);
    ASSERT(to_piece(BLACK_LANCE) == LANCE);
    ASSERT(to_piece(BLACK_KNIGHT) == KNIGHT);
    ASSERT(to_piece(BLACK_SILVER) == SILVER);
    ASSERT(to_piece(BLACK_GOLD) == GOLD);
    ASSERT(to_piece(BLACK_KING) == KING);
    ASSERT(to_piece(BLACK_BISHOP) == BISHOP);
    ASSERT(to_piece(BLACK_ROOK) == ROOK);
    ASSERT(to_piece(BLACK_PPAWN) == PPAWN);
    ASSERT(to_piece(BLACK_PLANCE) == PLANCE);
    ASSERT(to_piece(BLACK_PKNIGHT) == PKNIGHT);
    ASSERT(to_piece(BLACK_PSILVER) == PSILVER);
    ASSERT(to_piece(BLACK_PBISHOP) == PBISHOP);
    ASSERT(to_piece(BLACK_PROOK) == PROOK);

    ASSERT2(piece_color(WHITE_PAWN) == WHITE,{
        Tee<<WHITE_PAWN<<std::endl;
    });
    ASSERT(piece_color(WHITE_LANCE) == WHITE);
    ASSERT(piece_color(WHITE_KNIGHT) == WHITE);
    ASSERT(piece_color(WHITE_SILVER) == WHITE);
    ASSERT(piece_color(WHITE_GOLD) == WHITE);
    ASSERT(piece_color(WHITE_KING) == WHITE);
    ASSERT(piece_color(WHITE_BISHOP) == WHITE);
    ASSERT(piece_color(WHITE_ROOK) == WHITE);
    ASSERT(piece_color(WHITE_PPAWN) == WHITE);
    ASSERT(piece_color(WHITE_PLANCE) == WHITE);
    ASSERT(piece_color(WHITE_PKNIGHT) == WHITE);
    ASSERT(piece_color(WHITE_PSILVER) == WHITE);
    ASSERT(piece_color(WHITE_PBISHOP) == WHITE);
    ASSERT(piece_color(WHITE_PROOK) == WHITE);

    ASSERT(piece_color(BLACK_PAWN) == BLACK);
    ASSERT(piece_color(BLACK_LANCE) == BLACK);
    ASSERT(piece_color(BLACK_KNIGHT) == BLACK);
    ASSERT(piece_color(BLACK_SILVER) == BLACK);
    ASSERT(piece_color(BLACK_GOLD) == BLACK);
    ASSERT(piece_color(BLACK_KING) == BLACK);
    ASSERT(piece_color(BLACK_BISHOP) == BLACK);
    ASSERT(piece_color(BLACK_ROOK) == BLACK);
    ASSERT(piece_color(BLACK_PPAWN) == BLACK);
    ASSERT(piece_color(BLACK_PLANCE) == BLACK);
    ASSERT(piece_color(BLACK_PKNIGHT) == BLACK);
    ASSERT(piece_color(BLACK_PSILVER) == BLACK);
    ASSERT(piece_color(BLACK_PBISHOP) == BLACK);
    ASSERT(piece_color(BLACK_PROOK) == BLACK);

}
}

#endif