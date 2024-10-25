#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<int> visited(n, 0); // 0: unvisited, 1: visiting, 2: visited
        int longest = -1;

        for (int i = 0; i < n; ++i) {
            if (visited[i] == 0) { // If the node is unvisited
                int cycleLength = dfs(i, edges, visited);
                longest = max(longest, cycleLength);
            }
        }
        return longest;
    }

private:
    int dfs(int node, vector<int>& edges, vector<int>& visited) {
        if (visited[node] == 2) {
            return -1; // Already fully processed node, no cycle
        }
        if (visited[node] == 1) {
            // Cycle detected
            return calculateCycleLength(node, edges, visited);
        }

        visited[node] = 1; // Mark as visiting
        if (edges[node] != -1) { // If there's an outgoing edge
            return dfs(edges[node], edges, visited);
        }
        
        visited[node] = 2; // Mark as fully visited
        return -1; // No cycle found in this path
    }

    int calculateCycleLength(int start, vector<int>& edges, vector<int>& visited) {
        int length = 0;
        int current = start;

        // Use a set to track nodes in the cycle
        unordered_map<int, int> nodeToIndex;
        while (true) {
            if (nodeToIndex.find(current) != nodeToIndex.end()) {
                // Cycle found
                return length - nodeToIndex[current] + 1; // Length of the cycle
            }

            nodeToIndex[current] = length;
            current = edges[current];
            if (current == -1) break; // No outgoing edge
            length++;
        }
        return -1; // No cycle found
    }
};

// Example usage
int main() {
    Solution solution;
    vector<int> edges = {1, 2, 0, 4, 5, 3, -1}; // Example graph with a cycle
    int result = solution.longestCycle(edges);
    cout << "Length of the longest cycle: " << result << endl; // Output should be the length of the longest cycle

    return 0;
}
