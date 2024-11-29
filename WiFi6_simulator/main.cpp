#include "include/AccessPoint.h"  // Include WiFi6AccessPoint class
#include "include/User.h"         // Include WiFi6User class
#include "include/OFDMA.h"        // Include OFDMAChannelAllocator class

int main() {
    WiFi6AccessPoint wifi6AP;  // Create an instance of WiFi6AccessPoint

    // Add users to the access point
    wifi6AP.addUser(WiFi6User("User1", 50.0));
    wifi6AP.addUser(WiFi6User("User2", 100.0));
    wifi6AP.addUser(WiFi6User("User3", 200.0));
    wifi6AP.addUser(WiFi6User("User4", 75.0));

    // Simulate OFDMA communication (this calls the method in WiFi6AccessPoint)
    wifi6AP.simulateOFDMACommunication(10);

    return 0;
}
