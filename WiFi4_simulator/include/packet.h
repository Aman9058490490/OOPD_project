// packet.hpp
#pragma once

namespace wifi_sim {
    template <typename T>
    struct PacketTransmission {
        T senderID;
        double transmissionTime;
        double backoffTime;
        double totalTime;

        PacketTransmission() : senderID(0), transmissionTime(0), backoffTime(0), totalTime(0) {}
    };
}