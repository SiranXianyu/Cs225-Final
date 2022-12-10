#include <iostream>
#include "./src/graph.hpp"

int main () {
    
    Graph graph;// error in this line
    graph.Build();
    graph.ConnectedComponents();
    std::vector<std::vector<Node> > connected_component = graph.getConnectedComponents();
    for (unsigned i = 0; i < connected_component.size(); i++) {
        for (unsigned j = 0; j < connected_component.at(i).size(); j++) {
            std::cout << connected_component.at(i).at(j).name << ", ";
        }
        std::cout << std::endl;
    }
    graph.brandes();
    graph.printBetweenness();
    return 0;
}
