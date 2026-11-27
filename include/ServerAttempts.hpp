#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "ServerStatus.hpp"
#include "SortingAlgorithms.hpp"

using namespace std;

struct ServerRank {
    string server;
    ServerStatus status;
};

static bool rankMost(const ServerRank& a, const ServerRank& b) {
    return a.status.getAttempts() > b.status.getAttempts();
}

inline vector<ServerRank> sortServerRankings(const unordered_map<string, ServerStatus>& map) {
    vector<ServerRank> rankings;
    for (const auto& pair : map) rankings.push_back(ServerRank{pair.first, pair.second});
    mergeSortBy(rankings, rankMost);
    return rankings;
}
