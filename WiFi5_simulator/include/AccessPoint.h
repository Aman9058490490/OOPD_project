#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <vector>
#include "User.h"
#include "Packet.h"
#include <chrono>

class BaseStation {
public:
    virtual void sendBroadcast() = 0;
    virtual void receiveChannelStateInfo() = 0;
    virtual void communicate() = 0;
    virtual void computeMetrics() = 0;
};

template<typename T>
class AccessPoint : public BaseStation {
public:
    AccessPoint(int numUsers);
    void sendBroadcast() override;
    void receiveChannelStateInfo() override;
    void communicate() override;
    void computeMetrics() override;

private:
    std::vector<User> users;
    std::vector<Packet> packets;
    int totalBytesTransmitted;
    std::vector<double> latencies;
    double totalTime;  // in milliseconds

    double calculateThroughput();
    double calculateAverageLatency();
    double calculateMaxLatency();
};

#endif // ACCESSPOINT_H
