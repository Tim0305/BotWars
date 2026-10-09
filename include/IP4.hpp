#pragma once

#include <string>

using namespace std;

class IP4 {
private:
    int net1;
    int net2;
    int net3;
    int host;

public:
    IP4(int net1, int net2, int net3, int host) : net1(net1), net2(net2), net3(net3), host(host) {};
    bool operator>(const IP4& ip) const;
    bool operator<(const IP4& ip) const;
    bool operator==(const IP4& ip) const;
    bool operator>=(const IP4& ip) const;
    bool operator<=(const IP4& ip) const;
    string toString() const;
    static IP4 fromString(const string& strIp);
};