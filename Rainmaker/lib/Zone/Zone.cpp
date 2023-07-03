#include "Zone.h"
#include <Arduino.h>


Zone::Zone(int onPin, int offPin) : 
    onPin_(onPin), offPin_(offPin) {}

int Zone::on() const {
    return onPin_;
}

int Zone::off() const {
    return offPin_;
}

String Zone::pins() const {
    return String(onPin_) + "," + String(offPin_);
}
