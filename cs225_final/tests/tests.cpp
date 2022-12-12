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
    graph.Build("data_edge_test0.csv", "tests/test_data/data_vertex_test0.csv");

    // adj & Connected Components
    std::vector<std::vector<Node>> adj = graph.GetAdjacencyLists();
    graph.ConnectedComponents();
    std::vector<std::vector<Node>> connected_component_1 = graph.GetConnectedComponents();    

    // simple test - Count the number of connected_components;
    unsigned answer = 2; 
    unsigned num_of_subgraphs = connected_component_1.size();
    REQUIRE(answer == num_of_subgraphs);

    // exact test - one to one correspondence
    std::vector<std::vector<std::string>> cc_result_1;
    cc_result_1.resize(connected_component_1.size());
    for (unsigned i = 0; i < connected_component_1.size(); i++) {
        for (unsigned j = 0; j < connected_component_1.at(i).size(); j++) {
            std::string the_school = connected_component_1.at(i).at(j).name;
            if (!the_school.empty()) {
                cc_result_1[i].push_back(the_school);
            }
        }
    }

    std::vector<std::string> answer_1{"UIUC"};
    std::vector<std::string> answer_2{"Purdue"};
    REQUIRE(cc_result_1[0] == answer_1);
    REQUIRE(cc_result_1[1] == answer_2);
}

TEST_CASE("BST & Connected component Test 2", "[Simple Case]") {
    Graph graph;
    // Read test 0
    graph.Build("tests/test_data/data_edge_test1.csv", "tests/test_data/data_vertex_test1.csv");

    // adj & Connected Components
    std::vector<std::vector<Node>> adj = graph.GetAdjacencyLists();
    graph.ConnectedComponents();
    std::vector<std::vector<Node>> connected_component_2 = graph.GetConnectedComponents();    

    // simple test - Count the number of connected_components;
    unsigned answer = 2; 
    unsigned num_of_subgraphs = connected_component_2.size();
    REQUIRE(answer == num_of_subgraphs);

    // exact test - one to one correspondence
    std::vector<std::vector<std::string>> cc_result_2;
    cc_result_2.resize(connected_component_2.size());
    for (unsigned i = 0; i < connected_component_2.size(); i++) {
        for (unsigned j = 0; j < connected_component_2.at(i).size(); j++) {
            std::string the_school = connected_component_2.at(i).at(j).name;
            if (!the_school.empty()) {
                cc_result_2[i].push_back(the_school);
            }
        }
    }

    std::vector<std::string> answer_1{"UIUC","NU","Purdue"};
    std::vector<std::string> answer_2{"UChicago"};
    REQUIRE(cc_result_2[0] == answer_1);
    REQUIRE(cc_result_2[1] == answer_2);
}

TEST_CASE("BST & Connected component Test 3", "[Complex Case]") {
    Graph graph;
    // Read test 0
    graph.Build("tests/test_data/data_edge_test2.csv", "tests/test_data/data_vertex_test2.csv");

    // adj & Connected Components
    std::vector<std::vector<Node>> adj = graph.GetAdjacencyLists();
    graph.ConnectedComponents();
    std::vector<std::vector<Node>> connected_component_3 = graph.GetConnectedComponents();    

    // simple test - Count the number of connected_components;
    unsigned answer = 3; 
    unsigned num_of_subgraphs = connected_component_3.size();
    REQUIRE(answer == num_of_subgraphs);

    // exact test - one to one correspondence
    std::vector<std::vector<std::string>> cc_result_3;
    cc_result_3.resize(connected_component_3.size());
    for (unsigned i = 0; i < connected_component_3.size(); i++) {
        for (unsigned j = 0; j < connected_component_3.at(i).size(); j++) {
            std::string the_school = connected_component_3.at(i).at(j).name;
            if (!the_school.empty()) {
                cc_result_3[i].push_back(the_school);
            }
        }
    }

    std::vector<std::string> answer_1{"UIUC","NU","Purdue","MIT","UChicago"};
    std::vector<std::string> answer_2{"Harvard"};
    std::vector<std::string> answer_3{"U_of_T"};
    REQUIRE(cc_result_3[0] == answer_1);
    REQUIRE(cc_result_3[1] == answer_2);
    REQUIRE(cc_result_3[2] == answer_3);
}

TEST_CASE("Brandes algorithm Test 1", "[6 Schools]]") {
    Graph graph;

    // Read test 1
    graph.Build("tests/test_data/data_BC_edge_test0.csv", "tests/test_data/data_BC_vertex_test0.csv");
    graph.Brandes();

    // The answer :
    std::vector<double> answer{1,1.5,1.5,2.5,2.5,0};

    // Result
    std::vector<double> VofBetweenness;
    VofBetweenness = graph.GetBetweeness();

    REQUIRE(answer == VofBetweenness);
}


TEST_CASE("Brandes algorithm Test 2", "[5 Schools]") {
    Graph graph;

    // Read test 1
    graph.Build("tests/test_data/data_BC_edge_test1.csv", "tests/test_data/data_BC_vertex_test1.csv");
    graph.Brandes();

    // The answer :
    std::vector<double> answer{0,3,1,1,0};

    // Result
    std::vector<double> VofBetweenness;
    VofBetweenness = graph.GetBetweeness();

    REQUIRE(answer == VofBetweenness);
}

TEST_CASE("Brandes algorithm Test 3", "[6 Schools]") {
    Graph graph;

    // Read test 1
    graph.Build("tests/test_data/data_BC_edge_test2.csv", "tests/test_data/data_BC_vertex_test2.csv");
    graph.Brandes();

    // The answer :
    std::vector<double> answer{6,6,0,0,0,0};

    // Result
    std::vector<double> VofBetweenness;
    VofBetweenness = graph.GetBetweeness();

    REQUIRE(answer == VofBetweenness);
}