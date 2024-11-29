#ifndef OFDMACHANNELALLOCATOR_H
#define OFDMACHANNELALLOCATOR_H

#include <vector>
#include <random>
#include "User.h"

// Template-based Channel Allocation Strategy
template <typename UserType>
class OFDMAChannelAllocator {
private:
    const int _totalChannelWidth = 20; // MHz
    std::vector<SubChannelSize> _subChannelConfig;
    
    std::random_device _rd;
    std::mt19937 _gen;

public:
    // Constructor with flexible subchannel configuration
    OFDMAChannelAllocator() : _gen(_rd()) {
        _subChannelConfig = {
            SubChannelSize::TWO_MHZ,
            SubChannelSize::FOUR_MHZ,
            SubChannelSize::TEN_MHZ
        };
    }

    // Intelligent round-robin channel allocation
    std::vector<UserType> allocateChannels(std::vector<UserType>& users) {
        std::vector<UserType> allocatedUsers;
        size_t userCount = users.size();
        
        for (size_t i = 0; i < userCount; ++i) {
            // Rotate through sub-channel sizes for more dynamic allocation
            SubChannelSize allocatedSize = _subChannelConfig[i % _subChannelConfig.size()];
            
            // Move the user to avoid copying
            users[i].allocateSubChannel(allocatedSize);
            allocatedUsers.push_back(std::move(users[i]));
        }

        return allocatedUsers;
    }
};

#endif // OFDMACHANNELALLOCATOR_H
