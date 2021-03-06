#include "mbed.h"
#ifndef WHEEL_H
#define WHEEL_H

class Wheel
{
    protected:
        PwmOut motorSpeed;
        DigitalOut motorRotation;
        int senseOfRotation;
    public:   
        Wheel(PinName mSpeed,PinName mRotation,int sor);
        void forward(float speed);
        void backward(float spead);
        void brake();      
};
#endif