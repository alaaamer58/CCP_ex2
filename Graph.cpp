//id:214601296__email:alaaamer0508@gmail.com
#include <iostream>
#include <vector>
#include "Graph.hpp"

using namespace std;

namespace ariel
{
    void graph::loadGraph(vector<vector<int>> & graph)
    {
        for (size_t i = 0; i < graph.size(); i++)
        {
            if (graph.size() != graph[i].size())
            {
                cout<< "the matrix is not square" <<endl;
                return;
            }
            
        }
        nMatrix= graph;
        this->NegaCycles = false;
        this->Cycle = false;
        
    }
    void graph::printGraph ()
    {
        for (size_t i = 0; i < nMatrix.size(); i++)
        {
            for (size_t j = 0; i < nMatrix[i].size(); j++)
            {
                cout << nMatrix[i][j] << " ";
            }
            cout << endl;
        }
        
    }
    size_t graph::get_vertexNum()
    {
        return nMatrix.size();
    }
    int graph::getEdgeWeight(size_t x, size_t y) const
    {
        return this->nMatrix[x][y];
    }
    bool graph::hasCycle() const
    {
        return this->Cycle;
    }
    void graph::setCycle (bool v) 
    {
        this->Cycle = v; 
    }
    bool graph::hasNegaCycle() const
    {
        return this->NegaCycles;
    }
    void graph::setNegaCycle(bool v)
    {
        this->NegaCycles = v;
    }

    graph operator+ (graph& g1 , graph& g2)
    {
        if(g1.get_vertexNum()!=g2.get_vertexNum())
        {
            exit(1);
        }
        size_t size = g1.get_vertexNum();
        vector<vector<int>> mat(size, vector<int>(size));
        for (size_t i = 0; i < g1.get_vertexNum(); i++)
        {
            for (size_t j = 0; j < g2.get_vertexNum(); j++)
            {
                mat[i][j] = g1.nMatrix[i][j]+g2.nMatrix[i][j];
            }
        }
        graph g (mat);
        g.setCycle(g1.hasCycle() || g2.hasCycle());
        g.setNegaCycle(g1.hasNegaCycle() || g2.hasNegaCycle());
        return g;
    }
     graph operator+= (graph& g1 , graph& g2)
    {
        if(g1.get_vertexNum()!=g2.get_vertexNum())
        {
            exit(1);
        }
        for (size_t i = 0; i < g1.get_vertexNum(); i++)
        {
            for (size_t j = 0; j < g2.get_vertexNum(); j++)
            {
                 g1.nMatrix[i][j] += g2.nMatrix[i][j];
            }
        }
        return g1;
    }
    graph operator- (graph& g1 , graph& g2)
    {
        if(g1.get_vertexNum()!=g2.get_vertexNum())
        {
            exit(1);
        }
        size_t size = g1.get_vertexNum();
        vector<vector<int>> mat(size, vector<int>(size));
        for (size_t i = 0; i < g1.get_vertexNum(); i++)
        {
            for (size_t j = 0; j < g2.get_vertexNum(); j++)
            {
                mat[i][j] = g1.nMatrix[i][j] - g2.nMatrix[i][j];
            }
        }
        graph g (mat);
        g.setCycle(g1.hasCycle() || g2.hasCycle());
        g.setNegaCycle(g1.hasNegaCycle() || g2.hasNegaCycle());
        return g;
    }
     graph operator-= (graph& g1 , graph& g2)
    {
        if(g1.get_vertexNum()!=g2.get_vertexNum())
        {
            exit(1);
        }
        for (size_t i = 0; i < g1.get_vertexNum(); i++)
        {
            for (size_t j = 0; j < g2.get_vertexNum(); j++)
            {
                 g1.nMatrix[i][j] -= g2.nMatrix[i][j];
            }
        }
        return g1;
    }
    void operator++ (graph& g1)
    {
        for (size_t i = 0; i < g1.get_vertexNum(); i++)
        {
            for (size_t j = 0; j < g1.get_vertexNum(); j++)
            {
                g1.nMatrix[i][j]++;
            }
        }
    }
    void operator-- (graph& g1)
    {
        for (size_t i = 0; i < g1.get_vertexNum(); i++)
        {
            for (size_t j = 0; j < g1.get_vertexNum(); j++)
            {
                g1.nMatrix[i][j]--;
            }
        }
    }
    bool operator== (graph& g1, graph& g2)
    {
        if(g1.get_vertexNum() != g2.get_vertexNum())
        {
            return false;
        }
        for(size_t i = 0 ; i< g1.get_vertexNum(); i++)
        {
            for(size_t j=0 ; j<g1.get_vertexNum() ; j++)
            {
                if(g1.nMatrix[i][j] != g2.nMatrix[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator< (graph& g1 , graph& g2)
    {
        if (g1.get_vertexNum()>g2.get_vertexNum())
        {
            return false;
        }
        for(size_t i = 0 ; i< g1.get_vertexNum(); i++)
        {
            for(size_t j=0 ; j<g1.get_vertexNum() ; j++)
            {
                if(g1.nMatrix[i][j] != g2.nMatrix[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator> (graph& g1 , graph& g2)
    {
        if (g1.get_vertexNum() < g2.get_vertexNum())
        {
            return false;
        }
        for(size_t i = 0 ; i< g2.get_vertexNum(); i++)
        {
            for(size_t j=0 ; j<g2.get_vertexNum() ; j++)
            {
                if(g1.nMatrix[i][j] != g2.nMatrix[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator<= (graph& g1 , graph& g2)
    {
        return (g1<g2 || g1 == g2);
    }
    bool operator>= (graph& g1 , graph& g2)
    {
        return (g1>g2 || g1 == g2);
    }
    bool operator!= (graph& g1,graph& g2)
    {
        if (g1==g2)
        {
            return false;
        }
        return true;
    }
    graph operator* (graph& g1 , graph& g2)
    {
        if(g1.get_vertexNum() != g2.get_vertexNum())
        {
            exit(1);
        }
        size_t size = g1.get_vertexNum();
        vector<vector<int>> mat(size, vector<int>(size));
        for (size_t i = 0; i < g1.get_vertexNum(); i++)
        {
            for (size_t j = 0; j < g1.get_vertexNum(); i++)
            {
                for (size_t k = 0; k < g1.get_vertexNum(); i++)
                {
                    mat[i][j] = g1.nMatrix[i][k] * g1.nMatrix[k][j];
                }
                
            }
            
        }
        graph g (mat);
        g.setCycle(g1.hasCycle() || g2.hasCycle());
        g.setNegaCycle(g1.hasNegaCycle() || g2.hasNegaCycle());
        return g;
    }
    void operator*= (graph& g1 , int x)
    {
        for (size_t i = 0; i < g1.get_vertexNum(); i++)
            {
                for (size_t j = 0; i < g1.get_vertexNum(); i++)
                {
                    g1.nMatrix[i][j] *= x;
                }
                
            }
    }
    void operator/= (graph& g1 , int x)
    {
        for (size_t i = 0; i < g1.get_vertexNum(); i++)
            {
                for (size_t j = 0; i < g1.get_vertexNum(); i++)
                {
                    g1.nMatrix[i][j] /= x;
                }
                
            }
    }
    ostream& operator<<(ostream& out, graph& g) {
        for (size_t i = 0; i < g.nMatrix.size(); i++) {
            out << "[";
            for (size_t j = 0; j < g.nMatrix.size(); j++) {
                out << g.nMatrix[i][j];
                if (j < g.get_vertexNum() - 1) {
                    out << ", ";
                }
            }
            out << "]" << endl;
            if (i < g.get_vertexNum() - 1) {
                out << ", ";
            }
        }
        return out;
    }
}