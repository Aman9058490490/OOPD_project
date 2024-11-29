// access_point.hpp
#pragma once
#include <iostream>
#include <cmath>
#include "network_device.h"
#include "constants.h"
#include "exceptions.h"

namespace wifi_sim {
    template <typename T>
    class AccessPoint : public NetworkDevice<T> {
    private:
        using NetworkDevice<T>::userCount;
        using NetworkDevice<T>::transmissions;
        using NetworkDevice<T>::totalTransmissionTime;
        using NetworkDevice<T>::backoffCalc;

    public:
        AccessPoint(T numberOfUsers) : NetworkDevice<T>(numberOfUsers) {
            if (numberOfUsers <= 0) {
                this->userCount = 1; // default to 1 user if input is invalid
            }
        }

        void simulateTransmission() override {
            this->transmissions.clear();
            this->backoffCalc->reset();

            if (this->userCount == 0) {
                this->userCount = 1; // default to 1 user if no users are set
            }

            double effectiveBandwidth = constants::BASE_RATE / sqrt(this->userCount);

            for (T i = 0; i < this->userCount; ++i) {
                double transmissionTime = (constants::PACKET_SIZE * 8.0) / (effectiveBandwidth * 1000.0);

                double backoffTime = this->backoffCalc->calculateBackoffTime(this->userCount);

                if (backoffTime < 0) {
                    backoffTime = 0; // default to 0 if backoff time is negative
                }

                PacketTransmission<T> pkt;
                pkt.senderID = i + 1;
                pkt.transmissionTime = transmissionTime;
                pkt.backoffTime = backoffTime;
                pkt.totalTime = transmissionTime + backoffTime;

                this->transmissions.push_back(pkt);
                this->totalTransmissionTime += pkt.totalTime;
            }
        }

        void printResults() const override {
            if (this->transmissions.empty()) {
                std::cout << "No simulation results to print." << std::endl;
                return;
            }

            double throughput = (this->userCount * constants::PACKET_SIZE * 8.0) / (this->totalTransmissionTime / 1000.0) / 1000000.0;

            double totalLatency = 0.0;
            double maxLatency = 0.0;

            for (const auto& trans : this->transmissions) {
                totalLatency += trans.totalTime;
                maxLatency = std::max(maxLatency, trans.totalTime);
            }

            double averageLatency = totalLatency / this->userCount;

            std::cout << "\nSimulation Results for " << this->userCount << " Users\n";
            std::cout << "----------------------------------------\n";
            std::cout << "Total Transmission Time: " << this->totalTransmissionTime << " ms\n";
            std::cout << "Throughput: " << throughput << " Mbps\n";
            std::cout << "Average Latency: " << averageLatency << " ms\n";
            std::cout << "Maximum Latency: " << maxLatency << " ms\n";

            std::cout << "\nDetailed Backoff Times:\n";
            for (const auto& trans : this->transmissions) {
                std::cout << "Sender " << trans.senderID << ": Backoff = " << trans.backoffTime << " ms\n";
            }
            std::cout << std::endl;
        }
    };
}