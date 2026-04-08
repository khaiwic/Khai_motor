//cơ bản là đã xong
#include "motor.h"
//motorA
const int pwma = 9;
const int ina_1 = 10;
const int ina_2 = 11;

//motorB
const int pwmb = 12;
const int inb_1 = 14; 
const int inb_2 = 13; 

volatile int encoderA_values = 0;
volatile int encoderB_values = 0;
//he thong
#define freq 20000
#define resolution 10

//setupMotor
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
//setupEncoder
void initEncoder(){
    pinMode(encoder_1A, INPUT_PULLUP);
    pinMode(encoder_1B, INPUT_PULLUP);
    pinMode(encoder_2A, INPUT_PULLUP);
    pinMode(encoder_2B, INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(encoder_1A), positionA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoder_2A), positionB, CHANGE);
}
//interrupt encoder A
void IRAM_ATTR positionA(){
    int A = digitalRead(encoder_1A);
    int B = digitalRead(encoder_1B);
    if((A == HIGH) != (B == LOW)){
        encoderA_values --;
    }
    else{
        encoderA_values ++;
    }
}
//interrupt encoder B
void IRAM_ATTR positionB(){
    int A = digitalRead(encoder_2A);
    int B = digitalRead(encoder_2B);
    if((A == HIGH) != (B == LOW)){
        encoderB_values ++;
    }
    else{
        encoderB_values --;
    }
}
//reset
void reset(){
    encoderA_values = 0;
    encoderB_values = 0;
}
//receive speed
void go(control next, int speedA, int speedB){
    if(speedA > 1023) speedA = 1023;
    if(speedA < 0)    speedA = 0;
    
    if(speedB > 1023) speedB = 1023;
    if(speedB < 0)    speedB = 0;
        switch(next){
            case control::TOP:
                digitalWrite(ina_1, HIGH); digitalWrite(ina_2, LOW);
                digitalWrite(inb_1, HIGH); digitalWrite(inb_2, LOW);
                ledcWrite(pwma, speedA);
                ledcWrite(pwmb, speedB);
                break;
            
            case control::BACK:
                digitalWrite(ina_1, LOW); digitalWrite(ina_2, HIGH);
                digitalWrite(inb_1, LOW); digitalWrite(inb_2, HIGH);
                ledcWrite(pwma, speedA);
                ledcWrite(pwmb, speedB);
                break;
            
            case control::LEFT: 
                digitalWrite(ina_1, LOW); digitalWrite(ina_2, HIGH); 
                digitalWrite(inb_1, HIGH); digitalWrite(inb_2, LOW);
                ledcWrite(pwma, speedA);
                ledcWrite(pwmb, speedB);
            break;
            
            case control::RIGHT: 
                digitalWrite(ina_1, HIGH); digitalWrite(ina_2, LOW);
                digitalWrite(inb_1, LOW); digitalWrite(inb_2, HIGH);
                ledcWrite(pwma, speedA);
                ledcWrite(pwmb, speedB);
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