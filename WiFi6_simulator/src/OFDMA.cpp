#include "../include/OFDMA.h"  // Include OFDMA header

// These definitions should be moved to the header file, as shown above
OFDMAChannelAllocator<UserType>::OFDMAChannelAllocator() {
    _subChannelConfig = {SubChannelSize::TWO_MHZ, SubChannelSize::FOUR_MHZ, SubChannelSize::TEN_MHZ};
}

void OFDMAChannelAllocator<UserType>::allocateChannels(std::vector<UserType>& users) {
    for (size_t i = 0; i < users.size(); ++i) {
        SubChannelSize size = _subChannelConfig[i % _subChannelConfig.size()];
        users[i].allocateSubChannel(size);
    }
}
