//this file is used to read csv files and store values
#include "graph.h"
#include <queue>

//read file data_edge.csv into relations
void Graph::ReadRelations() {
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


//read file data_vertex.csv into schools
void Graph::ReadVertices() {
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


void Graph::ReadSchools() {
    for (unsigned i = 0; i < schools.size(); i++) {
        Node college;
        college.school_number = i;
        college.name = schools.at(i).first;
        college.cited_times = schools.at(i).second;
        nodes_.push_back(college);
    }
}

void Graph::ReadEdges() {
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
        if (relations.at(i + 1).first != school_1) {
            //convert vector of strings to vector of nodes
            std::vector<Node> nodes;
            for (unsigned i = 0; i < line.size(); i++) {
                for (unsigned j = 0; j < nodes_.size(); j++) {
                    if (line.at(i) == nodes_.at(j).name) {
                        nodes.push_back(nodes_.at(j));
                    }
                }
            }
            adjacency_lists_.push_back(nodes);
            line.clear();
            continue;
        }
    }
}

void Graph::RefineLists() {
    std::vector<std::vector<Node> >  new_lists;
    for (unsigned school_Number = 0; school_Number < nodes_.size(); school_Number++) {
        bool find_or_not = false;
        for (unsigned k = 0; k < adjacency_lists_.size(); k++) {
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



void Graph::ConnectedComponents() {
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

std::vector<Node> Graph::BFS(unsigned school_Number, bool visited[]) {
    //mark the current school node as visited
    visited[school_Number] = true;
    std::queue<Node> schools;
    schools.push(nodes_.at(school_Number));
    std::vector<Node> output_set;
    while (!schools.empty()) {
        Node n = schools.front();
        output_set.push_back(n);
        schools.pop();
        std::vector<Node> neighbors = adjacency_lists_.at(n.school_number);
        for (auto i: neighbors) {
            if (!visited[i.school_number]) {
                visited[i.school_number] = true;
                schools.push(i);
            }
        }
    }
    return output_set;
    

}

Graph::Graph() {
    ReadSchools();
    ReadRelations();
    ReadEdges();
    ReadVertices();
    RefineLists();
}
