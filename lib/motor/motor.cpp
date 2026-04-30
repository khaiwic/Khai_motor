#include <Arduino.h>
#include "motor.h"
#include "Kinematics.h"
#include "PinConfig.h"
#include "RobotConfig.h"

int encoder_1_val = 0;
int encoder_2_val = 0;

encoder::encoder(){
    _encoderA_1 = ENCODER::encoder_1A;
    _encoderA_2 = ENCODER::encoder_1B;
    _encoderB_1 = ENCODER::encoder_2A;
    _encoderB_2 = ENCODER::encoder_2B;
};
void encoder::init_encoder(){
    pinMode(_encoderA_1, INPUT_PULLUP);
    pinMode(_encoderA_2, INPUT_PULLUP);
    pinMode(_encoderB_1, INPUT_PULLUP);
    pinMode(_encoderB_2, INPUT_PULLUP);
}
void encoder::read_encoder_A(){
    int A = digitalRead(_encoderA_1);
    int B = digitalRead(_encoderA_2);
    if((A == HIGH) != (B == LOW)){
        encoder_1_val++;
    }
    else {
       encoder_1_val--;
    }
}
void encoder::read_encoder_B(){
    int A = digitalRead(_encoderB_1);
    int B = digitalRead(_encoderB_2);
    if((A == HIGH) != (B == LOW)){
        encoder_2_val--;
    }
    else {
        encoder_2_val--;
    }
}
void encoder::go(control command, int speedA, int speedB){
    switch(command){
        case control::TOP:
            break;
        case control::BACK: break;
        case control::RIGHT: break;
        case control::LEFT: break;
        case control::STOP: break;
            break;
    }
}