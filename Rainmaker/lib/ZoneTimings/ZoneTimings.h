#ifndef ZoneTimings_h
#define ZoneTimings_h

#include "Zone.h"
#include <Arduino.h>

class ZoneTimings {
public:
    ZoneTimings();
    void runZones();    

private:
    String getTimings();
    std::array<Zone, 4> zones; // This needs set to the max number of zones
    void runIrrigation(int, int, unsigned int);
};

#endif