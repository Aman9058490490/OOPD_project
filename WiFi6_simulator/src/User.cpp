#include "../include/User.h"

std::mt19937& WiFi6User::getSharedGenerator() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

std::uniform_real_distribution<>& WiFi6User::getSharedDistribution() {
    static std::uniform_real_distribution<> dist(0.8, 1.2);
    return dist;
}

WiFi6User::WiFi6User(const std::string& userId, double baseDataRate)
    : _userId(userId), _allocatedSubChannel(SubChannelSize::TWO_MHZ), _baseDataRate(baseDataRate) {}

void WiFi6User::allocateSubChannel(SubChannelSize subChannel) {
    _allocatedSubChannel = subChannel;
}

double WiFi6User::calculateEffectiveBandwidth() {
    double multiplier = 1.0;
    switch (_allocatedSubChannel) {
        case SubChannelSize::TWO_MHZ: multiplier = 1.0; break;
        case SubChannelSize::FOUR_MHZ: multiplier = 2.0; break;
        case SubChannelSize::TEN_MHZ: multiplier = 5.0; break;
    }
    return _baseDataRate * multiplier * getSharedDistribution()(getSharedGenerator());
}

double WiFi6User::transmit(double time, double congestion) {
    double bandwidth = calculateEffectiveBandwidth() / congestion;
    double transmittedData = bandwidth * time;
    double latency = (1.0 / bandwidth) * 1000 * congestion;

    _throughputHistory.push_back(transmittedData);
    _latencyHistory.push_back(latency);

    return transmittedData;
}

double WiFi6User::getAverageThroughput() const {
    if (_throughputHistory.empty()) return 0.0;
    return std::accumulate(_throughputHistory.begin(), _throughputHistory.end(), 0.0) / _throughputHistory.size();
}

double WiFi6User::getMaxLatency() const {
    return _latencyHistory.empty() ? 0.0 : *std::max_element(_latencyHistory.begin(), _latencyHistory.end());
}

double WiFi6User::getAverageLatency() const {
    if (_latencyHistory.empty()) return 0.0;
    return std::accumulate(_latencyHistory.begin(), _latencyHistory.end(), 0.0) / _latencyHistory.size();
}

const std::string& WiFi6User::getUserId() const {
    return _userId;
}
