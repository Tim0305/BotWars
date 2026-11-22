/**
 * @file ArcVertex.hpp
 * @brief Node of an arc list graph: its two arc lists plus degree and access counters.
 * @author Team 1
 * @date 2026-11-21
 */

#ifndef ARC_VERTEX_HPP
#define ARC_VERTEX_HPP

/**
 * @class ArcVertex
 * @brief Stores the heads of the out list and the in list of a node and their counters.
 * @tparam ArcType Arc type owned by the graph. Only pointers to it are stored here.
 *
 * @details The out list has the arcs that leave the node (the node is the origin) and the in
 * list has the arcs that enter it (the node is the destination). The vertex does not own the
 * arcs and does not follow the links between them, so the graph decides how they are chained.
 * Degrees and access totals are counters kept up to date by the graph, so reading them is O(1)
 * and never goes through the arcs:
 * - out-degree / in-degree: number of arcs in the out list / in list.
 * - out accesses / in accesses: sum of the weights of the arcs in the out list / in list.
 */
template <typename ArcType>
class ArcVertex {
private:
    ArcType* out = nullptr;
    ArcType* in = nullptr;
    int outDeg = 0;
    int inDeg = 0;
    int outAccesses = 0;
    int inAccesses = 0;

public:
    /**
     * @brief Creates a node with empty lists and all counters in zero.
     * Complexity: O(1).
     */
    ArcVertex() = default;

    /**
     * @brief Gets the first arc that leaves the node.
     * @return ArcType* First arc of the out list, or nullptr if the node has no outgoing arcs.
     */
    ArcType* getOut() const { return out; }

    /**
     * @brief Gets the first arc that enters the node.
     * @return ArcType* First arc of the in list, or nullptr if the node has no incoming arcs.
     */
    ArcType* getIn() const { return in; }

    /**
     * @brief Gets the number of arcs that leave the node.
     * @return int Out-degree.
     */
    int getOutDeg() const { return outDeg; }

    /**
     * @brief Gets the number of arcs that enter the node.
     * @return int In-degree.
     */
    int getInDeg() const { return inDeg; }

    /**
     * @brief Gets the sum of the weights of the arcs that leave the node.
     * @return int Total accesses made by this node as origin.
     */
    int getOutAccesses() const { return outAccesses; }

    /**
     * @brief Gets the sum of the weights of the arcs that enter the node.
     * @return int Total accesses received by this node as destination.
     */
    int getInAccesses() const { return inAccesses; }

    /**
     * @brief Sets the first arc of the out list.
     * @param newOut New head of the list (the graph links the previous head behind it).
     */
    void setOut(ArcType* newOut) { out = newOut; }

    /**
     * @brief Sets the first arc of the in list.
     * @param newIn New head of the list (the graph links the previous head behind it).
     */
    void setIn(ArcType* newIn) { in = newIn; }

    /**
     * @brief Adds one to the out-degree.
     */
    void incrementOutDeg() { outDeg++; }

    /**
     * @brief Adds one to the in-degree.
     */
    void incrementInDeg() { inDeg++; }

    /**
     * @brief Adds accesses to the out total.
     * @param amount Accesses to add.
     */
    void addOutAccesses(int amount) { outAccesses += amount; }

    /**
     * @brief Adds accesses to the in total.
     * @param amount Accesses to add.
     */
    void addInAccesses(int amount) { inAccesses += amount; }
};

#endif