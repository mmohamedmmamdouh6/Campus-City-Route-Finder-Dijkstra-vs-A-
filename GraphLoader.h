#pragma once
#include "Graph.h"
#include <string>

class GraphLoader
{
public:
    static Graph loadFromJSON(const std::string& filePath);
};