/**
 * @file IPRecord.cpp
 * @brief Implements access counter updates and comparisons by IP address.
 * @author Team 1
 * @date 2026-10-30
 */

#include "IPRecord.hpp"

/**
 * @brief Registers a new access of this IP address
 * @param success Whether the access was successful (Accepted).
 * @post Increments totalAccesses and increments successfulAccesses only on success.
 */
void IPRecord::registerAccess(bool success) {
    totalAccesses++;
    if (success)
        successfulAccesses++;
}

/**
 * @brief Compares only the IP addresses.
 * @param other Record whose IP is compared.
 * @return true If this IP is less than the other IP.
 */
bool IPRecord::operator<(const IPRecord& other) const { return ip < other.ip; }

/**
 * @brief Compares only the IP addresses.
 * @param other Record whose IP is compared.
 * @return true If this IP is greater than the other IP.
 */
bool IPRecord::operator>(const IPRecord& other) const { return ip > other.ip; }

/**
 * @brief Compares only the IP addresses.
 * @param other Record whose IP is compared.
 * @return true If this IP is equal to the other IP.
 */
bool IPRecord::operator==(const IPRecord& other) const { return ip == other.ip; }

/**
 * @brief Compares only the IP addresses.
 * @param other Record whose IP is compared.
 * @return true If this IP is different from the other IP.
 */
bool IPRecord::operator!=(const IPRecord& other) const { return ip != other.ip; }

/**
 * @brief Compares only the IP addresses.
 * @param other Record whose IP is compared.
 * @return true If this IP is less than or equal to the other IP.
 */
bool IPRecord::operator<=(const IPRecord& other) const { return ip <= other.ip; }

/**
 * @brief Compares only the IP addresses.
 * @param other Record whose IP is compared.
 * @return true If this IP is greater than or equal to the other IP.
 */
bool IPRecord::operator>=(const IPRecord& other) const { return ip >= other.ip; }