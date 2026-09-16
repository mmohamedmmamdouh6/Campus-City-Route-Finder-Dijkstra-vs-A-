#include "Graph.h"

bool Graph::isNode(long long u)
{
    return adj.count(u);
}

int Graph::countNode(long long u)
{
    if (isNode(u)) return adj[u].size();
    return 0;
}

void Graph::addEdge(long long u, long long v, double w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

std::vector<std::pair<long long, double>> Graph::getNeighbors(long long u)
{
    if (!isNode(u)) return {};
    
    return adj[u];
}

std::vector<long long> Graph::getNodes()
{
    std::vector<long long> nodes;
    for (auto &it : adj) 
        nodes.push_back(it.first);
    return nodes;
}

void Graph::setCoordinate(long long u, std::pair<double, double> coordinate)
{
    if (!isNode(u)) return;
    coordinates[u] = coordinate;
}

std::pair<double, double>Graph::getCoordinate(long long u)
{
    if (!isNode(u)) return {0.0, 0.0};
    
    return coordinates[u];
}
