#ifndef USER_H
#define USER_H

#include "FrequencyChannel.h"

class User {
public:
    User();
    void sendChannelState();
    void receiveData();

private:
    FrequencyChannel channel;
};

#endif // USER_H
