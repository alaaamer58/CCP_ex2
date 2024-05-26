//id:214601296__email:alaaamer0508@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>
#include <vector>


namespace ariel {
    using namespace std;

    class graph {
    private:
        vector<vector<int>> nMatrix;
        vector<bool> visit;
        bool NegaCycles;
        bool Cycle;
    public:
        graph() {
            nMatrix={};
            NegaCycles=false;
            Cycle=false;
        }
        graph(vector<vector<int>> matrix)
        {  
            graph();
            loadGraph(matrix);
        }

        
        void loadGraph(vector<vector<int>>& matrix);
        
        
        void printGraph();

        vector<vector<int>> getMatrix();
        
        size_t get_vertexNum();

        bool hasCycle() const;

        void setCycle(bool v);

        bool hasNegaCycle() const;

        void setNegaCycle(bool v);

        int getEdgeWeight(size_t a, size_t b) const;


        friend graph operator+ (graph& g1, graph& g2);
        friend graph operator+= (graph& g1, graph& g2);
        friend graph operator+ (graph& g1);
        friend graph operator- (graph& g1, graph& g2);
        friend graph operator-= (graph& g1, graph& g2);
        friend graph operator- (graph& g1);
        friend bool operator> (graph& g1,graph& g2);
        friend bool operator>= (graph& g1,graph& g2);
        friend bool operator< (graph& g1,graph& g2);
        friend bool operator<= (graph& g1,graph& g2);
        friend bool operator== (graph& g1,graph& g2);
        friend bool operator!= (graph& g1,graph& g2);
        friend void operator++ (graph& g1);
        friend void operator-- (graph& g1);
        friend graph operator* (graph& g1 , graph& g2);
        friend void operator*= (graph& g1 , int x);
        friend void operator/= (graph& g1 , int x);
        friend ostream& operator<<(ostream& os, graph& g1); 
    };

}
#endif