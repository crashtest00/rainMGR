#ifndef ZoneTimings_h
#define ZoneTimings_h

#include "Zone.h"
#include <Arduino.h>

class ZoneTimings {
public:
    ZoneTimings(String, int);
    void runZones();    

private:
    String host;
    int port;
    String getTimings();
    std::array<Zone, 4> zones; // This needs set to the max number of zones
    void runIrrigation(int, int, unsigned int);
};

#endif