#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <map>

#define c_auto const auto
#define all(v) v.begin(), v.end()
#define c_all(v) v.cbegin(), v.cend()

using Square = std::tuple<int, int>;
using Id = int;
using ClaimsMap = std::map<Square, std::vector<Id>>;

std::vector<std::string> load_lines(const std::string& filename) {
    // load data into a vector<T>
    std::ifstream input_file(filename);
    std::vector<std::string> data;
    std::string line;
    while (std::getline(input_file, line)) {
        data.push_back(line);
    }
    return data;
}

struct Claim {
    Id id;
    int x, y, w, h;

    Claim(Id id, int x, int y, int w, int h): id{id}, x{x}, y{y}, w{w}, h{h} {}

    [[nodiscard]]
    static Claim from_str(std::string& str) {
        Id id;
        int x, y, w, h;
        sscanf(str.data(), "#%d @ %d,%d: %dx%d", &id, &x, &y, &w, &h);
        return Claim{id, x, y, w, h};
    };
    std::vector<Square> squares() const {
        std::vector<Square> squares;
        squares.reserve(h * w);
        for (int i {y}; i < y + h; ++i) {
            for (int j {x}; j < x + w; ++j) {
                squares.emplace_back(j, i);
            }
        }
        return squares;
    }

};


ClaimsMap make_claims_map(const std::vector<Claim>& claims) {
    ClaimsMap claims_map;

//    // Using for_each and lambdas, in this case, does not
//    // look much better than range-based for loops.
//    std::for_each(c_all(claims), [&](c_auto &claim) {
//        auto squares {claim.squares()};
//        std::for_each(c_all(squares), [&](c_auto &parcel) {
//            claims_map[parcel].push_back(claim.id);
//        });
//    });

    // Using range-based for loops, in this case, this looks better
    for (c_auto &claim: claims) {
        for (c_auto &square: claim.squares()) {
            claims_map[square].push_back(claim.id);
        }
    }
    return claims_map;

}

void part_one(const ClaimsMap& claims_map) {
//    // Counting how many squares have more than one Id, using accumulate,
//    // structured binding not available for lambda params
//    auto n_overlapping{std::accumulate(c_all(claims_map), 0, [](auto &sum, c_auto &entry) {
//        return sum += entry.second.size() > 1;
//    })};
//    std::cout << "Part 1: " << n_overlapping << std::endl;

    // Counting how many squares have more than one Id, using range-based for loops,
    // and the structured binding C++17 feature for map entries.
    auto n_overlapping{0};
    for (c_auto& [square, ids]: claims_map) {
        n_overlapping += ids.size() > 1;
    }
    std::cout << "Part 1: " << n_overlapping << std::endl;

}

void part_two(ClaimsMap& claims_map, const std::vector<Claim>& claims) {
    // Find the claim for which all its squares have only one owner (it-self)
    // using STL algo find_if and all_of. With the help of the c_all and c_auto
    // macros, the code looks nice
    auto claim_it {std::find_if(c_all(claims), [&](c_auto& claim) {
        auto squares {claim.squares()};
        return std::all_of(c_all(squares), [&](c_auto& square) {
            return claims_map[square].size() == 1;
        });
    })};
    std::cout << "Part 2: " << (claim_it != claims.cend() ? std::to_string(claim_it->id) : "not found") << std::endl;


//    // Find the claim for which all its squares have only one owner (it-self)
//    // using range-based for loops. The use of the flag and two breaks do not
//    // make the code very sexy here. Note the std::optional in case no such
//    // claim exist.
//    std::optional<int> claim_id {};
//    for (c_auto &claim: claims) {
//        auto overlap {false};
//        for (c_auto &parcel: claim.squares()) {
//            overlap = claims_map[parcel].size() > 1;
//            if (overlap) break;
//        }
//        if (!overlap) {
//            claim_id = claim.id;
//            break;
//        }
//    }
//    std::cout << "Part 2: " << (claim_id ? std::to_string(claim_id.value()) : "not found") << std::endl;

}
int main() {
    auto data { load_lines("../../../input.txt") };

    // convert data to vector of Claim objects using their from_str method
    std::vector<Claim> claims;
    claims.reserve(data.size());
    std::transform(all(data), std::back_inserter(claims), &Claim::from_str);

    ClaimsMap claims_map {make_claims_map(claims)};
    part_one(claims_map);
    part_two(claims_map, claims);

    return 0;
}
