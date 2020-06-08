#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
	int N;
	std::cin >> N;
	std::cin.get();

	std::vector<std::string> inputStrings;

	while (N--)
	{
		std::string inputString;
		std::getline(std::cin, inputString);

		inputStrings.push_back(inputString);
	}

	for (auto iString : inputStrings)
	{
		std::vector<int> zFunction(iString.size(), 0);

		for (int i = 1; i < iString.size(); i++)
		{
			std::string suffix(iString.begin() + i, iString.end());
			std::string prefix(iString.begin(), iString.begin() + suffix.size());

			auto it = std::mismatch(prefix.begin(), prefix.size() >= suffix.size() ? prefix.begin() + suffix.size() : prefix.end(), suffix.begin());

			zFunction[i] = std::distance(prefix.begin(), it.first);
		}
	}	
}
