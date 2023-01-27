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
        value_type val;
        std::map<key_type, weight_type> edges;

    public:

        /*!
        *  \brief Дефолтный конструктор
        */
        Node() = default;
        /*!
        *  \brief Конструктор копирования
        */
        Node(const Node& other) = default;
        /*!
        *  \brief Конструктор перемещения
        */
        Node(Node&& other)  noexcept = default;


        /*!
         * \brief Проверка на пустоту узла
         */
        bool empty() {
            return edges.empty();
        }
        /*!
         * \brief Количество исходящих рёбер
         */
        size_t size() {
            return edges.size();
        }
        /*!
         * \brief Значение в узле
         */
        value_type& value() {
            return val;
        }
        /*!
         * \brief Удаление исходящих рёбер
         */
        void clear() {
            edges.clear();
        }

    };

    std::map<key_type, Node> graph;

public:
    /*!
    * \brief Дефолтный конструктор
    */
    Graph() = default;
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
     * \brief Оператор перемещающего присваивания
     */
    Graph<key_type, value_type, weight_type>& operator=(Graph<key_type, value_type, weight_type>&& rhs) noexcept = default;



    /*!
     * \brief Проверка на пустоту графа
     */
    bool empty() {
        return graph.empty();
    }
    /*!
     * \brief Количество узлов в графе
     */
    size_t size() {
        return graph.size();
    }
    /*!
     * \brief Удаление графа
     */
    void clear() {
        graph.clear();
    }
    /*!
     * \brief ? swap ?
     */
    void swap(Graph<key_type, value_type, weight_type>& g) {
        // ?
    }

};

