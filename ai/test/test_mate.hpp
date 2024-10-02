#ifndef __TEST_MATE_HPP__
#define __TEST_MATE_HPP__

#include "../common.hpp"
#include "../util.hpp"
#include "../game.hpp"
#include "../matesearch.hpp"
#include "../attack.hpp"
#include "../mate1.hpp"

namespace test {
void test_mate1() {
    {
       
        auto pos = sfen::sfen("1+P+P1+N1+P+P+S/L+P+PGP+P+P1P/1G+b1+LPSpk/1R+L4N1/P5P1K/3B2+l+p1/2RP5/3g+n3p/g1+p+nS2+s1 b 657");

        Tee<<pos<<std::endl;

        const auto mv = mate1::mate1<BLACK>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
    {
       
        auto pos = sfen::sfen("3+L4+N/rPn2g3/B2p1p1p1/k1n2Gp1p/Bs1P1PP1P/S2spK1g1/4l3L/2N1lS3/+p4+p+p2 b PRG3p 243");

        Tee<<pos<<std::endl;

        const auto mv = mate1::mate1<BLACK>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv == MOVE_NONE);     
    }
    {
       
        auto pos = sfen::sfen("1+N7/p+N1bl1g1L/4pksp1/2pp2P2/1pSG1NS2/b3SR2p/+n5+pPR/P3L4/1g3GK1L b 7p 201");

        Tee<<pos<<std::endl;

        const auto mv = mate1::mate1<BLACK>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
    {
       
        auto pos = sfen::sfen("2nnkb2+N/p1+Pg1p1G1/4sr1lL/1ppPpP2l/1P1S2Kpp/S1P2+p2L/n3P2PP/P1g4S1/1+p1G2B2 w r 274");

        Tee<<pos<<std::endl;

        const auto mv = mate1::mate1<WHITE>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
    {
       
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, WLA, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BGO, CEM, CEM, CEM, 
            CEM, CEM, CEM, BKN, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        const auto mv = mate1::mate1<BLACK>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
    {
       
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, WKN, WKI, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, WBI, WLA, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, BKN, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        const auto mv = mate1::mate1<BLACK>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
     {
       
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, WKN, WKI, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, WBI, WLA, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        hand[0] = inc_hand(HAND_NONE,KNIGHT);
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        const auto mv = mate1::mate1<BLACK>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
     {
       
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BGO, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        hand[0] = inc_hand(HAND_NONE,GOLD);
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        const auto mv = mate1::mate1<BLACK>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
     {
       
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BGO, BSI, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        const auto mv = mate1::mate1<BLACK>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
     {
       
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BGO, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        const auto mv = mate1::mate1<BLACK>(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv == MOVE_NONE);     
    }
}
bool test_mate2(std::string sfen, int ply, bool result) {
    auto pos = sfen::sfen(sfen);
    //Tee<<pos<<std::endl;
    // if (attack::in_checked(pos)) {
    //     Tee<<"skip!!\n";
    //     Tee<<pos<<std::endl;
    //     return result;
    // }
    auto mv = mate::mate_search(pos, ply);
    //Tee<<move_str(mv)<<std::endl;
    if (result) {
        if (mv == MOVE_NONE) {
            Tee<<pos<<std::endl;
            Tee<<move_str(mv)<<std::endl;
        }
        return mv != MOVE_NONE;
    } else {
        return mv == MOVE_NONE;
    }
}
void test_mate() {
    std::ifstream file("/home/tugajin/Documents/cpp_shogi2/ai/data/mate3.sfen");
    
    // ファイルが正しく開かれているかチェック
    if (!file.is_open()) {
        std::cerr << "ファイルを開くことができませんでした。" << std::endl;
    }
    
    std::string line;
    
    // 1行ずつ読み込む
    uint32 i = 0u;
    while (std::getline(file, line)) {
        //std::cout << line << std::endl;  // 読み込んだ行を出力
        //ASSERT(test_mate2(line,5,true));
        if (i % 100 == 0) {
            Tee<<i<<"\n";
        }
        i++;
        (test_mate2(line,7,true));
    }

    // ファイルを閉じる
    file.close();
}
}

#endif