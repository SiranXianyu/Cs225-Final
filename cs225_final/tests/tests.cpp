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
