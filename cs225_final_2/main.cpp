#include <iostream>
#include "./src/graph.hpp"
#include "./src/bfs_traversal.cpp"
#include "./src/brandes_algorithm.cpp"
#include "./src/export_bc.cpp"
#include "./src/get_functions.cpp"
#include "./src/fruchterman_Reingold.cpp"

int main () {
    
    Graph graph;
    graph.Build("data/data_edge_617.csv", "data/data_vertex_262.csv");
    graph.ConnectedComponents();
    //graph.Build("tests/test_data/data_BC_edge_test0.csv", "tests/test_data/data_BC_vertex_test0.csv");

    /*
    // Connected Components
    std::cout << '\n';
    std::cout << "___Connected Components___ " << std::endl;
    graph.ConnectedComponents();
    std::vector<std::vector<Node>> connected_component2 = graph.GetConnectedComponents();    

    std::vector<std::vector<std::string>> cc_result;
    cc_result.resize(connected_component2.size());
    for (unsigned i = 0; i < connected_component2.size(); i++) {
        for (unsigned j = 0; j < connected_component2.at(i).size(); j++) {
            std::string the_school = connected_component2.at(i).at(j).name;
            if (!the_school.empty()) {
                cc_result[i].push_back(the_school);
            }
        }
    }

    for (unsigned i = 0; i < cc_result.size(); i++) {
        std::vector<std::string> cc = cc_result[i];
        for (auto elem : cc) {
            std::cout << elem << ',';   
        }
        std::cout << '\n';
    }
    */
    // Betweenness Centrality
    graph.Brandes();
    std::vector<std::pair<std::string, double>> VofBetweenness;
    VofBetweenness = graph.GetNameAndBetweeness();
    /*
    std::cout << "\n";
    std::cout << "___Betweeness___" << std::endl;
    for (auto elem: VofBetweenness) {
        std::cout << elem.first << " - " << elem.second << std::endl;
    }

    // Export Betweenness Centrality
    std::cout << "\n";
    */
    std::cout << "___Betweeness_Export_CSV___" << std::endl;
    ExportBC(VofBetweenness);
    std::cout << "___Table_Created!___" << std::endl;
    
    // Visualization
    graph.updateCC();
    std::vector<std::vector<Node>> cc = graph.GetConnectedComponents();
    std::ofstream myFile("Net_Force_Table");
    for (unsigned i = 0; i < cc.size(); i++) {
        std::vector<Node> coordinated_cc = graph.Distribute(cc.at(i));
        std::vector<std::pair<double, double>> net_force = graph.CalculateNetForce(coordinated_cc);
        for (auto pair : net_force) {
            double force_on_x = pair.first;
            double force_on_y = pair.second;
            myFile << "force on x coordinate = " << force_on_x << ",  " << "force on y coordinate = " << force_on_y  << '\n';
        }
    }
    myFile.close();
    
    return 0;           
}
