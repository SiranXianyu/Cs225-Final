//this file is used to read csv files and store values
#include "graph.h"

//read file data_edge.csv into relations
void Graph::ReadEdges() {
    std::ifstream file_stream;
    file_stream.open("data_edge.csv");
    std::string token;
    
    while (!file_stream.eof()) {
        file_stream >> token;
        unsigned cut_index = token.find(",");
        //the string for the first school
        std::string school_1 = token.str(0, cut_index);
        //the string for the second school
        std::string school_2 = token.str(cut_index + 1, token.size() - 1 - cut_index);
        pair<std::string, std::string> relation(school_1, school_2);
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
        std::string school = token.str(0, cut_index);
        //the string for the cited times
        std::string cited_times = token.str(cut_index + 1, token.size() - 1 - cut_index);
        pair<std::string, int> university(school, cited_times);
        schools.push_back(university);
    }
}


void Graph::ReadSchools() {
    for (unsigned i = 0; i < schools.size(); i++) {
        Node college;
        college.school_number = i;
        college.name = schools.at(i).first;
        college.cited_times = school.at(i).second;
        nodes_.push_back(college);
    }
}

void Graph::ReadEdges() {
    //the adjacency list for one school
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
        if (std::count(line.begin(), line.end(), school_2) == 0) {
            line.push_back(school_2);
        } 
        //if the next relation represents a new school, we store 
        //this adjacency list in to our adjacency_lists
        if (relations.at(i + 1).first != school_1) {
            adjacency_lists_.push_back(line);
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
                new_lists.push_back(adjacency_lists_.at(k));
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