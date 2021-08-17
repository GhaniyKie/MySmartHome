#include "FullDate.h"

class DeviceTimer {

public:

    int onHour, onMinute;
    int offHour, offMinute;
    char relay;

    void setTimeOn(int, int);
    void setTimeOff(int, int);

    void timerOn(char relay) {
        digitalWrite(relay, LOW);
    }
    
    void timerOff(char relay) {
        digitalWrite(relay, HIGH);
    }
};

void DeviceTimer::setTimeOn(int h, int m) {
    onHour = h;
    onMinute = m;
}

void DeviceTimer::setTimeOff(int h, int m) {
    offHour = h;
    offMinute = m;
}
