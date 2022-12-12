#include <iostream>
#include "./src/graph.hpp"

int main () {
    
    Graph graph;// error in this line
    graph.Build("data_BC_edge_test0.csv", "data_BC_vertex_test0.csv");

    // adjacency_lists_
    // std::vector<std::vector<Node>> adjacency_lists_;

    std::cout << "Connected Components:" << std::endl;
    graph.ConnectedComponents();
    std::vector<std::vector<Node> > connected_component = graph.getConnectedComponents();
    for (unsigned i = 0; i < connected_component.size(); i++) {
        for (unsigned j = 0; j < connected_component.at(i).size(); j++) {
            std::cout << connected_component.at(i).at(j).name << ", ";
        }
        std::cout << std::endl;
    }
    

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
 
    return 0;
}
