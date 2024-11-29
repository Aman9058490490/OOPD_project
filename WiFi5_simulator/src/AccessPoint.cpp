#include "../include/AccessPoint.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <stdexcept>

template<typename T>
AccessPoint<T>::AccessPoint(int numUsers) : totalBytesTransmitted(0), totalTime(0) {
    if (numUsers <= 0) {
        throw std::invalid_argument("Number of users must be greater than zero");
    }
    // Initialize the specified number of users
    for (int i = 0; i < numUsers; ++i) {
        users.push_back(User());
    }
}

template<typename T>
void AccessPoint<T>::sendBroadcast() {
    std::cout << "Broadcast packet sent to users." << std::endl;
}

template<typename T>
void AccessPoint<T>::receiveChannelStateInfo() {
    std::cout << "Received channel state information from users." << std::endl;
}

template<typename T>
void AccessPoint<T>::communicate() {
    std::cout << "Users are communicating in parallel." << std::endl;

    auto startTime = std::chrono::high_resolution_clock::now();
    // Simulate data transmission
    for (auto& user : users) {
        user.receiveData();
        totalBytesTransmitted += 200; // Assume 200 bytes per user
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = endTime - startTime;

    // Scale latency based on number of users
    double scaledLatency = duration.count() * users.size();
    latencies.push_back(scaledLatency);
    totalTime += scaledLatency;
}

template<typename T>
double AccessPoint<T>::calculateThroughput() {
    // Throughput in Mbps
    double totalBitsTransmitted = totalBytesTransmitted * 8; // Convert bytes to bits
    double throughputInMbps = (totalBitsTransmitted / (totalTime / 1000.0)) / 1e6; // Mbps
    return throughputInMbps;
}

template<typename T>
double AccessPoint<T>::calculateAverageLatency() {
    return std::accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
}

template<typename T>
double AccessPoint<T>::calculateMaxLatency() {
    return *std::max_element(latencies.begin(), latencies.end());
}

template<typename T>
void AccessPoint<T>::computeMetrics() {
    std::cout << "Total Throughput: " << calculateThroughput() << " Mbps" << std::endl;
    std::cout << "Average Latency: " << calculateAverageLatency() << " ms" << std::endl;
    std::cout << "Maximum Latency: " << calculateMaxLatency() << " ms" << std::endl;
}

// Explicit template instantiation
template class AccessPoint<int>;  // You can instantiate with specific types as needed
