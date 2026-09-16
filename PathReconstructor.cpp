#include "PathReconstructor.h"

std::vector<long long> PathReconstructor::getPathTo(long long v)
{
    std::vector<long long> path;
    while(~v)
    {
        path.push_back(v);
        v = previous[v];
    }   
    for (int i=0;i<path.size() / 2;i++) // reverse instead of call algorithm
    {
        int j = path.size() - i - 1;
        // swap
        path[i] += path[j];
        path[j] = path[i] - path[j];
        path[i] = path[i] - path[j];
    }
    return path;
}