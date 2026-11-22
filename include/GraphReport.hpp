/**
 * @file GraphReport.hpp
 * @brief Vertex type of the access graph and the text reports built from it.
 * @details For complexity, V is the number of graph vertices, L is the largest vertex-name
 * length (at least 1), k is the number of ranking rows and H is the title length. Integer
 * operations and IPv4 comparisons take O(1). Copying or comparing server names takes O(L).
 * Bounds involving graph lookups are amortized because the index is a splay tree.
 * @author Team 1
 * @date 2026-11-21
 */

#pragma once

#include <iomanip>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "ArcListGraph.hpp"
#include "IP4.hpp"

using namespace std;

/**
 * @brief A vertex is either an IP (origin) or a server name (destination).
 * @details variant compares by alternative first (IPs before servers) and then by value, so IPs
 * are ordered numerically with IP4 and servers alphabetically, and an IP can never be confused
 * with a server.
 */
using NetVertex = variant<IP4, string>;

/// Access graph: an arc goes from the IP to the server it accessed.
using NetGraph = ArcListGraph<NetVertex>;

/**
 * @brief Degree and access total of a vertex in a ranking.
 * @details For the out ranking, degree is the out-degree and accesses is the sum of the
 * weights of the arcs that leave the vertex. For the in ranking they are the in versions.
 */
struct VertexRank {
    NetVertex vertex;
    int degree;
    int accesses;
};

/**
 * @brief Tells if a goes before b: larger degree, then more accesses, then smaller vertex.
 * Complexity: O(1) for degree/access comparisons or IP ties; O(L) for server-name ties.
 * @param a First ranked vertex.
 * @param b Second ranked vertex.
 * @return bool Whether a must precede b in the ranking.
 */
static bool ranksBefore(const VertexRank& a, const VertexRank& b) {
    if (a.degree != b.degree)
        return a.degree > b.degree;
    if (a.accesses != b.accesses)
        return a.accesses > b.accesses;
    return a.vertex < b.vertex;
}

/**
 * @brief Builds a ranking by out-degree or by in-degree.
 * Complexity: amortized O(V L log V) time and O(V L) additional space. For bounded-length
 * names this is O(V log V) time. Collecting rows also performs splay lookups.
 * @pre Access-graph arcs go from IP4 vertices to server-name vertices, so a nonzero outgoing
 * degree identifies an IP and a nonzero incoming degree identifies a server.
 * @param byOut true to rank by out-degree, false to rank by in-degree.
 * @param n Maximum number of vertices to return; zero or less returns an empty vector.
 * @param netGraph Access graph to rank.
 * @return vector<VertexRank> Ranked vertices, cut to n.
 */
inline vector<VertexRank> rankVertices(bool byOut, int n, const NetGraph& netGraph) {
    vector<VertexRank> ranking;
    vector<NetVertex> vertices = netGraph.getVertices();

    for (NetVertex vertex : vertices) {
        int degree = byOut ? netGraph.getOutDegree(vertex) : netGraph.getInDegree(vertex);
        if (degree != 0) {
            int accesses = byOut ? netGraph.getOutAccesses(vertex) : netGraph.getInAccesses(vertex);
            ranking.push_back(VertexRank{vertex, degree, accesses});
        }
    }

    mergeSortBy(ranking, ranksBefore);

    size_t keep = n > 0 ? (size_t)n : 0;
    if (ranking.size() > keep)
        ranking.erase(ranking.begin() + keep, ranking.end());
    return ranking;
}

/**
 * @brief Ranks the vertices that have outgoing arcs by out-degree.
 * Complexity: amortized O(V L log V) time and O(V L) additional space; O(V log V) time
 * for bounded-length names.
 * @param n Maximum number of vertices to return; zero or less returns an empty vector.
 * @param graph Access graph whose arcs go from IP4 origins to server-name destinations.
 * @return vector<VertexRank> Up to n vertices from the largest to the smallest out-degree.
 * If two vertices have the same degree, the one with more accesses goes first; if they still
 * tie, the smaller vertex (using <) goes first. Vertices with out-degree 0 are not ranked.
 */
inline vector<VertexRank> topByOutDegree(int n, const NetGraph& graph) {
    return rankVertices(true, n, graph);
}

/**
 * @brief Ranks the vertices that have incoming arcs by in-degree.
 * Complexity: amortized O(V L log V) time and O(V L) additional space; O(V log V) time
 * for bounded-length names.
 * @param n Maximum number of vertices to return; zero or less returns an empty vector.
 * @param graph Access graph whose arcs go from IP4 origins to server-name destinations.
 * @return vector<VertexRank> Up to n vertices from the largest to the smallest in-degree.
 * Ties are broken as in topByOutDegree. Vertices with in-degree 0 are not ranked.
 */
inline vector<VertexRank> topByInDegree(int n, const NetGraph& graph) {
    return rankVertices(false, n, graph);
}

/**
 * @brief Gets the text of a vertex.
 * Complexity: O(1) for IPv4; O(L) time and additional space for a copied server name.
 * @param vertex IP or server.
 * @return string The IP as a.b.c.d or the server name.
 */
inline string vertexName(const NetVertex& vertex) {
    return holds_alternative<IP4>(vertex) ? get<IP4>(vertex).toString() : get<string>(vertex);
}

/**
 * @brief Creates the text of one ranking.
 * Complexity: O(H + k L) time and additional space, including the returned text.
 * @param title Title of the ranking.
 * @param ranking Vertices already ordered from first to last.
 * @return string One line per vertex with position, name, degree and total accesses.
 */
inline string rankingReport(const string& title, const vector<VertexRank>& ranking) {
    stringstream ss;
    ss << endl << "==== " << title << " ====" << endl;
    for (size_t i = 0; i < ranking.size(); i++)
        ss << (i + 1) << ". " << vertexName(ranking[i].vertex)
           << "\t | \tDegree: " << ranking[i].degree << "\t | \tAccesses: " << ranking[i].accesses
           << endl;
    return ss.str();
}

/**
 * @brief Creates the graph report: size of the graph, top 5 IPs by out-degree and top 5
 * servers by in-degree.
 * Complexity: amortized O(V L log V) time and O(V L) additional space; O(V log V) time
 * for bounded-length names. Degree/access queries locate nodes without scanning arcs.
 * @pre Arcs go from IP4 origins to server-name destinations.
 * @param graph Graph with all the accesses.
 * @return string Graph sizes, matching incoming/outgoing access totals and both rankings.
 */
inline string graphReport(const NetGraph& graph) {
    stringstream ss;
    int verticesCount = graph.vertexCount();
    int arcsCount = graph.edgeCount();

    int srcIpsCount = 0;
    int dstServersCount = 0;
    int totalOutAccesses = 0;
    int totalInAccesses = 0;
    for (NetVertex vertex : graph.getVertices()) {
        if (holds_alternative<IP4>(vertex))
            srcIpsCount++;
        else
            dstServersCount++;
        totalOutAccesses += graph.getOutAccesses(vertex);
        totalInAccesses += graph.getInAccesses(vertex);
    }

    ss << endl << "==== Access graph ====" << endl;
    ss << "Vertices: " << verticesCount << endl;
    ss << "Arcs: " << arcsCount << endl;
    ss << "Src IPs: " << srcIpsCount << endl;
    ss << "Dst Servers: " << dstServersCount << endl;
    ss << "Total number of out-accesses: " << totalOutAccesses << endl;
    ss << "Total number of in-accesses: " << totalInAccesses << endl;
    ss << rankingReport("TOP 5 IPs by out-degree", topByOutDegree(5, graph));
    ss << rankingReport("TOP 5 servers by in-degree", topByInDegree(5, graph));
    return ss.str();
}