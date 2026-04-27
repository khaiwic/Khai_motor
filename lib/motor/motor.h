#ifndef MOTOR_H
#define MOTOR_H
#include "Kinematics.h"
#include "PinConfig.h"
#include "RobotConfig.h"

extern int encoder_1_val;
extern bool encoder_2_val;

class encoder{
private:
    int _encoderA_1;
    int _encoderA_2;
    int _encoderB_1;
    int _encoderB_2;
public:
    encoder();
    void init_encoder();
    void read_encoder_A();
    void read_encoder_B();
    void go(control command, int speedA, int speedB);
};
#endif