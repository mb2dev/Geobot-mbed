#include "mbed.h"
#include "Servo.h"
#include "Wheel.h"
#include "Robot.hpp"

#define FULL_SPEED 1.0f
#define MID_SPEED 0.6f
#define LOW_SPEED 0.2f
#define SERVO_INCREMENT 0.01f

Servo myservo(D15);
Servo myservo2(D14);
Serial pc(SERIAL_TX, SERIAL_RX);    // tx, rx
DigitalOut led1(LED1);
DigitalOut led2(LED2);
char err;
char command[15]="";
char previousCmd[15]="";
char *msg[] = {"STOP", "MOVE_FORWARD", "MOVE_BACKWARD", "MOVE_LEFT", "MOVE_RIGHT", "MOVE_AUTO"};
char *camControl[] =  {"MOVECAM_STOP","MOVECAM_UP", "MOVECAM_DOWN","MOVECAM_LEFT","MOVECAM_RIGHT"};
int cmd=0;
int cptB = 0;

Wheel* rightWheel = new Wheel(D11,D10, 1);
Wheel* leftWheel = new Wheel(D3,D2,1);
Robot* geobot = new Robot(leftWheel, rightWheel);

void readSerial(){
    if(pc.readable()){
        command[cptB] = pc.getc();
        if(command[cptB] == '$'){
             memset(command, 0, sizeof command);
             cptB = 0;
        }else{
             pc.putc(command[cptB]);
             cptB++;
        }

    }
}//readSerial

void init(){
    for(float p = 0; p < 1.0f; p += 0.1f) {
        myservo = p;
        wait(0.2);
    }
    for(float p = 0; p < 1.0f; p += 0.1f) {
        myservo2 = p;
        wait(0.2);
    }
    myservo = 0.5;
    myservo2 = 0.5;

    pc.baud(9600);
    pc.format(8, Serial::None, 1);
    led1 = 1;
}

int main(void)
{
    init();
    while(1) {
        
        readSerial();
        
        /******************* control robot *******************/
        
        if(strcmp(msg[0], command) == 0){
            led1 = 1;
            geobot->brake();
        }
        else if(strcmp(msg[1], command) == 0){
            led1 = 0;
            geobot->forward(MID_SPEED);
        }
        else if(strcmp(msg[2], command) == 0){
            geobot->backward(MID_SPEED);
        }
        else if(strcmp(msg[3], command) == 0){
            geobot->left();
        }
        else if(strcmp(msg[4], command) == 0){
            geobot->right();
        }
        else if(strcmp(msg[5], command) == 0){
            geobot->automove();
        }
        
        /******************* control cam *******************/
        if(strcmp(camControl[0], command) == 0){
            // MOVECAM STOP
            //memset(command, 0, sizeof command);
            continue;
        }
        
        if(strcmp(camControl[1], command) == 0){
            // UP
            myservo2 = myservo2 - SERVO_INCREMENT;
            wait(0.1);
        }else if(strcmp(camControl[2], command) == 0){
            // DOWN
            if( myservo2 < 1.0f ){
                float value = myservo2;
                myservo2 = value + SERVO_INCREMENT;
                wait(0.1);
            }
        }else if(strcmp(camControl[3], command) == 0){
            // LEFT
            if(myservo < 1.0f) {
                float value = myservo;
                myservo = value + SERVO_INCREMENT;
                wait(0.1);
            }
        }else if(strcmp(camControl[4], command) == 0){
            // RIGHT
            myservo = myservo - SERVO_INCREMENT;
            wait(0.1);
        }
        strcpy (previousCmd, command);
    }//while
}//main