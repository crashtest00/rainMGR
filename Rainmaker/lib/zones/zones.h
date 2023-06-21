#ifndef zones_h
#define zones_h

class IrrigationEvent {
private:
    float rate1 = 19.05 / 60;  // Backyard
    float rate2 = 7.143 / 60;  // South side yard
    float rate3 = 2.381 / 60;  // Front yard

public:
    float target;
    float freq;
    float event;
    int zone1;
    int zone2;
    int zone3;

    IrrigationEvent(float target, float freq);
};

#endif
