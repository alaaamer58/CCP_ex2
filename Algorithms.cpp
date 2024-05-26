#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <limits>
#include "Algorithms.hpp"
#include <stack>

using namespace std;
namespace ariel {
    bool Algorithms::isBiPartiteBFS(graph &g, size_t start, vector<int> &color, vector<size_t> &setA, vector<size_t> &setB) {
        queue<size_t> q;
        color[start] = 1;
        setA.push_back(start);
        q.push(start);

        // Perform BFS
        while (!q.empty()) {
            size_t vertex = q.front();
            q.pop();

            for (size_t neighbor = 0; neighbor < g.get_vertexNum(); ++neighbor) {
                if (color[neighbor] == 0) { // Not visited yet
                    color[neighbor] = -color[vertex]; // Assign opposite color to the neighbor
                    q.push(neighbor);

                    // Add neighbor to the appropriate set
                    if (color[neighbor] == -1) {
                    
                        setB.push_back(neighbor);

                    } else {

                        setA.push_back(neighbor);
                    }

                    } else if (color[vertex] == color[neighbor]) {

                        return false; // Graph is not bipartite
                }
            }
        }
        // Graph is bipartite
        return true;
    }

    size_t Algorithms::findMinDistance(vector<size_t>& distances, vector<bool>& visited) {
        size_t minVertex = 0;
        size_t minDistance = numeric_limits<size_t>::max();

        // Traverse all vertices
        for (size_t i = 0; i < distances.size(); ++i) {
            // If the vertex has not been visited and its distance is less than the current minimum distance
            if (!visited[i] && distances[i] < minDistance) {
                minVertex = i;        // Update the index of the minimum vertex
                minDistance = distances[i]; // Update the minimum distance
            }
        }

        return minVertex; // Return the index of the vertex with the minimum distance
    }
    vector<size_t> Algorithms::shortestPathDijkstra(graph& graph, size_t startVertex) {
     
        vector<size_t> distances(graph.get_vertexNum(), numeric_limits<size_t>::max()); // Initialize distances to infinity
        vector<bool> visited(graph.get_vertexNum(), false);       // Initialize visited vertices
        distances[startVertex] = 0; // Set distance from start to itself to 0

        // Traverse all vertices
        for (size_t i = 0; i < graph.get_vertexNum(); ++i) {
            // Find the vertex with the minimum distance among the unvisited vertices
            size_t minVertex = findMinDistance(distances, visited);
            visited[minVertex] = true; // Mark the vertex as visited

            // Update distances of adjacent vertices
            for (size_t j = 0; j < graph.get_vertexNum(); ++j) {
                if (!visited[j] && graph.getEdgeWeight(minVertex, j) && distances[minVertex] != numeric_limits<size_t>::max() &&
                    distances[minVertex] + static_cast<size_t>(graph.getEdgeWeight(minVertex, j)) < distances[j]) {
                    distances[j] = distances[minVertex] + static_cast<size_t>(graph.getEdgeWeight(minVertex, j));
                }
            }
        }

        return distances;
    }

    bool Algorithms::DFS(graph& g, size_t current, vector<bool>& visited, vector<size_t>& parent, vector<size_t>& cycle) {
    visited[current] = true;

    for (size_t neighbor = 0; neighbor < g.get_vertexNum(); ++neighbor) {
        int w = g.getEdgeWeight(current, neighbor);

        if (w != 0 && parent[current] != neighbor) {
            if (visited[neighbor]) {
                size_t curr = current;
                while (curr != neighbor) {
                    cycle.push_back(curr);
                    curr = parent[curr];
                }
                cycle.push_back(neighbor);
                cycle.push_back(current);
                return true;
            } else {
                parent[neighbor] = current; // neighbor not visited yet
                if (DFS(g, neighbor, visited, parent, cycle)) {
                    return true;
                }
            }
        }
    }
    // If we got here, it means that no cycles were found after running the DFS
    return false;
}


    bool Algorithms::isConnected(graph g) {
    size_t numOfVertices = g.get_vertexNum();

    // If the graph is empty or has only 1 vertex, it is considered connected
    if (numOfVertices <= 1) {
        return true;
    }  

    vector<bool> visited(numOfVertices, false);
    stack<size_t> s;
    s.push(0);

    // Perform DFS traversal
    while (!s.empty()) {
        size_t vertex = s.top();
        s.pop();

        visited[vertex] = true;

        // Traverse neighbors of the current vertex
        for (size_t n = 0; n < g.get_vertexNum(); ++n) {
            if (g.getEdgeWeight(vertex, n) != 0 && !visited[n]) {
                s.push(n); // Add the neighbor to the stack
            }
        }
    }

    // Check if all vertices are visited
    for (size_t i = 0; i < visited.size(); i++) {
        if (!visited[i]) {
            return false; // Graph is not connected if any vertex is unvisited
        }
    }
    // All vertices are visited, so the graph is connected
    return true;
}


// The algorithm receives a graph and checks if it contains a cycle. If there is a cycle in the graph, the algorithm returns 1; otherwise, it returns 0.
    string Algorithms::isContainsCycle(graph g) {
    vector<size_t> cycle;
    vector<size_t> parent(g.get_vertexNum(), INT32_MAX);
    vector<bool> visited(g.get_vertexNum(), false);

    // Iterate through each vertex in the graph
    for (size_t i = 0; i < g.get_vertexNum(); ++i) {
        // If the vertex has not been visited, perform DFS to check for cycles
        if (!visited[i]) {
            if (DFS(g, i, visited, parent, cycle)) {
                string ans = "The cycle is: ";
                size_t iCycle = 0; // Declare outside the loop to use it outside
                // Construct the string representation of the cycle
                for (; iCycle < cycle.size() - 1; ++iCycle) {
                    ans += to_string(cycle[iCycle]) + "->";
                }
                ans += to_string(cycle[iCycle]);
                g.setCycle(true); // Set graph flag indicating it contains cycles
                return ans;        // Return the string representation of the cycle
            }
        }
    }
    return "0"; // Return "0" if no cycle is found in the graph
}

    string Algorithms::shortestPath(graph g, size_t a, size_t b) {
       vector<size_t> path = shortestPathDijkstra(g, a);

    // Check if the path is empty or if vertex 'b' is unreachable, or if the graph has only 1 vertex
    if (path.empty() || path[b] == INT32_MAX || path[b] == INT32_MIN || path[b] == 0 || g.get_vertexNum() <= 1) {
        return "-1"; // No path exists
    }

    string ans = to_string(b);
    size_t i = b;

    // Reconstruct the shortest path from 'b' to 'a'
    while(path[i] != a){
        i = path[i];
        ans.insert(0, to_string(i) + "->");
    }
    ans.insert(0, to_string(a) + "->"); // Insert the starting vertex 'a' at the beginning of the path
    return ans;
    }

    string Algorithms::negativeCycle(graph g) {
        shortestPathDijkstra(g, 0);
        if (g.hasNegaCycle()) {
            return "the graph have negative cycles";
        }
        return "the graph doesent  have negative cycles";
    }

    string Algorithms::isBipartite(graph g) {
        string result;
        vector<int> colors(g.get_vertexNum(), 0);
        vector<size_t> setA;
        vector<size_t> setB;

        // Apply the bipartiteBFS algorithm
        for (size_t i = 0; i < g.get_vertexNum(); ++i) {
            if (colors[i] == 0) {
                if (!isBiPartiteBFS(g, i, colors, setA, setB)) {
                    return "The graph is not bipartite.";
                }
            }
        }

        // If the graph is bipartite, construct the result string
        result += "The graph is bipartite. A={";
        for (size_t i = 0; i < setA.size(); ++i) {
            result += to_string(setA[i]);
            if (i < setA.size() - 1) {
                result += ", ";
            }
        }
        result += "}, B={";
        for (size_t i = 0; i < setB.size(); ++i) {
            result += to_string(setB[i]);
            if (i < setB.size() - 1) {
                result += ", ";
            }
        }
        result += "}";
        return result;
    }
}