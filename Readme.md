# WiFi Communication Simulation Project

## Project Overview
This project simulates the evolution of WiFi communication technologies from WiFi 4 to WiFi 6, demonstrating the progressive improvements in wireless communication protocols.

## Implemented WiFi Technologies
1. **WiFi 4 (802.11n)**: 
   - Single access point communication
   - CSMA/CA (Carrier Sense Multiple Access with Collision Avoidance)
   - Random backoff mechanism for channel access

2. **WiFi 5 (802.11ac)**: 
   - Multi-User MIMO (Multiple Input Multiple Output)
   - Parallel transmission after channel state information exchange

3. **WiFi 6 (802.11ax)**: 
   - OFDMA (Orthogonal Frequency Division Multiple Access)
   - Channel subdivision into 2 MHz, 4 MHz, and 10 MHz sub-channels
   - Parallel transmission across sub-channels

## Prerequisites
- C++ Compiler (G++ 11.0 or later recommended)
- Make utility
- Git (for version control)

## Build Instructions

### Compilation
```bash
# Debug Build
make debug

# Release Build
make release

# Clean Build Artifacts
make clean
```

### Running the Simulation
```bash
# Run Debug Version
./wifi_simulator_debug

# Run Optimized Version
./wifi_simulator_release
```

## Simulation Parameters
- Bandwidth: 20 MHz
- Modulation: 256-QAM
- Coding Rate: 5/6
- Packet Size: 1 KB

### Simulation Scenarios
1. 1 User, 1 Access Point
2. 10 Users, 1 Access Point
3. 100 Users, 1 Access Point

## Performance Metrics
For each scenario, the simulator calculates:
- Throughput (bytes/second)
- Average Latency (milliseconds)
- Maximum Latency (milliseconds)

## Code Structure
- `AccessPoint` class: Manages channel allocation and transmission
- `User` class: Represents individual network devices
- `SubChannel` class: Models channel subdivisions
- Separate simulation functions for each WiFi technology

## Error Handling
- Template-based error handling
- Exception management for edge cases

## Version Control
- Minimum 4 significant Git commits
- Detailed commit messages describing changes


## Known Limitations
- Simplified simulation model
- Ignores certain network overhead periods
- Theoretical performance modeling

## Future Enhancements
- More detailed channel modeling
- Advanced error simulation
- Support for additional WiFi standards

## Authors
[Aman Sharma]
[IIIT Delhi]
Monsoon 2024
