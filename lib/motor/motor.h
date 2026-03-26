#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

enum control{
    TOP,
    LEFT,
    RIGHT, 
    BACK,
    STOP
};
void initMotor();
void go(control next, int speed);
#endif