#pragma once
#include<unordered_map>
#include<vector>
#include<utility>
#include<queue>
#include<set>

class Graph
{
private:
    std::unordered_map<long long, std::vector<std::pair<long long, double>>> adj;
    std::unordered_map<long long, std::pair<double, double>> coordinates;
public:
    bool isNode(long long u);
    int countNode(long long u);
    void addEdge(long long u, long long v, double w);
    std::vector<std::pair<long long, double>> getNeighbors(long long u);
    std::vector<long long> getNodes();
    void setCoordinate(long long u, std::pair<double, double> coordinate);
    std::pair<double, double> getCoordinate(long long u);
};