#include "graph.hpp"

std::vector<std::vector<Node>> Graph::BFS4ST(unsigned source, unsigned target, bool visited[]) {
    std::vector<std::vector<Node>> output;  // store the output paths
    std::vector<std::vector<Node>> schools; // store the current paths (perform as a queue)
    visited[source] = true; // mark the source as visited

    // if the source and target are not in the same connected component, return an empty vector
    for (auto i: connected_components) {
        std::vector<unsigned> c; // store the school numbers of the connected component
        for (auto j: i) c.push_back(j.school_number); // get the school numbers of the connected component

        if (std::find(c.begin(), c.end(), nodes_.at(source).school_number) != c.end()){
            if (std::find(c.begin(), c.end(), nodes_.at(target).school_number) == c.end()){
                return output; // if the source is in the connected component but the target is not, return an empty vector
            } else break; // if the source and target are in the same connected component, break the loop
        }
    }

    // if the source and target are in the same connected component, do the BFS
    schools.push_back({nodes_.at(source)}); // the first path is the source
    bool foundShoretestPath = false; // if the shortest path is found, stop the BFS
    while (!schools.empty()) {
        // get the first path in the queue
        std::vector<Node> current = schools.front();
        schools.erase(schools.begin());
        Node n = current.back();

        // if the current node is the target, add the current path to the output
        if (n.school_number == target){
            output.push_back(current);
            foundShoretestPath = true;
        }
        // if the current path is longer than the shortest path, stop the BFS
        // because the shortest path is already found
        if (foundShoretestPath){
            continue;
        }

        // Add all the neighbors of the current node to the queue
        std::vector<Node> neighbors = adjacency_lists_.at(n.school_number);
        for (auto i: neighbors) {
            if (!visited[i.school_number]) { // if the neighbor is not visited
                visited[i.school_number] = true;
                std::vector<Node> new_path = current;                    
                new_path.push_back(i);
                schools.push_back(new_path);
            }
        }
    }
    return output;
}

std::vector<double> Graph::Brandes() {      
    // Set all centrality C(v) to be 0;
    std::vector<double> centrality_;
    for (unsigned i = 0; i < nodes_.size(); i++) {
        centrality_.push_back(0);
    }
    double num_shortest_path[nodes_.size()][nodes_.size()];
    for (unsigned i = 0; i < nodes_.size(); i++) {
        for (unsigned j = 0; j < nodes_.size(); j++){
            // Set all num_shortest_path to be 0;
            memset(num_shortest_path, 0, sizeof(num_shortest_path));
            // Skip if i == j
            if (i == j) continue;
            // Set all visited status to be false;
            bool* visited = new bool[nodes_.size()]; 
            for (unsigned i = 0; i < nodes_.size(); i++) {
                visited[i] = false;
            }
            // Find all shortest paths from i to j
            std::vector<std::vector<Node>> paths = BFS4ST(i, j, visited);
            delete[] visited;
            // Calculate the number of shortest paths from i to j passed through v
            // When checking each path shortest path, increment S(v, t) as appropriate when each
            // inner node v is reached, rather than creating full paths.
            for(auto path: paths){
                for(auto node: path){
                    unsigned v = node.school_number;
                    if (v != i && v != j)
                        num_shortest_path[v][j] += 1;
                }
            }
            
            // Calculate the centrality of each node
            // Divide each S(v, t) by the total number of paths between
            // s and t (i.e., S(s, t)).
            for(unsigned t = 0; t < nodes_.size(); t++){
                if(num_shortest_path[i][j] != 0) 
                    num_shortest_path[t][j] /= num_shortest_path[i][j];
                centrality_[t] += num_shortest_path[t][j]; //Add the result to C(v).
            }
        }
    }
    // Update the centrality for each node in nodes_
    for (unsigned i = 0; i < nodes_.size(); i++) {
        nodes_.at(i).centrality = centrality_[i]/2;
    }
    // Return the centrality vector C(v) of each node v
    return centrality_;
}