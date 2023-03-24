#pragma once

#include <map>
#include <limits>

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
         * \brief Конструктор для значения в узле
         * @param other
         */
        Node(const value_type& other) {
            val = other;
        }

        /*!
         * \brief Оператор копирующего присваивания
         * @param rhs
         * @return Узел после присваивания
         */
        Node& operator=(const Node& rhs) = default;

        /*!
         * \brief Оператор перемещающего присваивания
         * @param rhs
         * @return Узел после присваивания
         */
        Node& operator=(Node&& rhs)  noexcept = default;

        /*!
         * \brief Оператор присваивания для значения в узле
         * @param other
         * @return Узел после присваивания
         */
        Node& operator=(const value_type& other) {
            val = other;
            return *this;
        }


        /*!
         * \brief Проверка на пустоту узла
         * @return bool - true если узел пустой, false - иначе.
         */
        bool empty() const {
            return edges.empty();
        }
        /*!
         * \brief Количество исходящих рёбер
         * @return Количество исходящих из узла рёбер
         */
        size_t size() const {
            return edges.size();
        }
        /*!
         * \brief Значение в узле
         * @return Значение, находящееся в узле
         */
        value_type & value() {
            return val;
        }
        /*!
         * \brief Значение в узле (const версия)
         * @return Значение, находящееся в узле
         */
        const value_type & value() const {
            return val;
        }
        /*!
         * \brief Удаление исходящих рёбер
         */
        void clear() {
            edges.clear();
        }

        /*!
         * \brief Псевдоним для итератора узла
         */
        typedef typename std::map<key_type, weight_type>::iterator iterator;
        /*!
         * \brief Псевдоним для константного итератора узла
         */
        typedef typename std::map<key_type, weight_type>::const_iterator const_iterator;

        /*!
         * \brief Итератор begin
         * @return Итератор, показывающий на первый элемент узла.
         */
        iterator begin() noexcept {
            return edges.begin();
        }
        /*!
         * \brief Итератор end
         * @return Итератор, показывающий на элемент, следующий за последним элементом узла.
         */
        iterator end() noexcept {
            return edges.end();
        }
        /*!
         * \brief Итератор begin (const версия)
         * @return Константный итератор, показывающий на первый элемент узла.
         */
        const_iterator begin() const noexcept {
            return edges.begin();
        }
        /*!
         * \brief Итератор end (const версия)
         * @return Константный итератор, показывающий на элемент, следующий за последним элементом узла.
         */
        const_iterator end() const noexcept {
            return edges.end();
        }
        /*!
         * \brief Итератор cbegin
         * @return Константный итератор, показывающий на первый элемент узла.
         */
        const_iterator cbegin() const noexcept {
            return edges.cbegin();
        }
        /*!
         * \brief Итератор cend
         * @return Константный итератор, показывающий на элемент, следующий за последним элементом узла.
         */
        const_iterator cend() const noexcept {
            return edges.cend();
        }

        /*!
         * \brief Доступ к элементу узла
         * @param key
         * @return Вес соответствующего ребра.
         */
        weight_type& operator[](key_type key) {
            return edges[key];
        }

        /*!
         * \brief Доступ к элементу узла (const версия)
         * @param key
         * @return Вес соответствующего ребра.
         */
        const weight_type& operator[](key_type key) const {
            return edges[key];
        }

        /*!
         * \brief Вставка ребра в узел (без переприсваивания)
         * @param key
         * @param weight
         * @return Значение std::pair<iterator, bool>, где итератор показывает на элемент узла, откуда идёт ребро, bool - true (если произошла вставка), false - иначе.
         */
        std::pair<iterator, bool> insert_edge(key_type key, weight_type weight) {
            return edges.insert(std::make_pair(key, weight));
        }

        /*!
         * \brief Вставка ребра в узел (с переприсваиванием)
         * @param key
         * @param weight
         * @return Значение std::pair<iterator, bool>, где итератор показывает на элемент узла, откуда идёт ребро, bool - true (если произошла вставка), false - иначе.
         */
        std::pair<iterator, bool> insert_or_assign_edge(key_type key, weight_type weight) {
            return edges.insert_or_assign(key, weight);
        }

        /*!
         * \brief Удаление ребра из узла
         * @param key
         * @return bool - false если такого ребра нет, true - иначе.
         */
        bool erase_edge(key_type key) {
            if (edges.find(key) == edges.end()) {
                return false;
            }

            edges.erase(key);
            return true;
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
     * @return Граф после присваивания.
     */
     Graph<key_type, value_type, weight_type>& operator=(const Graph<key_type, value_type, weight_type>& rhs) = default;

    /*!
     * \brief Оператор перемещающего присваивания
     * @param rhs
     * @return Граф после присваивания.
     */
    Graph<key_type, value_type, weight_type>& operator=(Graph<key_type, value_type, weight_type>&& rhs) noexcept = default;



    /*!
     * \brief Проверка на пустоту графа
     * @return bool - true, если граф пустой, false - иначе.
     */
    bool empty() const noexcept {
        return graph.empty();
    }
    /*!
     * \brief Количество узлов в графе
     * @return Размер графа (число узлов).
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
     * \brief Обмен местами (как метод класса)
     * @param other
     */
    void swap(Graph<key_type, value_type, weight_type>& other) {
        Graph<key_type, value_type, weight_type> tmp = other;
        other = *this;
        *this = tmp;
    }

    /*!
     * \brief Обмен местами (как дружественная функция)
     * @param lhs
     * @param rhs
     */
    friend void swap(Graph<key_type, value_type, weight_type>& lhs, Graph<key_type, value_type, weight_type>& rhs) {
        Graph<key_type, value_type, weight_type>& tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }

    /*!
     * \brief Псевдоним для итератора графа
     */
    typedef typename std::map<key_type, Node>::iterator iterator;
    /*!
     * \brief Псевдоним для константного итератора графа
     */
    typedef typename std::map<key_type, Node>::const_iterator const_iterator;

    /*!
     * \brief Итератор begin
     * @return Итератор, показывающий на первый элемент графа.
     */
    iterator begin() noexcept {
        return graph.begin();
    }
    /*!
     * \brief Итератор end
     * @return Итератор, показывающий на элемент, следующий за последним элементом графа.
     */
    iterator end() noexcept {
        return graph.end();
    }
    /*!
     * \brief Итератор begin (const версия)
     * @return Константный итератор, показывающий на первый элемент графа.
     */
    const_iterator begin() const noexcept {
        return graph.begin();
    }
    /*!
     * \brief Итератор end (const версия)
     * @return Константный итератор, показывающий на элемент, следующий за последним элементом графа.
     */
    const_iterator end() const noexcept {
        return graph.end();
    }
    /*!
     * \brief Константный итератор cbegin
     * @return Константный итератор, показывающий на первый элемент графа.
     */
    const_iterator cbegin() const {
        return graph.cbegin();
    }
    /*!
     * \brief Константный итератор cend
     * @return Константный итератор, показывающий на элемент, следующий за последним элементом графа.
     */
    const_iterator cend() const {
        return graph.cend();
    }



    /*!
     * \brief Степень (входящие рёбра)
     * @param key
     * @return Степень узла по входящим рёбрам.
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
     * @return Степень узла по выходящим рёбрам.
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
     * @return bool - true, если петля у узла есть, false - иначе.
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
     * \brief Доступ к узлу по ключу
     * @param key
     * @return Узел с таким ключом из графа.
     */
    Node& operator[](key_type key) {
        if (graph.find(key) == graph.end()) {
            graph[key] = Node();
            return graph[key];
        }

        return graph[key];
    }

    /*!
     * \brief Доступ к узлу по ключу (const версия)
     * @param key
     * @return Узел с таким ключом из графа.
     */
    const Node& operator[](key_type key) const {
        if (graph.find(key) == graph.end()) {
            throw std::logic_error("no such node in graph.\n");
        }

        return graph.at(key);
    }


    /*!
     * \brief Доступ к элементу по ключу
     * @param key
     * @return Узел с таким ключом из графа.
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
     * @return Значение std::pair<iterator, bool>, где итератор показывает на элемент графа, bool - true (если произошла вставка), false - иначе.
     */
    std::pair<iterator, bool> insert_node(key_type key, value_type val) {
        Node tmp;
        tmp.value() = val;
        return graph.emplace(key, tmp);
    }

    /*!
     * Вставка узла (с переприсваиванием)
     * @param key
     * @param val
     * @return Значение std::pair<iterator, bool>, где итератор показывает на элемент графа, bool - true (если произошла вставка), false - иначе.
     */
    std::pair<iterator, bool> insert_or_assign_node(key_type key, value_type val) {
        if (graph.find(key) != graph.end()) {
            graph[key].value() = val;
            return std::pair<iterator, bool>(graph.find(key), false);
        }

        Node tmp;
        tmp.value() = val;
        return graph.insert_or_assign(key, tmp);
    }

    /*!
     * \brief Вставка ребра (без переприсваивания)
     * @param keys
     * @param weight
     * @return Значение std::pair<iterator, bool>, где итератор показывает на элемент графа, откуда идёт ребро, bool - true (если произошла вставка), false - иначе.
     */
    std::pair<iterator, bool> insert_edge(std::pair<key_type, key_type> keys, weight_type weight) {
        key_type key_from = keys.first, key_to = keys.second;
        if (graph.find(key_from) == graph.end()) {
            throw std::logic_error("node referencing to key_from is not in the graph.\n");
        }

        if (graph.find(key_to) == graph.end()) {
            throw std::logic_error("node referencing to key_to is not in the graph.\n");
        }

        auto [key, flag] = graph[key_from].insert_edge(key_to, weight);

        return std::pair<iterator, bool>(graph.find(key_from), flag);
    }

    /*!
     * \brief Вставка ребра (с переприсваиванием)
     * @param keys
     * @param weight
     * @return Значение std::pair<iterator, bool>, где итератор показывает на элемент графа, откуда идёт ребро, bool - true (если произошла вставка), false - иначе.
     */
    std::pair<iterator, bool> insert_or_assign_edge(std::pair<key_type, key_type> keys, weight_type weight) {
        key_type key_from = keys.first, key_to = keys.second;
        if (graph.find(key_from) == graph.end()) {
            throw std::logic_error("node referencing to key_from is not in the graph.\n");
        }

        if (graph.find(key_to) == graph.end()) {
            throw std::logic_error("node referencing to key_to is not in the graph.\n");
        }

        auto [key, flag] = graph[key_from].insert_or_assign_edge(key_to, weight);

        return std::pair<iterator, bool>(graph.find(key_from), flag);
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
     * @return Значение bool (false - если узел не найден, true - иначе).
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
     * @return Значение bool (false - если узел не найден, true - иначе).
     */
    bool erase_edges_go_to(key_type key) {
        if (graph.find(key) == graph.end()) {
            return false;
        }

        for (auto& [node_key, node] : graph) {
            node.erase_edge(key);
        }
        return true;
    }

    /*!
     * \brief Удаление узла
     * @param key
     * @return Значение bool (true, если узел найден и удалён, false - иначе).
     */
    bool erase_node(key_type key) {
        if (graph.find(key) == graph.end()) {
            return false;
        }

        for (auto& [node_key, node] : graph) {
            node.erase_edge(key);
        }

        graph.erase(key);
        return true;
    }

};

/*!
 * \brief Алгоритм Дейкстры
 * @tparam graph_t
 * @tparam weight_t
 * @tparam route_t
 * @tparam node_name_t
 * @param graph
 * @param key_from
 * @param key_to
 * @return Возвращает длину кратчайшего пути между из вершины с клучом key_from в вершину с ключом key_to.
 */
template<typename graph_t, typename weight_t, typename route_t, typename node_name_t>
std::pair<weight_t, route_t> dijkstra(const graph_t& graph, node_name_t key_from, node_name_t key_to) {
    graph[key_from];
    graph[key_to];


    route_t route;

    std::map<node_name_t, node_name_t> route_tmp;

    const weight_t INF = std::numeric_limits<weight_t>::max();

    route_tmp[key_from] = std::numeric_limits<node_name_t>::max();

    std::map<node_name_t, weight_t> d; // d[v]
    std::map<node_name_t, bool> used;  // used[v] = true/false;
    for (auto [key, node] : graph) {
        d[key] = INF;
        used[key] = false;
    }
    d[key_from] = 0;

    for (int i = 0; i < graph.size(); i++) {
        node_name_t v = -1;

        // d[v] -> min, v: used[v] = false;

        for (auto [key, node] : graph) {
            if (!used[key] && (v == -1 || d[key] < d[v])) {
                v = key;
            }
        }

        if (d[v] == INF) {
            break;
        }
        used[v] = true;

        for (auto [to, len] : graph[v]) {
            if (len < 0) {
                throw std::logic_error("there are negative weights in the graph.\n");
            }
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                route_tmp[to] = v;
            }
        }
    }

    if (route_tmp.find(key_to) == route_tmp.end()) {
        throw std::logic_error("nodes are not connected.\n");
    }

    for (auto key = key_to; route_tmp[key] < std::numeric_limits<node_name_t>::max(); ) {
        route.push_back(key);
        key = route_tmp[key];
    }

    route.push_back(key_from);
    std::reverse(route.begin(), route.end());

    return std::pair<weight_t, route_t>(d[key_to], route);
}
