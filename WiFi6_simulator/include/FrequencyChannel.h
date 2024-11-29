#ifndef FREQUENCYCHANNEL_H
#define FREQUENCYCHANNEL_H

class FrequencyChannel {
public:
    FrequencyChannel(double bandwidth);
    double getBandwidth() const;

private:
    double bandwidth;
};

#endif // FREQUENCYCHANNEL_H
