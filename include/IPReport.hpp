/**
 * @file IPReports.hpp
 * @brief Helpers to rank the IP records by number of accesses (monthly and final reports)
 * @author Team 1
 * @date 2026-10-28
 */
#pragma once

#include <cstddef>
#include <vector>

#include "IPRecord.hpp"
#include "SortingAlgorithms.hpp"
#include "Splay.hpp"

/**
 * @brief Comparator that sorts IPRecords by totalAccesses from highest to lowest.
 * @details It does not use the IPRecord operators (those compare by IP for the SplayTree).
 * Ties are left as they come, so with getAllRecords() they stay in ascending IP order
 * (mergeSortBy is stable).
 * @param a First record.
 * @param b Second record.
 * @return true If a has strictly more accesses than b.
 */
inline bool byAccessesDesc(const IPRecord& a, const IPRecord& b) { return a.totalAccesses > b.totalAccesses; }

/**
 * @brief Gets the n most accessed IP addresses of the tree.
 * Complexity: O(mlogm), where m is the number of different IPs in the tree.
 *
 * @param tree The tree with the records (it is not modified).
 * @param n How many IPs to return (5, 15, ...).
 * @return std::vector<IPRecord> Up to n records sorted by totalAccesses, highest first.
 *         It has fewer than n elements if the tree has fewer different IPs.
 */
inline std::vector<IPRecord> topIPs(const SplayTree& tree, std::size_t n) {
    std::vector<IPRecord> records = tree.getAllRecords();

    mergeSortBy(records, byAccessesDesc);

    if (records.size() > n)
        records.erase(records.begin() + n, records.end());
    return records;
}