/*https://leetcode.com/problems/course-schedule/submissions/*/

class Solution {
public:
    int isCyclic = 0;
    
    vector<int> color;
    
    void dfs(int vertex) {
        color[vertex] = 1;
        
        for (size_t i = 0; i < Graph[vertex].size(); ++i) {
            if (Graph[vertex][i] == 1)
            {
                if (color[i] == 0)
                    dfs(i);
                if (color[i] == 1)
                {
                    isCyclic = 1;
                }
            }
        }
        color[vertex] = 2;
    }
    
    vector<vector<int>> Graph;
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
	   color.assign(numCourses, 0);
        
       Graph = vector<vector<int>>(numCourses, vector<int>(numCourses, 0));
        
       for(auto i=0; i < prerequisites.size(); i++)
       {
           auto& p = prerequisites[i];
           Graph[p[0]][p[1]] = 1;
       }
     
       for (int i=0; i<numCourses; ++i)
            dfs (i);
        
        if (isCyclic == 0)
            return true;
        return false;
    }
};
