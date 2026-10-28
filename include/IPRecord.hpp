/**
 * @file IPRecord.hpp
 * @brief Struct that holds an IP4 address and its access counters.
 * @author Team 1
 * @date 2026-10-31
 */
#pragma once

#include "IP4.hpp"

/**
 * @struct IPRecord
 * @brief Access counters of a single IP address.
 *
 * @details The comparison operators only look at the IP address (the counters are ignored),
 * so two records of the same IP are considered equal even if their counters differ.
 */
struct IPRecord {
    IP4 ip;
    int totalAccesses;
    int successfulAccesses;

    /**
     * @brief Construct a new IPRecord object from its first access
     * @param ip The IP4 address
     * @param success Whether the initial access was successful (Accepted)
     */
    IPRecord(const IP4& ip, bool success) : ip(ip), totalAccesses(1), successfulAccesses(success ? 1 : 0) {}

    /**
     * @brief Registers a new access of this IP address
     * @param success Whether the access was successful (Accepted)
     */
    void registerAccess(bool success) {
        totalAccesses++;
        if (success)
            successfulAccesses++;
    }

    bool operator<(const IPRecord& other) const { return ip < other.ip; }
    bool operator>(const IPRecord& other) const { return ip > other.ip; }
    bool operator==(const IPRecord& other) const { return ip == other.ip; }
    bool operator<=(const IPRecord& other) const { return ip <= other.ip; }
    bool operator>=(const IPRecord& other) const { return ip >= other.ip; }
};