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
	int partNumber;
	std::cin >> partNumber;

	std::vector<long long> height;

	while (partNumber--)
	{
		long long num;
		std::cin >> num;
		height.push_back(num);
	}

	std::sort(height.begin(), height.end(), std::greater<int>());

	auto total = 0ll;

	if (height.size() == 0)
	{
		std::cout << total;
		return 0;
	}

	if (height.size() == 1)
	{
		std::cout << 1;
		return 0;
	}

	if (height.size() == 2)
	{
		auto heightOfFirst = height[0];
		auto heightOfSecond = height[1];

		if (heightOfFirst - heightOfSecond <= 20)
		{
			total += 1;
		}
		else
		{
			total += 2;
		}

		std::cout << total;
		return 0;
	}

	for (auto i = 0; i < height.size() - 2; i++)
	{
		auto heightOfFirst = height[i];
		auto heightOfSecond = height[i + 1];
		auto heightOfThird = height[i + 2];

		if (heightOfFirst - heightOfThird <= 10)
		{
			total++;
			if (i == height.size() - 3)
				break;
			i = i + 2;
			continue;
		}

		if (heightOfFirst - heightOfSecond <= 20)
		{
			total++;
			if (i == height.size() - 3)
			{
				total++;
				break;
			}
			i = i + 1;
			continue;
		}
		/*
		6
		120 115 110 100 50 40

		*/


		if (i == height.size() - 3)
		{
			total++;
			if (heightOfSecond - heightOfThird <= 20)
				total++;
			else
				total += 2;
			break;
		}

		total++;
	}

	std::cout << total;

	return 0;
}