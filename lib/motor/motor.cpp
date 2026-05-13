#include <Arduino.h>
#include "motor.h"
#include "Kinematics.h"
#include "PinConfig.h"
#include "RobotConfig.h"

int encoder_1_val = 0;
int encoder_2_val = 0;

const int _encoderA_1 = ENCODER::encoder_1A;
const int _encoderA_2 = ENCODER::encoder_1B;
const int _encoderB_1 = ENCODER::encoder_2A;
const int _encoderB_2 = ENCODER::encoder_2B;
void init_encoder(){
    pinMode(_encoderA_1, INPUT_PULLUP);
    pinMode(_encoderA_2, INPUT_PULLUP);
    pinMode(_encoderB_1, INPUT_PULLUP);
    pinMode(_encoderB_2, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(_encoderA_1), read_encoder_A, RISING);
    attachInterrupt(digitalPinToInterrupt(_encoderB_1), read_encoder_B, RISING);
}
void IRAM_ATTR read_encoder_A(){
    int A = digitalRead(_encoderA_1);
    int B = digitalRead(_encoderA_2);
    if((A == HIGH) != (B == LOW)){
        encoder_1_val++;
    }
    else {
       encoder_1_val--;
    }
}
void IRAM_ATTR read_encoder_B(){
    int A = digitalRead(_encoderB_1);
    int B = digitalRead(_encoderB_2);
    if((A == HIGH) != (B == LOW)){
        encoder_2_val--;
    }
    else {
        encoder_2_val++;
    }
}
//chua dung gia tri tuyet doi

void reset(){
    encoder_1_val = 0;
    encoder_2_val = 0;
}

void go(int speedA, int speedB){
    if(speedA > 0){
        if(speedB < 0){
            ledcWrite(MOTOR::channela, speedA);
            ledcWrite(MOTOR::channelb, -speedB);
        }
        else{
            ledcWrite(MOTOR::channela, speedA);
            ledcWrite(MOTOR::channelb, speedB);
        }
    }
    else if (speedA < 0){
        if(speedB > 0){
            ledcWrite(MOTOR::channela, -speedA);
            ledcWrite(MOTOR::channelb, speedB);
        }
        else{
            ledcWrite(MOTOR::channela, -speedA);
            ledcWrite(MOTOR::channelb, -speedB);
        }
    }
    else if(speedA == 0){
        if(speedB == 0){
            ledcWrite(MOTOR::channela, 0);
            ledcWrite(MOTOR::channelb, 0);
        }
    }
}