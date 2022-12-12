#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
#include <stdexcept>
#include <iostream>
#include "../src/graph.hpp"

TEST_CASE("BST & Connected component Test 1", "[Special Case]") {
    Graph graph;

    // Read test 0
    graph.Build("data_edge_test0.csv", "data_vertex_test0.csv");

    // adj
    std::vector<std::vector<Node>> adj = graph.getAdjacencyLists();
    
    for (unsigned i = 0; i < adj.size(); i++) {
        for (unsigned j = 0; j < adj.at(i).size(); j++) {
            std::cout << adj.at(i).at(j).name << ", ";
        }
        std::cout << std::endl;
    }

    // Connected Components
    graph.ConnectedComponents();
    // the answer
    unsigned answer = 2;
    // Count the number of connected_components;
    std::vector<std::vector<Node>> connected_component = graph.getConnectedComponents();
    unsigned num_of_subgraphs = connected_component.size();

    REQUIRE(answer == num_of_subgraphs);
}

TEST_CASE("BST & Connected component Test 2", "[Simple Case]") {
    Graph graph;

    // Read test 1
    graph.Build("data_edge_test1.csv", "data_vertex_test1.csv");
    // Connected Components
    graph.ConnectedComponents();
    // the answer
    unsigned answer = 2;
    // Count the number of connected_components;
    std::vector<std::vector<Node>> connected_component = graph.getConnectedComponents();
    unsigned num_of_subgraphs = connected_component.size();

    REQUIRE(answer == num_of_subgraphs);
}

TEST_CASE("BST & Connected component Test 3", "[Complex Case]") {
    Graph graph;

    // Read test 1
    graph.Build("data_edge_test2.csv", "data_vertex_test2.csv");
    // Connected Components
    graph.ConnectedComponents();
    // the answer
    unsigned answer = 3;
    // Count the number of connected_components;
    std::vector<std::vector<Node>> connected_component = graph.getConnectedComponents();
    unsigned num_of_subgraphs = connected_component.size();

    REQUIRE(answer == num_of_subgraphs);
}

TEST_CASE("Brandes algorithm Test 1", "[6 Schools]]") {
    Graph graph;

    // Read test 1
    graph.Build("data_BC_edge_test0.csv", "data_BC_vertex_test0.csv");
    graph.brandes();

    // The answer :
    std::vector<double> answer{1,1.5,1.5,2.5,2.5,0};

    // Result
    std::vector<double> VofBetweenness;
    VofBetweenness = graph.getBetweeness();

    REQUIRE(answer == VofBetweenness);
}


TEST_CASE("Brandes algorithm Test 2", "[5 Schools]") {
    Graph graph;

    // Read test 1
    graph.Build("data_BC_edge_test1.csv", "data_BC_vertex_test1.csv");
    graph.brandes();

    // The answer :
    std::vector<double> answer{0,3,1,1,0};

    // Result
    std::vector<double> VofBetweenness;
    VofBetweenness = graph.getBetweeness();

    REQUIRE(answer == VofBetweenness);
}

TEST_CASE("Brandes algorithm Test 3", "[6 Schools]") {
    Graph graph;

    // Read test 1
    graph.Build("data_BC_edge_test2.csv", "data_BC_vertex_test2.csv");
    graph.brandes();

    // The answer :
    std::vector<double> answer{6,6,0,0,0,0};

    // Result
    std::vector<double> VofBetweenness;
    VofBetweenness = graph.getBetweeness();

    REQUIRE(answer == VofBetweenness);
}