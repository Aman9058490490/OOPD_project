#ifndef MIMO_H
#define MIMO_H

#include "AccessPoint.h"

class MIMO {
public:
    template<typename T>
    static void multiUserMIMO(AccessPoint<T>& ap);
};

#endif // MIMO_H
