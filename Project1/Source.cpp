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
	int setSize;
	std::cin >> setSize;

	std::vector<long long> numbers;

	while (setSize--)
	{
		long long num;
		std::cin >> num;
		numbers.push_back(num);
	}

	std::vector<long long> gcds;
	std::deque<long long> localGcds;

	for (long long i = numbers.size() - 1; i >= 0; i--)
	{
		localGcds.push_front(std::gcd(numbers[i], localGcds.empty() ? numbers[i] : localGcds.front()));
	}

	for (auto i = 0; i < numbers.size() - 1; i++)
	{
		/*
			gcd(lcm(a,b), lcm(a,c)) = lcm(a, gcd(b, c))
			gcd(lcm(a,b), lcm(a,c), lcm(a,d)) = lcm(a, gcd(b, c, d))
			gcd(lcm(b,c), lcm(b,d)) = lcm(b, gcd(c,d))

			gcd(lcm(c,d), lcm(c, e), ..lcm(c,z)) = 
			lcm(gcd(a,b), gcd(a,c)) = gcd(a, lcm(b, c))
		*/
		auto gcdViaLcm = std::lcm(numbers[i], localGcds[i+1]);
		gcds.push_back(gcdViaLcm);
	}

	auto res = std::accumulate(gcds.begin(), gcds.end(), gcds[0], std::gcd<long long, long long>);

	std::cout << res;

	return 0;
}