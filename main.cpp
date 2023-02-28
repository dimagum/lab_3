#include <iostream>
#include "Graph.h"

/*!
 * \brief Вывод графа в консоль
 * @tparam Graph
 * @param graph
 */
template<typename Graph>
void print(const Graph& graph) {
    if (graph.empty()) {
        std::cout << "> This graph is empty!" << std::endl;
        return;
    }
    std::cout << "> Size of graph: " << graph.size() << std::endl;
    for (const auto& [key1, node] : graph) {
        std::cout << '[' << key1 << "] stores: " << node.value() << " and matches with:" << std::endl;
        for (const auto& [key2, weight] : node)
            std::cout << "\t[" << key2 << "]\t with weight: " << weight << std::endl;
    }
}


int main() {
    Graph<int, int, int> graph;
    auto [it1, flag1] = graph.insert_node(1, 1);
    auto [it11, flag11] = graph.insert_node(2, 2);

    std::cout << std::boolalpha << "[" << it1->first << "] = " << it1->second.value() << " " << flag1 <<"\n";
    std::cout << std::boolalpha << "[" << it11->first << "] = " << it11->second.value() << " " << flag1 <<"\n";

    auto [it2, flag2] = graph.insert_edge(std::pair<int, int>(1, 1), 5);

    std::cout << std::boolalpha << "[" << it2->first << "] = " << it2->second << " " << flag2 << "\n";

    auto [it3, flag3] = graph.insert_or_assign_edge(std::pair<int, int>(1, 1), 5);

    std::cout << std::boolalpha << "[" << it3->first << "] = " << it3->second << " " << flag3 << "\n";

    std::cout << graph.degree_in(1) << " " << graph.degree_out(1) << "\n";

    std::cout << graph.loop(1) << "\n";

    if (graph[1].empty()) {
        std::cout << std::boolalpha << true << "\n";
    }
    else {
        std::cout << std::boolalpha << false << "\n";
    }


    if (graph[1].empty()) {
        std::cout << std::boolalpha << true << "\n";
    }
    else {
        std::cout << std::boolalpha << false << "\n";
    }

    graph.clear_edges();

    if (graph[1].empty()) {
        std::cout << std::boolalpha << true << "\n";
    }
    else {
        std::cout << std::boolalpha << false << "\n";
    }
    // print(graph);


    return 0;
}
