#include "MIMO.h"
#include <iostream>

template<typename T>
void MIMO::multiUserMIMO(AccessPoint<T>& ap) {
    ap.sendBroadcast();
    ap.receiveChannelStateInfo();
    ap.communicate();
}

// Explicit template instantiation
template void MIMO::multiUserMIMO<int>(AccessPoint<int>& ap);
