#ifndef __TEST_GAME_HPP__
#define __TEST_GAME_HPP__

#include "../common.hpp"
#include "../util.hpp"
#include "../game.hpp"
#include "../movegen.hpp"
#include "../moveevasion.hpp"
#include "../movecheck.hpp"
#include "../sfen.hpp"

namespace test {
void test_game() {
    // {
    //     ColorPiece pieces[] = {
    //         WLA, WKN, WSI, WGO, WKI, WGO, WSI, WKN, WLA,
    //         CEM, WRO, CEM, CEM, CEM, CEM, CEM, WBI, CEM,
    //         WPA, WPA, WPA, WPA, WPA, WPA, WPA, WPA, WPA, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         BPA, BPA, BPA, BPA, BPA, BPA, BPA, BPA, BPA, 
    //         CEM, BBI, CEM, CEM, CEM, CEM, CEM, BRO, CEM,
    //         BLA, BKN, BSI, BGO, BKI, BGO, BSI, BKN, BLA,
    //     };
    //     Hand hand[] = {HAND_NONE, HAND_NONE};
    //     auto pos = game::Position(pieces,hand,BLACK);

    //     Tee<<pos<<std::endl;
    //     auto mv = move(SQ_77, SQ_76,false);
    //     auto pos2 = pos.next(mv);
    //     Tee<<pos2<<std::endl;
    //     movelist::MoveList ml;
    //     gen::gen_moves<BLACK>(pos,ml);
    //     Tee<<ml<<std::endl;

    //     // for(auto *p = SQUARE_INDEX; *p != SQ_WALL; ++p) {
    //     //     Tee<<sq_str(*p)<<attack::is_attacked(pos,*p,BLACK)<<std::endl;
    //     //     Tee<<sq_str(*p)<<attack::is_attacked(pos,*p,WHITE)<<std::endl;
    //     // }
    // }
    // {
    //     ColorPiece pieces[] = {
    //         CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, BKN, BKI, CEM, CEM, CEM, CEM, 
    //     };
    //     Hand hand[] = {HAND_NONE, HAND_NONE};
    //     auto pos = game::Position(pieces,hand,BLACK);

    //     Tee<<pos<<std::endl;
    //     ASSERT(attack::is_attacked(pos,SQ_57,BLACK));
    //     ASSERT(!attack::is_attacked(pos,SQ_67,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_77,BLACK));
    // }
    // {
    //     ColorPiece pieces[] = {
    //         CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, BLA, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, 
    //     };
    //     Hand hand[] = {HAND_NONE, HAND_NONE};
    //     auto pos = game::Position(pieces,hand,BLACK);

    //     Tee<<pos<<std::endl;
    //     ASSERT(attack::is_attacked_dir(pos,SQ_61,INC_UP,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_61,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_62,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_63,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_64,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_65,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_66,BLACK));
    //     ASSERT(!attack::is_attacked(pos,SQ_67,BLACK));
    //     ASSERT(!attack::is_attacked(pos,SQ_68,BLACK));
    //     ASSERT(!attack::is_attacked(pos,SQ_69,BLACK));
    //     ASSERT(!attack::is_attacked(pos,SQ_71,BLACK));
    // }
    // {
    //     ColorPiece pieces[] = {
    //         CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, WPA, CEM, BRO, CEM, BKI, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //         CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
    //     };
    //     Hand hand[] = {HAND_NONE, HAND_NONE};
    //     auto pos = game::Position(pieces,hand,BLACK);

    //     Tee<<pos<<std::endl;
    //     ASSERT(attack::is_attacked(pos,SQ_61,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_62,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_63,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_64,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_65,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_66,BLACK));
    //     ASSERT(!attack::is_attacked(pos,SQ_67,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_68,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_69,BLACK));

    //     ASSERT(!attack::is_attacked(pos,SQ_17,BLACK));
    //     ASSERT(!attack::is_attacked(pos,SQ_27,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_37,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_47,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_57,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_77,BLACK));
    //     ASSERT(attack::is_attacked(pos,SQ_87,BLACK));
    //     ASSERT(!attack::is_attacked(pos,SQ_97,BLACK));

    //     ASSERT(!attack::is_attacked(pos,SQ_71,BLACK));
    // }
 {
       
        auto pos = sfen::sfen("l1s2Gsnb/4r1k1n/2p4pl/gG1p2p1p/1pP1pp3/L3P3P/B1KP1PPPL/p1S1G1S2/P6NR w Np 90");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_check_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 1);     
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BGO, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BLA, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_check_moves(pos,ml);    
        Tee<<ml<<std::endl; 
        ASSERT(ml.len() == 5);     
    }
    {
       
        auto pos = sfen::sfen("2+L+Sr+P+NG+N/lK1P1+P2+B/7PP/2P2+Pp2/1P2P+bP2/G4l3/3g+p+s2p/k+n2+np1p+p/2+s+p+s1+lgr w p");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_check_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 4);     
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, BSI, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, WKI, CEM, BSI, CEM, CEM, 
            CEM, CEM, CEM, BKN, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, BGO, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, BGO, CEM, 
            CEM, CEM, BKN, CEM, BKI, CEM, BKN, CEM, BBI, 
            BRO, CEM, CEM, CEM, BLA, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_check_moves(pos,ml);    
        Tee<<ml<<std::endl; 
        ASSERT(ml.len() == 18);     
    }
    {
       
        auto pos = sfen::sfen("1n+N5k/lp1g5/+Psp6/3KGrpNp/1r2P1PP1/pBP4p1/3P1P2P/L1SSG4/GB1S1L1+l1 w 3Pnp 252");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 88);     
    }
    {
       
        auto pos = sfen::sfen("4+P4/G3+S1p1+S/lpp2ks+R1/pP4P1B/+r1Pp+Bp3/n2nPG1gP/3+s3pl/NN2l3L/1+p1G1K3 b 2P2p 231");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 71);     
    }
    {
       
        auto pos = sfen::sfen("n1+P1Gp1+N+N/kp1+L2+Pp1/1rps1P2+P/1SB3K1p/l1PgpG1S1/1P5SP/4P2l1/1+p2L1p+b1/Rg+n2+p3 b P 301");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 79);     
    }
    {
       
        auto pos = sfen::sfen("6+Rn1/2K1S1SSk/4B4/9/9/9/9/9/1L1L1L3 b PLNSBRG17p2n3g - 3");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 559);     
    }
    {
       
        auto pos = sfen::sfen("6+R2/2K1S1SSk/4B4/7n1/9/9/9/9/1L1L1L3 b PLNSBRG17p2n3g - 3");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 556);     
    }
    {
       
        auto pos = sfen::sfen("p5+R2/2K1S1SSk/4B4/9/9/9/9/9/1L1L1L3 b PLNSBRG16p3n3g - 3");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 559);     
    }
    {
       
        auto pos = sfen::sfen("1+Rp6/2K1S1SSk/4B4/9/9/9/9/9/1L1L1L3 b PLNSBRG16p3n3g - 3");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_evasion_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 10);     
    }
    {
       
        auto pos = sfen::sfen("R8/2K1S1SSk/4B4/9/9/9/9/9/1L1L1L3 b RBGSNLP3g3n17p - 2");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_moves<BLACK>(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 593);     
    }
    {
       
        auto pos = sfen::sfen("lnsgkgsnl/1r7/pppppp1pp/6p2/P8/9/1P+bPPPPPP/1B5R1/LNSGKGSNL b p - 5");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_evasion_moves<BLACK>(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 7);     
    }
    {
        auto pos = sfen::sfen("+P+N1+P1+N+L1+S/+LGp1+PP+S+N1/+NK2+P+b+P1+P/1+r+P1P2p1/1G6L/4b+r3/1p1+s5/2gkl1+p+p1/1+p1+pg1+s+p1 b p - 743");
        Tee<<pos<<std::endl;
        movelist::MoveList ml;
        gen::gen_evasion_moves(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 3);     
    }
    {
       
        auto pos = sfen::sfen("1n1gkgsnl/lrs4b1/ppppppppp/9/9/P1P6/1P1PPPPPP/1B5R1/LNSGKGSNL b - 5");

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        gen::gen_moves<BLACK>(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 40);     
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, WGO, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        Piece pieces2[] = {};
        gen::gen_evasion_moves<BLACK,false,false,false,0>(pos,ml,pieces2);
        ASSERT(ml.len() == 4);     
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, WPA, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, WGO, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        Piece pieces2[] = {};
        gen::gen_evasion_moves<BLACK,false,false,false,0>(pos,ml,pieces2);
        ASSERT(ml.len() == 3);     
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, WRO, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;

        movelist::MoveList ml;
        Piece pieces2[] = {};
        gen::gen_evasion_moves<BLACK,false,false,false,0>(pos,ml,pieces2);
        ASSERT(ml.len() == 5);     
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, WLA, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        attack::Checker checker(pos);
        ASSERT(checker.checker_from[0] == SQ_46);
        ASSERT(checker.checker_inc[0] == INC_DOWN);
        movelist::MoveList ml;
        gen::gen_evasion_moves<BLACK>(pos,ml);
        ASSERT(ml.len() == 7);     
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, WLA, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, BSI, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, BBI, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        attack::Checker checker(pos);
        ASSERT(checker.checker_from[0] == SQ_41);
        ASSERT(checker.checker_inc[0] == INC_DOWN);
        movelist::MoveList ml;
        gen::gen_evasion_moves<BLACK>(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 10);     
    }
    {
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, WLA, BSI, CEM, CEM, 
            BRO, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, BKN, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKN, CEM, BSI, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, BBI, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
        };
        auto tmp = inc_hand(HAND_NONE,PAWN);
        tmp = inc_hand(tmp,LANCE);
        tmp = inc_hand(tmp,KNIGHT);
        tmp = inc_hand(tmp,SILVER);
        tmp = inc_hand(tmp,GOLD);
        tmp = inc_hand(tmp,BISHOP);
        tmp = inc_hand(tmp,ROOK);
        Hand hand[] = {tmp, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        attack::Checker checker(pos);
        ASSERT(checker.checker_from[0] == SQ_41);
        ASSERT(checker.checker_inc[0] == INC_DOWN);
        movelist::MoveList ml;
        gen::gen_evasion_moves<BLACK>(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 50);     
    }
{
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, WPA, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BLA, CEM, CEM, CEM, 
            CEM, CEM, WRO, BGO, CEM, BKI, BGO, CEM, WRO, 
            CEM, CEM, CEM, CEM, BSI, CEM, BKN, CEM, CEM, 
            CEM, CEM, CEM, WBI, CEM, CEM, CEM, WPB, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        movelist::MoveList ml;
        gen::gen_moves<BLACK>(pos,ml);
        Tee<<ml<<std::endl;
        ASSERT(ml.len() == 10);     
    }
}
}

#endif