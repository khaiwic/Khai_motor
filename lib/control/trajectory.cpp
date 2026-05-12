#include <Arduino.h>
#include "trajectory.h"
#include "Kinematics.h"
#include "PinConfig.h"
#include "RobotConfig.h"
#include "iostream"
#include "math.h"
// // Constructor
// traject::traject(float v_max, float a_max, float dt_step) {
//     _v_max = v_max;
//     _a_max = a_max;
//     _dt = dt_step;
//     _current_pos = 0;
//     _current_vel = 0;
//     _target_pos = robo::tagpos;
//     _target_pivot = robo::pivot;
// }

// void traject::reset(float start_pos) {
//     _current_pos = start_pos;
//     _current_vel = 0;
//     _target_pos = start_pos;
// }

// void traject::set_target(float target) {
//     _target_pos = target;
// }

// // Trái tim của quỹ đạo hình thang
// float traject::update() {
//     float error = _target_pos - _current_pos;

//     // v = can 2 ( 2 * a * S)
//     float max_stop_vel = sqrt(2.0f * _a_max * fabs(error));

//     float desired_vel = _v_max; // van toc mong muon
//     if (desired_vel > max_stop_vel) {
//         desired_vel = max_stop_vel;
//     }
//     //di lui
//     if (error < 0) {
//         desired_vel = -desired_vel;
//     }
//     // tinh toan  accel
//     float vel_error = desired_vel - _current_vel;
//     float accel = vel_error / _dt;

//     //khung a
//     if (fabs(accel) > _a_max) {
//         accel = (accel > 0) ? _a_max : -_a_max; 
//     }
//     // if (accel > _a_max) accel = _a_max;
//     // if (accel < -_a_max) accel = -_a_max;

//     // 7. Cập nhật vận tốc và vị trí ảo (Công thức Euler)
//     _current_vel += accel * _dt;
//     _current_pos += _current_vel * _dt;

//     // 8. Chống rung/lắc (Jitter) khi đã đến rất gần đích
//     if (fabs(error) < 0.5f && fabs(_current_vel) < 0.1f) {
//         _current_pos = _target_pos;
//         _current_vel = 0;
//     }

//     // Trả về Setpoint (vị trí từng bước) để nạp vào hàm PID
//     return _current_pos;
// }

//---------------------------------------------------------------
// traject::traject(float max, float a, float dt){
//     _a_max = 100;
//     _v_max = 50;
//     _dt = 0.01;
//     _current_pos = 0;
//     _current_vel = 0;
//     _sys_pos = robo::tagpos;
//     _sys_pivot = robo::pivot;
// }
// long traject::set_target(control command, int count){
//     switch (command){
//         case control::TOP:
//             _sys_pos = robo::tagpos * count;
//             _current_pos = 0;
//             _current_vel = 0;
//             traject::update();
//             break;
//         case control::BACK:
//             _sys_pos = -robo::tagpos * count;
//             _current_pos = 0;
//             _current_vel = 0;
//             traject::update();
//             break;
//         case control::LEFT:
//             _sys_pivot = robo::pivot * count;
//             _current_pos = 0;
//             _current_vel = 0;
//             traject::update();
//             break;
//         case control::RIGHT:
//             _sys_pivot = -robo::pivot * count;
//             _current_pos = 0;
//             _current_vel = 0;
//             traject::update();
//             break;
//         default:
//             break;
//     }
// }
// void traject::reset(float pos){
//     _current_pos = 0;
//     _current_vel = 0;
//     _sys_pos = pos;
// }
// long traject::update(){
//     long error = _sys_pos - _current_pos;
    
// }
//---------------------------------------------

volatile MotorState leftTire = {0, 0, 0, 0, 0, 0};
volatile MotorState rightTire = {0, 0, 0, 0, 0, 0};

traject::traject(float vmax, float amax, float dt_step) {
    _v_max = vmax;
    _a_max = amax;
    _dt = dt_step;
}

// Reset trạng thái xe
void traject::reset() {
    leftTire.pos_curr = 0; leftTire.pos_tar = 0; leftTire.pos_setpoint = 0; leftTire.vel_setpoint = 0;
    rightTire.pos_curr = 0; rightTire.pos_tar = 0; rightTire.pos_setpoint = 0; rightTire.vel_setpoint = 0;
}

// Thiết lập đích đến cho 2 bánh dựa vào lệnh
void traject::caculate_traject(control command, int count) {
    switch(command) {
        case control::TOP:
            leftTire.pos_tar += robo::tagpos * count;
            rightTire.pos_tar += robo::tagpos * count;
            break; // QUAN TRỌNG: Phải có break!
            
        case control::BACK:
            leftTire.pos_tar -= robo::tagpos * count;
            rightTire.pos_tar -= robo::tagpos * count;
            break;
            
        case control::LEFT:
            leftTire.pos_tar -= robo::pivot * count;
            rightTire.pos_tar += robo::pivot * count;
            break;
            
        case control::RIGHT:
            leftTire.pos_tar += robo::pivot * count;
            rightTire.pos_tar -= robo::pivot * count;
            break;
            
        default:
            break;
    }
}

// Hàm tính toán logic quỹ đạo chung
void traject::update() {
    // Cập nhật đồng thời cho cả bánh trái và bánh phải
    update_single_motor(leftTire);
    update_single_motor(rightTire);
}

// Thuật toán cốt lõi tính quỹ đạo cho TỪNG động cơ
void traject::update_single_motor(volatile MotorState& motor) {
    // Tính khoảng cách còn lại tới đích (Dựa vào vị trí Setpoint ảo để tạo độ mượt)
    float error = motor.pos_tar - motor.pos_setpoint; 

    // Tính vận tốc hãm phanh tối đa cho phép: v = sqrt(2 * a * S)
    float max_stop_vel = sqrt(2.0f * _a_max * fabs(error));

    // Vận tốc mong muốn (Duy trì v_max hoặc bắt đầu hãm phanh)
    float desired_vel = _v_max;
    if (desired_vel > max_stop_vel) {
        desired_vel = max_stop_vel; // Bắt đầu giảm tốc (Pha 3)
    }

    // Đảo chiều vận tốc nếu cần đi lùi
    if (error < 0) {
        desired_vel = -desired_vel;
    }

    // Tính toán độ lệch vận tốc và gia tốc cần thiết
    float vel_error = desired_vel - motor.vel_setpoint;
    float accel = vel_error / _dt;

    // Ràng buộc giới hạn gia tốc phần cứng (Pha 1 & 3)
    if (fabs(accel) > _a_max) {
        accel = (accel > 0) ? _a_max : -_a_max; 
    }

    // Cập nhật Setpoint (Vận tốc và Vị trí ảo) cho chu kỳ này
    motor.vel_setpoint += accel * _dt;
    motor.pos_setpoint += motor.vel_setpoint * _dt;

    // Chống rung/lắc (Jitter) khi đã đến rất gần đích
    if (fabs(error) < 1.0f && fabs(motor.vel_setpoint) < 0.1f) {
        motor.pos_setpoint = motor.pos_tar;
        motor.vel_setpoint = 0;
    }
}