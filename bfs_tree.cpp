/*
 * bfs_tree.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: arifullin_ayrat
 */


#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <sstream>
#include <set>

int main()
{
	std::string input_string;
	std::getline(std::cin, input_string);
	std::stringstream input_as_string_stream{ input_string };

	int test_cases;
	input_as_string_stream >> test_cases;

	while(test_cases--) {
		input_as_string_stream.clear();
		std::getline(std::cin, input_string);
		input_as_string_stream.str(input_string);

		int N, M, K;
		input_as_string_stream >> N;
		input_as_string_stream >> M;
		input_as_string_stream >> K;

		std::getline(std::cin, input_string);
		int C = std::stoi(input_string);

		std::vector<std::vector<std::tuple<int, int, int>>> Graph(N, std::vector<std::tuple<int, int, int>>(N));
		std::map<int, std::set<int>> adjacent_with;


		while(M--) {
			std::getline(std::cin, input_string);
			input_as_string_stream.str(input_string);

			int fromNode, toNode, a, b, k;

			input_as_string_stream >> fromNode;
			input_as_string_stream >> toNode;
			input_as_string_stream >> a; //ax + b
			input_as_string_stream >> b;
			input_as_string_stream >> k;

			Graph[fromNode-1][toNode-1] = std::make_tuple(a, b, k);
			adjacent_with[fromNode-1].insert(toNode-1);
		}

		std::deque<std::tuple<int, int, int, int>> q = { std::make_tuple(0, K, C, 0) };
		std::deque<std::tuple<int, int, int, int>> result;

		while(!q.empty())
		{
			auto curr { q.front() };
			q.pop_front();
			auto& adjacent_nodes = adjacent_with[std::get<0>(curr)];

			for(const auto& node : adjacent_nodes) {
				auto tuple { Graph[std::get<0>(curr)][node] };

				auto a = std::get<0>(tuple); auto b = std::get<1>(tuple); auto k = std::get<2>(tuple);

				auto x = std::get<2>(curr);
				auto _k = std::get<1>(curr);
				auto total = std::get<3>(curr);


				auto after_pass = a * x + b;
				auto k_diff = _k - k;
				total += after_pass;

				if(k_diff > 0)
				{
					auto add_node = std::make_tuple(node, k_diff, after_pass, total);
					q.push_back(add_node);
				}

				if(k_diff == 0 && node == N-1)
					result.push_back( std::make_tuple(node, k_diff, after_pass, total));
			}
		}
	}


	return 0;
}
