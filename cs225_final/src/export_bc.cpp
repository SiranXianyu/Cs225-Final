#include "graph.hpp"
#include <string>
#include <fstream>
#include <vector>

/**
 * Make a CSV file of Betweenness Centrality
 * @param Betweenness : a vector of pairs, which stores the schools'name 
 * and its betweenness centrality
 */ 
void ExportBC(std::vector<std::pair<std::string, double>> Betweenness) {
    // create an output filestream object;
    std::ofstream myFile("Betweenness_Centrality_Table");
    
    for (auto pair : Betweenness) {
        std::string school = pair.first;
        double BC = pair.second;
        myFile << school << ',' << BC << '\n';
    }

    myFile.close();
}
