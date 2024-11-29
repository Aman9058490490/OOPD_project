// simulator.hpp
#pragma once
#include <memory>
#include <iostream>
#include <limits>
#include "Access_point.h"
#include "exceptions.h"

namespace wifi_sim {
    class WiFiSimulator {
    private:
        template <typename T>
        void simulateWiFi4(T numberOfUsers) {
            try {
                AccessPoint<T> ap(numberOfUsers);
                ap.simulateTransmission();
                ap.printResults();
            } catch (const WiFiSimException& ex) {
                std::cerr << "Simulation Error: " << ex.what() << std::endl;
            } catch (const std::exception& ex) {
                std::cerr << "Unexpected Error: " << ex.what() << std::endl;
            }
        }

    public:
        void run() {
            while (true) {
                try {
                    std::cout << "\nWiFi 4 Simulation Menu:\n"
                              << "1. Simulate with 1 User\n"
                              << "2. Simulate with 10 Users\n"
                              << "3. Simulate with 100 Users\n"
                              << "4. Custom Number of Users\n"
                              << "5. Exit\n"
                              << "Enter your choice: ";

                    int choice;
                    if (!(std::cin >> choice)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw InvalidInputException("Invalid input! Please enter a number.");
                    }

                    if (choice == 5) {
                        std::cout << "Exiting WiFi Simulator...\n";
                        break;
                    }

                    switch (choice) {
                        case 1: simulateWiFi4(1); break;
                        case 2: simulateWiFi4(10); break;
                        case 3: simulateWiFi4(100); break;
                        case 4: {
                            std::cout << "Enter number of users: ";
                            int customUsers;
                            if (!(std::cin >> customUsers)) {
                                throw InvalidInputException("Invalid user count input!");
                            }
                            simulateWiFi4(customUsers);
                            break;
                        }
                        default:
                            throw InvalidInputException("Invalid menu choice!");
                    }
                } catch (const InvalidInputException& ex) {
                    std::cerr << "Input Error: " << ex.what() << std::endl;
                } catch (const std::exception& ex) {
                    std::cerr << "Error: " << ex.what() << std::endl;
                }
            }
        }
    };
}