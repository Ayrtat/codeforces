#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <numeric>
#include <iomanip>
#include <numeric>
#include <deque>

int main()
{
	long long queries;
	std::cin >> queries;

	std::vector<std::string> answers;

	while (queries--)
	{
		long long numberOfElements, median;
		std::cin >> numberOfElements;
		std::cin >> median;

		std::vector<long long> elements;
		std::vector<long long> coincidence;

		while (numberOfElements--)
		{
			long long n; std::cin >> n;

			elements.push_back(n);
		}

		std::vector<long long> states(elements.size(), 0);

		for (long long i = 0; i < elements.size(); i++)
		{
			if (elements[i] == median)
			{
				states[i] = 1;
				coincidence.push_back(i);
			}
		}

		for (long long i = 0; i < states.size(); i++)
		{
			long long radius = 1;
			auto whichIndex = i;

			if (states[i] == 0)
				continue;

			while ((whichIndex - radius > -1) && (whichIndex + radius < elements.size()))
			{
				states[whichIndex - radius] = states[whichIndex + radius] = states[whichIndex];
				radius++;
			}
		}

		auto it = std::find(states.begin(), states.end(), 0);
		it == states.end() ? answers.push_back("yes") : answers.push_back("no");
	}

	std::copy(answers.begin(), answers.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

	return 0;
}