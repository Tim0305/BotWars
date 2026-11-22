/**
 * @file ArcListGraph.hpp
 * @brief Directed weighted graph stored as an arc list.
 * @author Team 1
 * @date 2026-11-21
 */

#ifndef ARC_LIST_GRAPH_HPP
#define ARC_LIST_GRAPH_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "ArcVertex.hpp"
#include "SearchAlgorithms.hpp"
#include "SortingAlgorithms.hpp"
#include "Splay.hpp"

using namespace std;

/**
 * @class ArcListGraph
 * @brief Directed graph where the nodes are kept in a list and every node has two arc lists.
 * @tparam T Node type. It must be copyable and support ==, !=, < and > (nodes are found with
 * these operators, and < is also used to break ties when ranking).
 *
 * @details Only the arcs that exist are stored. Each arc is stored once and is chained in two
 * lists: the out list of its origin and the in list of its destination. The weight of an arc is
 * the number of accesses from the origin to the destination. Adding the same pair again does not
 * create another arc; it adds to the weight. The out-degree, the in-degree and the access totals
 * of a node are counters, so reading them is O(1).
 * For complexity, V is the number of nodes and E is the number of arcs.
 * The graph cannot be copied.
 */
template <typename T>
class ArcListGraph {
private:
    /**
     * @brief Arc stored once and linked into the out list of from and the in list of to.
     */
    struct Arc {
        int from;
        int to;
        int weight;
        Arc* nextOut;
        Arc* nextIn;
    };

    /**
     * @brief Pairs a node value with its position in the node list.
     * @details Only key takes part in comparisons.
     */
    struct IndexEntry {
        T key;
        int id;
        bool operator<(const IndexEntry& other) const { return key < other.key; }
        bool operator>(const IndexEntry& other) const { return key > other.key; }
        bool operator==(const IndexEntry& other) const { return key == other.key; }
        bool operator!=(const IndexEntry& other) const { return !(key == other.key); }
    };

    vector<T> ids;                        // Node list: position -> node value.
    vector<ArcVertex<Arc>> g;             // One vertex per node; same positions as ids.
    mutable SplayTree<IndexEntry> index;  // Node value -> position (self-adjusting, so mutable).
    int arcCount = 0;

    /**
     * @brief Gets the position of a node.
     * Complexity: amortized O(log V).
     * @param value Node to look for.
     * @return int Position of the node, or NOT_FOUND.
     */
    int getId(const T& value) const {
        IndexEntry probe{value, NOT_FOUND};
        return index.contains(probe) ? index.getRootValue().id : NOT_FOUND;
    }

    /**
     * @brief Gets the position of a node and adds the node if it does not exist.
     * Complexity: amortized O(log V).
     * @param value Node to look for or add.
     * @return int Position of the node.
     */
    int getOrCreateId(const T& value) {
        int id = getId(value);
        if (id == NOT_FOUND) {
            id = (int)ids.size();
            ids.push_back(value);
            g.emplace_back();
            index.insert(IndexEntry{value, id});
        }
        return id;
    }

    /**
     * @brief Gets the position of a node that must exist.
     * @param value Node to look for.
     * @return int Position of the node.
     * @throws std::invalid_argument If the node is not in the graph.
     */
    int requireId(const T& value) const {
        int id = getId(value);
        if (id == NOT_FOUND)
            throw invalid_argument("Value not found");
        return id;
    }

    /**
     * @brief Finds the arc between two nodes by walking the shorter of the two lists.
     * Complexity: O(min(out-degree of from, in-degree of to)).
     * @param from Position of the origin.
     * @param to Position of the destination.
     * @return Arc* The arc, or nullptr if there is none.
     */
    Arc* findArc(int from, int to) const {
        if (g[from].getOutDeg() <= g[to].getInDeg()) {
            for (Arc* arc = g[from].getOut(); arc != nullptr; arc = arc->nextOut)
                if (arc->to == to)
                    return arc;
        } else {
            for (Arc* arc = g[to].getIn(); arc != nullptr; arc = arc->nextIn)
                if (arc->from == from)
                    return arc;
        }
        return nullptr;
    }

public:
    /**
     * @brief Creates an empty graph.
     * Complexity: O(1).
     */
    ArcListGraph() = default;

    ArcListGraph(const ArcListGraph&) = delete;
    ArcListGraph& operator=(const ArcListGraph&) = delete;

    /**
     * @brief Deletes all the arcs. Every arc is in exactly one out list, so it is deleted once.
     * Complexity: O(V + E).
     */
    ~ArcListGraph() {
        for (ArcVertex<Arc>& vertex : g) {
            Arc* arc = vertex.getOut();
            while (arc != nullptr) {
                Arc* next = arc->nextOut;
                delete arc;
                arc = next;
            }
        }
    }

    /**
     * @brief Registers accesses from u to v, creating the nodes and the arc if needed.
     * Complexity: amortized O(log V + min(out-degree of u, in-degree of v)).
     * @param u Origin node.
     * @param v Destination node.
     * @param weight Accesses to add (one per log line).
     * @pre weight must be at least 1.
     * @post If the arc u -> v already exists, its weight grows by weight; otherwise a new arc is
     * created with that weight. The degrees only change when a new arc is created.
     * @throws std::invalid_argument If weight is less than 1.
     */
    void addEdge(const T& u, const T& v, int weight = 1) {
        if (weight < 1)
            throw invalid_argument("Weight must be at least 1");

        int from = getOrCreateId(u);
        int to = getOrCreateId(v);

        Arc* arc = findArc(from, to);
        if (arc != nullptr) {
            arc->weight++;
        } else {
            arc = new Arc{from, to, weight, g[from].getOut(), g[to].getIn()};
            g[from].setOut(arc);
            g[to].setIn(arc);
            g[from].incrementOutDeg();
            g[to].incrementInDeg();
            arcCount++;
        }

        g[from].addOutAccesses(weight);
        g[to].addInAccesses(weight);
    }

    /**
     * @brief Gets the weight of the arc u -> v.
     * Complexity: amortized O(log V + min(out-degree of u, in-degree of v)).
     * @return int Number of accesses from u to v, or 0 if there is no arc.
     */
    int getWeight(const T& u, const T& v) const {
        int from = getId(u);
        int to = getId(v);
        if (from == NOT_FOUND || to == NOT_FOUND)
            return 0;

        Arc* arc = findArc(from, to);
        return arc == nullptr ? 0 : arc->weight;
    }

    /**
     * @brief Checks if there is an arc from u to v. The arc v -> u is a different arc.
     * Complexity: same as getWeight.
     */
    bool hasEdge(const T& u, const T& v) const { return getWeight(u, v) > 0; }

    /**
     * @brief Gets the nodes that u reaches (the most recently added arc first).
     * Complexity: amortized O(log V + out-degree of u).
     * @return vector<T> Destinations of the arcs that leave u; empty if u is not in the graph.
     */
    vector<T> outNeighbors(const T& u) const {
        vector<T> result;
        int from = getId(u);
        if (from != NOT_FOUND)
            for (Arc* arc = g[from].getOut(); arc != nullptr; arc = arc->nextOut)
                result.push_back(ids[arc->to]);
        return result;
    }

    /**
     * @brief Gets the nodes that reach v (the most recently added arc first).
     * Complexity: amortized O(log V + in-degree of v).
     * @return vector<T> Origins of the arcs that enter v; empty if v is not in the graph.
     */
    vector<T> inNeighbors(const T& v) const {
        vector<T> result;
        int to = getId(v);
        if (to != NOT_FOUND)
            for (Arc* arc = g[to].getIn(); arc != nullptr; arc = arc->nextIn)
                result.push_back(ids[arc->from]);
        return result;
    }

    /**
     * @brief Gets the number of distinct nodes that u reaches.
     * Complexity: amortized O(log V) (the degree is a counter; no arc is visited).
     * @throws std::invalid_argument If u is not in the graph.
     */
    int getOutDegree(const T& u) const { return g[requireId(u)].getOutDeg(); }

    /**
     * @brief Gets the number of distinct nodes that reach v.
     * Complexity: amortized O(log V) (the degree is a counter; no arc is visited).
     * @throws std::invalid_argument If v is not in the graph.
     */
    int getInDegree(const T& v) const { return g[requireId(v)].getInDeg(); }

    /**
     * @brief Gets the total accesses made by u (sum of the weights of its outgoing arcs).
     * Complexity: amortized O(log V).
     * @throws std::invalid_argument If u is not in the graph.
     */
    int getOutAccesses(const T& u) const { return g[requireId(u)].getOutAccesses(); }

    /**
     * @brief Gets the total accesses received by v (sum of the weights of its incoming arcs).
     * Complexity: amortized O(log V).
     * @throws std::invalid_argument If v is not in the graph.
     */
    int getInAccesses(const T& v) const { return g[requireId(v)].getInAccesses(); }

    /**
     * @brief Gets the number of vertices.
     * Complexity: O(1).
     */
    int vertexCount() const { return (int)ids.size(); }

    /**
     * @brief Gets the number of arcs (distinct origin-destination pairs).
     * Complexity: O(1).
     */
    int edgeCount() const { return arcCount; }

    vector<T> getVertices() const { return ids; }
};

#endif