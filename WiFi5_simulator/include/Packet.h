#ifndef PACKET_H
#define PACKET_H

class Packet {
public:
    Packet(int size);
    int getSize() const;

private:
    int size;
};

#endif // PACKET_H
