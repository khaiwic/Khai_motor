#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
//setup control matrixbutton
const int encoder_1A = 1;
const int encoder_1B = 2;
const int encoder_2A = 3;
const int encoder_2B = 4;
extern volatile int encoderA_values;
extern volatile int encoderB_values;
enum class control{
    TOP,
    LEFT,
    RIGHT, 
    BACK,
    STOP,
    FINISH,
};
//setup motor
void initMotor();
void go(control next, int speed);
//setup control by encoder
void initEncoder();
void positionA();
void positionB();

void reset();
#endif