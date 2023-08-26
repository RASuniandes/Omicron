#ifndef STARTER_H
#define STARTER_H

#include <Arduino.h>

class Starter {
private:
    int pinStart;
    int pinStop;

public:
    Starter(int pinStartNumber, int pinStopNumber);
    int getStart();
    int getStop();
};

#endif