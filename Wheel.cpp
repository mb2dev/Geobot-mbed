#include "mbed.h"
#include "Wheel.h"

Wheel::Wheel(PinName mSpeed,PinName mRotation, int sor) : motorSpeed(mSpeed), motorRotation(mRotation){
     motorSpeed = 0.0;
     motorRotation = senseOfRotation;
     senseOfRotation = sor;
};

void Wheel::brake(){
    motorSpeed = 0.0;
    motorRotation = 0.0;
}

void Wheel::forward(float speed){
    motorSpeed = speed;
    motorRotation = senseOfRotation;
}

void Wheel::backward(float speed){
    motorSpeed = speed;
    if(senseOfRotation == 0) motorRotation = 1;
    if(senseOfRotation == 1) motorRotation = 0;
}