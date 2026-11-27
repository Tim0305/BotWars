/**
 * @file IP4.hpp
 * @brief Class that represents an IPv4 address
 * @author Team 1
 * @date 2026-10-09
 */
#pragma once

#include <string>

/**
 * @class IP4
 * @brief Represents an IPv4 address as four integer components.
 *
 * The comparison operators compare the components from left to
 * right, starting with the first octet.
 *
 * @property net1 First octet of the address.
 * @property net2 Second octet of the address.
 * @property net3 Third octet of the address.
 * @property host Fourth octet of the address.
 */
class IP4 {
private:
    int net1;
    int net2;
    int net3;
    int host;

public:
    /**
     * @brief Constructs an address from its four components.
     * Complexity: O(1).
     * @pre Each number should be between 0 and 255
     * @param net1 First octet.
     * @param net2 Second octet.
     * @param net3 Third octet.
     * @param host Fourth octet.
     */
    IP4(int net1, int net2, int net3, int host) : net1(net1), net2(net2), net3(net3), host(host) {}

    /**
     * @brief Checks if an address is greater than another address.
     * Complexity: O(1).
     * @param ip Address to compare with.
     * @return true If this address is greater than @p ip.
     * @return false Otherwise.
     */
    bool operator>(const IP4& ip) const;

    /**
     * @brief Checks if an address is less than another address.
     * Complexity: O(1).
     * @param ip Address to compare with.
     * @return true If this address is less than @p ip.
     * @return false Otherwise.
     */
    bool operator<(const IP4& ip) const;

    /**
     * @brief Checks if two addresses are identical.
     * Complexity: O(1).
     * @param ip Address to compare with.
     * @return true If all four components are equal.
     * @return false Otherwise.
     */
    bool operator==(const IP4& ip) const;

    /**
     * @brief Checks if two addresses are different.
     * Complexity: O(1).
     * @param ip Address to compare with.
     * @return true If at least one component differs.
     * @return false Otherwise.
     */
    bool operator!=(const IP4& ip) const;

    /**
     * @brief Checks if an address is greater than or equal to another address.
     * Complexity: O(1).
     * @param ip Address to compare with.
     * @return true If this address is greater than or equal to @p ip.
     * @return false Otherwise.
     */
    bool operator>=(const IP4& ip) const;

    /**
     * @brief Checks if an address is less than or equal to another address.
     * Complexity: O(1).
     * @param ip Address to compare with.
     * @return true If this address is less than or equal to @p ip.
     * @return false Otherwise.
     */
    bool operator<=(const IP4& ip) const;

    /**
     * @brief Formats the address.
     * Complexity: O(1).
     * @return std::string Address formatted as `a.b.c.d`.
     */
    std::string toString() const;

    /**
     * @brief Parses the formatted address.
     * Complexity: O(n) for input length n; valid IPv4 strings have bounded length.
     * @param strIp Address in a.b.c.d format. Each number must have one to three
     * digits and be between 0 and 255. Spaces, signs and extra dots are not accepted.
     * @return IP4 Address created from the parsed components.
     * @throws std::invalid_argument If the string does not follow that format.
     */
    static IP4 fromString(const std::string& strIp);

    /**
     * @brief Gets the first part of the address.
     * Complexity: O(1).
     * @return int The stored number.
     */
    int getNet1() const;

    /**
     * @brief Gets the second part of the address.
     * Complexity: O(1).
     * @return int The stored number.
     */
    int getNet2() const;

    /**
     * @brief Gets the third part of the address.
     * Complexity: O(1).
     * @return int The stored number.
     */
    int getNet3() const;

    /**
     * @brief Gets the fourth part of the address.
     * Complexity: O(1).
     * @return int The stored number.
     */
    int getHost() const;

    uint32_t toUint32() const noexcept {
        return (uint32_t(net1) << 24) | (uint32_t(net2) << 16) | (uint32_t(net3) << 8) |
            uint32_t(host);
    }

    std::size_t hash() const noexcept { return std::hash<uint32_t>{}(toUint32()); }
};

// Add the hash function to IP4
namespace std {
template <>
struct hash<IP4> {
    std::size_t operator()(const IP4& ip) const noexcept { return ip.hash(); }
};
}  // namespace std