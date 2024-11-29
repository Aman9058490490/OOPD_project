#include "../include/FrequencyChannel.h"

FrequencyChannel::FrequencyChannel(double bandwidth) : bandwidth(bandwidth) {}

double FrequencyChannel::getBandwidth() const {
    return bandwidth;
}
