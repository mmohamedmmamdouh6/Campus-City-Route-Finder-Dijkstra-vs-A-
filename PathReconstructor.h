/*
    To enable us to use it on other shortest path algorithms
*/

#pragma once

#include<vector>
#include<unordered_map>
class PathReconstructor
{
private:
    std::unordered_map<long long, long long> previous;
public:
    PathReconstructor(const std::unordered_map<long long, long long>& prev)
    {
        previous = prev;
    }
    std::vector<long long> getPathTo(long long v);
};