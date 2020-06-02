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

		while (true)
		{
			long long radius = 1;

			auto j = -1;

			for (int i = 0; i < states.size() - 1; i++)
				if (states[i] == 0 && states[i + 1] == 1 && (i != states.size() - 2))
				{
					j = i + 1;
					break;
				}

			if (j == -1)
			{
				for (int i = 0; i < states.size() - 1; i++)
					if (states[i] == 1 && states[i + 1] == 0 && (i != 0))
					{
						j = i;
						break;
					}

				if (j == -1) break;
			}

			auto i = j;

			auto whichIndex = i;

			if (states[i] == 0)
				continue;

			while ((whichIndex - radius > -1) && (whichIndex + radius < elements.size()))
			{
				states[whichIndex - radius] = states[whichIndex + radius] = states[whichIndex];
				radius++;
			}

			i = whichIndex - radius + 1;
		}

		auto it = std::find(states.begin(), states.end(), 0);
		it == states.end() ? answers.push_back("yes") : answers.push_back("no");
	}

	std::copy(answers.begin(), answers.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

	return 0;
}