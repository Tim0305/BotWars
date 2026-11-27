/**
 * @file ServerAttempts.hpp
 * @author Team 1
 * @brief Defines the server ranking records and ordering operation.
 * @date 2026-11-27
 */
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "ServerStatus.hpp"
#include "SortingAlgorithms.hpp"

using namespace std;

/**
 * @struct ServerRank
 * @brief Associates server with status.
 */
struct ServerRank {
    string server;
    ServerStatus status;
};

/**
 * @brief Orders server rankings by descending attempt count.
 * Complexity: O(1).
 * @param a First ranking.
 * @param b Second ranking.
 * @return true if a has more attempts than b.
 */
static bool rankMost(const ServerRank& a, const ServerRank& b) {
    return a.status.getAttempts() > b.status.getAttempts();
}

/**
 * @brief Builds a ranking vector and orders servers by their attempt counts.
 * @param map Hash table containing the server statistics.
 * @return std::vector<ServerRank> Rankings from most to fewest attempts.
 */
inline vector<ServerRank> sortServerRankings(const unordered_map<string, ServerStatus>& map) {
    vector<ServerRank> rankings;
    for (const auto& pair : map) rankings.push_back(ServerRank{pair.first, pair.second});
    mergeSortBy(rankings, rankMost);
    return rankings;
}
