#pragma once

#include <map>


template<typename key_type, typename value_type, typename weight_type>
class Graph {
    class Node {
        value_type value;
        std::map<key_type, weight_type> edges;
    };

    std::map<key_type, Node> graph;

public:

    


};

