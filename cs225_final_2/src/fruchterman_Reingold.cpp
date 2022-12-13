#include "graph.hpp"

void Graph::updateCC() {
    for (unsigned k = 0; k < connected_components.size(); k++) {
        for (unsigned l = 0; l < connected_components.at(k).size(); l++) {
            double c = nodes_.at(connected_components.at(k).at(l).school_number).centrality;
            connected_components.at(k).at(l).centrality = c;
        }
    }
}

//these functions are used for drawing images
//this function distribute vertex in one connected components randomly
std::vector<Node> Graph::Distribute(std::vector<Node> cc) {
    std::vector<Node> coordinated_connected_components;
    for (unsigned i = 0; i < cc.size(); i++) {
        //retrieve two random number(coordinates) between [0 and 999]
        //assign coordinates to each school
        //if the coordinates exists, assign again 
        Node school = cc.at(i);
        unsigned c_x = 0; unsigned c_y = 0;
        do {          
            int r_x = 0 + (rand() % 1200);
            int r_y = 0 + (rand() % 1200);
            c_x = (unsigned)r_x;
            c_y = (unsigned)r_y;
        } while (image[c_x][c_y] == true);
        school.x = c_x; school.y = c_y;
        //std::cout << c_x << "   " <<c_y << std::endl;
        coordinated_connected_components.push_back(school);
        image[c_x][c_y] = true;
    }
    return coordinated_connected_components;
}

//calculate absolute attractive force between two vertex k (x1 - x2)
//produce force as scaler
std::pair<double, double> Graph::CalculateAttractive(Node n1, Node n2) {
    //std::cout << "-------Attractive Force-------" << std::endl;
    double parameter = 0.1;
    double d = std::sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y));
    //std::cout << "n1 coordinate" << "(" << n1.x << ", " << n1.y << ")" << std::endl;
    //std::cout << "n2 coordinate" << "(" << n2.x << ", " << n2.y << ")" << std::endl;
    //std::cout << "distance = " << d <<std::endl;
    //std::cout << "n1.centrality = " << n1.centrality << std::endl;
    //std::cout << "n2.centrality = " << n2.centrality << std::endl;
    double force = d * parameter;
    //std::cout << "force = " << force << std::endl;
    double force_x = force * (std::abs((int)n1.x - (int)n2.x) / d );
    double force_y = force * (std::abs((int)n1.y - (int)n2.y) / d );
    std::pair<double, double> f(force_x, force_y);
    //std::cout << "-------Attractive Force End-------" << std::endl;
    return f;
}

//calculate absolute repulsive force between two vertex c1 c2 k / d^2
//produce force as scaler
std::pair<double, double> Graph::CalculateRepulsive(Node n1, Node n2) {
    //std::cout << "-------Repulsive Force-------" << std::endl;
    double d_2 = (n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y);
    double k = 1;
    //std::cout << "n1 coordinate" << "(" << n1.x << ", " << n1.y << ")" << std::endl;
    //std::cout << "n2 coordinate" << "(" << n2.x << ", " << n2.y << ")" << std::endl;
    //std::cout << "n1.centrality = " << n1.centrality << std::endl;
    //std::cout << "n2.centrality = " << n2.centrality << std::endl;
    //std::cout << "distance = " << (int)d_2 << std::endl;
    double force = n1.centrality * n2.centrality * k / d_2;
    //std::cout << "force = " << (int)force << std::endl;
    double force_x = force * (std::abs((int)n1.x - (int)n2.x) / std::sqrt(d_2) );
    double force_y = force * (std::abs((int)n1.y - (int)n2.y) / std::sqrt(d_2) );
    std::pair<double, double> f(force_x, force_y);
    //std::cout << "-------Repulsive Force End-------" << std::endl;
    return f;
}

std::vector<std::pair<double, double>> Graph::CalculateNetForce(std::vector<Node> cc) {
    std::vector<std::pair<double, double>> nf_cc;
    for (unsigned k = 0; k < cc.size(); k++) {
        Node school = cc.at(k);
        std::pair<double, double> netforce(0, 0);
        //calculate the netforce of a single vertex in the whole connected components
        std::vector<Node> neighbors_origin = adjacency_lists_.at(school.school_number);
        std::vector<Node> neighbors;
        for (unsigned k = 0; k < neighbors_origin.size(); k++) {
            for (unsigned l = 0; l < cc.size(); l++) {
                if (cc.at(l).name == neighbors_origin.at(k).name) {
                    neighbors.push_back(cc.at(l));
                }
            }
        }
        
        for (unsigned i = 0; i < neighbors.size(); i++) {
            std::pair<double, double> attractive_force = CalculateAttractive(school, neighbors.at(i));
            std::pair<double, double> repulsive_force = CalculateRepulsive(school, neighbors.at(i));
            
            //add direction
            double direction_attractive_x = ((int)neighbors.at(i).x - (int)school.x) / std::abs((int)neighbors.at(i).x - (int)school.x);
            double direction_attractive_y = ((int)neighbors.at(i).y - (int)school.y) / std::abs((int)neighbors.at(i).y - (int)school.y);
            
            attractive_force.first = attractive_force.first * direction_attractive_x;
            attractive_force.second = attractive_force.second * direction_attractive_y;
            double direction_repulsive_x = ((int)school.x - (int)neighbors.at(i).x) / std::abs((int)neighbors.at(i).x - (int)school.x);
            double direction_repulsive_y = ((int)school.y - (int)neighbors.at(i).y) / std::abs((int)neighbors.at(i).y - (int)school.y);
            repulsive_force.first = repulsive_force.first * direction_repulsive_x;
            repulsive_force.second = repulsive_force.second * direction_repulsive_y;
            netforce.first += attractive_force.first;
            netforce.first += repulsive_force.first;
            netforce.second += attractive_force.second;
            netforce.second += repulsive_force.second;
            
        }
        nf_cc.push_back(netforce);
    }
    return nf_cc;
}
