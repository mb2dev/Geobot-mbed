#include "mbed.h"
#include "Wheel.h"
#include "ObstacleDetector.hpp"

#ifndef ROBOT_H
#define ROBOT_H

#define FULL_SPEED 1.0f
#define MID_SPEED 0.8f
#define LOW_SPEED 0.5f

class Robot
{
    protected:
        ObstacleDetector ol;
        Wheel* leftWheel;
        Wheel* rightWheel;
    public:
        Robot(Wheel* wl, Wheel* wr) : leftWheel(wl), rightWheel(wr) {};
        void forward(float speed = MID_SPEED){
            leftWheel->forward(speed);
            rightWheel->forward(speed);
        }
        void backward(float speed = MID_SPEED){
            leftWheel->backward(speed);
            rightWheel->backward(speed);
        }
        void left(){
            leftWheel->forward(LOW_SPEED);
            rightWheel->forward(MID_SPEED);
        }
        void right(){
            leftWheel->forward(MID_SPEED);
            rightWheel->forward(LOW_SPEED);
        }
        void brake(){
            leftWheel->brake();
            rightWheel->brake();
        }
        void automove(){
            if(ol.obstacle_center()){
                backward();
            }else if(ol.obstacle_left()){
                right();
            }else if(ol.obstacle_right()){
                left();
            }else{
                forward();
            }
        }
};

#endif
