#ifndef NextRun_h
#define NextRun_h

#include <Arduino.h>

class NextRun {
public:
    NextRun();
    int delayUntil();

private:
    String getDelay();

};

#endif