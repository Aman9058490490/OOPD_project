#include "../include/AccessPoint.h"

void WiFi6AccessPoint::addUser(const WiFi6User& user) {
    _users.push_back(user);
}

void WiFi6AccessPoint::simulateOFDMACommunication(int rounds) {
    std::cout << "OFDMA Communication Simulation\n";
    std::cout << "----------------------------\n";

    for (int round = 1; round <= rounds; ++round) {
        double congestionFactor = 1.0 + 0.1 * (_users.size() - 1);

        std::cout << "Round " << round << ":\n";
        _channelAllocator.allocateChannels(_users);

        for (auto& user : _users) {
            double transmittedData = user.transmit(5.0, congestionFactor);
            std::cout << "User " << user.getUserId()
                      << " - Transmitted: " << std::fixed << std::setprecision(2)
                      << transmittedData << " Mbps, Latency: " 
                      << user.getAverageLatency() << " ms\n";
        }
    }

    printPerformanceMetrics();
}

void WiFi6AccessPoint::printPerformanceMetrics() {
    std::cout << "\nOverall Performance Metrics:\n";
    for (const auto& user : _users) {
        std::cout << "User " << user.getUserId() << ":\n"
                  << "  Avg Throughput: " << std::fixed << std::setprecision(2)
                  << user.getAverageThroughput() << " Mbps\n"
                  << "  Avg Latency: " << user.getAverageLatency() << " ms\n"
                  << "  Max Latency: " << user.getMaxLatency() << " ms\n\n";
    }
}
