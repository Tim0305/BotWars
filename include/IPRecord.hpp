/**
 * @file IPRecord.hpp
 * @brief Struct that holds an IP4 address and its access counters.
 * @author Team 1
 * @date 2026-10-31
 */
 #pragma once
    
 #include "IP4.hpp"

 using namespace std;

 struct IPRecord{
    IP4 ip;
    int totalAccesses;
    int successfulAccesses;

    /**
     * @brief Construct a new IPRecord object
     * @param ip The IP4 address
     * @param success Whether the initial access was successful (Accepted)
     */

     IPRecord(IP4 ip, bool success) 
        : ip(ip), totalAccesses(1), successfulAccesses(success ? 1 : 0) {}

    bool operator<(const IPRecord& other) const { return ip < other.ip; }
    bool operator>(const IPRecord& other) const { return ip > other.ip; }
    bool operator==(const IPRecord& other) const { return ip == other.ip; }
    bool operator<=(const IPRecord& other) const { return ip <= other.ip; }
    bool operator>=(const IPRecord& other) const { return ip >= other.ip; }
 };