#ifndef DOBSTACLE_HPP
#define DOBSTACLE_HPP

#include "mbed.h"

extern DigitalIn ir1(D5); // sur le nucleo board, la pin femelle envoie du courant (pas exploitable comme sortie!!), mais la pin male est OK
extern DigitalIn ir2(D6);
extern DigitalIn ir3(D7);

class ObstacleDetector {
private:
public:
    ObstacleDetector() {};
    //t_DIRECTION isAnyObstacle();
    bool obstacle_right(){
        return ir3.read() == 0;
    }
    bool obstacle_center(){
        return ir2.read() == 0;
    }
    bool obstacle_left(){
        // detection => 0
        return ir1.read() == 0;
    }
    void printValues(){
        //sprintf(Display::buffer1, "IR: %d|%d|%d", ir1.read(), ir2.read(), ir3.read());
        //Display::display(Display::buffer1, "-------------");
    }
    void test(){
        while(1){
            this->printValues();
        }
    }
};

#endif //DOBSTACLE_HPP