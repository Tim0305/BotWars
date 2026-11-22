/**
 * @file GraphReport.hpp
 * @brief Node type of the access graph and the text reports built from it.
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
 * @brief A node is either an IP (origin) or a server name (destination).
 * @details variant compares by alternative first (IPs before servers) and then by value, so IPs
 * are ordered numerically with IP4 and servers alphabetically, and an IP can never be confused
 * with a server.
 */
using NetNode = variant<IP4, string>;

/// Access graph: an arc goes from the IP to the server it accessed.
using NetGraph = ArcListGraph<NetNode>;

/**
 * @brief Gets the text of a node.
 * @param node IP or server.
 * @return string The IP as a.b.c.d or the server name.
 */
inline string nodeName(const NetNode& node) {
    return holds_alternative<IP4>(node) ? get<IP4>(node).toString() : get<string>(node);
}

/**
 * @brief Creates the text of one ranking.
 * @param title Title of the ranking.
 * @param ranking Nodes already ordered from first to last.
 * @return string One line per node with position, name, degree and total accesses.
 */
inline string rankingReport(const string& title, const vector<NetGraph::NodeRank>& ranking) {
    stringstream ss;
    ss << endl << "==== " << title << " ====" << endl;
    for (size_t i = 0; i < ranking.size(); i++)
        ss << (i + 1) << ". " << nodeName(ranking[i].node) << "\t | \tDegree: " << ranking[i].degree
           << "\t | \tAccesses: " << ranking[i].accesses << endl;
    return ss.str();
}

/**
 * @brief Creates the graph report: size of the graph, top 5 IPs by out-degree and top 5
 * servers by in-degree.
 * @param graph Graph with all the accesses.
 * @return string The full report.
 */
inline string graphReport(const NetGraph& graph) {
    stringstream ss;
    ss << endl << "==== Access graph ====" << endl;
    ss << "Nodes: " << graph.nodeCount() << endl;
    ss << "Arcs: " << graph.edgeCount() << endl;
    ss << rankingReport("TOP 5 IPs by out-degree", graph.topByOutDegree(5));
    ss << rankingReport("TOP 5 servers by in-degree", graph.topByInDegree(5));
    return ss.str();
}