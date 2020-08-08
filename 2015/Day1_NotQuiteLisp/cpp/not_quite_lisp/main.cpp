#include <iostream>
#include <fstream>
#include <string_view>
#include <numeric>
#include <vector>
#include <algorithm>
#include <optional>

#define all(v) std::begin(v), std::end(v)

void part_one(std::string_view instructions) {
    int floor {0};
    for (auto ch: instructions) {
        floor += ch == '(' ? 1 : -1;
    }
    std::cout << "Part 1: " << floor << std::endl;
}

void part_two_from_one(std::string_view instructions) {
    int floor {0};
    int counter {0};
    for (auto ch: instructions) {
        counter++;
        floor += ch == '(' ? 1 : -1;
        if (floor < 0) break;
    }
    std::cout << "Part 2: " << counter << std::endl;
}

void part_two(std::string& instructions) {
    int floor {0}, counter{0};
    while (floor >= 0) {
        floor += instructions[counter++] == '(' ? 1 : -1;
    }
    std::cout << "Part 2: " << counter << std::endl;
}

void combo_part_one_and_two(std::string_view instructions) {
    int floor {0};
    std::optional<int> index {std::nullopt};
    for (int i {0}; i < instructions.size(); ++i) {
        floor += instructions[i] == '(' ? 1 : -1;
        if (floor == -1 && !index) {
            index = i + 1;
        }
    }
    std::cout << "Part 1: " << floor << std::endl;
    std::cout << "Part 2: " << index.value() << std::endl;
}

void combo_part_one_and_two_stl(std::string_view instructions) {
    std::vector<int> partial_sum;
    partial_sum.reserve(instructions.size());
    std::transform(all(instructions), std::back_inserter(partial_sum), [](char ch) {return ch=='('?1:-1;});
    std::partial_sum(all(partial_sum), std::begin(partial_sum));
    std::cout << "Part 1: " << partial_sum.back() << std::endl;
    std::cout << "Part 2: " << 1 + std::distance(std::begin(partial_sum), std::find(all(partial_sum), -1)) << std::endl;
}

int main() {

    std::ifstream input_file {"../../../input.txt"};
    std::string line;
    input_file >> line;

    part_one(line);
    part_two_from_one(line);
    part_two(line);

    combo_part_one_and_two(line);
    combo_part_one_and_two_stl(line);

    return 0;
}
