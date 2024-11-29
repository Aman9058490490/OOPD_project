#pragma once
#include <cmath>
#include <algorithm>
#include <random>
#include "constants.h"

namespace wifi_sim {
    class IBackoffCalculator {
    public:
        virtual double calculateBackoffTime(int userCount) = 0;
        virtual void reset() = 0;
        virtual ~IBackoffCalculator() = default;
    };

    template <typename T>
    class ExponentialBackoffCalculator : public IBackoffCalculator {
    private:
        int currentStage;
        int collisionCount;
        std::random_device rd;
        std::mt19937 gen;

        // Function to calculate backoff slots based on current stage
        int calculateBackoffSlots(int stage) {
            int maxBackoffStage = std::min(stage, constants::MAX_BACKOFF_STAGE);
            int maxBackoffSlots = (1 << maxBackoffStage) - 1;
            std::uniform_int_distribution<> dis(0, maxBackoffSlots);
            return dis(gen);
        }

    public:
        ExponentialBackoffCalculator() : currentStage(0), collisionCount(0), gen(rd()) {}

        double calculateBackoffTime(int userCount) override {
            try {
                if (userCount <= 0) {
                    throw std::invalid_argument("User count must be greater than zero.");
                }

                int backoffSlots = calculateBackoffSlots(currentStage);
                double backoffTime = backoffSlots * constants::SLOT_TIME * (1.0 + std::log(userCount));

                currentStage = std::min(currentStage + 1, constants::MAX_BACKOFF_STAGE);
                collisionCount++;

                return backoffTime;  // Return time in seconds
            } catch (const std::exception& e) {
                // Handle the exception
                return 0.0;
            }
        }

        void reset() override {
            currentStage = 0;
            collisionCount = 0;
        }
    };
}
