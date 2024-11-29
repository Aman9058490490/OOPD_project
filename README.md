# OOPD_project
#Project Overview:
 This project aims to design a simple WiFi simulator that leverages object-oriented features such 
 as inheritance, data abstraction, data hiding, and polymorphism. The simulator models different 
 types of WiFi communication (WiFi 4, WiFi 5, WiFi 6) to analyze throughput, average latency, and 
 maximum latency.

#Project Details:
# WiFi 4 Communication:
  WiFi 4 communication involves a single access point and a set of users. The transmission 
  process includes channel sniffing and data packet transmission if the channel is free. If the 
  channel is not free, the transmission is deferred by a random unit of time (subject to a 
  maximum backoff time), and the process repeats.
  I.Simulation Tasks:
    1.Simulate the transmission process.
    2.Measure the throughput, average latency, and maximum latency for:
      a.1 user and 1 AP
      b.10 users and 1 AP
      c.100 users and 1 AP
  II.Assumptions:
     Total bandwidth: 20 MHz
     Modulation: 256-QAM
     Coding rate: 5/6
     Packet size: 1 KB
     Ignore DIFS, CIFS, and guard intervals.

# WiFi 5 Communication:
  WiFi 5 introduces multi-user MIMO communication, enabling parallel transmissions.

Simulation Tasks:
Parallel communication occurs only after:
   a.Sending a broadcast packet from the access point.
   b.Sequentially sending channel state information from each user (200 bytes per packet).
   c.Users communicate in parallel for 15 ms. The process then repeats.
   d.Measure throughput, average latency, and maximum latency with round-robin scheduling.

# Wifi 6 Communication:
  WiFi 6 allows parallel communication using OFDMA. The 20 MHz channel is subdivided into 
  units of 2 MHz, 4 MHz, or 10 MHz.

Simulation Tasks:
   a.Utilize sub-channels in parallel for 5 ms.
   b.Reallocate channels every 5 ms.
   c.Measure throughput, average latency, and maximum latency with round-robin scheduling.
  
