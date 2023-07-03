#ifndef Zone_h
#define Zone_h

#include <Arduino.h> // Include necessary Arduino libraries

class Zone {
public:
    Zone(int, int);
    int on() const;
    int off() const;
    String pins() const;

private:
    int onPin_;
    int offPin_;
};

#endif