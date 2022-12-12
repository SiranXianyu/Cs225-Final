//construct a graph class, reading values from csv files and store them 
//we store data in adjacency lists
#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <set>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <string.h>
// #include <deque>

struct Node {
    //the school number is based on the order we read data
    unsigned school_number;
    std::string name;
    unsigned occurrence_times;
    double centrality;
};

class Graph {
    public:
    //constructor:
    Graph() = default;

    void Build(const std::string & edge_file, const std::string & vertex_file) {
        ReadRelations(edge_file);
        ReadVertices(vertex_file);
        ReadSchools();
        ReadEdges();
        ReadEdges2();
        RefineLists();
    }
    
void ReadRelations(const std::string & edge_file) {
        std::ifstream file_stream;
        file_stream.open(edge_file);
        std::string token;
    
        while (!file_stream.eof()) {
            file_stream >> token;
            unsigned cut_index = token.find(",");
            // the string for the first school
            std::string school_1 = token.substr(0, cut_index);
            // the string for the second school
            std::string school_2 = token.substr(cut_index + 1, token.size() - 1 - cut_index);
            std::pair<std::string, std::string> relation(school_1, school_2);
            relations.push_back(relation);
        }
    }

    void ReadVertices(const std::string & vertex_file) {
        std::ifstream file_stream;
        file_stream.open(vertex_file);
        std::string token;
        
        while (!file_stream.eof()) {
            file_stream >> token;
            unsigned cut_index = token.find(",");
            // the string for the school
            std::string school = token.substr(0, cut_index);
            // the string for the cited times
            std::string occurrence_times_string = token.substr(cut_index + 1, token.size() - 1 - cut_index);
            int occurrence_times = std::stoi(occurrence_times_string);
            std::pair<std::string, int> university(school, occurrence_times);
            schools.push_back(university);
        }
    }

    void ReadSchools() {
        // the last row has been read two times
        for (unsigned i = 0; i < schools.size() - 1; i++) {
                Node college;
                college.school_number = i;
                college.name = schools.at(i).first;
                // JIALONG -> consider remove occurrence_times
                college.occurrence_times = schools.at(i).second;
                nodes_.push_back(college);
        }
    }


    void ReadEdges() {
        // the adjacency list for one school
        // line only contains the school name
        std::vector<std::string> line;
        for (unsigned i = 0; i < relations.size(); i++) {
            std::string school_1 = relations.at(i).first;
            std::string school_2 = relations.at(i).second;
            // if nothing is in the adjacency list for one school
            if (line.empty()) {
                line.push_back(school_1);
            }
            // if the other school has not appeared in the list, we add it, 
            // if it has been in the list, leave it away
            bool contained_in_line = false;
            for (unsigned k = 0; k < line.size(); k++) {
                if (line.at(k) == school_2) {
                    contained_in_line = true;
                }
            }
            if (!contained_in_line) {
                line.push_back(school_2);
            }
            // if the next relation represents a new school, we store 
            // this adjacency list in to our adjacency_lists
            // if it comes to the last line, directly store it.
            if (i == relations.size() - 1 || relations.at(i + 1).first != school_1) {
                // convert vector of strings to vector of nodes
                std::vector<Node> nodes;
                // this time, we push back nodes
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
    }

    // ???????????????????????
    void RefineLists() {
        std::vector<std::vector<Node> >  new_lists;
        for (unsigned school_Number = 0; school_Number < nodes_.size(); school_Number++) {
            bool find_or_not = false;
            for (unsigned k = 0; k < adjacency_lists_.size(); k++) {
                if (adjacency_lists_.at(k).empty()) continue;
                if (adjacency_lists_.at(k).at(0).school_number == school_Number) {
                    std::vector<Node> list = adjacency_lists_.at(k);

                    // delete the first one(the school itself) in each neighbor line, so
                    // that each list only contains all the neighbor
                    list.erase(list.begin());
                    new_lists.push_back(list);
                    find_or_not = true;
                    break;
                }
            }
            // if a school has not relations, we pushback a vacant vector
            if (!find_or_not) {
                std::vector<Node> empty_one;
                new_lists.push_back(empty_one);
            }
        }
        adjacency_lists_ = new_lists;
    }


    /**
    *
    * use BFS to do the traversal. The input will be a list of nodes and the output will
    * be a matrix representing the connected components while each line refers to 
    *  one connected component. The time complexity will be O(V+E),
    *  and the space complexity will be O(V).
    */
    void ConnectedComponents(); 

    // Algorithm 1, normal BFS
    std::vector<Node> BFS(unsigned school_number, bool visited[]);

    // Algorithm 1, BFS4 for shortest path
    std::vector<std::vector<Node>> BFS4ST(unsigned source, unsigned target, bool visited[]);

    void ReadEdges2() {
        for (unsigned k = 0; k < adjacency_lists_.size(); k++) {
            Node school1 = adjacency_lists_.at(k).at(0);
            for (unsigned l = 1; l < adjacency_lists_.at(k).size(); l++) {
                Node school2 = adjacency_lists_.at(k).at(l);
                bool have_line = false; 
                int line_num = -1;
                for (unsigned i = 0; i < adjacency_lists_.size(); i++) {
                    if (adjacency_lists_.at(i).at(0).name == school2.name) {
                        have_line = true;
                        line_num = i;
                    }
                    
                }
                
                if (have_line) {
                    //test if contain school1, if not, add school1
                    bool contained = false;
                    for (unsigned i = 0; i < adjacency_lists_.at(line_num).size(); i++) {
                        if (adjacency_lists_.at(line_num).at(i).name == school1.name) {
                            contained = true; break;
                        }
                    }
                    if (contained) {
                        continue;
                    } else {
                        adjacency_lists_.at(line_num).push_back(school1);
                    }
                }
                else {
                    //create new line, and push back to al
                    std::vector<Node> newline;
                    newline.push_back(school2); 
                    newline.push_back(school1);
                    adjacency_lists_.push_back(newline); 
                }
            }
        }
    }

    /**
    * Reference: https://www.cl.cam.ac.uk/teaching/1617/MLRD/handbook/brandes.pdf 
    * Compute the betweenness centrality of each node
        * 1. For every node v in V , set CB(v) = 0.
        * 2. For each node s in V :
        *      1. set S(v, t) to zero for all nodes v and t in V.
        *      2. Use the BFS algorithm, as above, to reach each target t from s.
        *      3. In the backward phase, increment S(v, t) as appropriate when each
        *          node v is reached, rather than creating full paths.
        *      4. At the end, divide each S(v, t) by the total number of paths between
        *          s and t (i.e., S(s, t)). Add the result to CB(v).
        * 3. CB(w) gives the final result.
        * 
        * @param: none
        * @return: centrality_ : std::vector<double> the centrality vector C(v) of each node v
        * @time complexity: O(V^3)
        * @space complexity: O(V^2)
    */        
    std::vector<double> Brandes();

    // Getter Functions:
    // return index of school, and its betweenness centrality
    std::vector<std::pair<std::string, double>> GetNameAndBetweeness();

    // return only betweenness centrality
    std::vector<double> GetBetweeness(); 

    std::vector<Node> GetNodes();
    std::vector<std::vector<Node>> GetAdjacencyLists();
    std::vector<std::vector<Node>> GetConnectedComponents();

    private:
    //refined data used for future algorithms
    std::vector<Node> nodes_;
    std::vector<std::vector<Node>> adjacency_lists_;

    //raw data of universities stored in pairs
    std::vector<std::pair<std::string, int>> schools;
    std::vector<std::pair<std::string, std::string>> relations;

    //data after BFS for searchwing for connected components
    std::vector<std::vector<Node>> connected_components;
};

// Helper Functions: (export)
void ExportBC(std::vector<std::pair<std::string, double>> Betweenness);
