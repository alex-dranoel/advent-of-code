#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <optional>
#include <set>

template<typename T>
std::vector<T> load_data(const std::string& filename) {
    // load data into a vector<T>
    std::ifstream input_file(filename);
    using iter_t = std::istream_iterator<T>;
    std::vector<T> data(iter_t{input_file}, iter_t{});
    return data;
}

void part_one(const std::vector<int>& data) {
    // sum up all the data
    int sum {std::accumulate(data.cbegin(), data.cend(), 0)};
    std::cout << "Part 1: " << sum << std::endl;
}

void part_two(const std::vector<int>& data) {
    // search first repeated cumulative by using set property
    std::set<int> set{};
    int frequency {0};
    std::optional<int> repeated_frequency {};
    while (!repeated_frequency) {
        for (auto i : data) {
            frequency += i;
            if (auto [iter, inserted] = set.insert(frequency); !inserted) {
                repeated_frequency = frequency;
                break;
            }
        }
    }
    std::cout << "Part 2: " << repeated_frequency.value() << std::endl;
}

int main() {
    const auto data {load_data<int>("../../../input.txt")};
    part_one(data);
    part_two(data);
}
