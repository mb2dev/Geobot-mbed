#include "mbed.h"
#include "Servo.h"
#include "wheel.h"


Servo myservo(D15);
Servo myservo2(D14);
Serial pc(SERIAL_TX, SERIAL_RX);    // tx, rx
DigitalOut led1(LED1);
DigitalOut led2(LED2);
char err;
char command[15]="";
char *msg[] = {"STOP","MOVE_FORWARD", "MOVE_BACKWARD","MOVE_LEFT","MOVE_RIGHT"};
char *camControl[] =  {"STOPCAM","MOVECAM_UP", "MOVECAM_DOWN","MOVECAM_LEFT","MOVECAM_RIGHT"};
int cmd=0;
int cptB = 0;

Wheel* rightWheel = new Wheel(D11,D10, 1);
Wheel* leftWheel = new Wheel(D3,D2,1);


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
}


int main(void)
{
    
     for(float p=0; p<1.0; p += 0.1) {
        myservo = p;
        wait(0.2);
    }
    for(float p=0; p<1.0; p += 0.1) {
        myservo2 = p;
        wait(0.2);
    }
    myservo = 0.5;
    myservo2 = 0.5;
    pc.baud(9600); 
    pc.format(8, Serial::None, 1);
    led1 = 1;
    
    
    
    
     
   /*while (1) {
       // pc.putc('F');
        pc.printf("go");
        
        
        break;
        wait(1);
    }*/
    while(1) {
    readSerial();
    // control robot
    if(strcmp(msg[0], command)==0){
        led1 = 1;
        leftWheel->moveForward(0);
            rightWheel->moveForward(0);
    }
    else if(strcmp(msg[1], command)==0){
        led1 = 0;
        leftWheel->moveForward(0.5);
        rightWheel->moveForward(0.5);
    }
    else if(strcmp(msg[2], command)==0){
        leftWheel->backForward(0.5);
        rightWheel->backForward(0.5);
    }
    else if(strcmp(msg[3], command)==0){
        leftWheel->moveForward(0.5);
        rightWheel->moveForward(0);
    }
    else if(strcmp(msg[4], command)==0){
        leftWheel->moveForward(0);
        rightWheel->moveForward(0.5);
    }
    
    // control cam 
     if(strcmp(camControl[0], command)==0){ 
    }
     if(strcmp(camControl[1], command)==0){ 
      myservo2 = myservo2 - 0.0001;
     // wait(0.1);
      
    }
     if(strcmp(camControl[2], command)==0){ 
      myservo2 = myservo2+0.0001;
      // wait(0.1);
    }
     if(strcmp(camControl[3], command)==0){ 
     myservo =myservo + 0.0001;
      //wait(0.1);
    }
     if(strcmp(camControl[4], command)==0){ 
       myservo=myservo - 0.0001;
       // wait(0.1);
    }
}}



