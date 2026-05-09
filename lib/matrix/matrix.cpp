#include <Arduino.h>
#include "Kinematics.h"
#include "PinConfig.h"
#include "RobotConfig.h"
#include "matrix.h"

#define MAX_STEPS 100 

matrix::matrix(){
    _pin = MATRIX::analog_button;
}

void matrix::initmatrix(){  
    pinMode(_pin, INPUT); 
}

control matrix::read_analog_matrix(){
    int A = analogRead(_pin);

    Serial.print("Gia tri Analog: "); Serial.println(A);

    control btn_pressed = control::STOP; 

    if(A > 100 && A < 600){
        btn_pressed = control::TOP;
        Serial.println("BUOC DI :: TOP");
    }
    else if(A > 800 && A < 1400){
        btn_pressed = control::BACK;
        Serial.println("BUOC DI :: BACK");
    }
    else if(A > 1600 && A < 2200){
        btn_pressed = control::LEFT;
        Serial.println("BUOC DI :: LEFT");
    }
    else if(A > 2500 && A < 3000){
        btn_pressed = control::RIGHT;
        Serial.println("BUOC DI :: RIGHT");
    }
    else if(A > 3200 && A < 3800){
        btn_pressed = control::OK;
        Serial.println("HOAN THANH");
    }
    return btn_pressed; 
}