#include "GraphLoader.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

Graph GraphLoader::loadFromJSON(const std::string& filePath)
{
    std::ifstream file(filePath);
    json info;

    file >> info;

    Graph g;
    
    for (auto &node : info["nodes"])
    {
        long long id = node["id"];
        double lat = node["lat"];
        double lng = node["lng"];

        g.setCoordinate(id, {lat, lng});
    }
    for (auto &edge : info["edges"])
    {
        long long from = edge["from"];
        long long to = edge["to"];
        double weight = edge["distance"];

        g.addEdge(from, to, weight);
    }
    return g;
}