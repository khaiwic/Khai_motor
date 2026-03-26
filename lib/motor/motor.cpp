#include "motor.h"

//motorA
#define ledcChannel 0
const int pwma = 1;
const int ina_1 = 2;
const int ina_2 = 3;
const int bemf_1 = 4;

//motorB
#define ledcChannel 1
const int pwmb = 5;
const int inb_1 = 6; 
const int inb_2 = 7; 
const int bemf_2 = 8;

//he thong
#define freq 20000
#define resolution 10

void initMotor(){  
    //MotorA
    pinMode(ina_1, OUTPUT);
    pinMode(ina_2, OUTPUT);
    ledcAttach(pwma, freq, resolution);
    
    //MotorB
    pinMode(inb_1, OUTPUT);
    pinMode(inb_2, OUTPUT);
    ledcAttach(pwmb, freq, resolution);
}
void go(control next, int speed){
        switch(next){
        case TOP:
            digitalWrite(ina_1, HIGH); digitalWrite(ina_2, LOW);
            digitalWrite(inb_1, HIGH); digitalWrite(inb_2, LOW);
            ledcWrite(pwma, speed);
            ledcWrite(pwmb, speed);
            break;
            
        case BACK:
            digitalWrite(ina_1, LOW); digitalWrite(ina_2, HIGH);
            digitalWrite(inb_1, LOW); digitalWrite(inb_2, HIGH);
            ledcWrite(pwma, speed);
            ledcWrite(pwmb, speed);
            break;
            
        case LEFT: 
            digitalWrite(ina_1, LOW); digitalWrite(ina_2, HIGH); 
            digitalWrite(inb_1, HIGH); digitalWrite(inb_2, LOW);
            ledcWrite(pwma, speed); 
            ledcWrite(pwmb, speed); 
            break;
            
        case RIGHT: 
            digitalWrite(ina_1, HIGH); digitalWrite(ina_2, LOW);
            digitalWrite(inb_1, LOW); digitalWrite(inb_2, HIGH);
            ledcWrite(pwma, speed); 
            ledcWrite(pwmb, speed);
            break;
            
        case STOP:
        default:
            digitalWrite(ina_1, LOW); digitalWrite(ina_2, LOW);
            digitalWrite(inb_1, LOW); digitalWrite(inb_2, LOW);
            ledcWrite(pwma, 0);
            ledcWrite(pwmb, 0);
            break;
    }
}