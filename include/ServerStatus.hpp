#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "IP4.hpp"

class ServerStatus {
private:
    int attempts = 0;
    std::unordered_map<IP4, int> ipAccess;
    std::vector<int> hourAttempts = std::vector<int>(24, 0);

public:
    void addIpAccess(const IP4& ip, int h) {
        if (h < 0 || h > 23)
            throw std::invalid_argument("Invalid hour");
        ipAccess[ip]++;
        attempts++;
        hourAttempts[h]++;
    }

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

    int getAttempts() const { return attempts; }

    vector<int> getHourAttempts() const { return hourAttempts; }
};