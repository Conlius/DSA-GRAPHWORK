
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        // Using a map to count occurrences of each node
        unordered_map<int, int> degreeCount;

        // Count the degree of each node based on edges
        for (const auto& edge : edges) {
            degreeCount[edge[0]]++;
            degreeCount[edge[1]]++;
        }

        // The center node will have degree of n - 1
        for (const auto& entry : degreeCount) {
            if (entry.second == edges.size()) {
                return entry.first; // Return the center node
            }
        }
        
        return -1; // Should not reach here for a valid star graph
    }
};

// Example usage
int main() {
    Solution solution;
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {4, 2}}; // Example star graph edges
    int center = solution.findCenter(edges);
    cout << "Center of the star graph: " << center << endl; // Expected output: 2

    return 0;
}

