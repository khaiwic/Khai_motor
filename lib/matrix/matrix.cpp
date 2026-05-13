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

int matrix::read_filtered_analog(){
    long sum = 0;
    for(int i = 0; i < READ_SAMPLES; i++){
        sum += analogRead(_pin);
    }
    return sum / READ_SAMPLES;
}

control matrix::classify_analog(int value){
    control btn_pressed = control::NONE; 

    if(value > 100 && value < 600){
        btn_pressed = control::TOP;
    }
    else if(value > 800 && value < 1400){
        btn_pressed = control::BACK;
    }
    else if(value > 1600 && value < 2200){
        btn_pressed = control::LEFT;
    }
    else if(value > 2500 && value < 3000){
        btn_pressed = control::RIGHT;
    }
    else if(value > 3200 && value < 3800){
        btn_pressed = control::OK;
    }
    return btn_pressed; 
}

control matrix::read_analog_matrix(){
    int analog_value = read_filtered_analog();
    control raw_button = classify_analog(analog_value);
    unsigned long now = millis();

    if(raw_button != _last_raw_button){
        _last_raw_button = raw_button;
        _last_change_ms = now;
        return control::NONE;
    }

    if(now - _last_change_ms < DEBOUNCE_MS){
        return control::NONE;
    }

    if(raw_button == control::NONE){
        _waiting_release = false;
        return control::NONE;
    }

    if(_waiting_release){
        return control::NONE;
    }

    _waiting_release = true;

    Serial.print("Gia tri Analog: ");
    Serial.println(analog_value);

    if(raw_button == control::TOP){
        Serial.println("BUOC DI :: TOP");
    }
    else if(raw_button == control::BACK){
        Serial.println("BUOC DI :: BACK");
    }
    else if(raw_button == control::LEFT){
        Serial.println("BUOC DI :: LEFT");
    }
    else if(raw_button == control::RIGHT){
        Serial.println("BUOC DI :: RIGHT");
    }
    else if(raw_button == control::OK){
        Serial.println("HOAN THANH");
    }

    return raw_button;
}
