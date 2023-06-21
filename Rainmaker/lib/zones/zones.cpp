#include "zones.h"
#include <cmath>

IrrigationEvent::IrrigationEvent(float target, float freq) {
    this->target = target;
    this->freq = freq;
    this->event = this->target / this->freq;

    this->zone1 = round(this->event / this->rate1);
    this->zone2 = round(this->event / this->rate2);
    this->zone3 = round(this->event / this->rate3);

};