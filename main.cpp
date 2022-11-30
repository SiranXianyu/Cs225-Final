#include <iostream>
#include "./src/graph.h"
#include "./src/graph.cpp"
int main () {
    std::cout << "Hello" << std::endl;
    return 0;
    Graph graph;
    std::vector<Node> schools_list = graph.getNodes();

    //Cout all the schools
    for (unsigned k = 0; k < schools_list.size(); k++) {
        std::cout << schools_list.at(k).name << std::endl;
    }
}
