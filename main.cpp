#include "Graph.h"
#include "Dijkstra.h"
#include "PathReconstructor.h"
#include "GraphLoader.h"
#include "Astar.h"
#include <iostream> 
#include <chrono>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

int main()
{
    Graph g = GraphLoader::loadFromJSON("data/graph_data.json");
    
    std:: cout << "Graph loaded " << g.getNodes().size() << " nodes successfully." << std::endl;
    
    long long idSource;
    std::cout << "Enter the source node ID: ";
    std::cin >> idSource;
    
    long long idDestination;
    std::cout << "Enter the destination node ID: ";
    std::cin >> idDestination;

   
    // ------Dijkstra Algorithm------
    Dijkstra dijkstra(g);
    auto start1 = std::chrono::high_resolution_clock::now();
    dijkstra.run(g, idSource);
    auto end1 = std::chrono::high_resolution_clock::now();
    double dijkstraTime = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count() / 1000.0;
    PathReconstructor dijkstraPathReconstructor(dijkstra.getAllPrevious());
    std::vector<long long> dijkstraPath = dijkstraPathReconstructor.getPathTo(idDestination);
    long long dijkstraNumOfNodes = dijkstra.getNumberOfNodes();
    double dijkstraDist = dijkstra.getDistance(idDestination);
    std::vector<long long> dijkstraNodes = g.getNodes();

    // ------A* Algorithm------
    Astar astar(g);
    auto start2 = std::chrono::high_resolution_clock::now();
    astar.run(g, idSource, idDestination);
    auto end2 = std::chrono::high_resolution_clock::now();
    double astarTime = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() / 1000.0;
    PathReconstructor astarPathReconstructor(astar.getAllPrevious());
    std::vector<long long> astarPath = astarPathReconstructor.getPathTo(idDestination);
    long long astarNumOfNodes = astar.numberOfVisitedNodes();
    double astarDist = astar.getDistance(idDestination);
    std::vector<long long> astarNodes = astar.getNodes();

    // ---- Results ----
    std::cout << "=== Dijkstra ===\n";
    std::cout << "Time: " << dijkstraTime << " ms\n";
    std::cout << "Nodes visited: " << dijkstraNumOfNodes << "\n";
    std::cout << "Distance: " << dijkstraDist << " m\n\n";
    
    std::cout << "=== A* ===\n";
    std::cout << "Time: " << astarTime << " ms\n";
    std::cout << "Nodes visited: " << astarNumOfNodes << "\n";
    std::cout << "Distance: " << astarDist << " m\n\n";
    
    // ---- Validation ----
    if (std::abs(dijkstraDist - astarDist) < 0.01) {
        std::cout << "✓ Both algorithms agree on shortest distance\n";
    } else {
        std::cout << "✗ MISMATCH! Dijkstra=" << dijkstraDist 
                   << " vs A*=" << astarDist << "\n";
        std::cout << "There is a bug somewhere!\n";
    }
    
    std::cout << "\nSpeedup (nodes): " 
               << (double)dijkstraNumOfNodes / astarNumOfNodes << "x\n";
    
    
    // visualization data
    json output;

    output["dijkstra"]["visited"] = dijkstraNodes;
    output["dijkstra"]["path"] = dijkstraPath;
    output["dijkstra"]["distance"] = dijkstraDist;

    output["astar"]["visited"] = astarNodes;
    output["astar"]["path"] = astarPath;
    output["astar"]["distance"] = astarDist;

    std::ofstream out("comparison_result.json");
    out << output.dump(2);
    return 0;
}
// To build project
// g++ main.cpp Graph.cpp Dijkstra.cpp PathReconstructor.cpp GraphLoader.cpp Astar.cpp -o main.exe
// ./main.exe