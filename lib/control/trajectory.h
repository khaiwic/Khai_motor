#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include "Kinematics.h"
#include "RobotConfig.h"
#include "PinConfig.h"
#include "read_command.h"

// ranh thi se say dung mot mo hinh colab bieu dien
class traject
{
private:
    float _v_max;      // van toc max cho phep
    float _a_max;      // gia toc max cho phep
    float _dt;         // thoi gian
    int _current_pos;  // Vi tri hien tai
    int _current_vel;  // van toc hien tai
    int _target_pos;   // setpoint position top and back
    int _target_pivot; // setpoint position in process pivot
public:
    traject(float vmax, float amax, float dt_step);
    void reset(float start_pos);
    long set_target(control command, int count);
    float update();
};
#endif