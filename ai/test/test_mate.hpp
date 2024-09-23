#ifndef __TEST_MATE_HPP__
#define __TEST_MATE_HPP__

#include "../common.hpp"
#include "../util.hpp"
#include "../game.hpp"
#include "../matesearch.hpp"
#include "../attack.hpp"

namespace test {
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
        (test_mate2(line,5,true));
    }

    // ファイルを閉じる
    file.close();
}
}

#endif