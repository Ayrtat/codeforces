#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>
#include <set>

std::vector<std::vector<int>> mapOfSold{
	/*{5, 5, 1, 4, 4},
	{4, 0, 2, 4, 2},
	{5, 0, 0, 2, 0},
	{5, 4, 3, 0, 1},
	{1, 3, 3, 2, 1}*/

	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{5, 0, 5, 0, 5, 0, 5},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0}
};

std::map<char, int> lengthOfMark;
std::map<char, int> markCorrespondsTo;
std::set<std::set<std::pair<int, int>>> zeroAreas;

std::vector<std::vector<char>> traverseTheMap(std::vector<std::vector<int>> the_map) {
	std::set<std::pair<int, int>> visited;
	std::vector<std::vector<char>> markedMap(std::size(mapOfSold), std::vector<char>(std::size(mapOfSold)));
	char mark = 'a';

	std::deque< std::pair<int, int> > q;

	for (int i = 0; i < std::size(the_map); i++) {
		for (int j = 0; j < std::size(the_map); j++) {
			if (visited.count(std::make_pair(i, j)) == 0) {
				q.push_back(std::make_pair(i, j));
				visited.insert(q.back());
			}
			else {
				continue;
			}

			std::set<std::pair<int, int>> onDigit;
			
			while (!q.empty()) {
				auto the_pair = q.front();
				onDigit.insert(the_pair);
				q.pop_front();

				if (the_pair.second < std::size(the_map) - 1 &&
					visited.count(std::make_pair(the_pair.first, the_pair.second + 1)) == 0 &&
					the_map[the_pair.first][the_pair.second + 1] == the_map[the_pair.first][the_pair.second]) {
					q.push_back(std::make_pair(the_pair.first, the_pair.second + 1));
					visited.insert(q.back());
					
				}

				if (the_pair.first < std::size(the_map) - 1 &&
					visited.count(std::make_pair(the_pair.first + 1, the_pair.second)) == 0 &&
					the_map[the_pair.first + 1][the_pair.second] == the_map[the_pair.first][the_pair.second]) {
					q.push_back(std::make_pair(the_pair.first + 1, the_pair.second));
					visited.insert(q.back());
				}
			}

			for (auto& coordPair : onDigit) {
				markedMap[coordPair.first][coordPair.second] = mark;
			}

			auto beginOf = std::begin(onDigit);
			markCorrespondsTo[mark] = the_map[beginOf->first][beginOf->second];
			if (the_map[beginOf->first][beginOf->second] == 0) {
				zeroAreas.insert(std::set<std::pair<int, int>>(std::begin(onDigit), std::end(onDigit)));
			}

			lengthOfMark[mark] = onDigit.size();

			mark++;
		}
	}
	return markedMap;
}

void neighborOfZeroAreas(std::vector<std::vector<char>>&& marked) {
	for (auto& set_of : zeroAreas) {
		std::set<char> neighborMarks;

		for (auto& pair_within : set_of) {
			auto i = pair_within.first;
			auto j = pair_within.second;

			if (i > 0) {
				neighborMarks.insert(marked[i - 1][j]);
			}

			if (j > 0) {
				neighborMarks.insert(marked[i][j - 1]);
			}

			if (i < std::size(mapOfSold) - 1) {
				neighborMarks.insert(marked[i + 1][j]);
			}

			if (j < std::size(mapOfSold) - 1) {
				neighborMarks.insert(marked[i][j + 1]);
			}
		}

		std::map<int, int> lengthOfNeighbors{
			{1, 0},
			{2, 0},
			{3, 0},
			{4, 0},
			{5, 0}
		};
		
		for (auto& n : neighborMarks) {
			lengthOfNeighbors[markCorrespondsTo[n]] += lengthOfMark[n];
		}

		int max = 0;
		int replaceOn = -1;
		for (int i = 1; i <= 5; i++) {
			if (lengthOfNeighbors[i] >= max) {
				max = lengthOfNeighbors[i];
				replaceOn = i;
			}
		}

		for (auto& pair_within : set_of) {
			auto i = pair_within.first;
			auto j = pair_within.second;

			mapOfSold[i][j] = replaceOn;
		}
	}
}

int main()
{
	neighborOfZeroAreas(traverseTheMap(mapOfSold));

	lengthOfMark.clear();
	markCorrespondsTo.clear();

	auto m = traverseTheMap(mapOfSold);

	std::cout << std::size(lengthOfMark);

	return 0;
}
