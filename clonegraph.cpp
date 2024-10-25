#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node(int _val) : val(_val) {}
};

class Solution {
public:
    // Clone the graph and return a vector of cloned nodes
    vector<Node*> cloneGraph(Node* node) {
        if (!node) return {};  // Return an empty vector if the input node is null

        unordered_map<Node*, Node*> clones;  // Map to keep track of cloned nodes
        vector<Node*> clonedNodes;  // Vector to store all cloned nodes
        
        clone(node, clones, clonedNodes);  // Start the cloning process
        return clonedNodes;  // Return the vector of cloned nodes
    }

private:
    void clone(Node* node, unordered_map<Node*, Node*>& clones, vector<Node*>& clonedNodes) {
        if (clones.find(node) != clones.end()) {
            return;  // If the node is already cloned, return
        }

        // Create a clone for the current node
        Node* cloneNode = new Node(node->val);
        clones[node] = cloneNode;  // Store the clone in the map
        clonedNodes.push_back(cloneNode);  // Add the cloned node to the vector

        // Clone the neighbors
        for (Node* neighbor : node->neighbors) {
            clone(neighbor, clones, clonedNodes);  // Recursive call for neighbors
            cloneNode->neighbors.push_back(clones[neighbor]);  // Link the cloned neighbor
        }
    }
};

// Function to generate adjacency list from cloned nodes
vector<vector<int>> getAdjacencyList(const vector<Node*>& clonedNodes) {
    vector<vector<int>> adjacencyList;
    for (const Node* node : clonedNodes) {
        vector<int> neighbors;
        for (const Node* neighbor : node->neighbors) {
            neighbors.push_back(neighbor->val);  // Store the value of the neighbor
        }
        adjacencyList.push_back(neighbors);  // Add the neighbors' list to the adjacency list
    }
    return adjacencyList;
}

// Example usage
int main() {
    // Create a simple graph for testing
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);

    node1->neighbors = {node2, node3};
    node2->neighbors = {node1, node4};
    node3->neighbors = {node1};
    node4->neighbors = {node2};

    Solution solution;
    vector<Node*> clonedGraphNodes = solution.cloneGraph(node1);

    // Generate adjacency list and print it
    vector<vector<int>> adjacencyList = getAdjacencyList(clonedGraphNodes);

    // Output in the required format
    cout << "[";
    for (size_t i = 0; i < adjacencyList.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < adjacencyList[i].size(); ++j) {
            cout << adjacencyList[i][j];
            if (j < adjacencyList[i].size() - 1) {
                cout << ",";
            }
        }
        cout << "]";
        if (i < adjacencyList.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;

    // Clean up memory (optional, for demonstration purposes)
    for (Node* node : clonedGraphNodes) {
        delete node;
    }

    return 0;
}
