#include <Arduino.h>
#include "Kinematics.h"
#include "PinConfig.h"
#include "RobotConfig.h"
#include "matrix.h"


matrix::matrix(){
    _pin = MATRIX::analog_button;
}
void matrix::initmatrix(){  
    pinMode(_pin, INPUT);
}
control matrix::read_analog_matrix(){
    int A = analogRead(_pin);
    if(A == 0){
        route[step++] = control::TOP;
        Serial.println("BUOC DI :: TOP");
    }
    else if(A == 0){
        route[step++] = control::BACK;
        Serial.println("BUOC DI :: BACK");
    }
    else if(A == 0){
        route[step++] = control::LEFT;
        Serial.println("BUOC DI :: LEFT");
    }
    else if(A == 0){
        route[step++] = control::RIGHT;
        Serial.println("BUOC DI :: RIGHT");
    }
    else if(A == 0){
        route[step++] = control::OK;
        Serial.println("HOAN THANH");
    }
    delay(500);
}