#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <bitset>

int main()
{
    int lower_limit = 500;
    int upper_limit = 700;

    int count = 0;

    std::vector<std::vector<int>> ingr = {
            {2, 100},
            {3, 50},
            {2, 200}};

    std::vector<int> reffer_to;
    std::set<std::multiset<int>> poses;

    for(int i = 0; i < ingr.size(); i++) {
        int value = ingr[i][0];
        while (value--) {
            reffer_to.push_back(i);
        }
    }


    int into_power = 0;

    for(auto & i : ingr) {
        into_power += i[0];
    }

    auto combs = std::pow(2, into_power);

    for (int i = 0; i < combs; i++) {
        auto bit_set = std::bitset<8>(i).to_string();

        auto it = std::find(bit_set.begin(), bit_set.end(), '1');
        std::string reduced(it, bit_set.end());

        int sum = 0;

        std::multiset<int> positions;

        for(auto it = std::rbegin(reduced); it != std::rend(reduced); it++) {
            if(*it == '1') {
                int pos = std::distance(std::rbegin(reduced), it);

                sum += ingr[reffer_to[pos]][1];
                positions.insert(reffer_to[pos]);
            }
        }

        if(sum >= lower_limit && sum <= upper_limit) {
            if(poses.count(positions) == 0) {
                count++;
                poses.insert(positions);
            }
        }
    }

    std::set<std::set<int>> pizzas;

    for(auto pos : poses) {
        std::set<int> pizza_kind_set(pos.begin(), pos.end());
        pizzas.insert(pizza_kind_set);
    }

    std::cout << pizzas.size();

    return 0;
}
