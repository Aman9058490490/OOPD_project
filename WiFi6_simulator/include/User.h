#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <numeric>
#include <iomanip>


#include "SubChannelSize.h"  // Include the SubChannelSize enum

class WiFi6User {
private:
    std::string _userId;
    SubChannelSize _allocatedSubChannel;
    double _baseDataRate; // Mbps
    std::vector<double> _throughputHistory;
    std::vector<double> _latencyHistory;

    static std::mt19937& getSharedGenerator();
    static std::uniform_real_distribution<>& getSharedDistribution();

public:
    WiFi6User(const std::string& userId, double baseDataRate = 100.0);
    void allocateSubChannel(SubChannelSize subChannel);
    double calculateEffectiveBandwidth();
    double transmit(double time = 5.0, double congestion = 1.0);
    double getAverageThroughput() const;
    double getMaxLatency() const;
    double getAverageLatency() const;
    const std::string& getUserId() const;
};

#endif // USER_H
