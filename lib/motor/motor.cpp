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

void go(control command, int speedA, int speedB){
    switch(command){
        case control::TOP:
            digitalWrite(MOTOR::ina_1, HIGH); digitalWrite(MOTOR::inb_1, HIGH);
            digitalWrite(MOTOR::ina_2, LOW);  digitalWrite(MOTOR::inb_2, LOW);
            ledcWrite(MOTOR::pwma, speedA);
            ledcWrite(MOTOR::pwmb, speedB);
            break;
        case control::BACK: 
            digitalWrite(MOTOR::inb_1, LOW);    digitalWrite(MOTOR::ina_1, LOW);
            digitalWrite(MOTOR::inb_2, HIGH);   digitalWrite(MOTOR::ina_2, HIGH);
            ledcWrite(MOTOR::pwma, speedA);
            ledcWrite(MOTOR::pwmb, speedB);
            break;
        case control::RIGHT: 
            digitalWrite(MOTOR::ina_1, HIGH); digitalWrite(MOTOR::ina_2, LOW);
            digitalWrite(MOTOR::inb_1, LOW);  digitalWrite(MOTOR::inb_2, HIGH);
            ledcWrite(MOTOR::pwma, speedA);
            ledcWrite(MOTOR::pwmb, speedB);
            break;
        case control::LEFT: 
            digitalWrite(MOTOR::ina_1, LOW); digitalWrite(MOTOR::ina_2, HIGH);
            digitalWrite(MOTOR::inb_1, HIGH); digitalWrite(MOTOR::inb_2, LOW);
            ledcWrite(MOTOR::pwma, speedA);
            ledcWrite(MOTOR::pwmb, speedB);
            break;
        case control::STOP:
            digitalWrite(MOTOR::ina_1, LOW); digitalWrite(MOTOR::ina_2, LOW);
            digitalWrite(MOTOR::inb_1, LOW); digitalWrite(MOTOR::inb_2, LOW);
            ledcWrite(MOTOR::pwma, 0);
            ledcWrite(MOTOR::pwmb, 0);
            break;
    }
}