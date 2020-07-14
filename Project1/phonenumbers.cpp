//https://acm.timus.ru/problem.aspx?space=1&num=1002

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <deque>
std::string phoneNumber;
std::map<int, std::set<int>> fromTo;
std::map<std::pair<int, int>, std::string> inRange;
std::deque<int> indexes;
std::deque<int> tempIndexes;

/*
7325189087
5
it
your
reality
real
our
      */

void findConvinient(int indexFrom)
{
    if (fromTo.find(indexFrom) != fromTo.end())
    {
        tempIndexes.push_back(indexFrom);

        if (fromTo[indexFrom].find(phoneNumber.size() - 1) != fromTo[indexFrom].end())
        {
            if (indexes.size() > tempIndexes.size())
                indexes = tempIndexes;
            tempIndexes.pop_back();
            return;
        }

        for (auto it = std::begin(fromTo[indexFrom]); it != std::end(fromTo[indexFrom]); it++)
        {
            findConvinient(*it + 1);
        }

        tempIndexes.pop_back();
    }

    return;
}

int main()
{
    std::getline(std::cin, phoneNumber);
    indexes.resize(phoneNumber.size());

    std::map<char, char> buttons{
        {'i', 1}, {'j', 1}, {'a', 2}, {'b',2}, {'c', 2}, {'d', 3}, {'e', 3}, {'f',3},
        {'g', 4}, {'h', 4}, {'k', 5}, {'l', 5}, {'m', 6}, {'n', 7},
        {'p', 7}, {'r', 7}, {'s', 7}, {'t', 8}, {'u', 8}, {'v', 8}, {'w', 9}, {'x', 9}, {'y', 9},
        {'o', 0}, {'q', 0}, {'z', 0}
    };
    //std::cin.ignore();
    int N;
    std::cin >> N;
    std::cin.ignore();
    while (N--)
    {
        std::string word;
        std::getline(std::cin, word);
        std::string transformedWord;
        transformedWord.resize(word.size());
        std::transform(word.begin(), word.end(), transformedWord.begin(), [&buttons](std::string::value_type sym) { return static_cast<char>(buttons[sym] + '0'); });
        auto it = std::search(phoneNumber.begin(), phoneNumber.end(), transformedWord.begin(), transformedWord.end());
        if (it != phoneNumber.end())
        {
            auto posFrom = std::distance(phoneNumber.begin(), it);
            fromTo[posFrom].insert(posFrom + transformedWord.size() - 1);
            inRange[std::make_pair(posFrom, posFrom + transformedWord.size() - 1)] = word;
        }
    }

    findConvinient(0);

    if (indexes.empty())
        std::cout << "No solutions!";
    else
    {
        for (auto it = std::begin(indexes); it != std::end(indexes); it++)
        {
            if (it + 1 != std::end(indexes))
                std::cout << inRange[std::make_pair(*it, *(it + 1) - 1)] << " ";
            else
                std::cout << inRange[std::make_pair(*it, phoneNumber.size() - 1)];
        }
    }

    return 0;
}
