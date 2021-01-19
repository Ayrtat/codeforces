#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <bitset>
#include <iterator>

int findOnlyOnceEntrance(const std::string& str) {
    int N = str.size();

    std::map<std::string, int> length_map;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            const auto& sub_str = std::string(str.begin() + i, str.begin() + j);

            if(length_map.count(sub_str)) {
                length_map[sub_str]++;
            } else {
                length_map[sub_str] = 1;
            }
        }
    }

    int result = std::numeric_limits<int>::max();

    for(auto&& key_val : length_map) {
        if(key_val.second == 1) {
            if(result > key_val.first.length()) {
                result = key_val.first.length();
                std::cout << key_val.first << std::endl;
            }
        }
    }

    return result;
}

int main()
{

    std::set<char> letters = {'a', 'g', 't', 'c'};
    std::string L1 = "aacc";
    std::string L2 = "aaaaaccacacgacgacgtacgcgacg";
    std::string L3 = "cgcagttactgttttatacaacagcatagattcgagcc";

    std::cout << findOnlyOnceEntrance(L1) << std::endl;
    std::cout << findOnlyOnceEntrance(L2) << std::endl;
    std::cout << findOnlyOnceEntrance(L3) << std::endl;

    return 0;
}
