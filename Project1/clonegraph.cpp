//https://leetcode.com/problems/clone-graph/submissions/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    map<int, Node*> alreadyVisitedOnVal;
    
    Node* cloneGraph(Node* node) {
        if(node == nullptr)
            return nullptr;
        
        Node* newVertex = new Node();
        newVertex->val = node->val;
        alreadyVisitedOnVal[node->val] = newVertex;
                
        for(auto it = node->neighbors.begin(); it != node->neighbors.end(); it++)
        {
            if(alreadyVisitedOnVal.find((*it)->val) ==                                   alreadyVisitedOnVal.end())
                {
                    Node* newNeighbor = cloneGraph(*it);
                    newVertex->neighbors.push_back(newNeighbor);
                }
            else
            {
                newVertex->neighbors.push_back(alreadyVisitedOnVal[(*it)->val]);
            }
        }
        
        return newVertex;
    }
};
