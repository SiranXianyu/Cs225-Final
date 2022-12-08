
#include <cstdlib>
#include <cmath>
//this file is used to draw a force-directed graph
//all the parater k need to be modified in accordance to centrality value



//this function distribute vertex in one connected components randomly
std::vector<Node> Distribute(std::vector<Node> cc) {
    std::vector<Node> coordinated_connected_components;
    for (unsigned i = 0; i < cc.size(); i++) {
        //retrieve two random number(coordinates) between [0 and 999]
        //assign coordinates to each school
        Node school = cc.at(i);
        int r_x = 0 + (rand() % 1000);
        int r_y = 0 + (rand() % 1000);
        unsigned c_x = std::static_cast<unsigned>(r_y);
        unsigned c_y = std::static_cast<unsigned>(r_y);
        school.x = c_x; school.y = c_y;
        coordinated_connected_components.push_back(school);
    }
    return coordinated_connected_components;
}


//calculate absolute attractive force between two vertex k (x1 - x2) c1 c2
//produce force as scaler
std::pair<double, double> CalculateAttractive(Node n1, Node n2) {
    double k = 1;
    double d = std::sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y));
    double force = n1.centrality * n2.centrality * d * k;
    double force_x = force * (std::abs(n1.x - n2.x) / d );
    double force_y = force * (std::abs(n1.y - n2.y) / d );
    std::pair<double, double> f(force_x, force_y);
    return f;

}

//calculate absolute repulsive force between two vertex c1 c2 k / d^2
//produce force as scaler
std::pair<double, double> CalculateReplusive(Node n1, Node n2) {
    double d_2 = (n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y);
    double k = 1;
    double force = n1.centrality * n2.centrality * k / d_2;
    double force_x = force * (std::abs(n1.x - n2.x) / std::sqrt(d_2) );
    double force_y = force * (std::abs(n1.y - n2.y) / std::sqrt(d_2) );
    std::pair<double, double> f(force_x, force_y);
    return f;
}





    
