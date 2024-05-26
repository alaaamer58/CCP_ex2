#include <iostream>
#include <vector>
#include <string>
#include "Graph.hpp"

using namespace std;
namespace ariel
{
    class Algorithms
    {
        public:
            //The algorithm accepts a graph and returns 1 if the graph is connected (otherwise returns 0)
            static bool isConnected(graph g);

            //The algorithm receives a graph, a start vertex and an end vertex and returns the easiest route (in case the graph is not weighted - the shortest) between the two vertices. If there is no such route, the algorithm will return -1.
            static string shortestPath(graph g, size_t a, size_t b);

            //The algorithm receives a graph and prints some circle. If there is no circle in the graph, the algorithm will return 0.
            static string isContainsCycle(graph g);


            //The algorithm receives a graph and returns the partition of the graph into a bipartite graph. If the graph cannot be partitioned, the algorithm will return 0.
            static string isBipartite(graph g);


            //The algorithm accepts a graph and finds a negative circle (that is, a circle whose sum of the weights of the sides is negative). If no such circle exists, the algorithm will print that there is no negative circle.
            static string negativeCycle(graph g);
        private:
            /**
            * Find the index of the vertex with the minimum distance among the unvisited vertices.
            * 
            * @param distances A vector containing the distances from the start vertex to each vertex.
            * @param visited   A vector indicating whether each vertex has been visited.
            * @return          The index of the vertex with the minimum distance among the unvisited vertices.
            */
            static size_t findMinDistance(vector<size_t>& distances, vector<bool>& visited);  

            /**
            * Shortest Path Algorithm using Dijkstra's Algorithm.
            * 
            * @param graph       The graph being traversed.
            * @param startVertex The index of the starting vertex.
            * @return            A vector containing the shortest distance from the starting vertex to each vertex in the graph.
            */
            static vector<size_t> shortestPathDijkstra(graph& graph, size_t startVertex);
            
            /**
            * Depth-First Search (DFS) algorithm to detect cycles in a graph.
            * 
            * @param g        The graph being traversed.
            * @param current  The index of the current vertex being visited.
            * @param visited  A vector indicating whether each vertex has been visited or not.
            * @param parent   A vector containing the parent of each vertex in the traversal.
            * @param cycle    A vector storing the vertices involved in the detected cycle (if any).
            * @return         True if a cycle is detected, false otherwise.
            */
            static bool DFS(graph& g, size_t current, vector<bool>& visited, vector<size_t>& parent, vector<size_t>& cycle);

            /**
            * Check if a graph is bipartite using Breadth-First Search (BFS).
            * 
            * @param g      The graph being checked for bipartiteness.
            * @param start  The starting vertex for BFS traversal.
            * @param color  Vector to store the color of each vertex (-1 or 1).
            * @param setA   Vector to store vertices in the first partition.
            * @param setB   Vector to store vertices in the second partition.
            * @return       True if the graph is bipartite, otherwise false.
            */
            static bool isBiPartiteBFS(graph &g, size_t start, vector<int> &color, vector<size_t> &setA, vector<size_t> &setB);  
               
    };
}