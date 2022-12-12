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
    unsigned cited_times;
    double centrality;
};

class Graph {
    public:
    //constructor:
    Graph() = default;

    void coutsth() {
        std::cout << "print" <<std::endl;
    }

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
            //the string for the first school
            std::string school_1 = token.substr(0, cut_index);
            //the string for the second school
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
            //the string for the school
            std::string school = token.substr(0, cut_index);
            //the string for the cited times
            std::string occurrence_times_string = token.substr(cut_index + 1, token.size() - 1 - cut_index);
            int occurrence_times = std::stoi(occurrence_times_string);
            std::pair<std::string, int> university(school, occurrence_times);
            schools.push_back(university);
        }
    }

    void ReadSchools() {
        //the last row has been read two times
        for (unsigned i = 0; i < schools.size() - 1; i++) {
                Node college;
                college.school_number = i;
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

    //BFS traversal
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


    std::vector<std::vector<Node>> BFS4ST(unsigned source, unsigned target, bool visited[]) {
        std::vector<std::vector<Node>> output;  // store the output paths
        std::vector<std::vector<Node>> schools; // store the current paths (perform as a queue)
        visited[source] = true; // mark the source as visited

        // if the source and target are not in the same connected component, return an empty vector
        for(auto i: connected_components){
            std::vector<unsigned> c; // store the school numbers of the connected component
            for(auto j: i) c.push_back(j.school_number); // get the school numbers of the connected component

            if(std::find(c.begin(), c.end(), nodes_.at(source).school_number) != c.end()){
                if(std::find(c.begin(), c.end(), nodes_.at(target).school_number) == c.end()){
                    return output; // if the source is in the connected component but the target is not, return an empty vector
                }else break; // if the source and target are in the same connected component, break the loop
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
            if(n.school_number == target){
                output.push_back(current);
                foundShoretestPath = true;
            }

            // if the current path is longer than the shortest path, stop the BFS
            // because the shortest path is already found
            if(foundShoretestPath){
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

    std::vector<double> brandes(){
        // Compute the betweenness centrality of each node
        // 1. For every node v in V , set CB(v) = 0.
        // 2. For each node s in V :
        //      1. set S(v, t) to zero for all nodes v and t in V.
        //      2. Use the BFS algorithm, as above, to reach each target t from s.
        //      3. In the backward phase, increment S(v, t) as appropriate when each
        //          node v is reached, rather than creating full paths.
        //      4. At the end, divide each S(v, t) by the total number of paths between
        //          s and t (i.e., S(s, t)). Add the result to CB(v).
        // 3. CB(w) gives the final result.
        // 
        // @param: none
        // @return: centrality_ : std::vector<double> the centrality vector C(v) of each node v
        // @time complexity: O(V^3)
        // @space complexity: O(V^2)
        
        
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

    // print the betweenness centrality of each node
    void printBetweenness(){
        for (unsigned i = 0; i < nodes_.size(); i++) {
            std::cout << nodes_.at(i).school_number << " " << nodes_.at(i).centrality << std::endl;
        }
    }

    std::vector<double> getBetweeness() {
        std::vector<double> result;
        for (unsigned i = 0; i < nodes_.size(); i++) {
            result.push_back(nodes_.at(i).centrality);
        }
        return result;
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

    private:

    //refined data used for future algorithms
    std::vector<Node> nodes_;
    std::vector<std::vector<Node>> adjacency_lists_;

    //raw data of universities stored in pairs
    std::vector<std::pair<std::string, int> > schools;
    std::vector<std::pair<std::string, std::string>> relations;

    //data after BFS for searchwing for connected components
    std::vector<std::vector<Node> > connected_components;
};


