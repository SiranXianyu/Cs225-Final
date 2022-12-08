//construct a graph class, reading values from csv files and store them 
//we store data in adjacency lists
#pragma once

#include "draw.hpp"
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <queue>

struct Node {
    //the school number is based on the order we read data
    unsigned school_number;
    std::string name;
    unsigned x;
    unsigned y;
    unsigned cited_times;
    double centrality;
};

struct Red {
    unsigned r = 252;
    unsigned g = 25;
    unsigned b = 63;
}

struct Grey {
    unsigned r = 100;
    unsigned g = 100;
    unsigned b = 100;
}

class Graph {
    public:
    //constructor:
    Graph() = default;

    void coutsth() {
        std::cout << "print" <<std::endl;
    }

    void Build() {
        ReadRelations();
        ReadVertices();
        ReadSchools();
        ReadEdges();
        RefineLists();
        for (unsigned x = 0; x < 1000; x++) {
            for (unsigned y = 0; y < 1000; y++) {
                image[x][y] = 0;
            }
        }
    }
    
    void ReadRelations() {
        std::ifstream file_stream;
        file_stream.open("data_edge.csv");
        std::string token;
    
        while (!file_stream.eof()) {
            file_stream >> token;
            unsigned cut_index = token.find(",");
            //the string for the first school
            std::string school_1 = token.substr(0, cut_index);
            //the string for the second school
            std::string school_2 = token.substr(cut_index + 1, token.size() - 1 - cut_index);
            std::pair<std::string, std::string> relation(school_1, school_2);
            relations.push_back(relation);
        }
    }


    void ReadVertices() {
        std::ifstream file_stream;
        file_stream.open("data_vertex.csv");
        std::string token;
        
        while (!file_stream.eof()) {
            file_stream >> token;
            unsigned cut_index = token.find(",");
            //the string for the school
            std::string school = token.substr(0, cut_index);
            //the string for the cited times
            std::string cited_times_string = token.substr(cut_index + 1, token.size() - 1 - cut_index);
            int cited_times = std::stoi(cited_times_string);
            std::pair<std::string, int> university(school, cited_times);
            schools.push_back(university);
        }
        

    }


    void ReadSchools() {
        //the last row has been read two times
        for (unsigned i = 0; i < schools.size() - 1; i++) {
                Node college;
                college.school_number = i;
                college.centrality = 0;
                college.x = 0; college.y = 0;
                college.name = schools.at(i).first;
                college.cited_times = schools.at(i).second;
                nodes_.push_back(college);
        }
    }


    void ReadEdges() {
        //the adjacency list for one school
        //line only contains the school name
        std::vector<std::string> line;
        for (unsigned i = 0; i < relations.size(); i++) {
            std::string school_1 = relations.at(i).first;
            std::string school_2 = relations.at(i).second;
            //if nothing is in the adjacency list for one school
            if (line.empty()) {
                line.push_back(school_1);
            }
            //if the other school has not appeared in the list, we add it, 
            //if it has been in the list, leave it away
            bool contained_in_line = false;
            for (unsigned k = 0; k < line.size(); k++) {
                if (line.at(k) == school_2) {
                    contained_in_line = true;
                }
            }
            if (!contained_in_line) {
                line.push_back(school_2);
            }
            //if the next relation represents a new school, we store 
            //this adjacency list in to our adjacency_lists
            //if it comes to the last line, directly store it.
            if (i == relations.size() - 1 || relations.at(i + 1).first != school_1) {
                //convert vector of strings to vector of nodes
                std::vector<Node> nodes;
                //this time, we push back nodes
                for (unsigned i = 0; i < line.size(); i++) {
                    for (unsigned j = 0; j < nodes_.size(); j++) {
                        if (line.at(i) == nodes_.at(j).name) {
                            nodes.push_back(nodes_.at(j));
                            break;
                        }
                    }
                }
                adjacency_lists_.push_back(nodes);
                line.clear();
                continue;
            }
        }
        //for (unsigned i = 0; i < adjacency_lists_.size(); i++) {
        //    for (unsigned j = 0; j < adjacency_lists_.at(i).size(); j++) {
        //        std::cout << adjacency_lists_.at(i).at(j).name << ", ";
        //    }
        //    std::cout << std::endl;
        //}
    }

    void RefineLists() {
        std::vector<std::vector<Node> >  new_lists;
        for (unsigned school_Number = 0; school_Number < nodes_.size(); school_Number++) {
            bool find_or_not = false;
            for (unsigned k = 0; k < adjacency_lists_.size(); k++) {
                if (adjacency_lists_.at(k).empty()) continue;
                if (adjacency_lists_.at(k).at(0).school_number == school_Number) {
                    std::vector<Node> list = adjacency_lists_.at(k);

                    //delete the first one(the school itself) in each neighbor line, so
                    // that each list only contains all the neighbor
                    list.erase(list.begin());
                    new_lists.push_back(list);
                    find_or_not = true;
                    break;
                }
            }
            //if a school has not relations, we pushback a vacant vector
            if (!find_or_not) {
                std::vector<Node> empty_one;
                new_lists.push_back(empty_one);
            }
        }
        adjacency_lists_ = new_lists;
    }

    //use BFS to do the traversal. The input will be a list of nodes and the output will
    //be a matrix representing the connected components while each line refers to 
    //one connected component. The time complexity will be O(V+E),
    //and the space complexity will be O(V).
    void ConnectedComponents() {
        bool* visited = new bool[nodes_.size()]; 
        
        //set all visited status to be false;
        for (unsigned i = 0; i < nodes_.size(); i++) {
            visited[i] = false;
        }
        
        //start with the first school, the order of school is determined by school_number
        for (unsigned school_Number = 0; school_Number < nodes_.size(); school_Number++) {
            //if the school has not been visited
            if (visited[school_Number] == false) {
                std::vector<Node> one_connected_component = BFS(school_Number, visited);
                connected_components.push_back(one_connected_component);
            }
        }
    }
    std::vector<Node> BFS(unsigned school_number, bool visited[]) {
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


    //store netforce of one connected component into a 2d vector, 
    std::vector<<std::pair<double, double>> CalculateNetForce(std::vector<Node> cc) {
        cc = Distribute(cc);
        std::vector<<std::pair<double, double>> nf_cc;
        for (unsigned k = 0; k < cc.size(); k++) {
            Node school = cc.at(k);
            std::pair<double, double> netforce(0, 0);
            //calculate the netforce of a single vertex in the whole connected components
            std::vector<Node> neighbors = adjacency_lists_.at(school.school_number);
            for (unsigned l = 0; l < neighbors.size(); l++) {
                std::pair<double, double> attractive_force = CalculateAttractive(school, neighbors.at(i));
                std::pair<double, double> repulsive_force = CalculateReplusive(school, neighbors.at(i));
                //add direction
                double direction_attractive_x = (neighbors.at(i).x - school.x) / std::abs(neighbors.at(i).x - school.x);
                double direction_attractive_y = (neighbors.at(i).y - school.y) / std::abs(neighbors.at(i).y - school.y);
                attractive_force.first = attractive_force.first * direction_attractive_x;
                attractive_force.second = attractive_force.second * direction_attractive_y;

                double direction_repulsive_x = (school.x - neighbors.at(i).x) / std::abs(neighbors.at(i).x - school.x);
                double direction_repulsive_y = (school.y - neighbors.at(i).y) / std::abs(neighbors.at(i).y - school.y);
                repulsive_force.first = repulsive_force.first * direction_repulsive_x;
                repulsive_force.second = repulsive_force.second * direction_repulsive_y;

                netforce.first += attractive_force.first;
                netforce.first += repulsive_force.first;
                netforce.second += attractive_force.second;
                netforce.second += repulsive_force.second;
                
            }
            nf_cc.push_back(netforce);
        }
    }


    //accepts the original connected components, returns the connected components with new location
    std::vector<Node> Move(std::vector<Node> cc) {
        double max_d = 5;
        double min_d = -5;
        std::vector<Node> updated_cc;
        std::vector<<std::pair<double, double>> nf_cc = CalculateNetForce(cc);
        for (unsigned k = 0; k < cc.size(); k++) {
            Node school = cc.at(i);
            std::pair<double, double> netforce = nf_cc.at(k);
            double time = 1
            double d_x = netforce.first * time * time  * / (2 * school.centrality);
            double d_y = netforce.second * time * time  * / (2 * school.centrality);
            if (d_x > max_d) d_x = max_d;
            if (d_y > max_d) d_y = max_d;
            if (d_x < min_d) d_x = min_d;
            if (d_y < min_d) d_y = min_d;
            school.x += std::round(d_x);
            school.y += std::round(d_y);
            updated_cc.push_back(school);
        }
    }

    void Draw(std::vector<Node> cc) {
        //Selection sort: sort the connected component from low centrality to high centrality
        for (unsigned k = 0; k < cc.size() - 1; k++) {
            Node n1 = cc.at(k);
            for (unsigned l = k + 1; l < cc.size(); l++) {
                if (cc.at(l).centrality < n1.centrality) {
                    Node temp = cc.at(l);
                    cc.at(l) = n1;
                    n1 = temp;
                }
            }
        }

        unsigned base_size = 5; 
        for (unsigned k = 0; k < cc.size(); k++) {
            Node school = cc.at(k);
            image[school.x][school.y] = true;
            for (unsigned i = school.x - k - 5; i <= school.x + k + 5) {
                for (unsigned j = school.y - k - 5; j <= school.y + k + 5) {
                    if (std::sqrt((school.x - i) * (school.x - i) + (school.y - j) * (school.y - j)) <= 5) {
                        image[i][j] = true;
                    }
                }
            }
        }
    }

    
    //getter functions:
    std::vector<Node> getNodes() {
        return nodes_;
    }

    std::vector<std::vector<Node> > getAdjacencyLists() {
        return adjacency_lists_;
    }

    std::vector<std::vector<Node> > getConnectedComponents() {
        return connected_components;
    }
    

    unsigned* getImage() {
        return image;
    }


    private:

    //raw data of universities stored in pairs
    std::vector<std::pair<std::string, int> > schools;
    std::vector<std::pair<std::string, std::string>> relations;


    //refined data used for future algorithms
    std::vector<Node> nodes_;
    std::vector<std::vector<Node> > adjacency_lists_;

    //data after BFS for searchwing for connected components
    std::vector<std::vector<Node> > connected_components;

    //if true, color with red, else color with green
    bool image[1000][1000];
};
