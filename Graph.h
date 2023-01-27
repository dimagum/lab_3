#pragma once

#include <map>

/*!
 *  \brief Шаблонный класс графа
 */
template<typename key_type, typename value_type, typename weight_type>
class Graph {
    /*!
    *  \brief Внутренний класс узла
    */
    class Node {
        value_type value;
        std::map<key_type, weight_type> edges;

    public:

        /*!
        *  \brief Дефолтный конструктор
        */
        Node() {
            value = 0;
            edges = std::map<key_type, weight_type>();
        }
    };

    std::map<key_type, Node> graph;

public:
    /*!
    * \brief Дефолтный конструктор
    */
    Graph() {
        graph = std::map<key_type, Node>();
    }
    /*!
     * \brief Конструктор копирования
     */
    Graph(const Graph<key_type, value_type, weight_type>& other) {
        graph = other.graph;
    }
    /*!
     * \brief Конструктор перемещения
     */
    Graph(Graph<key_type, value_type, weight_type>&& other) noexcept {
        graph = other.graph;
    }
};

