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
        /*!
        *  \brief Конструктор копирования
        */
        Node(const Node& other) = default;
        /*!
        *  \brief Конструктор перемещения
        */
        Node(Node&& other)  noexcept = default;
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
    Graph(const Graph<key_type, value_type, weight_type>& other) = default;
    /*!
     * \brief Конструктор перемещения
     */
    Graph(Graph<key_type, value_type, weight_type>&& other) noexcept = default;

    /*!
     * \brief Оператор копирующего присваивания
     */
     Graph<key_type, value_type, weight_type>& operator=(const Graph<key_type, value_type, weight_type>& rhs) = default;

    /*!
     * \brief Опервтор перемещающего присваивания
     */

    Graph<key_type, value_type, weight_type>& operator=(Graph<key_type, value_type, weight_type>&& rhs) noexcept = default;

};

