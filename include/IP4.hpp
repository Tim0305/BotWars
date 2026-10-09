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
    string toString();
};