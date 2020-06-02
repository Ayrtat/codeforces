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

int main()
{
	int setSize;
	std::cin >> setSize;

	std::cin.get();

	std::string numbersString;
	std::getline(std::cin, numbersString);
	std::istringstream iNumbers(numbersString);

	std::vector<int> numbers;

	std::copy(std::istream_iterator<int>(iNumbers), std::istream_iterator<int>(),
			std::back_inserter(numbers));

	std::vector<int> gcds;

	for (auto i = 0; i < numbers.size(); i++)
	{
		/*
			gcd(lcm(a,b), lcm(a,c)) = lcm(a, gcd(b, c))
			gcd(lcm(a,b), lcm(a,c), lcm(a,d)) = lcm(a, gcd(b, c, d))
			lcm(gcd(a,b), gcd(a,c)) = gcd(a, lcm(b, c))
		*/
		std::rotate(numbers.begin(), numbers.begin() + 1, numbers.end());
		auto gcdOnRotated = std::accumulate(numbers.begin(), numbers.end() - 1, numbers[0], std::gcd<int, int>);
		auto gcdViaLcm = std::lcm(numbers.back(), gcdOnRotated);
		gcds.push_back(gcdViaLcm);
	}

	auto res = std::accumulate(gcds.begin(), gcds.end() - 1, gcds[0], std::gcd<int, int>);

	std::cout << res;

	return 0;
}