#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <cmath>
#include <stdexcept>

using namespace std;

const int CHANNEL_BANDWIDTH =50 ;
const double BASE_RATE = 35.0;
const int PACKET_SIZE = 2048;
const int MAX_BACKOFF_STAGE = 3;
const int SLOT_TIME = 11;

class InvalidInputException : public std::exception {
public:
    virtual const char* what() const noexcept {
        return "Invalid input!";
    }
};

class InvalidUserCountException : public InvalidInputException {
public:
    const char* what() const noexcept override {
        return "Invalid number of users! User count must be greater than 0.";
    }
};

template <typename T>
class BackoffCalculator {
private:
    int currentStage;
    int collisionCount;
    int calculateMaxBackoffSlots() const {
        return min(
            (1 << min(currentStage, MAX_BACKOFF_STAGE)) - 1,
            (1 << MAX_BACKOFF_STAGE) - 1
        );
    }
    int selectRandomSlot(int maxSlots) {
        return rand() % (maxSlots + 1);
    }

public:
    BackoffCalculator() : currentStage(0), collisionCount(0) {}
    double calculateBackoffTime(T userCount) {
        int maxBackoffSlots = calculateMaxBackoffSlots();
        int backoffSlots = selectRandomSlot(maxBackoffSlots);
        double backoffTime = backoffSlots * SLOT_TIME * (1.0 + log(userCount));
        currentStage++;
        collisionCount++;
        return backoffTime / 1000.0;
    }
    void reset() {
        currentStage = 0;
        collisionCount = 0;
    }
};

template <typename T>
struct PacketTransmission {
    T senderID;
    double transmissionTime;
    double backoffTime;
    double totalTime;
};

template <typename T>
class AccessPoint {
private:
    T userCount;
    vector<PacketTransmission<T>> transmissions;
    double totalTransmissionTime;
    BackoffCalculator<T> backoffCalc;

    double calculateEffectiveBandwidth() const {
        return BASE_RATE / sqrt(userCount);
    }

    double calculateTransmissionTime(double bandwidth) const {
        return (PACKET_SIZE * 8.0) / (bandwidth * 1000.0);
    }

public:
    AccessPoint(T numberOfUsers) : userCount(numberOfUsers), totalTransmissionTime(0.0) {
        if (userCount <= 0) {
            throw InvalidUserCountException();
        }
    }

    void simulateTransmission() {
        transmissions.clear();
        backoffCalc.reset();
        double effectiveBandwidth = calculateEffectiveBandwidth();

        for (T i = 0; i < userCount; ++i) {
            double transmissionTime = calculateTransmissionTime(effectiveBandwidth);
            double backoffTime = backoffCalc.calculateBackoffTime(userCount);

            PacketTransmission<T> pkt;
            pkt.senderID = i + 1;
            pkt.transmissionTime = transmissionTime;
            pkt.backoffTime = backoffTime > 0 ? backoffTime : 0;
            pkt.totalTime = transmissionTime + backoffTime;

            transmissions.push_back(pkt);
            totalTransmissionTime += pkt.totalTime;
        }
    }

    void printResults() {
        if (transmissions.empty()) {
            cout << "No simulation results to print." << endl;
            return;
        }

        double throughput = (userCount * PACKET_SIZE * 8.0) / (totalTransmissionTime / 1000.0) / 1000000.0;
        double totalLatency = 0.0;
        double maxLatency = 0.0;

        for (const auto& trans : transmissions) {
            totalLatency += trans.totalTime;
            maxLatency = max(maxLatency, trans.totalTime);
        }

        double averageLatency = totalLatency / userCount;

        cout << "Scenario: " << userCount << " Users" << endl;
        cout << "----------------------------" << endl;
        cout << "Total Transmission Time: " << totalTransmissionTime << " ms" << endl;
        cout << "Throughput: " << throughput << " Mbps" << endl;
        cout << "Total Packets: " << userCount << endl;
        cout << "Average Latency: " << averageLatency << " ms" << endl;
        cout << "Maximum Latency: " << maxLatency << " ms" << endl;
        
        cout << "\nBackoff Time Details:" << endl;
        for (const auto& trans : transmissions) {
            cout << "Sender " << trans.senderID 
                 << ": Backoff Time = " << trans.backoffTime << " ms" << endl;
        }
        cout << endl;
    }
};

template <typename T>
void simulateWiFi4(T numberOfUsers) {
    try {
        if (numberOfUsers <= 0) {
            throw InvalidUserCountException();
        }

        AccessPoint<T> ap(numberOfUsers);
        ap.simulateTransmission();
        ap.printResults();
    }
    catch (const InvalidUserCountException& ex) {
        cout << ex.what() << endl;
    }
}

void runWiFiSimulation() {
    int choice;
    while (true) {
        cout << "WiFi 4 Simulation Menu:" << endl;
        cout << "1. Simulate with 1 User" << endl;
        cout << "2. Simulate with 10 Users" << endl;
        cout << "3. Simulate with 100 Users" << endl;
        cout << "4. Custom Number of Users" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        switch (choice) {
            case 1: simulateWiFi4(1); break;
            case 2: simulateWiFi4(10); break;
            case 3: simulateWiFi4(100); break;
            case 4: {
                int customUsers;
                cout << "Enter number of users: ";
                cin >> customUsers;
                try {
                    if (customUsers <= 0) {
                        throw InvalidUserCountException();
                    }
                    simulateWiFi4(customUsers);
                } catch (const InvalidUserCountException& ex) {
                    cout << ex.what() << endl;
                }
                break;
            }
            case 5:
                cout << "Exiting WiFi Simulator..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    srand(time(NULL));
    runWiFiSimulation();
    return 0;
}
