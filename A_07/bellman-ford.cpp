#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "graph.h"
#include "graphexamples.h"
using namespace std;

// change this to false to turn off debug print statements
bool debug = true;

// Doesn't work when a negative weight cycle is present
class BellmanFord{
    Graph *graph;
    int v;
    vector<int> distanceVector;

    public:
    BellmanFord()
    {
        initialiseGraph();
        initialiseDistanceVector();
    }

    BellmanFord(Graph *graph)
    {
        this->graph = graph;
        v = graph->returnV();
        initialiseDistanceVector();
    }

    void initialiseDistanceVector()
    {
        distanceVector.push_back(0);
        for(int i = 1; i < v; ++i)
            distanceVector.push_back(INT_MAX);
    }

    void initialiseGraph()
    {
        graph = graphB();
        v = graph->returnV();
        for(int i = 0; i < v; ++i)
        {
            map<int, int> neighbors = graph->returnNeighbors(i);
            if(debug)
            cout<<"node: "<<i<<" neighbors: "<<neighbors.size()<<endl;
        }
    }

    // Time complexity: O(VE)
    void runBellmanFordAlgorithm()
    {
        vector<pair<pair<int, int>, int>> edges = graph->generateEdgeList();
        bool updateFlag = true;
        // O(V)
        for(int r = 0; r < v; ++r) // RUNS V-1 TIMES ORIGINALLY, it runs an additional iteration for checking a negative weight cycle
        {
            // stop looping when you reach the final set of distances
            if(!updateFlag)
                break;
            updateFlag = false;
            // O(E)
            for(auto it = edges.begin(); it != edges.end(); ++it) // in case of a connected graph, max edges are E
            {
                int u = it->first.first;
                int v = it->first.second;
                int weight = it->second;
                if(debug)
                cout<<"edge: "<<u<<"->"<<v<<endl;
                if(weight == INT_MIN)
                {
                    cout<<"An error occured.\n";
                    return;
                }

                // relaxing edge u->v 
                if(distanceVector[u] + weight < distanceVector[v])
                {
                    distanceVector[v] = distanceVector[u] + weight;
                    updateFlag = true;
                    if(r == graph->returnV() - 1)
                    {
                        cout<<"Negative cycle detected. Discarding weights.\n";
                        distanceVector.clear();
                    }
                }
            }
        }
    }

    void printCostTable()
    {
        for(int i = 0; i < distanceVector.size(); ++i)
        {
            cout<<i<<" : "<<distanceVector[i]<<endl;
        }
    }
};

int main()
{
    BellmanFord obj(graphB());
    obj.runBellmanFordAlgorithm();
    obj.printCostTable();

    return 0;
}