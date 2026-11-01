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
 * Each record starts with one access. Successful accesses are counted separately.
 */
struct IPRecord {
    IP4 ip;                  // IP address of the record.
    int totalAccesses;       // Number of registered accesses, including the initial access.
    int successfulAccesses;  // Number of registered accesses marked successful.

    /**
     * @brief Construct a new IPRecord object from its first access
     * @param ip The IP4 address
     * @param success Whether the initial access was successful (Accepted).
     * @post totalAccesses is 1; successfulAccesses is 1 if success is true, otherwise 0.
     */
    IPRecord(const IP4& ip, bool success)
        : ip(ip), totalAccesses(1), successfulAccesses(success ? 1 : 0) {}

    /**
     * @brief Registers a new access of this IP address
     * @param success Whether the access was successful (Accepted).
     * @post Increments totalAccesses and increments successfulAccesses only on success.
     */
    void registerAccess(bool success);

    /**
     * @brief Compares only the IP addresses.
     * @param other Record whose IP is compared.
     * @return true If this IP is less than the other IP.
     */
    bool operator<(const IPRecord& other) const;

    /**
     * @brief Compares only the IP addresses.
     * @param other Record whose IP is compared.
     * @return true If this IP is greater than the other IP.
     */
    bool operator>(const IPRecord& other) const;

    /**
     * @brief Compares only the IP addresses.
     * @param other Record whose IP is compared.
     * @return true If this IP is equal to the other IP.
     */
    bool operator==(const IPRecord& other) const;

    /**
     * @brief Compares only the IP addresses.
     * @param other Record whose IP is compared.
     * @return true If this IP is different from the other IP.
     */
    bool operator!=(const IPRecord& other) const;

    /**
     * @brief Compares only the IP addresses.
     * @param other Record whose IP is compared.
     * @return true If this IP is less than or equal to the other IP.
     */
    bool operator<=(const IPRecord& other) const;

    /**
     * @brief Compares only the IP addresses.
     * @param other Record whose IP is compared.
     * @return true If this IP is greater than or equal to the other IP.
     */
    bool operator>=(const IPRecord& other) const;
};