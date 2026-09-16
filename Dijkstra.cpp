#include "Graph.h"
#include "Dijkstra.h"

const long long oo = 1e18;
Dijkstra::Dijkstra(Graph &g)
{
    std::vector<long long> nodes = g.getNodes();
    for (long long &node : nodes)
    {
        distance[node] = oo;
        previous[node] = -1;
    }
}

void Dijkstra::run(Graph &g, long long source)
{
    // Initialize the distance for the source node
    distance[source] = 0;
    pq.push(Node(0, source));
    
    while(!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        visited.insert(u);
        if (d != distance[u]) continue;
        std::vector<std::pair<long long, double>> neighbors = g.getNeighbors(u);
        for (auto [v, w] : neighbors)
        {
            if (distance[u] + w < distance[v])
            {
                previous[v] = u;
                distance[v] = distance[u] + w;
                pq.push(Node(distance[v], v));
            }
        }
    }
}
long long Dijkstra::getNumberOfNodes()
{
    return visited.size();
}
long long Dijkstra::getPrevious(long long u)
{
    return previous[u];
} 

double Dijkstra::getDistance(long long u)
{
    return distance[u];
}

std::unordered_map<long long, long long> Dijkstra::getAllPrevious()
{
    return previous;
}