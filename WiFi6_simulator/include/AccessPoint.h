#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "User.h"
#include "OFDMA.h"

class WiFi6AccessPoint {
private:
    std::vector<WiFi6User> _users;
    OFDMAChannelAllocator<WiFi6User> _channelAllocator;

public:
    void addUser(const WiFi6User& user);
    void simulateOFDMACommunication(int rounds = 10);
    void printPerformanceMetrics();
};

#endif // ACCESSPOINT_H
