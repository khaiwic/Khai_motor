#include "motor.h"
//motorA
const int pwma = 1;
const int ina_1 = 2;
const int ina_2 = 3;

//motorB
const int pwmb = 5;
const int inb_1 = 6; 
const int inb_2 = 7; 

volatile int encoderA_values = 0;
volatile int encoderB_values = 0;
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
void initEncoder(){
    pinMode(encoder_1A, INPUT_PULLUP);
    pinMode(encoder_1B, INPUT_PULLUP);
    pinMode(encoder_2A, INPUT_PULLUP);
    pinMode(encoder_2B, INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(encoder_1A), positionA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoder_2A), positionB, CHANGE);
}
void IRAM_ATTR positionA(){
    int A = digitalRead(encoder_1A);
    int B = digitalRead(encoder_1B);
    if((A == HIGH) != (B == LOW)){
        encoderA_values++;
    }
    else{
        encoderA_values--;
    }
}
void IRAM_ATTR positionB(){
    int A = digitalRead(encoder_2A);
    int B = digitalRead(encoder_2B);
    if((A == HIGH) != (B == LOW)){
        encoderB_values++;
    }
    else{
        encoderB_values--;
    }
}
void reset(){
    encoderA_values = 0;
    encoderB_values = 0;
}
void go(control next, int speed){
        switch(next){
            case control::TOP:
                digitalWrite(ina_1, HIGH); digitalWrite(ina_2, LOW);
                digitalWrite(inb_1, HIGH); digitalWrite(inb_2, LOW);
                ledcWrite(pwma, speed);
                ledcWrite(pwmb, speed);
                break;
            
            case control::BACK:
                digitalWrite(ina_1, LOW); digitalWrite(ina_2, HIGH);
                digitalWrite(inb_1, LOW); digitalWrite(inb_2, HIGH);
                ledcWrite(pwma, speed);
                ledcWrite(pwmb, speed);
                break;
            
            case control::LEFT: 
                digitalWrite(ina_1, LOW); digitalWrite(ina_2, HIGH); 
                digitalWrite(inb_1, HIGH); digitalWrite(inb_2, LOW);
                ledcWrite(pwma, speed); 
                ledcWrite(pwmb, speed); 
            break;
            
            case control::RIGHT: 
                digitalWrite(ina_1, HIGH); digitalWrite(ina_2, LOW);
                digitalWrite(inb_1, LOW); digitalWrite(inb_2, HIGH);
                ledcWrite(pwma, speed); 
                ledcWrite(pwmb, speed);
            break;
            
            case control::STOP:
                default:
                digitalWrite(ina_1, LOW); digitalWrite(ina_2, LOW);
                digitalWrite(inb_1, LOW); digitalWrite(inb_2, LOW);
                ledcWrite(pwma, 0);
                ledcWrite(pwmb, 0);
                break;
    }
}