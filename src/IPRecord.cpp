#include "IPRecord.hpp"

void IPRecord::registerAccess(bool success) {
    totalAccesses++;
    if (success)
        successfulAccesses++;
}

bool IPRecord::operator<(const IPRecord& other) const { return ip < other.ip; }

bool IPRecord::operator>(const IPRecord& other) const { return ip > other.ip; }

bool IPRecord::operator==(const IPRecord& other) const { return ip == other.ip; }

bool IPRecord::operator!=(const IPRecord& other) const { return ip != other.ip; }

bool IPRecord::operator<=(const IPRecord& other) const { return ip <= other.ip; }

bool IPRecord::operator>=(const IPRecord& other) const { return ip >= other.ip; }