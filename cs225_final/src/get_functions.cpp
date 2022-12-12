#include "graph.hpp"

std::vector<Node> Graph::GetNodes() {
    return nodes_;
}

std::vector<std::vector<Node>> Graph::GetAdjacencyLists() {
    return adjacency_lists_;
}

std::vector<std::vector<Node>> Graph::GetConnectedComponents() {
    return connected_components;
}

std::vector<std::pair<std::string, double>> Graph::GetNameAndBetweeness() {
    std::vector<std::pair<std::string, double>> result;
    for (unsigned i = 0; i < nodes_.size(); i++) {
        std::pair<std::string, double> a_row;
        double betweeness_centrality = nodes_.at(i).centrality;
        std::string school= nodes_.at(i).name;
        a_row = std::make_pair(school,betweeness_centrality);
        result.push_back(a_row);
    }
    return result;
}

std::vector<double> Graph::GetBetweeness() {
    std::vector<double> result;
    for (unsigned i = 0; i < nodes_.size(); i++) {
        result.push_back(nodes_.at(i).centrality);
    }
    return result;
}