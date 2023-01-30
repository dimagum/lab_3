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

        typedef std::map<key_type, weight_type>::iterator iterator;

        /*!
         * \brief Итератор begin
         */
        iterator begin() {
            return edges.begin();
        }
        /*!
         * \brief Итератор end
         */
        iterator end() {
            return edges.end();
        }
        /*!
         * \brief Итератор begin
         */
        iterator cbegin() {
            return edges.cbegin();
        }
        /*!
         * \brief Итератор end
         */
        iterator cend() {
            return edges.cend();
        }

        friend bool operator==(const Node& lhs, const Node& rhs) {
            return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
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

    typedef std::map<key_type, Node>::iterator iterator;
    typedef std::map<key_type, Node>::const_iterator const_iterator;

    /*!
     * \brief Итератор begin
     */
    iterator begin() {
        return graph.begin();
    }
    /*!
     * \brief Итератор end
     */
    iterator end() {
        return graph.end();
    }
    /*!
     * \brief Константный итератор cbegin
     */
    const_iterator cbegin() {
        return graph.cbegin();
    }
    /*!
     * \brief Константный итератор cend
     */
    const_iterator cend() {
        return graph.cend();
    }



    /*!
     * \brief Степень (входящие рёбра)
     */
    size_t degree_in(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw std::logic_error("no node with this key in the graph.");
        }

        size_t result = 0;

        for (auto &item : graph) {
            if (item.second.find(key) != item.second.end()) {
                result++;
            }
        }

        return result;
    }
    /*!
     * \brief Степень (выходящие рёбра)
     */
    size_t degree_out(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw std::logic_error("no node with this key in the graph.");
        }

        return graph[key].edges.size();
    }
    /*!
     * \brief Проверка на наличие петли
     */
    bool loop(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw std::logic_error("no node with this key in the graph.");
        }

        if (graph[key].edges.find(key) != graph[key].edges.end()) {
            return true;
        }

        return false;
    }

    Node& operator[](key_type key) {
        if (graph.find(key) == graph.end()) {
            graph[key] = Node();
            return graph[key];
        }

        return graph[key];
    }

    Node& at(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw std::logic_error("no node with this key in the graph.");
        }

        return graph[key];
    }

};

