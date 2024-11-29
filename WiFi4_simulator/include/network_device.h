#pragma once
#include <vector>
#include <memory>
#include "packet.h"
#include "backoff_calculator.h"
#include "exceptions.h"  // Added this include

namespace wifi_sim {
    template <typename T>
    class NetworkDevice {
    protected:
        T userCount;
        std::vector<PacketTransmission<T>> transmissions;
        double totalTransmissionTime;
        std::unique_ptr<IBackoffCalculator> backoffCalc;

        // Validate the number of users
        void validateUserCount(T users) {
            if (users <= 0) {
                throw InvalidUserCountException();
            }
        }

        // Initialize backoff calculator
        void initializeBackoffCalculator() {
            backoffCalc = std::make_unique<ExponentialBackoffCalculator<T>>();
        }

        // Initialize network device with given user count
        void initializeDevice(T users) {
            userCount = users;
            totalTransmissionTime = 0.0;
            transmissions.clear();
            initializeBackoffCalculator();
        }

    public:
        explicit NetworkDevice(T users) {
            validateUserCount(users);
            initializeDevice(users);
        }

        virtual void simulateTransmission() = 0;
        virtual void printResults() const = 0;
        virtual ~NetworkDevice() = default;
    };
}
