/**
 * @file IP4.cpp
 * @author Team 1
 * @brief Implements the functionality and methods of the IP4 class
 * @date 2026-10-09
 */

#include "IP4.hpp"

#include <sstream>
#include <vector>

using namespace std;

/**
 * @brief Checks if this address is greater than another address.
 * @param ip Address to compare.
 * @return true If this address is greater than @p ip.
 * @return false Otherwise.
 */
bool IP4::operator>(const IP4& ip) const {
    if (this->net1 != ip.net1)
        return this->net1 > ip.net1;
    if (this->net2 != ip.net2)
        return this->net2 > ip.net2;
    if (this->net3 != ip.net3)
        return this->net3 > ip.net3;
    return this->host > ip.host;
}

/**
 * @brief Checks if this address is less than another address.
 * @param ip Address to compare with.
 * @return true If @p ip is greater than this address.
 * @return false Otherwise.
 */
bool IP4::operator<(const IP4& ip) const { return (ip > (*this)); }

/**
 * @brief Checks if all four components match another address.
 * @param ip Address to compare with.
 * @return true If all components are equal.
 * @return false Otherwise.
 */
bool IP4::operator==(const IP4& ip) const {
    return this->net1 == ip.net1 && this->net2 == ip.net2 && this->net3 == ip.net3 &&
        this->host == ip.host;
}

/**
 * @brief Checks if two addresses are different.
 * @param ip Address to compare with.
 * @return true If at least one component differs.
 * @return false Otherwise.
 */
bool IP4::operator!=(const IP4& ip) const { return !(*this == ip); }

/**
 * @brief Checks if this address is greater than or equal to another address.
 * @param ip Address to compare with.
 * @return true If this address is not less than @p ip.
 * @return false Otherwise.
 */
bool IP4::operator>=(const IP4& ip) const { return !(*this < ip); }

/**
 * @brief Checks if this address is less than or equal to another address.
 * @param ip Address to compare with.
 * @return true If @p ip is not less than this address.
 * @return false Otherwise.
 */
bool IP4::operator<=(const IP4& ip) const { return !(ip < *this); }

/**
 * @brief Formats the four components of the address.
 * @return string Address formatted as `a.b.c.d`.
 */
string IP4::toString() const {
    stringstream ss;
    ss << net1 << ".";
    ss << net2 << ".";
    ss << net3 << ".";
    ss << host;
    return ss.str();
}

/**
 * @brief Parses an IPv4 address into four integer components.
 * @param strIp String containing the address to parse.
 * @return IP4 Parsed address.
 * @throws std::invalid_argument If the input does not have exactly four dot-separated
 *         components, or if a component is empty, has anything other than digits
 *         (spaces and signs included), has more than three digits or is greater than 255.
 * @details Leading zeros are accepted when the component has at most three digits.
 */
IP4 IP4::fromString(const string& strIp) {
    int parts[4];
    size_t pos = 0;

    for (int i = 0; i < 4; i++) {
        size_t end = strIp.find('.', pos);
        bool hasDot = (end != string::npos);

        // The first three components must be followed by a dot; the last one must not
        // (this rejects missing components, extra components and a trailing dot)
        if (hasDot != (i < 3))
            throw invalid_argument("Invalid ip");

        string token = strIp.substr(pos, hasDot ? end - pos : string::npos);

        // Only 1 to 3 digits, so stoi can never overflow
        if (token.empty() || token.size() > 3 ||
            !std::all_of(token.begin(), token.end(),
                         [](unsigned char c) { return std::isdigit(c); }))
            throw invalid_argument("Invalid ip");

        parts[i] = std::stoi(token);
        if (parts[i] > 255)
            throw invalid_argument("Invalid ip");

        pos = end + 1;
    }

    return IP4(parts[0], parts[1], parts[2], parts[3]);
}

/**
 * @brief Gets the first part of the address.
 * @return int The stored number.
 */
int IP4::getNet1() const { return net1; };

/**
 * @brief Gets the second part of the address.
 * @return int The stored number.
 */
int IP4::getNet2() const { return net2; };

/**
 * @brief Gets the third part of the address.
 * @return int The stored number.
 */
int IP4::getNet3() const { return net3; };

/**
 * @brief Gets the fourth part of the address.
 * @return int The stored number.
 */
int IP4::getHost() const { return host; };