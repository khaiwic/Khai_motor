#ifndef PID_H
#define PID_H
#include "Kinematics.h"
#include "RobotConfig.h"
#include "PinConfig.h"

class pid{
private:
    int _Kp_A;
    int _Ki_A;
    int _Kd_A;
    //
    int _Kp_B;
    int _Ki_B;
    int _Kd_B;
public:
    int error_pre = 0;

    pid();
    void resolve_pid();
};
#endif