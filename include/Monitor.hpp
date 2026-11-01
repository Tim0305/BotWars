/**
 * @file Monitor.hpp
 * @author Team 1
 * @brief File that defines the functionality of the IPRecords monitor
 * @date 2026-10-30
 */

#pragma once

#include <vector>

#include "IPRecord.hpp"
#include "SortingAlgorithms.hpp"
#include "Splay.hpp"

using namespace std;

/**
 * @brief Compares two IP records by their total number of accesses.
 * @param a First record.
 * @param b Second record.
 * @return true If a has more accesses than b.
 */
inline bool byAccessesDesc(const IPRecord& a, const IPRecord& b) {
    return a.totalAccesses > b.totalAccesses;
}

/**
 * @brief Gets the n IP addresses with the most accesses.
 * Complexity: O(mlogm), where m is the number of different IPs in the tree.
 *
 * @param splayTree Tree with the IP records; it is not changed.
 * @param n Maximum number of IPs to return.
 * @pre n must be zero or greater.
 * @return vector<IPRecord> Up to n records, from most to least accesses.
 * IPs with the same number of accesses are returned in ascending IP order.
 */
vector<IPRecord> topIPs(const SplayTree<IPRecord>& splayTree, const int n) {
    vector<IPRecord> records = splayTree.inorder();

    mergeSortBy(records, byAccessesDesc);

    // Return only the top n elements
    if (records.size() > n)
        records.erase(records.begin() + n, records.end());
    return records;
}

/**
 * @brief Creates the report shown at the end of a month.
 * @param splayTree Tree with all IP records read so far.
 * @param month Month shown in the report title.
 * @return string Number of different IPs, average accesses and top 5 IPs.
 * If the tree is empty, returns only the title and "Total IPs: 0".
 * @details Includes accesses from earlier months, not just the named month.
 */
string monthSummary(const SplayTree<IPRecord>& splayTree, const Month month) {
    stringstream ss;

    // Get all the IP records accumulated up to that moment
    vector<IPRecord> records = splayTree.inorder();

    ss << endl << "==== End of " << monthToString(month) << " ====" << endl;
    ss << "Total IPs: " << records.size() << endl;

    if (!records.empty()) {
        int totalAccesses = 0;
        for (const IPRecord& record : records) totalAccesses += record.totalAccesses;

        // Get the average number of accesses per IP
        float avgAccesses = (float)totalAccesses / records.size();
        ss << "Average accesses per IP: " << fixed << setprecision(2) << avgAccesses << endl;

        // Add up to five IPs with the most accesses
        ss << endl << "Top 5 IPs with the most accesses:" << endl;
        vector<IPRecord> top5IPs = topIPs(splayTree, 5);
        for (const IPRecord& record : top5IPs)
            ss << record.ip.toString() << "\t\t | \tAccesses: " << record.totalAccesses << endl;
    }

    return ss.str();
}

/**
 * @brief Creates a report of the 15 IPs with the most accesses.
 * @param splayTree Tree with the IP records.
 * @pre Each record must have at least one access.
 * @return string Up to 15 IPs with their total accesses, successful accesses
 * and percentage of successful accesses. Ties use ascending IP order.
 */
string top15IpRecords(const SplayTree<IPRecord>& splayTree) {
    stringstream ss;

    // Get up to fifteen records ranked by access count
    vector<IPRecord> top15IPs = topIPs(splayTree, 15);

    ss << endl << "==== TOP 15 IPs ====" << endl;

    for (const IPRecord& record : top15IPs) {
        ss << record.ip.toString() << "\t\t | \tAccesses: " << record.totalAccesses
           << "\t | \tSuccessful: " << record.successfulAccesses << "\t | \tSuccess rate: " << fixed
           << setprecision(2) << (100.0 * record.successfulAccesses / record.totalAccesses) << "%"
           << endl;
    }

    return ss.str();
}

/**
 * @brief Creates a report of the IPs between two IP addresses.
 * @param splayTree Tree with the IP records; it is not changed.
 * @param startIp First IP in the range, included in the search.
 * @param endIp Last IP in the range, included in the search.
 * @return string Matching IPs in ascending order, their counters and total accesses.
 * Returns a report with zero matches if no IP is found or startIp is greater than endIp.
 */
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

/**
 * @brief Creates a report of the block containing the most accessed IP.
 * @param splayTree Tree with the IP records; it is not changed.
 * @pre The tree must contain at least one record.
 * @return string The most accessed IP and the records in its block.
 * @details The range keeps the first three numbers of that IP and uses 0 through
 * 255 for the last number. For example, 192.168.1.5 gives 192.168.1.0 to 192.168.1.255.
 * If IPs have the same highest access count, the lowest IP is selected.
 */
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
