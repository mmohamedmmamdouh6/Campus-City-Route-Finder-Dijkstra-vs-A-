#pragma once
#include "Graph.h"

struct NodeA
{
    long long u;
    double f, g;

    NodeA(long long u, double f, double g)
    {
        this->u = u;
        this->f = f;
        this->g = g;
    }
    bool operator>(const NodeA& other) const
    {
        return f > other.f;
    }
};
class Astar
{
private:
    std::priority_queue<NodeA, std::vector<NodeA>, std::greater<NodeA>> pq;
    std::unordered_map<long long, std::pair<double, double>> coordinates;
    std::unordered_map<long long, long long> previous;
    std::unordered_map<long long, double> distance;
    std::set<long long> visited;
public:
    Astar(Graph& graph);
    void run(Graph& graph, long long sourceId, long long targetId);
    long long numberOfVisitedNodes();
    double getDistance(long long u);
    long long getPrevious(long long u);
    std::unordered_map<long long, long long> getAllPrevious();
    std::vector<long long> getNodes();
};