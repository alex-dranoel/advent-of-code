#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <string_view>

#define c_auto const auto
#define all(v) v.begin(), v.end()
#define c_all(v) v.cbegin(), v.cend()

template<typename T>
std::vector<T> load_data(const std::string& filename) {
    // load data into a vector<T>
    std::ifstream input_file(filename);
    using iter_t = std::istream_iterator<T>;
    std::vector<T> data(iter_t{input_file}, iter_t{});
    return data;
}

class WordType {
    bool two, three;

    [[nodiscard]]
    static auto value_is(int value) {
        return [=](c_auto& v) { return v.second == value; };
    }

public:
    WordType(bool two, bool three): two{two}, three{three} {}

    [[nodiscard]]
    static WordType from_str(std::string_view str) {
        std::map<char, int> freqs{};
        std::for_each(c_all(str), [&](auto c) {++freqs[c - 'a'];});
        auto two { std::any_of(c_all(freqs), value_is(2)) };
        auto three { std::any_of(c_all(freqs), value_is(3)) };
        return WordType{two, three};
    }

    [[nodiscard]]
    static WordType from_str_using_sort(std::string str) {
        std::sort(all(str));
        char prev_ch {'\0'};
        int count {1}, two_letters {0}, three_letters {0};
        for (c_auto current_ch: str) {
            if (prev_ch == current_ch) {
                switch (++count) {
                    case 2:
                        ++two_letters;
                        break;
                    case 3:
                        --two_letters;
                        ++three_letters;
                        break;
                    case 4:
                        --three_letters;
                }
            } else if (two_letters == 1 && three_letters == 1) {
                // if prev_ch and current_ch are different, and we have already
                // found a two-consecutive and a three-consecutive char, then we can break;
                break;
            } else {
                prev_ch = current_ch;
                count = 1;
            }
        }
        return WordType{two_letters > 0, three_letters > 0};
    }

    [[maybe_unused, nodiscard]]
    inline bool is_two() const {
        return two;
    }

    [[maybe_unused, nodiscard]]
    inline bool is_three() const {
        return three;
    }
};

template <typename Transformer>
void part_one(const std::vector<std::string>& data, Transformer transformer) {
    std::vector<WordType> words;
    words.reserve(data.size());
    std::transform(c_all(data), std::back_inserter(words), transformer);

    c_auto two_count { std::count_if(c_all(words), [](const auto& w) {return w.is_two();}) };
    c_auto three_count { std::count_if(c_all(words), [](const auto& w) {return w.is_three();}) };

    std::cout << "Part 1: " << two_count * three_count << std::endl;
}

void part_two(const std::vector<std::string>& data) {
    auto base {data.begin()};
    c_auto last {data.end()};
    std::string searched_box_id{};

    while (base != last) {
        auto next {base};
        auto base_str {*next};
        while (++next != last) {
            c_auto& test_str{ *next };
            int ndiff {0}, k_at_diff{0};
            for (auto k{0}; k < base_str.size(); ++k) {
                if (base_str[k] != test_str[k]) {
                    ++ndiff;
                    k_at_diff = k;
                }
                if (ndiff > 1) {
                    break;
                }
            }
            if (ndiff == 1) {
                searched_box_id = base_str.erase(k_at_diff, 1);
                break;
            }
        }
        ++base;
    }

    std::cout << "Part 2: " << searched_box_id << std::endl;
}

int main() {
    c_auto data { load_data<std::string>("../../../input.txt") };
    part_one(data, &WordType::from_str);
    part_one(data, &WordType::from_str_using_sort);
    part_two(data);
}