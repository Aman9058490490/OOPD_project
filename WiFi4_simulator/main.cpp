#include <cstdlib>
#include <ctime>
#include "simulator.h"

int main() {
    std::srand(std::time(nullptr));
    
    wifi_sim::WiFiSimulator simulator;
    simulator.run();
    
    return 0;
}