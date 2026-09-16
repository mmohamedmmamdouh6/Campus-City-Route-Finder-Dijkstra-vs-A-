#include "Astar.h"
#include <cmath>

const long long oo = 1e18;

double heuristic(std::pair<double, double> coord1, std::pair<double, double> coord2)
{
    // Implement your heuristic function here
    // we use Haversine

    const double R = 6371000; // Radius of the Earth in meters
    double toRadian = M_PI / 180.0;
    
    double lat1 = coord1.first, lng1 = coord1.second;
    double lat2 = coord2.first, lng2 = coord2.second;
    
    double dlat = lat2 - lat1;
    double dlng = lng2 - lng1;

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1 * toRadian) * cos(lat2 * toRadian) *
               sin(dlng / 2) * (sin(dlng / 2));
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c; // in meters
}

Astar::Astar(Graph& graph)
{
    // Initialize the distance
    std::vector<long long> nodes = graph.getNodes();
    for (long long node : nodes)
    {
        distance[node] = oo;
        previous[node] = -1;
        coordinates[node] = graph.getCoordinate(node);
    }
}

void Astar::run(Graph& graph, long long sourceId, long long targetId)
{
    // Initialize the distance for the source node
    distance[sourceId] = 0.0;
    pq.push(NodeA(sourceId, 0.0 + heuristic(graph.getCoordinate(sourceId), 
                                graph.getCoordinate(targetId)),
                                0.0));

    while (!pq.empty())
    {
        auto [u, f, g] = pq.top();
        pq.pop();

        if (visited.find(u) != visited.end())
            continue;
        visited.insert(u);

        // If we can stop
        if (u == targetId)
            break;

        // Go to the neighbors of the current node
        std::vector<std::pair<long long, double>> neighbors = graph.getNeighbors(u);
        for (auto [v, w] : neighbors)
        {
            double newG = g + w;
            if (newG < distance[v])
            {
                distance[v] = newG;
                previous[v] = u;

                // f = g + h
                double newH = heuristic(graph.getCoordinate(v), 
                                        graph.getCoordinate(targetId));
                double newF = newG + newH;
                pq.push(NodeA(v, newF, newG));
            }
        }
    }
}

long long Astar::numberOfVisitedNodes()
{
    return visited.size();
}

double Astar::getDistance(long long u)
{
    return distance[u];
}

long long Astar::getPrevious(long long u)
{
    return previous[u];
}

std::unordered_map<long long, long long> Astar::getAllPrevious()
{
    return previous;
}

std::vector<long long> Astar::getNodes()
{
    std::vector<long long> nodes;
    for (long long node : visited)
    {
        nodes.push_back(node);
    }
    return nodes;
}