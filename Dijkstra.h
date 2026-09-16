#pragma once

#include "Graph.h"

struct Node
{
    double w;
    long long v;
    
    Node(double w, long long v)
    {
        this->v = v;
        this->w = w;
    }

    bool operator>(const Node& other) const 
    {
        return w > other.w; // min heap
    } 
};

class Dijkstra
{
private:
    std::set<long long> visited;
    std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
    std::unordered_map<long long, long long> previous;
    std::unordered_map<long long, double> distance;
public:
    Dijkstra(Graph &g);
    void run(Graph &g, long long source);
    long long getNumberOfNodes();
    long long getPrevious(long long u);
    double getDistance(long long u);
    std::unordered_map<long long, long long> getAllPrevious();
};