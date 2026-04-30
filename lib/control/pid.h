#ifndef PID_H
#define PID_H
#include "Kinematics.h"
#include "RobotConfig.h"
#include "PinConfig.h"
#include "motor.h"
#include "trajectory.h"
extern hw_timer_t* timer;
extern portMUX_TYPE timerMUX;
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
    void IRAM_ATTR resolve_pid();
};
#endif