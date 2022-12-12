#include "graph.hpp"

void Graph::ConnectedComponents() {
    bool* visited = new bool[nodes_.size()]; 
    
    // set all visited status to be false;
    for (unsigned i = 0; i < nodes_.size(); i++) {
        visited[i] = false;
    }
    
    // start with the first school, the order of school is determined by school_number
    for (unsigned school_Number = 0; school_Number < nodes_.size(); school_Number++) {
        // if the school has not been visited
        if (visited[school_Number] == false) {
            std::vector<Node> one_connected_component = BFS(school_Number, visited);
            connected_components.push_back(one_connected_component);
        }
    }
}

// BFS traversal
std::vector<Node> Graph::BFS(unsigned school_number, bool visited[]) {
    visited[school_number] = true;
    std::queue<Node> schools;
    schools.push(nodes_.at(school_number));
    std::vector<Node> output;
    while (!schools.empty()) {
        Node n = schools.front();
        output.push_back(n);
        schools.pop();
        std::vector<Node> neighbors = adjacency_lists_.at(n.school_number);
        for (auto i: neighbors) {
            if (!visited[i.school_number]) {
                visited[i.school_number] = true;
                schools.push(i);
            }
        }
    }
    return output;
}