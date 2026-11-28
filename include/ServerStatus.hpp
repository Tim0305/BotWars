/**
 * @file ServerStatus.hpp
 * @author Team 1
 * @brief Defines the per-server counters used by the hash-table traffic monitor.
 * @date 2026-11-27
 */
#pragma once

#include <iomanip>
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
     * @brief Formats the stats of this server: total attempts, number of distinct IPs, the average
     * attempts per IP of the whole server and a table with the attempts of each IP.
     * @details The average is for the server, not for each IP: total attempts divided by the number
     * of distinct IPs, using integer division (the result is truncated). The IP table only shows
     * the attempt count of each IP; it has no average column.
     * @pre At least one IP has been recorded.
     * @return std::string with all the server stats.
     */
    std::string toString() const {
        std::stringstream ss;
        ss << "Attempts: " << attempts << std::endl;
        ss << "Num. IPs: " << ipAccess.size() << std::endl;
        ss << "Avg. Attempts: " << attempts / ipAccess.size() << std::endl;

        ss << std::endl << "==== IP Table ====";
        ss << std::endl << std::left << std::setw(18) << "IP" << "| Attempts" << std::endl;

        for (const auto& pair : ipAccess)
            ss << std::left << std::setw(18) << pair.first.toString() << "| " << pair.second << std::endl;
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
    std::vector<int> getHourAttempts() const { return hourAttempts; }
};