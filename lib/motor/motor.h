#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

enum class control{
    TOP,
    LEFT,
    RIGHT, 
    BACK,
    STOP,
    FINISH,
};
void initMotor();
void go(control next, int speed);
#endif