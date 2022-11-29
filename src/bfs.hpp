//this files is used to do BFS traversal and store several or one connected components
#include "graph.h"
#include <queue>
void Graph::ConnectedComponents() {
    bool* visited = new bool[nodes_.size()]; w  '[`1'
    
    //set all visited status to be false;
    for (unsigned i = 0; i < nodes_.size(); i++) {
        visited[i] = false;
    }
    
    //start with the first school, the order of school is determined by school_number
    for (unsigned school_Number = 0; school_Number < nodes_.size(); school_Number++) {
        //if the school has not been visited
        if (visited[school_Number] == false) {
            std::unordered_set<Node> one_connected_component = BFS(school_Number, visited);
            connected_components.push_back(one_connected_component);
        }
    }


}

std::unordered_set<Node> Graph::BFS(unsigned school_Number, bool visited[]) {
    //mark the current school node as visited
    visited[school_Number] = true;
    std::queue<Node> schools;
    schools.push(nodes_.at(school_Number));
    std::unordered_set<Node> output_set;
    while (!schools.empty()) {
        Node n = queue.front();
        output_set.insert(n);
        schools.pop();
        std::vector<Node> neighbors = adjacency_lists_.at(n.school_number);
        for (auto i: neighbors) {
            if (!visited[i.school_number]) {
                visited[i.school_number] = true;
                schools.push(i);
            }
        }
    }
    return output_set;
    

}
