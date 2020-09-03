#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>
#include <map>

struct Box
{
	static int box_number;
	int width{};
	int length{};
	int height{};

	int type;

	Box() = default;
	Box(int _width, int _length, int _height) : width(_width), length(_length), height(_height) { type = box_number++; }
	Box(int _width, int _length, int _height, int _type) : width(_width), length(_length), height(_height), type(_type) { }
};

int Box::box_number = 0;

int main()
{
	std::vector<Box> boxes{ Box(24, 5, 36), Box(76, 23, 3) };
	std::vector<Box> boxRotations;

	std::map < std::pair<int, int>, std::pair<int, std::set<int>>> boxMap;

	/* One box can be turned right or rotated*/
	for (auto& box : boxes)
	{
		boxRotations.push_back(Box(box.length, box.width, box.height, box.type));
		boxRotations.push_back(Box(box.height, box.length, box.width, box.type));
	}

	for (auto& box : boxRotations)
	{
		boxes.push_back(box);
	}

	std::sort(std::begin(boxes), std::end(boxes), [](Box& a, Box& b) { return (a.length <= b.length) && (a.width <= b.width);  });

	for (auto& boxVariant : boxes)
	{
		auto pairOfParam = std::make_pair(boxVariant.width, boxVariant.length);
		auto height = boxVariant.height;
		std::set<int> set_of_boxes;

		/*find the biggest convinient box that can be put on this box*/
		for (auto it = std::rbegin(boxMap); it != std::rend(boxMap); it++)
		{
			auto key = it->first;
			auto width = key.first;
			auto length = key.second;

			if (pairOfParam.first >= width && pairOfParam.second >= length)
			{
				auto value = boxMap[key];
				auto total_height = value.first;

				auto box_numbers = value.second;

				if (box_numbers.find(boxVariant.type) != box_numbers.end())
					continue;

				height += total_height;
				set_of_boxes = std::set<int>{ box_numbers };

				break;
			}
		}

		set_of_boxes.insert(boxVariant.type);

		boxMap[pairOfParam] = std::make_pair(height, set_of_boxes);
	}

	return 0;
}
