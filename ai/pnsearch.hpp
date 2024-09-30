#ifndef __PNSEARCH_HPP__
#define __PNSEARCH_HPP__

#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>
#include "common.hpp"
#include "util.hpp"
#include "game.hpp"
#include "movecheck.hpp"
#include "moveevasion.hpp"
#include "mate1.hpp"

namespace mate {

enum PNNodeState : int8 {
    PNNodeWin = 1,
    PNNodeLose = 2,
    PNNodeTimeOut = 3,
    PNNodeUnknown = -1
};

enum PNNodeType : int {
    PN_OR = 0,
    PN_AND = 1,
};

static const uint32 PN_MAX = 0xFFFFFFF;

constexpr PNNodeType change_nodetype(const PNNodeType nt) {
    return static_cast<PNNodeType>(static_cast<int>(nt) ^ 1);
}

std::string node_state_str(const PNNodeState n) {
    switch (n) {
        case PNNodeWin:
            return "NODE_WIN";
        case PNNodeLose:
            return "NODE_LOSE";
        case PNNodeUnknown:
            return "NODE_UNKNOWN";
        default:
            return "ERROR_NODE_STATE";
    }
}
std::ostream& operator<<(std::ostream& os, const PNNodeState n) {
    os << node_state_str(n);
    return os;
}
class Node {
public:
    Node() : child_nodes(nullptr),
             parent_move(MOVE_NONE),
             best_move(MOVE_NONE),
             state(PNNodeUnknown),
             pn(1),
             dn(1),
             n(0),
             child_len(-1),
             ply(-1){}
   Node( const Node & ) = delete ;
   Node & operator = ( const Node & ) = delete ;
   Node & operator = ( const Node && n) = delete;
    void init() {
        this->n = 0;
        this->parent_move = this->best_move = MOVE_NONE;
        this->child_len = -1;
        this->child_nodes = nullptr;
        this->ply = 0;
        this->state = PNNodeUnknown;
        this->pn = this->dn = 1;
    }
    bool is_resolved() const {
        return state != PNNodeUnknown;
    }
    bool is_win() const {
        return state == PNNodeWin;
    }
    bool is_lose() const {
        return state == PNNodeLose;
    }
    bool is_terminal() const {
        return child_len == -1;
    }

    std::string str(const bool is_root = true) const {
        const std::string padding = is_root ? "" :"        ";
        std::string str = "---------------------------\n";
        if (is_root) { str += pos.str(); }
        str += padding + "n:" + to_string(n) + "\n";
        str += padding + "child_len:" + to_string(child_len) + "\n";
        str += padding + "ply:" + to_string(ply) + "\n";
        str += padding + "parent_move:" + move_str(parent_move) + "\n";
        str += padding + "best_move:" + move_str(best_move) + "\n";
        str += padding + "state:" + to_string(state) + "\n";
        str += padding + "pn:"+to_string(pn) + " : dn:" + to_string(dn) + "\n"; 
        str += "---------------------------\n";
        if (is_root && !this->is_terminal()) {
            str += "child\n";
            REP(i, this->child_len) {
                str += "no:" + to_string(i) + "\n";
                ASSERT(i>=0);
                ASSERT(i<this->child_len);
                auto child = this->child(i);
                str += child->str(false);
            }
        }
        return str;
    }
    Node* child(const int index) const {
        ASSERT(index < child_len);
        ASSERT(index >= 0);
        return child_nodes[index].get();
    }
    void set_win() {
        this->pn = 0;
        this->dn = PN_MAX;
        this->state = PNNodeWin;
    }
    void set_lose() {
        this->pn = PN_MAX;
        this->dn = 0;
        this->state = PNNodeLose;
    }
    game::Position pos;
    std::unique_ptr<std::unique_ptr<Node>[]> child_nodes;
    Move parent_move;
    Move best_move;
    PNNodeState state;
    uint32 pn;
    uint32 dn;
    int n;
    int child_len;
    int ply;
};
class PNSearcherGlobal;

class PNSearcherLocal {
public:
    PNSearcherLocal(int id, PNSearcherGlobal * global) : 
                     global(global),
                     thread(nullptr),
                     thread_id(id){
                
    }
    template<Color turn> void search(const uint32 simulation_num);
    bool is_ok();
    void run();
    void join();
protected:
    template<Color turn, PNNodeType node_type> void evaluate(Node *node);
    template<Color turn, PNNodeType node_type> void expand(Node *node);
    template<PNNodeType node_type> Node *next_child(const Node *node) const;
    template<PNNodeType node_type> void update_node(Node *node);
    bool interrupt(const uint32 current_num, const uint32 simulation_num) const;
    Node *root_node() const ;

    PNSearcherGlobal *global;
    std::thread *thread;
    int thread_id;
};

class PNSearcherGlobal {
public:
    PNSearcherGlobal() :
                       THREAD_NUM(1){}
    PNSearcherGlobal(const int thread_num) : 
                       THREAD_NUM(thread_num){}
    Node root_node;
    void init();
    void clear_tree();
    void run();
    void join();
    void choice_best_move();

    int THREAD_NUM;
protected:
    std::vector<PNSearcherLocal> worker;
};

extern PNSearcherGlobal g_mate_solver_global;

Move think(game::Position &pos) {
    ASSERT(g_mate_solver_global.root_node.n == 0);
    g_mate_solver_global.root_node.pos = pos;
    g_mate_solver_global.run();
    g_mate_solver_global.join();
    g_mate_solver_global.choice_best_move();
    return g_mate_solver_global.root_node.best_move;
}

Node *PNSearcherLocal::root_node() const {
    return &this->global->root_node;
}

void PNSearcherGlobal::init() {
    this->worker.clear();
    this->worker.shrink_to_fit();
    REP(i, PNSearcherGlobal::THREAD_NUM) {
        this->worker.emplace_back(i,this);
    }
    this->clear_tree();
}

void PNSearcherGlobal::clear_tree() {
    this->root_node.init();
}

void PNSearcherGlobal::run() {
    REP(i, PNSearcherGlobal::THREAD_NUM) {
        this->worker[i].run();
    }
}

void PNSearcherGlobal::join() {
    REP(i, PNSearcherGlobal::THREAD_NUM) {
        this->worker[i].join();
    }
}

void PNSearcherGlobal::choice_best_move() {
    if (this->root_node.is_lose()) {
        this->root_node.best_move = MOVE_NONE;
    } else if (!this->root_node.is_resolved()){
        this->root_node.best_move = MOVE_NONE;
        this->root_node.state = PNNodeTimeOut;
    }
}

void PNSearcherLocal::run() {
	this->thread = new std::thread([this]() {
        if (g_mate_solver_global.root_node.pos.turn() == BLACK) {
            this->search<BLACK>(int(2000 / this->global->THREAD_NUM));
        } else {
            this->search<WHITE>(int(2000 / this->global->THREAD_NUM));
        }
    });
}
void PNSearcherLocal::join() {
    this->thread->join();
    delete this->thread;
}

bool PNSearcherLocal::interrupt(const uint32 current_num, const uint32 simulation_num) const {
    if (this->root_node()->is_resolved()) {
        return true;
    }
    if (current_num >= simulation_num) {
        return true;
    }
    return false;
}

template<Color turn>void PNSearcherLocal::search(const uint32 simulation_num) {
    
    const auto is_out = false;
    for(auto i = 0u ;; ++i) {
        Tee<<"start simulation:" << i <<"/"<<simulation_num<<"\r";
        const auto interrupt = this->interrupt(i, simulation_num);
        if (interrupt) {
            break;
        }
        this->evaluate<turn,PN_OR>(this->root_node());
        if (is_out) {
            Tee<<this->root_node()->str()<<std::endl;
        }
    }
    if (is_out) {
        Tee<<this->root_node()->str()<<std::endl;
    }
}

template<Color turn, PNNodeType node_type>void PNSearcherLocal::evaluate(Node *node) {

    ASSERT(node != nullptr);
    ASSERT(node->pos.is_ok());
    node->n++;

    if (node->is_resolved()) {
        //Tee<<node->str()<<std::endl;
        //ASSERT(false);
        return;
    }
    if (node->is_terminal()) {
        this->expand<turn,node_type>(node);
    } else {
        auto next_node = this->next_child<node_type>(node);
        this->evaluate<change_turn(turn),change_nodetype(node_type)>(next_node);
    }
    this->update_node<node_type>(node);
}

template<Color turn,PNNodeType node_type> void PNSearcherLocal::expand(Node *node) {
    ASSERT(node->pos.is_ok());

    auto moveList = movelist::MoveList();
    if (node_type == PN_OR) {
        gen::gen_check_moves<turn>(node->pos, moveList);
    } else {
        gen::gen_evasion_moves<turn>(node->pos, moveList);
    }
    constexpr auto next_node_type = change_nodetype(node_type);
    constexpr auto next_turn = change_turn(turn);

    node->child_len = moveList.len();
    node->child_nodes = std::make_unique<std::unique_ptr<Node>[]>(node->child_len);
    REP(i, node->child_len) {
        auto next_pos = node->pos.next(moveList[i]);
        ASSERT(next_pos.is_ok());

        node->child_nodes[i] = std::make_unique<Node>();
        auto next_node = node->child_nodes[i].get();
        next_node->pos = next_pos;
        next_node->ply = node->ply+1;
        next_node->parent_move = moveList[i];
        if (next_pos.is_draw()) {
            next_node->set_lose();
        } else {
            if (next_node_type == PN_OR) {
                if (!attack::in_checked(next_pos)) {
                    const auto mv = mate1::mate1<next_turn>(next_pos);
                    if (mv != MOVE_NONE) {
                        next_node->set_win();
                    }
                }
            } 
        }
        
    }
}

template<PNNodeType node_type> Node *PNSearcherLocal::next_child(const Node *node) const {
    ASSERT(node->child_len >= 0);
    ASSERT(node->pos.is_ok());
    Node *best_child = nullptr;
    uint32 best_score = PN_MAX + 1;
    REP(i, node->child_len) {

        auto child = node->child(i);
        ASSERT(child->pos.is_ok());
        auto score = (node_type == PN_OR) ? child->pn : child->dn;
        if (score < best_score) {
            best_score = score;
            best_child = child;
        } 
    }
    ASSERT2(best_child != nullptr, {
        Tee<<"next_child error\n";
        Tee<<node->str();
    });
    return best_child;
}

template<PNNodeType node_type>void PNSearcherLocal::update_node(Node *node) {
    ASSERT(node->pos.is_ok());

    const auto child_len = node->child_len;
    uint32 best_score = PN_MAX+1;
    Move best_move = MOVE_NONE;
    if (node_type == PN_OR) {
        node->pn = PN_MAX;
        node->dn = 0;
        REP(i, child_len) {
            auto child = node->child(i);
            node->pn = std::min(node->pn,child->pn);
            node->dn += child->dn; 

            node->pn = std::min(node->pn,PN_MAX);
            node->dn = std::min(node->dn,PN_MAX);
            if (child->pn < best_score) {
                best_score = child->pn;
                best_move = child->parent_move;
            }
        }
    } else {
        node->pn = 0;
        node->dn = PN_MAX;
        REP(i, child_len) {
            auto child = node->child(i);
            node->pn += child->pn;
            node->dn = std::min(node->dn,child->dn);
            
            node->pn = std::min(node->pn,PN_MAX);
            node->dn = std::min(node->dn,PN_MAX);
            if (child->dn < best_score) {
                best_score = child->dn;
                best_move = child->parent_move;
            }
        }
    }
    if (node->pn == 0) {
        node->state = PNNodeWin;
    } else if (node->dn == 0) {
        node->state = PNNodeLose;
    }
    node->best_move = best_move;
}


}
#endif