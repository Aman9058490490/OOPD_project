#ifndef OFDMA_H
#define OFDMA_H

#include <vector>
#include "User.h"  // Ensure this includes the WiFi6User class

#include "SubChannelSize.h"  // Include the SubChannelSize enum

// Template class for OFDMAChannelAllocator
template <typename UserType>
class OFDMAChannelAllocator {
private:
    std::vector<SubChannelSize> _subChannelConfig;

public:
    OFDMAChannelAllocator() {  // Constructor
        _subChannelConfig = {SubChannelSize::TWO_MHZ, SubChannelSize::FOUR_MHZ, SubChannelSize::TEN_MHZ};
    }

    // Method to allocate channels to users
    void allocateChannels(std::vector<UserType>& users) {
        for (size_t i = 0; i < users.size(); ++i) {
            SubChannelSize size = _subChannelConfig[i % _subChannelConfig.size()];
            users[i].allocateSubChannel(size);
        }
    }
};

#endif // OFDMA_H
