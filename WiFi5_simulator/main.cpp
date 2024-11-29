#include "AccessPoint.h"
#include "MIMO.h"
#include <iostream>
#include <exception>

int main() {
    try {
        int numUsers;
        std::cout << "Enter the number of users: ";
        std::cin >> numUsers;

        if (numUsers <= 0) {
            throw std::invalid_argument("Number of users must be greater than zero");
        }

        AccessPoint<int> ap(numUsers);

        // Example execution loop
        for (int i = 0; i < 10; ++i) {
            MIMO::multiUserMIMO(ap);
        }

        ap.computeMetrics();

        std::cout << "Simulation complete." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
