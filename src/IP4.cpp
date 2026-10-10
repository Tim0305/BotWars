/**
 * @file IP4.cpp
 * @brief Implements IPv4 address comparison, formatting, and parsing.
 */
#include "IP4.hpp"
#include <vector>
#include <sstream>

/**
 * @brief Compares IPv4 addresses from the first component to the last.
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
    return this->net1 == ip.net1 && this->net2 == ip.net2 && this->net3 == ip.net3 && this->host == ip.host;
}

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
 * @brief Parses a IP4 address into four integer components.
 * @param strIp String containing the address to parse.
 * @return IP4 Parsed address.
 * @throws std::invalid_argument If the input does not have four components or
 *         one of its components is not an integer.
 * @throws std::out_of_range If a component cannot be represented as an int.
 */
IP4 IP4::fromString(const string& strIp) {
    vector<int> tokens;
    stringstream ss(strIp);
    string token;

    while (getline(ss, token, '.')) {
        tokens.push_back(stoi(token));
    }

    if (tokens.size() != 4)
        throw invalid_argument("Invalid ip");

    return IP4(tokens[0], tokens[1], tokens[2], tokens[3]);
}
