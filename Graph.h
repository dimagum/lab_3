#pragma once

#include <map>

/*!
 * \brief Шаблонный класс графа
 * @tparam key_type
 * @tparam value_type
 * @tparam weight_type
 */
template<typename key_type, typename value_type, typename weight_type>
class Graph {
    /*!
     * \brief Внутренний класс узла
     */
    class Node {
    public:
        value_type val;
        std::map<key_type, weight_type> edges;

        std::pair<typename std::map<key_type, weight_type>::iterator, bool> insert_edge(key_type key, weight_type weight) {
            return edges.emplace(key, weight);
        }

        std::pair<typename std::map<key_type, weight_type>::iterator, bool> insert_or_assign_edge(key_type key, weight_type weight) {
            return edges.emplace(key, weight);
        }

    //public:

        /*!
         * \brief Дефолтный конструктор
         */
        Node() = default;
        /*!
         * \brief Конструктор копирования
         * @param other
         */
        Node(const Node& other) = default;
        /*!
         * \brief Конструктор перемещения
         * @param other
         */
        Node(Node&& other)  noexcept = default;


        /*!
         * \brief Проверка на пустоту узла
         * @return
         */
        bool empty() {
            return edges.empty();
        }
        /*!
         * \brief Количество исходящих рёбер
         * @return
         */
        size_t size() {
            return edges.size();
        }
        /*!
         * \brief Значение в узле
         * @return
         */
        value_type & value() {
            return val;
        }
        /*!
         * \brief Удаление исходящих рёбер
         */
        void clear() {
            edges.clear();
        }

        typedef typename std::map<key_type, weight_type>::iterator iterator;
        typedef typename std::map<key_type, weight_type>::const_iterator const_iterator;

        /*!
         * \brief Итератор begin
         * @return
         */
        iterator begin() {
            return edges.begin();
        }
        /*!
         * \brief Итератор end
         * @return
         */
        iterator end() {
            return edges.end();
        }
        /*!
         * \brief Итератор begin
         * @return
         */
        const_iterator cbegin() const {
            return edges.cbegin();
        }
        /*!
         * \brief Итератор end
         * @return
         */
        const_iterator cend() const {
            return edges.cend();
        }
        /*!
         * \brief Оператор сравнения ==
         * @param lhs
         * @param rhs
         * @return
         */
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
     * @param other
     */
    Graph(const Graph<key_type, value_type, weight_type>& other) = default;
    /*!
     * \brief Конструктор перемещения
     * @param other
     */
    Graph(Graph<key_type, value_type, weight_type>&& other) noexcept = default;

    /*!
     * \brief Оператор копирующего присваивания
     * @param rhs
     * @return
     */
     Graph<key_type, value_type, weight_type>& operator=(const Graph<key_type, value_type, weight_type>& rhs) = default;

    /*!
     * \brief Оператор перемещающего присваивания
     * @param rhs
     * @return
     */
    Graph<key_type, value_type, weight_type>& operator=(Graph<key_type, value_type, weight_type>&& rhs) noexcept = default;



    /*!
     * \brief Проверка на пустоту графа
     * @return
     */
    constexpr bool empty() const noexcept {
        return graph.empty();
    }
    /*!
     * \brief Количество узлов в графе
     * @return
     */
    size_t size() const noexcept {
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
     * @param g
     */
    void swap(Graph<key_type, value_type, weight_type>& g) {
        // ?
    }

    typedef typename std::map<key_type, Node>::iterator iterator;
    typedef typename std::map<key_type, Node>::const_iterator const_iterator;

    /*!
     * \brief Итератор begin
     * @return
     */
    iterator begin() noexcept {
        return graph.begin();
    }
    /*!
     * \brief Итератор end
     * @return
     */
    iterator end() noexcept {
        return graph.end();
    }
    /*!
     * \brief Константный итератор cbegin
     * @return
     */
    const_iterator cbegin() const {
        return graph.cbegin();
    }
    /*!
     * \brief Константный итератор cend
     * @return
     */
    const_iterator cend() const {
        return graph.cend();
    }



    /*!
     * \brief Степень (входящие рёбра)
     * @param key
     * @return
     */
    size_t degree_in(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw std::logic_error("no node with this key in the graph.");
        }

        size_t result = 0;

        for (auto& [node_key, node] : graph) {
            if (node.edges.find(key) != node.edges.end()) {
                result++;
            }
        }

        return result;
    }
    /*!
     * \brief Степень (выходящие рёбра)
     * @param key
     * @return
     */
    size_t degree_out(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw std::logic_error("no node with this key in the graph.");
        }

        return graph[key].edges.size();
    }
    /*!
     * \brief Проверка на наличие петли
     * @param key
     * @return
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


    /*!
     * \brief Доступ к элементу по ключу
     * @param key
     * @return
     */
    Node& operator[](key_type key) {
        if (graph.find(key) == graph.end()) {
            graph[key] = Node();
            return graph[key];
        }

        return graph[key];
    }


    /*!
     * \brief Доступ к элементу по ключу
     * @param key
     * @return
     */
    Node& at(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw std::logic_error("no node with this key in the graph.");
        }

        return graph[key];
    }

    /*!
     * \brief Вставка узла (без переприсваивания)
     * @param key
     * @param val
     * @return
     */
    std::pair<iterator, bool> insert_node(key_type key, value_type val) {
        Node tmp;
        tmp.value() = val;
        return graph.emplace(key, tmp);
    }

    /*!
     * \brief Вставка узла (с переприсваиванием)
     * @param key
     * @param val
     * @return
     */
    std::pair<iterator, bool> insert_or_assign_node(key_type key, value_type val) {
        if (graph.find(key) != graph.end()) {
            graph[key].value() = val;
            return std::pair<iterator, bool>(graph.find(key), false);
        }

        Node tmp;
        tmp.value() = val;
        return graph.emplace(key, tmp);
    }

    /*!
     * \brief Вставка ребра (без переприсваивания)
     * @param keys
     * @param weight
     * @return std::pair<iterator, bool>
     */
    std::pair<iterator, bool> insert_edge(std::pair<key_type, key_type> keys, weight_type weight) {
        key_type key_from = keys.first, key_to = keys.second;
        if (graph.find(key_from) == graph.end() || graph.find(key_to) == graph.end()) {
            throw std::logic_error("one of the keys is not in the graph.");
        }

        if (graph[key_from].edges.find(key_to) != graph[key_from].edges.end()) {
            return std::pair<iterator, bool>(graph.find(key_from), false);
        }

        return std::pair<iterator, bool>(graph.find(key_from), true);
    }

    /*!
     * \brief Вставка ребра (с переприсваиванием)
     * @param keys
     * @param weight
     * @return std::pair<iterator, bool>
     */
    std::pair<iterator, bool> insert_or_assign_edge(std::pair<key_type, key_type> keys, weight_type weight) {
        key_type key_from = keys.first, key_to = keys.second;
        if (graph.find(key_from) == graph.end() || graph.find(key_to) == graph.end()) {
            throw std::logic_error("one of the keys is not in the graph.");
        }

        if (graph[key_from].edges.find(key_to) != graph[key_from].edges.end()) {
            graph[key_from].edges[key_to] = weight;
            return std::pair<iterator, bool>(graph.find(key_from), false);
        }

        return std::pair<iterator, bool>(graph.find(key_from), true);
    }

    /*!
     * \brief Очистка рёбер графа
     */
    void clear_edges() {
        for (auto& [node_key, node] : graph) {
            node.edges.clear();
        }
    }

    /*!
     * \brief Очистка рёбер, выходящих из узла
     * @param key
     * @return
     */
    bool erase_edges_go_from(key_type key) {
        if (graph.find(key) == graph.end()) {
            return false;
        }

        graph[key].clear();
        return true;
    }

    /*!
     * \brief Очистка рёбер, входящих в узел
     * @param key
     * @return
     */
    bool erase_edges_go_to(key_type key) {
        if (graph.find(key) == graph.end()) {
            return false;
        }

        for (auto& [node_key, node] : graph) {
            for (auto& [go_to_key, weight] : node) {
                if (go_to_key == key) {
                    node.edges.erase(node.find(key));
                }
            }
        }
        return true;
    }

};

