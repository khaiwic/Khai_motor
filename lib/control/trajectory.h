#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include "Kinematics.h"
#include "RobotConfig.h"
#include "PinConfig.h"
#include "read_command.h"

// ranh thi se say dung mot mo hinh colab bieu dien
// class traject
// {
// private:
//     float _v_max;      // van toc max cho phep
//     float _a_max;      // gia toc max cho phep
//     float _dt;         // thoi gian
//     int _current_pos;  // Vi tri hien tai
//     int _current_vel;  // van toc hien tai
//     int _sys_pos;   // setpoint position top and back
//     int _sys_pivot; // setpoint position in process pivot
// public:
//     traject(float vmax, float amax, float dt_step);
//     void reset(float start_pos);
//     long set_target(control command, int count);
//     long update();
// };
typedef struct {
    volatile long pos_curr;     // Vị trí thực tế (Từ Encoder)
    volatile float vel_curr;    // Vận tốc thực tế (Từ Encoder)
    volatile long pos_tar;      // Vị trí đích cuối cùng muốn đến
    volatile float pos_setpoint;// Vị trí ảo (thay đổi từng dt) đưa vào PID
    volatile float vel_setpoint;// Vận tốc ảo (thay đổi từng dt) đưa vào PID
    volatile long pwm_output;   // Xung xuất ra động cơ
} MotorState;

extern volatile MotorState leftTire;
extern volatile MotorState rightTire;

class traject {
private:
    float _v_max;      
    float _a_max;      
    float _dt;        

    void update_single_motor(volatile MotorState& motor);

public:
    traject(float vmax, float amax, float dt_step);
    
    void reset();
    
    void caculate_traject(control command, int count);
    
    void update();

    void pull_pid_tool();
};
#endif