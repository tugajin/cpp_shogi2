#include "game.hpp"
#include "sfen.hpp"
#include "movelist.hpp"
#include "movegen.hpp"
//#include "movelegal.hpp"
#include "util.hpp"
// #include "search.hpp"
// #include "selfplay.hpp"
// #include "ubfm.hpp"
#include "attack.hpp"
//#include "matesearch.hpp"
#include "hash.hpp"
// #include "nn.hpp"
// #include "countreward.hpp"
// #include "reviewbuffer.hpp"
// #include "model.hpp"
#include "pnsearch.hpp"
#include "hash.hpp"

#if DEBUG
#include "test/test_common.hpp"
#include "test/test_game.hpp"
#include "test/test_attack.hpp"
#include "test/test_gen.hpp"
#include "test/test_mate.hpp"
#include "test/test_pn.hpp"
#include "test/test_hash.hpp"
#endif

TeeStream Tee;

uint64 g_piece_color_piece[COLOR_SIZE][PIECE_END];

Square g_delta_inc_line[DELTA_NB];
ColorPiece g_delta_flag_all[DELTA_NB];
ColorPiece g_delta_flag_slider[DELTA_NB];

namespace game {
GameHistoryList g_history;

}

namespace hash {
Key g_hash_pos[COLOR_SIZE][PIECE_END][SQ_END];
Key g_hash_hand[COLOR_SIZE][PIECE_END][32];
Key g_hash_color;
}

// namespace ubfm {
// UBFMSearcherGlobal g_searcher_global;
// }
namespace mate {
    PNSearcherGlobal g_mate_solver_global;
}
// namespace selfplay {
// SelfPlayWorker g_selfplay_worker[SelfPlayWorker::NUM];
// int g_thread_counter;
// SelfPlayInfo g_selfplay_info;
// }

// namespace review {
// ReviewBuffer g_review_buffer;
// }
// namespace model {
// GPUModel g_gpu_model[GPUModel::GPU_NUM];
// }
int main(int /*argc*/, char **/*argv*/){
    //auto num = 999999999;
    /*std::string sfen_str = "";
    if (argc > 1) {
        //num = std::stoi(std::string(argv[1]));
        sfen_str = std::string(argv[1]);
    }*/
    check_mode();
    attack::init();
    game::init();
    hash::init();

    test::test_hash();
    
    test::test_pn();

    //test::test_attack();
    //test::test_game();
    //test::test_mate();
    //test::test_mate1();
    test::test_gen();
    
    //gen::test_gen();
    //mate::test_mate();
    //attack::test_attack();
    //gen::test_gen3();
    //oracle::g_oracle.load();
    //model::g_gpu_model[0].load_model(0);
    //model::test_oracle_model();
    //selfplay::execute_selfplay(num);
    //review::test_review();
    //model::test_model();
    return 0;
}