  #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <set>
    #include <sstream>
    #include <map>
    #include <list>
    #include <iterator>
    #include <deque>
    #include <bitset>
    #include <numeric>
    
    using namespace std;
    
    //test cases
    std::vector<std::vector<int>> mapOfPlatform{
    	/*{0, 1, 1, 1, 0, 0},
    	{3, 1, 0, 1, 1, 0},
    	{0, 0, 0, 0, 1, 1},
    	{0, 0, 0, 0, 0, 1},
    	{2, 1, 1, 1, 1, 1}*/
    
    	/*{1, 1, 1, 1, 0, 0, 0, 0},
    	{0, 0, 0, 3, 0, 1, 1, 1},
    	{1, 1, 1, 0, 0, 1, 0, 0},
    	{0, 0, 0, 0, 0, 0, 1, 0},
    	{2, 1, 1, 1, 1, 1, 1, 1}*/
    	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    
    struct Node {
    	int x, y;
    	Node() = default;
    	Node(int _x, int _y) : x(_x), y(_y) {}
    	bool operator==(Node a) {
    		return (x == a.x) && (y == a.y);
    	}
    };
    
    std::vector<Node> nodes;
    Node start;
    Node finish;
    
    //the number of nodes coincides with number of platforms in the map
    //the main problem is how to numerate the nodes when the platforms are representes as its coordinates
    //however it's not important and a number of a node is given in the order that they are pushed back in vector
    
    void createNodesFromMapOfPlatforms() {
    	for (int i = 0; i < mapOfPlatform.size(); i++) {
    		for (int j = 0; j < mapOfPlatform[0].size(); j++) {
    			if (mapOfPlatform[i][j] != 0) {
    				nodes.push_back(Node(i, j));
    
    				if (mapOfPlatform[i][j] == 2)
    					start = nodes.back();
    
    				if (mapOfPlatform[i][j] == 3)
    					finish = nodes.back();
    			}
    		}
    	}
    }
    
    std::vector<std::vector<int>> adjacent_matrix;
    
    void createGraphFromNodes() {
    	createNodesFromMapOfPlatforms();
    	std::vector<std::vector<int>> adj_temp(nodes.size(), std::vector<int>(nodes.size(), INT_MAX));
    	for (int i = 0; i < nodes.size(); i++) {
    		auto x = nodes[i].x;
    		auto y = nodes[i].y;
    
    		/*
    			  _ V _    
    			D _ + _ _  
    		        +   _ _
    			    +     _
    			S _ U _ _ _
    		
    		    the distance between U and V is 3
    
    		*/
    		//find the closest node on the same column
    		if (x < mapOfPlatform.size() - 1) { 
    			for (auto j = x + 1; j < mapOfPlatform.size(); j++) {
    				if (mapOfPlatform[j][y] > 0) {
    					for (int k = 0; k < nodes.size(); k++) {
    						auto search_this = Node(j, y);
                
                //find the number of neighbour node (we are looking for the number from vector)
    						if (search_this == nodes[k]) {
    							adj_temp[i][k] = j - x;
    							adj_temp[k][i] = j - x;
    						}
    					}
    					break;
    				}
    			}
    		}
    
    		//find the neighbour platform to the right
    		if (y < mapOfPlatform[0].size() - 1 && mapOfPlatform[x][y + 1] > 0) {
    			for (int k = 0; k < nodes.size(); k++) {
    				auto search_this = Node(x, y + 1);
    				if (search_this == nodes[k]) {
    					adj_temp[i][k] = 0;
    					adj_temp[k][i] = 0;
    				}
    			}
    		}
    	}
    
    	adjacent_matrix = adj_temp;
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
    		Edge the_shortest = { -1, -1, INT_MAX };
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
    
    int main() {
    	createGraphFromNodes();
    
    	auto result_spanning_tree = minimum_spanning_tree(adjacent_matrix);
    
    	auto the_edge = std::max_element(std::begin(result_spanning_tree), std::end(result_spanning_tree), 
    		[](Edge a, Edge b) { return a.length < b.length; });
    
    	std::cout << the_edge->length;
    
    	return 0;
    }

