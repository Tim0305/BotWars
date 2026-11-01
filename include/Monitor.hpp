#pragma once

#include <vector>

#include "IPRecord.hpp"
#include "SortingAlgorithms.hpp"
#include "Splay.hpp"

using namespace std;

/**
 * @brief Comparator that sorts IPRecords by totalAccesses from highest to lowest.
 * @details It does not use the IPRecord operators (those compare by IP for the SplayTree).
 * Ties are left as they come, so with getAllRecords() they stay in ascending IP order
 * (mergeSortBy is stable).
 * @param a First record.
 * @param b Second record.
 * @return true If a has strictly more accesses than b.
 */
inline bool byAccessesDesc(const IPRecord& a, const IPRecord& b) {
    return a.totalAccesses > b.totalAccesses;
}

/**
 * @brief Gets the n most accessed IP addresses of the tree.
 * Complexity: O(mlogm), where m is the number of different IPs in the tree.
 *
 * @param tree The tree with the records (it is not modified).
 * @param n How many IPs to return (5, 15, ...).
 * @return std::vector<IPRecord> Up to n records sorted by totalAccesses, highest first.
 *         It has fewer than n elements if the tree has fewer different IPs.
 */
vector<IPRecord> topIPs(const SplayTree<IPRecord>& splayTree, const int n) {
    vector<IPRecord> records = splayTree.inorder();

    mergeSortBy(records, byAccessesDesc);

    // Return only the top n elements
    if (records.size() > n)
        records.erase(records.begin() + n, records.end());
    return records;
}

string monthSummary(const SplayTree<IPRecord>& splayTree, const Month month) {
    stringstream ss;

    // Get all the IP records accumulated up to that moment
    vector<IPRecord> records = splayTree.inorder();

    ss << endl << "==== End of " << monthToString(month) << " ====" << endl;
    ss << "Total IPs: " << records.size() << endl;

    if (!records.empty()) {
        // Total accesses monthly
        int totalAccesses = 0;
        for (const IPRecord& record : records) totalAccesses += record.totalAccesses;

        // Get the average number of accesses per IP
        float avgAccesses = (float)totalAccesses / records.size();
        ss << "Average accesses per IP: " << fixed << setprecision(2) << avgAccesses << endl;

        // Print the 5 IPs with the most accesses
        ss << endl << "Top 5 IPs with the most accesses:" << endl;
        vector<IPRecord> top5IPs = topIPs(splayTree, 5);
        for (const IPRecord& record : top5IPs)
            ss << record.ip.toString() << "\t\t | \tAccesses: " << record.totalAccesses << endl;
    }

    return ss.str();
}

string top15IpRecords(const SplayTree<IPRecord>& splayTree) {
    stringstream ss;

    // Get all the IP records
    vector<IPRecord> top15IPs = topIPs(splayTree, 15);

    ss << endl << "==== TOP 15 IPs ====" << endl;

    for (const IPRecord& record : top15IPs) {
        ss << record.ip.toString() << "\t\t | \tAccesses: " << record.totalAccesses
           << "\t | \tSuccessful: " << record.successfulAccesses << "\t | \tSuccess rate: " << fixed
           << setprecision(2) << (float)record.successfulAccesses / record.totalAccesses << "%"
           << endl;
    }

    return ss.str();
}

string queryByIpRange(const SplayTree<IPRecord>& splayTree, const IP4& startIp, const IP4& endIp) {
    stringstream ss;

    // Get all the ip records within a range
    IPRecord startRecord = IPRecord(startIp, false);
    IPRecord endRecord = IPRecord(endIp, false);
    vector<IPRecord> records = splayTree.inorderRange(startRecord, endRecord);

    ss << endl
       << "==== Records within " << startIp.toString() << " - " << endIp.toString()
       << " ====" << endl;
    ss << "Total IPs: " << records.size() << endl;

    int totalAccesses = 0;
    for (const IPRecord& record : records) {
        ss << record.ip.toString() << "\t | \tAccesses: " << record.totalAccesses
           << "\t | \tSuccessful: " << record.successfulAccesses << endl;
        totalAccesses += record.totalAccesses;
    }
    ss << "Total accesses: " << totalAccesses << endl;

    return ss.str();
}

string queryMostAccessedIpBlock(const SplayTree<IPRecord>& splayTree) {
    stringstream ss;

    // Get the most accessed ip
    IPRecord topRecord = topIPs(splayTree, 1)[0];
    int net1 = topRecord.ip.getNet1();
    int net2 = topRecord.ip.getNet2();
    int net3 = topRecord.ip.getNet3();

    ss << endl
       << "Top IP: " << topRecord.ip.toString()
       << queryByIpRange(splayTree, IP4(net1, net2, net3, 0), IP4(net1, net2, net3, 255));
    return ss.str();
}