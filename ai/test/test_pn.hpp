#ifndef __TEST_PN_HPP__
#define __TEST_PN_HPP__

#include "../common.hpp"
#include "../util.hpp"
#include "../game.hpp"
#include "../matesearch.hpp"
#include "../attack.hpp"
#include "../pnsearch.hpp"

namespace test {
void test_pn() {
    mate::g_mate_solver_global.init();
    {
       
        auto pos = sfen::sfen("1+R2Rlkn1/3g2ss1/2+Npsp3/2g1p1p1g/B1n6/1PG1P1P2/PNKP1P3/9/L1+b+p3+lP w 5PLps 1");

        Tee<<pos<<std::endl;
        mate::g_mate_solver_global.init();
        const auto mv = mate::think(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
    {
       
        auto pos = sfen::sfen("+BKsg4l/1l4gr1/1s2p4/ps2P1ppP/3Pk+b3/P1P4P1/1P2+r4/1sg6/LN3+p3 w GN3P2nl3p 130");

        Tee<<pos<<std::endl;
        mate::g_mate_solver_global.init();
        const auto mv = mate::think(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
    {
       
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BPA, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        hand[0] = inc_hand(hand[0],GOLD);
        hand[0] = inc_hand(hand[0],GOLD);
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        mate::g_mate_solver_global.init();
        const auto mv = mate::think(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv == MOVE_NONE);     
    }
    {
       
        ColorPiece pieces[] = {
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, WKI, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BPA, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, CEM, 
            CEM, CEM, CEM, CEM, BKI, CEM, CEM, CEM, CEM, 
        };
        Hand hand[] = {HAND_NONE, HAND_NONE};
        hand[0] = inc_hand(hand[0],GOLD);
        hand[0] = inc_hand(hand[0],GOLD);
        hand[0] = inc_hand(hand[0],GOLD);
        hand[0] = inc_hand(hand[0],GOLD);
        auto pos = game::Position(pieces,hand,BLACK);

        Tee<<pos<<std::endl;
        mate::g_mate_solver_global.init();

        const auto mv = mate::think(pos);
        Tee<<move_str(mv)<<std::endl;
        ASSERT(mv != MOVE_NONE);     
    }
}
bool test_pn2(std::string sfen, bool result) {
    auto pos = sfen::sfen(sfen);
    Tee<<pos<<std::endl;
    mate::g_mate_solver_global.init();
    const auto mv = mate::think(pos);
    Tee<<move_str(mv)<<std::endl;
    if (result) {
        if (mv == MOVE_NONE) {
            //Tee<<pos<<std::endl;
            Tee<<move_str(mv)<<std::endl;
        }
        return mv != MOVE_NONE;
    } else {
        return mv == MOVE_NONE;
    }
}
void test_pn1() {
    std::ifstream file("/home/tugajin/Documents/cpp_shogi2/ai/data/mate5.sfen");
    
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
        if (i % 1000 == 0) {
            Tee<<i<<"\n";
        }
        i++;
        if(!test_pn2(line,true)) {
            Tee<<line<<std::endl;
            ASSERT(false);
        }
    }

    // ファイルを閉じる
    file.close();
}
}

#endif