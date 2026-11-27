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
    void addIpAccess(const IP4& ip) {
        ipAccess[ip]++;
        incrementAttempt();
    }

    void incrementAttempt() { attempts++; }

    void decrementAttempt() { attempts--; }

    void incrementAttempt(int h) {
        if (h < 0 || h > 23)
            throw std::invalid_argument("Invalid hour");
        attempts++;
        hourAttempts[h]++;
    }

    void decrementAttempt(int h) {
        if (h < 0 || h > 23)
            throw std::invalid_argument("Invalid hour");
        attempts--;
        hourAttempts[h]--;
    }

    std::string toString() {
        std::stringstream ss;
        ss << "Attempts: " << attempts << std::endl;
        ss << "Num. IPs: " << ipAccess.size() << std::endl;

        ss << "==== IP Table ====" << std::endl;
        ss << std::endl << "IP" << "\t|\t" << "Avg. Attempts" << std::endl;

        for (const auto& pair : ipAccess)
            ss << pair.first.toString() << "\t|\t" << pair.second / attempts << std::endl;

        return ss.str();
    }
};