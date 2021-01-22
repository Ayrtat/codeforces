#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <numeric>
#include <map>
#include <iterator>
#include <set>
#include <deque>

struct BoxSizes {
    int length{};
    int width{};
    int height{};
    int type{-1};
    int num_of_box{};

    BoxSizes(const BoxSizes&) = default;
    BoxSizes(const std::vector<int>& box, int type, int num_of_box) : length(box[0]), width(box[1]), height(box[2]), type(type), num_of_box(num_of_box) {}
    friend bool operator<(const BoxSizes& lhs, const BoxSizes& rhs) {
        return (lhs.length < rhs.length && lhs.width < rhs.width) || (lhs.width < rhs.length && lhs.length < rhs.width);
    }

    friend bool operator<=(const BoxSizes& lhs, const BoxSizes& rhs) {
        return (lhs.length <= rhs.length && lhs.width < rhs.width) || (lhs.width < rhs.length && lhs.length <= rhs.width) || (lhs.width <= rhs.length && lhs.length <= rhs.width);
    }

    friend bool operator>=(const BoxSizes& lhs, const BoxSizes& rhs) {
        return (lhs.length <= rhs.length && lhs.width > rhs.width) || (lhs.width > rhs.length && lhs.length <= rhs.width);
    }
};

void operator<<(std::ostream& o, BoxSizes b)
{
    o << b.length << " " << b.width << " " << b.height << " " << std::endl;
}

BoxSizes rotateRight(const BoxSizes& box) {
    BoxSizes box_sizes(box);

    int height = box_sizes.height;
    int width = box_sizes.width;
    int length = box_sizes.length;

    box_sizes.length = width;
    box_sizes.height = length;
    box_sizes.width = height;
    box_sizes.num_of_box += 1;

    return box_sizes;
}

BoxSizes rotateOnward(const BoxSizes& box) {
    BoxSizes box_sizes(box);

    int height = box_sizes.height;
    int width = box_sizes.width;
    int length = box_sizes.length;

    box_sizes.length = height;
    box_sizes.height = length;
    box_sizes.width = width;

    box_sizes.num_of_box += 2;

    return box_sizes;
}

int main(int argc, char *argv[]) {
    std::vector<std::vector<int>> box_sizes = {
//            {28, 33, 45},
//            {80, 53, 23},
//            {38, 90, 45}
//            {27, 24, 35},
//            {76, 36, 3}
            {269, 152, 375},
            {45, 8, 259},
            {37, 113, 98},
            {685, 40, 35}
    };

    std::vector<BoxSizes> all_rotated_box;

    int type = 1;
    int count = 0;
    for (const auto& box_as_vector : box_sizes) {
        const auto& box = BoxSizes(box_as_vector, type++, count);
        count += 3;
        all_rotated_box.emplace_back(box);
        all_rotated_box.emplace_back(rotateRight(box));
        all_rotated_box.emplace_back(rotateOnward(box));
    }

    std::sort(all_rotated_box.begin(), all_rotated_box.end());

    struct Node {
        int x, y, z;
        int type;
        Node() = default;
        Node(int _x, int _y, int _z, int type) : x(_x), y(_y), z(_z), type(type) {}
        bool operator==(Node a) {
            return (x == a.x) && (y == a.y);
        }
    };

    std::vector<Node> nodes;

    std::transform(all_rotated_box.begin(), all_rotated_box.end(), std::back_inserter(nodes),
                   [](const auto& box) { return  Node(box.length, box.width, box.height, box.type); });

   std::vector<std::vector<int>> Graph(nodes.size(), std::vector<int>(nodes.size(), 0));

    for (int i = 0; i < nodes.size(); i++) {
        auto x = nodes[i].x;
        auto y = nodes[i].y;
        auto type = nodes[i].type;

        for (int j = 0; j < nodes.size(); j++) {
            auto x_ = nodes[j].x;
            auto y_ = nodes[j].y;
            auto type_ = nodes[j].type;

            if(i == j) {
                Graph[i][j] = nodes[i].z;
            }

            if(type == type_ || (x == x_ && y == y_))
                continue;

            if((x < x_ || x <= x_) && (y < y_ || y <= y_) ||
               (x < y_ || x <= y_) && (y < x_ || y <= x_)) {
                Graph[i][j] = std::abs( nodes[j].z);
            }

        }
    }

    for(int i = 0; i < Graph.size(); i++) {
        for(int j = 0; j < Graph.size(); j++) {
            std::cout << Graph[i][j] << "\t\t\t";
        }

        std::cout << std::endl;
    }

    int the_heighest = 0;

    for(auto j = 0; j < nodes.size(); j++) {
        std::deque<int> q;

        q.push_back(j);

        std::set<int> considered;


        std::vector<int> heighest(nodes.size(), 0);
        heighest[j] = Graph[j][j];

        while (!q.empty()) {
            std::vector<int> adjacent_nodes;

            auto curr{q.front()};

            considered.insert(nodes[curr].type);

            q.pop_front();

            for (int i = 0; i < Graph[0].size(); i++) {
                if (Graph[curr][i] > 0 && i != curr && !considered.count(i)) {
                    adjacent_nodes.push_back(i);
                }
            }

            for (auto node : adjacent_nodes) {
                heighest[node] = std::max(heighest[node], heighest[curr] + Graph[curr][node]);
                q.push_back(node);
            }
        }

        the_heighest = std::max(the_heighest, *std::max_element(heighest.begin(), heighest.end()));
    }

    return 0;
}
