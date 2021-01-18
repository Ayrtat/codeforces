#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <list>

struct NodeCoord {
    int x;
    int y;
    int value;
    NodeCoord() = default;
    NodeCoord(int x, int y, int value) : x(x), y(y), value(value) {}
};

auto transformMapToGraph(std::vector<std::vector<int>>& map_of_paths) {
    std::vector<std::vector<int>> graph_matrix(map_of_paths.size() * map_of_paths.size(),
                                               std::vector<int>(map_of_paths.size() * map_of_paths.size(), 0));//std::numeric_limits<int>::max()));

    std::map<int, NodeCoord> node_coords;

    int count = 0;
    for(int i = 0; i < map_of_paths.size(); i++) {
        for(int j = 0; j < map_of_paths.size(); j++) {
            //NodeCoord(i, j, map_of_paths[i][j]);
            node_coords[count++] = NodeCoord(i, j, map_of_paths[i][j]);
        }
    }

    for(auto&& node : node_coords) {
        auto count = node.first;
        const auto& node_info = node.second;

        NodeCoord from_left, from_right, from_above, from_below;

        for(auto&& temp_node : node_coords) {
            const auto& temp_node_info = temp_node.second;

            if(temp_node_info.x == node_info.x + 1 && temp_node_info.y == node_info.y) {
                if(temp_node_info.value > node_info.value) {
                    graph_matrix[count][temp_node.first] = std::abs(temp_node_info.value - node_info.value) + 1;
                    graph_matrix[temp_node.first][count] = 1;
                } else {
                    graph_matrix[count][temp_node.first] = 1;
                    graph_matrix[temp_node.first][count] =
                            std::abs(temp_node_info.value - node_info.value) + 1;
                }
            }

            if(temp_node_info.y == node_info.y + 1 && temp_node_info.x == node_info.x) {
                graph_matrix[count][temp_node.first] = 1;
                graph_matrix[temp_node.first][count] = 1;
            }
        }
    }

    return graph_matrix;
}

struct Edge
{
    // A---------B
    //   length
    int a;
    int b;
    int length;
};

std::vector<Edge> minimum_spanning_tree(const std::vector<std::vector<int>>& graph)
{
    std::set<int> unvisited;
    std::vector<int> visited;
    std::vector<Edge> result;

    auto const number_of_nodes = graph.size();

    // mark first as visited and mark the rest as unvisited
    visited.reserve(number_of_nodes);
    visited.push_back(0);
    for (auto i = 1u; i < number_of_nodes; ++i)
        unvisited.insert(i);
    result.reserve(number_of_nodes - 1);

    while (!unvisited.empty()) {
        Edge the_shortest = { -1, -1, std::numeric_limits<int>::max() };
        //put all edges (with their lengths) from nodes that are in visited
        for (auto node : visited) {
            auto const& lengths = graph[node];
            for (int sec_node = 0; sec_node < lengths.size(); sec_node++) {
                auto const length = lengths[sec_node];
                if (length >= 0 && length < the_shortest.length
                    && unvisited.count(sec_node)) {
                    // our new closest node
                    the_shortest = { node, sec_node, length };
                }
            }
        }

        //add the shortest path to the result
        result.push_back(the_shortest);

        // mark the destination as visited
        unvisited.erase(the_shortest.b);
        visited.push_back(the_shortest.b);
    };
    return result;
}

int minimumDist(int dist[], bool Tset[])
{
    int min= std::numeric_limits<int>::max(),index;

    for(int i=0;i<36;i++)
    {
        if(Tset[i]==false && dist[i] <= min)
        {
            min=dist[i];
            index=i;
        }
    }
    return index;
}

void Dijkstra(const std::vector<std::vector<int>>& graph ,int src) // adjacency matrix used is 6x6
{
    int dist[36]; // integer array to calculate minimum distance for each node.
    bool Tset[36];// boolean array to mark visted/unvisted for each node.

    // set the nodes with infinity distance
    // except for the initial node and mark
    // them unvisited.
    for(int i = 0; i < 36; i++)
    {
        dist[i] = std::numeric_limits<int>::max();
        Tset[i] = false;
    }

    dist[src] = 0;   // Source vertex distance is set to zero.

    for(int i = 0; i < 36; i++)
    {
        int m=minimumDist(dist,Tset); // vertex not yet included.
        Tset[m]=true;// m with minimum distance included in Tset.
        for(int i = 0; i < 36; i++)
        {
            // Updating the minimum distance for the particular node.
            if(!Tset[i] && graph[m][i] && dist[m] != std::numeric_limits<int>::max() && dist[m]+graph[m][i]<dist[i])
                dist[i]=dist[m]+graph[m][i];
        }
    }
    std::cout << "Vertex\t\tDistance from source" << std::endl;
    for(int i = 0; i < 36; i++)
    { //Printing
        char str=65+i; // Ascii values for pritning A,B,C..
        std::cout << str<< "\t\t\t" << dist[i] << std::endl;
    }
}

int onlyGreedy(const std::vector<std::vector<int>>& graph) {
    auto sum = 0;

    std::list<int> q;
    std::set<std::pair<int, int>> visited;

    q.push_back(0);
    visited.insert(std::make_pair(0, 0));
    while(visited.size() != graph.size()) {
        auto i = q.back();
        q.pop_back();

        auto it = std::begin(graph[i]);
        int node = -1;

        while (true) {
            it = std::min_element(it, std::end(graph[i]));

            auto node_ = std::distance(std::begin(graph[i]), it);

            if(visited.count(std::make_pair(i, node_)))
                continue;
            node = node_;
            break;
        }

        sum += graph[i][node];
        q.push_back(node);
        visited.insert(std::make_pair(i, node));

    }
}


int main()
{
    int N;

    //std::vector<std::vector<int>> map_of_paths =
          //  {{9, 5, 7, 9}, {8, 4, 2, 5}, {7, 6, 5, 4}, {8, 8, 9, 5}};

    std::vector<std::vector<int>> map_of_paths =
            {{3, 2, 6, 0, 1, 2},
             {9, 2, 2, 9, 2, 9},
             {4, 9, 2, 2, 0, 1},
             {0, 2, 4, 2, 2, 4},
             {4, 5, 0, 1, 2, 2},
             {9, 8, 1, 7, 5, 1}};

    Dijkstra(transformMapToGraph(map_of_paths), 0);

    return 0;
}
