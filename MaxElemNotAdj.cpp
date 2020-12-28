/*
Find an efficient algorithm to find the maximum sum of a subsequence in an array so that no consecutive elements are part of this subsequence.
Consider the following examples:
1, 6, 10, 14, -5, -1, 2, -1, 3

6 + 14 + 2 + 3 = 25

The max sum of a subsequence with no consecutive elements in the example below is 25
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> numbers = {1, 6, 10, 14, -5, -1, 2, -1, 3};
    std::vector<int> states(numbers.size(), 0);

    states.at(0) = numbers.at(0);
    states.at(1) = numbers.at(1);
   
    /*
      Formula maxNotAdjacent(Ai) = std::max(maxNotAdjacent(Ai-2), Ai, maxNotAdjacent(Ai-2) + Ai)
    */

    for(int i = 2; i < numbers.size(); i++) {
        auto untilIterator = states.begin();
        std::advance(untilIterator, i - 1);

        auto max_with_others = *std::max_element(states.begin(), untilIterator);
        states.at(i) = std::max(std::max(max_with_others, numbers.at(i)), max_with_others + numbers.at(i));
    }

    std::cout << *std::max_element(states.begin(), states.end());

    return 0;
}
