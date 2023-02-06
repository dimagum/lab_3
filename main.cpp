#include <iostream>
#include "Graph.h"

/*!
 * \brief Вывод графа к консоль
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
        std::cout << '[' << key1 << "] stores: " << node.value()
                  << " and matches with:" << std::endl;
        for (const auto& [key2, weight] : node)
            std::cout << "\t[" << key2 << "]\t with weight: "
                      << weight << std::endl;
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
