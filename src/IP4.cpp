#include "IP4.hpp"

#include <sstream>

bool IP4::operator>(const IP4& ip) const {
    if (this->net1 != ip.net1)
        return this->net1 > ip.net1;
    if (this->net2 != ip.net2)
        return this->net2 > ip.net2;
    if (this->net3 != ip.net3)
        return this->net3 > ip.net3;
    return this->host > ip.host;
}

bool IP4::operator<(const IP4& ip) const { return (ip > (*this)); }

bool IP4::operator==(const IP4& ip) const {
    return this->net1 == ip.net1 && this->net2 == ip.net2 && this->net3 == ip.net3 && this->host == ip.host;
}

bool IP4::operator>=(const IP4& ip) const { return (*this) == ip || (*this) > ip; }

bool IP4::operator<=(const IP4& ip) const { return (*this) == ip || (*this) < ip; }

string IP4::toString() const {
    stringstream ss;
    ss << net1 << ".";
    ss << net2 << ".";
    ss << net3 << ".";
    ss << host;
    return ss.str();
}

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