#include <iostream>
#include "./src/graph.hpp"

int main () {
    
    Graph graph;// error in this line
    graph.Build("tests/test_data/data_edge_test2.csv", "tests/test_data/data_vertex_test2.csv");
    
    // Connected Components
    std::cout << '\n';
    std::cout << "___Connected Components___ " << std::endl;
    graph.ConnectedComponents();
    std::vector<std::vector<Node>> connected_component2 = graph.GetConnectedComponents();    

    std::vector<std::vector<std::string>> cc_result;
    cc_result.resize(connected_component2.size());
    for (unsigned i = 0; i < connected_component2.size(); i++) {
        for (unsigned j = 0; j < connected_component2.at(i).size(); j++) {
            std::string the_school = connected_component2.at(i).at(j).name;
            if (!the_school.empty()) {
                cc_result[i].push_back(the_school);
            }
        }
    }

    for (unsigned i = 0; i < cc_result.size(); i++) {
        std::vector<std::string> cc = cc_result[i];
        for (auto elem : cc) {
            std::cout << elem << ',';   
        }
        std::cout << '\n';
    }

    // Adjacency List
    std::cout << "___Adjacency List___" << std::endl;    std::vector<std::vector<Node>> adj = graph.GetAdjacencyLists();
    for (unsigned i = 0; i < adj.size(); i++) {
        for (unsigned j = 0; j < adj.at(i).size(); j++) {
            std::cout << adj.at(i).at(j).name << ", ";
        }
        std::cout << std::endl;
    }
    
    // Betweenness Centrality
    graph.Brandes();
    std::vector<double> VofBetweenness;
    VofBetweenness = graph.GetBetweeness();
    std::cout << "\n";
    std::cout << "___Betweeness___" << std::endl;
    for (auto elem: VofBetweenness) {
        std::cout << elem << std::endl;
    }
 
    return 0;
}
