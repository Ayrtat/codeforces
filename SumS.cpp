#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <numeric>
#include <iterator>

/*
Imagine a game where a player can score 1, 2,1,2, or 44 runs. Given a score, nn, find the total number of ways to score nn runs.
For example, to score 33 runs, a player can score in the following 3 ways
*/

int scoring_options(int n) {
	std::vector<int> numbers(n);

	std::iota(numbers.begin(), numbers.end(), 1);
	std::reverse(numbers.begin(), numbers.end());

	std::vector<int> states(n);

	numbers.at(0) = 1;
	states.at(0) = 1;

	for (int i = 1; i < states.size(); i++) {
		states.at(i) = std::accumulate(numbers.begin(), numbers.begin() + i, 0);
	}

	return states.back();
}

int main() {
	int n = 5;
	std::cout << scoring_options(5);
	return 0;
}
