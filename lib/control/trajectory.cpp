#include <Arduino.h>
#include "trajectory.h"
#include "Kinematics.h"
#include "PinConfig.h"
#include "RobotConfig.h"

// Constructor
traject::traject(float v_max, float a_max, float dt_step) {
    _v_max = v_max;
    _a_max = a_max;
    _dt = dt_step;
    _current_pos = 0;
    _current_vel = 0;
    _target_pos = robo::tagpos;
    _target_pivot = robo::pivot;
}

void traject::reset(float start_pos) {
    _current_pos = start_pos;
    _current_vel = 0;
    _target_pos = start_pos;
}

void traject::set_target(float target) {
    _target_pos = target;
}

// Trái tim của quỹ đạo hình thang
float traject::update() {
    float error = _target_pos - _current_pos;

    // v = can 2 ( 2 * a * S)
    float max_stop_vel = sqrt(2.0f * _a_max * fabs(error));

    float desired_vel = _v_max; // van toc mong muon
    if (desired_vel > max_stop_vel) {
        desired_vel = max_stop_vel;
    }
    //di lui
    if (error < 0) {
        desired_vel = -desired_vel;
    }
    // tinh toan  accel
    float vel_error = desired_vel - _current_vel;
    float accel = vel_error / _dt;

    //khung a
    if (fabs(accel) > _a_max) {
        accel = (accel > 0) ? _a_max : -_a_max; 
    }
    // if (accel > _a_max) accel = _a_max;
    // if (accel < -_a_max) accel = -_a_max;

    // 7. Cập nhật vận tốc và vị trí ảo (Công thức Euler)
    _current_vel += accel * _dt;
    _current_pos += _current_vel * _dt;

    // 8. Chống rung/lắc (Jitter) khi đã đến rất gần đích
    if (fabs(error) < 0.5f && fabs(_current_vel) < 0.1f) {
        _current_pos = _target_pos;
        _current_vel = 0;
    }

    // Trả về Setpoint (vị trí từng bước) để nạp vào hàm PID
    return _current_pos;
}