#ifndef NextRun_h
#define NextRun_h

#include <Arduino.h>

class NextRun {
public:
    NextRun(String, int);
    int delayUntil();

private:
    String host;
    int port;

};

#endif