#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <numeric>
#include <iterator>

/*
Given a set of positive numbers, find if we can partition it into two subsets such that the sum of elements in both subsets is equal.

*/

class PartitionSet {
public:
	bool canPartition(const std::vector<int> &num) {
		auto total_sum = std::accumulate(num.begin(), num.end(), 0);

		auto should_be_sum = total_sum / 2;

		auto num_sorted(num);

		std::sort(num_sorted.begin(), num_sorted.end());
		
		std::vector<std::vector<bool>> states(num.size(), std::vector<bool>(should_be_sum, false));

		for (int i = 0; i < states[0].size(); i++) {
			states[0][i] = (num.at(0) - (i + 1)) == 0;
		}

		for (int i = 1; i < states.size(); i++) {
			auto subsum = i;

			auto prev_state = i - 1;

			std::vector<int> set_of_subsums;

			for (auto it = states.at(prev_state).begin(); it != states.at(prev_state).end(); it++) {
				if(*it == true)
					set_of_subsums.push_back(std::distance(states.at(prev_state).begin(), it) + 1);
			}

			states.at(i) = states.at(prev_state);

			for (auto subsum : set_of_subsums) {
				if(subsum - 1 + num.at(i) < states[0].size())
				 states.at(i).at(subsum - 1 + num.at(i)) = true;
			}
		}

		/*
			     1  2  3  4  5  6  7  8
			{1}  T  F  F  F  F  F  F  F
 		     {1, 1}  T  T  F  F  F  F  F  F 
	          {1, 1, 3}  T  T  T  T  T  F  F  F
               {1, 1, 3, 4}  T
            {1, 1, 3, 4, 7}  T
		*/

		return states.back().back();
	}
};

int main(int argc, char *argv[]) {
	PartitionSet ps;
	std::vector<int> num = { 1, 2, 3, 4 };
	std::cout << ps.canPartition(num) << std::endl;
	num = std::vector<int>{ 1, 1, 3, 4, 7 };
	std::cout << ps.canPartition(num) << std::endl;
	num = std::vector<int>{ 2, 3, 4, 6 };
	std::cout << ps.canPartition(num) << std::endl;
}
