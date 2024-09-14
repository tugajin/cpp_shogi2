#ifndef __MOVELIST_HPP__
#define __MOVELIST_HPP__

#include "common.hpp"
#include "util.hpp"
namespace movelist {
class MoveList {
private:
    // そのうち将棋もやるので多めに
    static constexpr int MAX_LIST_SIZE = 600;
    Move moves[MAX_LIST_SIZE];
    Move *curr;
public:
    MoveList() {
        this->init();
    }
    void init() {
        this->curr = this->moves;
#if DEBUG
    REP(i,MAX_LIST_SIZE) {
        moves[i] = MOVE_NONE;
    }
#endif
    }
    int len() const {
        return this->curr - this->moves;
    }
    void add(const Move m) {
        ASSERT(len() < MAX_LIST_SIZE);
        (*this->curr++) = m;
    }
    Move* begin() {
        return this->moves;
    }
    Move* end() {
        return this->curr;
    }
	Move operator [] (const int i) const {
		return *(this->moves+i);
	}
    std::string str() const {
        std::string s;
        REP(i, this->len()) {
            s += padding_str(to_string(i),3) + ":" + move_str(this->moves[i]) +"\n";
        }
        return s;
    }
	friend std::ostream& operator<<(std::ostream& os,  const MoveList& ml) {
        os << ml.str();
		return os;
	}
    bool contain(const Move m) const {
        REP(i, this->len()) {
            if (this->moves[i] == m) {
                return true;
            }
        }
        return false;
    }
};
void test_move_list() {
    MoveList ml;
    ASSERT(ml.len() == 0);
    REP(i, 9) {
        const auto m = Move(i);
        ml.add(m);
        ASSERT2(ml.len() == i+1,{
            Tee<<"ml_len:"<<ml.len()<<std::endl;
            Tee<<"index:"<<i+1<<std::endl;
        });
        ASSERT(ml[i] == m);
    }
    ml.init();
    ASSERT(ml.len() == 0);
}
}
#endif