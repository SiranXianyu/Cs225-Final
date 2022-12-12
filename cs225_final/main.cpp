#include <iostream>
#include "./src/graph.hpp"

int main () {
    
    Graph graph;// error in this line
    graph.Build("data_edge_test2.csv", "data_vertex_test2.csv");

    // adjacency_lists_
    // std::vector<std::vector<Node>> adjacency_lists_;

/*
    std::cout << "Connected Components:" << std::endl;
    graph.ConnectedComponents();
    std::vector<std::vector<Node>> connected_component = graph.getConnectedComponents();
    for (unsigned i = 0; i < connected_component.size(); i++) {
        for (unsigned j = 0; j < connected_component.at(i).size(); j++) {
            std::cout << connected_component.at(i).at(j).name;
        }
        std::cout << std::endl;
    }
*/
    std::cout << "Connected Components:" << std::endl;
    graph.ConnectedComponents();
    std::vector<std::vector<Node>> connected_component2 = graph.getConnectedComponents();    

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
        std::cout << "size: " << cc.size() << std::endl;
        for (auto elem : cc) {
            std::cout << elem << std::endl;   
        }
    }

/*
    std::cout << "____________" << std::endl;
    std::vector<std::vector<Node>> adj = graph.getAdjacencyLists();
    for (unsigned i = 0; i < adj.size(); i++) {
        for (unsigned j = 0; j < adj.at(i).size(); j++) {
            std::cout << adj.at(i).at(j).name << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "____________" << std::endl;
    
    graph.brandes();
    std::vector<double> VofBetweenness;
    VofBetweenness = graph.getBetweeness();
    std::cout << "___Betweeness___" << std::endl;
    for (auto elem: VofBetweenness) {
        std::cout << elem << std::endl;
    }

    // graph.printBetweenness();
 */
    return 0;
}
