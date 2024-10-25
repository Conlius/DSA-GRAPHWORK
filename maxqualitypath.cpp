#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size();
        
        // Build the graph as an adjacency list
        vector<vector<pair<int, int>>> graph(n); // (neighbor, time)
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], time = edge[2];
            graph[u].emplace_back(v, time);
            graph[v].emplace_back(u, time);
        }

        int maxQuality = 0;
        unordered_set<int> visited; // To track unique nodes visited
        dfs(0, 0, 0, visited, graph, values, maxTime, maxQuality); // Start DFS from node 0
        return maxQuality;
    }

private:
    void dfs(int node, int currentTime, int currentQuality, unordered_set<int>& visited,
             const vector<vector<pair<int, int>>>& graph, const vector<int>& values, int maxTime, int& maxQuality) {
        // If the current time exceeds the max allowed time, return
        if (currentTime > maxTime) return;

        // Update maxQuality if we are back at the starting node
        if (node == 0) {
            maxQuality = max(maxQuality, currentQuality);
        }

        // Explore neighbors
        for (const auto& neighbor : graph[node]) {
            int nextNode = neighbor.first;
            int travelTime = neighbor.second;

            // Visit the next node
            if (visited.find(nextNode) == visited.end()) {
                // If the node has not been visited, add its value
                visited.insert(nextNode);
                dfs(nextNode, currentTime + travelTime, currentQuality + values[nextNode], visited, graph, values, maxTime, maxQuality);
                visited.erase(nextNode); // Backtrack
            } else {
                // If the node has been visited, continue without adding its value
                dfs(nextNode, currentTime + travelTime, currentQuality, visited, graph, values, maxTime, maxQuality);
            }
        }
    }
};

// Example usage
int main() {
    Solution solution;
    vector<int> values = {10, 5, 15, 20}; // Example node values
    vector<vector<int>> edges = {
        {0, 1, 5}, {1, 2, 10}, {2, 3, 5}, {0, 3, 15} // Example edges
    };
    int maxTime = 25; // Example max time

    int result = solution.maximumQuality(values, edges, maxTime);
    cout << "Maximum Quality of Valid Path: " << result << endl; // Expected output: quality value

    return 0;
}
