// constants.hpp
#pragma once

namespace wifi_sim {
    namespace constants {
        constexpr int CHANNEL_BANDWIDTH = 50;  // MHz
        constexpr double BASE_RATE = 35.0;     // Mbps
        constexpr int PACKET_SIZE = 2048;      // 1 KB
        constexpr int MAX_BACKOFF_STAGE = 3;
        constexpr int SLOT_TIME = 11;           // microseconds
    }
}