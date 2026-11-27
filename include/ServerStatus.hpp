/**
 * @file ServerStatus.hpp
 * @author Team 1
 * @brief Defines the per-server counters used by the hash-table traffic monitor.
 * @date 2026-11-27
 */
#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "IP4.hpp"

/**
 * @class ServerStatus
 * @brief Stores the access totals for one server.
 * @details The IP table stores each source IP once and counts its attempts.
 */
class ServerStatus {
private:
    int attempts = 0;
    std::unordered_map<IP4, int> ipAccess;
    std::vector<int> hourAttempts = std::vector<int>(24, 0);

public:
    /**
     * @brief Records one access from an IP at the given hour.
     * @param ip Source IP address.
     * @param hour Hour of day, from 0 to 23.
     * @throws std::invalid_argument If hour is outside 0 to 23.
     * @post Increments this server's total, that IP's count, and the hour count.
     */
    void addIpAccess(const IP4& ip, int h) {
        if (h < 0 || h > 23)
            throw std::invalid_argument("Invalid hour");
        ipAccess[ip]++;
        attempts++;
        hourAttempts[h]++;
    }

    /**
     * @brief Formats the table of IP access stats.
     * @pre At least one IP has been recorded.
     * @return std::string with all the server stats.
     */
    std::string toString() const {
        std::stringstream ss;
        ss << "Attempts: " << attempts << std::endl;
        ss << "Num. IPs: " << ipAccess.size() << std::endl;
        ss << "Avg. Attempts: " << attempts / ipAccess.size() << std::endl;

        ss << std::endl << "==== IP Table ====";
        ss << std::endl << "IP \t|\t Attempts \t|\t Avg. Attempts" << std::endl;

        for (const auto& pair : ipAccess)
            ss << pair.first.toString() << "\t|\t" << pair.second << "\t|\t"
               << pair.second / ipAccess.size() << std::endl;

        return ss.str();
    }

    /**
     * @brief Gets the total number of accesses received by this server.
     * @return int Total access count.
     */
    int getAttempts() const { return attempts; }

    /**
     * @brief Gets a copy of the number of accesses received in each hour.
     * @return std::vector<int> Counts indexed by hour 0 to 23.
     */
    vector<int> getHourAttempts() const { return hourAttempts; }
};