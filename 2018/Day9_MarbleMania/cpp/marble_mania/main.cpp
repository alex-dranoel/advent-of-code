#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <deque>

#define c_auto const auto
#define all(v) std::begin(v), std::end(v)
#define c_all(v) std::cbegin(v), std::cend(v)

template <typename T>
void rotate(typename std::list<T>::iterator &it, int n, std::list<T> &list) {
    if (n == 0) return;
    auto inc {n>0};
    n = std::abs(n);
    auto edge {inc ? list.end() : list.begin()};
    auto roll {inc ? list.begin() : list.end()};
    for (int counter{0}; counter < n; ++counter) {
        if (inc) ++it;
        if (it == edge) it = roll;
        if (!inc) --it;
    }
}

template <typename T>
void erase_rotate(typename std::list<T>::iterator &it, std::list<T> &list) {
    it = list.erase(it);
    if (it == list.end()) {
        it = list.begin();
    }
}

template <typename T>
void insert_rotate(typename std::list<T>::iterator &it, T& val, std::list<T> &list) {
    it = list.insert(it, val);
}

long long play_game_list(int n_player, int n_marble) {
    std::vector<long long> player_scores(n_player, 0);
    std::list<long long> board;

    board.push_front(0);
    auto current {board.begin()};

    for (long long marble {1}; marble <= n_marble; ++marble) {
        if (marble % 23 == 0) {
            rotate(current, -7, board);
            player_scores[(marble - 1) % n_player] += marble + *current;
            erase_rotate(current, board);
        } else {
            rotate(current, 2, board);
            insert_rotate(current, marble, board);
        }
    }

    auto pr { std::max_element(c_all(player_scores)) };
    return *pr;
}

void rotate(std::deque<long long>& board, int n) {
    if (n == 0) return;
    if (n > 0) {
        for (int i {0}; i < n; ++i) {
            auto tmp = board.front();
            board.pop_front();
            board.push_back(tmp);
        }
    } else {
        for (int i {0}; i < -n; ++i) {
            auto tmp = board.back();
            board.pop_back();
            board.push_front(tmp);
        }
    }
}

long long play_game_deque(int n_player, int n_marble) {
    std::vector<long long> player_scores(n_player, 0);
    std::deque<long long> board;

    board.push_back(0);
    for (long long marble {1}; marble <= n_marble; ++marble) {
        if (marble % 23 == 0) {
            //std::rotate(board.rbegin(), board.rbegin() + 7, board.rend());
            rotate(board, -7);
            player_scores[(marble - 1) % n_player] += marble + board.back();
            board.pop_back();
            //std::rotate(board.begin(), board.begin() + 1, board.end());
            rotate(board, 1);
        } else {
            //std::rotate(board.begin(), board.begin() + 1, board.end());
            rotate(board, 1);
            board.push_back(marble);
        }
    }

    auto pr { std::max_element(c_all(player_scores)) };
    return *pr;
}

void part_one(bool use_deque=true) {
    constexpr int n_player {441};
    constexpr int last_marble {71032};

    auto highest_score {use_deque ? play_game_deque(n_player, last_marble) : play_game_list(n_player, last_marble)};
    std::cout << "Part 1: " << highest_score << std::endl;
}

void part_two(bool use_deque=true) {
    constexpr int n_player {441};
    constexpr int last_marble {7103200};

    auto highest_score {use_deque ? play_game_deque(n_player, last_marble) : play_game_list(n_player, last_marble)};
    std::cout << "Part 2: " << highest_score << std::endl;
}

int main() {
    part_one();
    part_two();
    return 0;
}


