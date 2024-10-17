#include <iostream>
#include <vector>

using namespace std;

// Function to perform DFS and mark all astronauts in the same connected component (i.e., from the same country)
void dfs(int astronaut, vector<vector<int>>& adjList, vector<bool>& visited, int& componentSize) {
    visited[astronaut] = true;
    componentSize++;
    
    // Traverse all the astronauts connected to this astronaut
    for (int neighbor : adjList[astronaut]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adjList, visited, componentSize);
        }
    }
}

int main() {
    int n, p;
    // n is the number of astronauts, p is the number of pairs (edges)
    cin >> n >> p;

    // Adjacency list to store the pairs (graph representation)
    vector<vector<int>> adjList(n);

    // Read the pairs of astronauts from the same country
    for (int i = 0; i < p; i++) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // To keep track of visited astronauts
    vector<bool> visited(n, false);

    // List to store the size of each connected component (each country's astronaut group)
    vector<int> componentSizes;

    // Find all connected components using DFS
    for (int astronaut = 0; astronaut < n; astronaut++) {
        if (!visited[astronaut]) {
            int componentSize = 0;
            dfs(astronaut, adjList, visited, componentSize);
            componentSizes.push_back(componentSize);
        }
    }

    // Calculate the number of valid pairs of astronauts from different countries
    long long totalAstronauts = n;
    long long totalPairs = totalAstronauts * (totalAstronauts - 1) / 2;  // Total possible pairs

    // Subtract pairs from the same country (within each connected component)
    for (int size : componentSizes) {
        totalPairs -= (long long)size * (size - 1) / 2;
    }

    cout << totalPairs << endl;

    return 0;
}
