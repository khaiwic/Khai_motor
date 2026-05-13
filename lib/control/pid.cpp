#include <Arduino.h>
#include "pid.h"
#include "Kinematics.h"
#include "RobotConfig.h"
#include "PinConfig.h"
#include "motor.h"
#include "trajectory.h"

traject mytr(100.0, 50.0, 0.01); 
float sum_err_a = 0;
float err_pre_a = 0;

float sum_err_b = 0;
float err_pre_b = 0;

const float dt = 0.01; 

pid::pid(){
    _Kp_A = 1.0; 
    _Ki_A = 0.0;
    _Kd_A = 0.0;
    
    _Kp_B = 1.0;
    _Ki_B = 0.0;
    _Kd_B = 0.0;
}   

void IRAM_ATTR pid::resolve_pid() {
    portENTER_CRITICAL_ISR(&timerMUX);
    
    float curr_encoder_A = (float)encoder_1_val;
    float curr_encoder_B = (float)encoder_2_val;

    float error_a = leftTire.pos_setpoint - curr_encoder_A;
    float error_b = rightTire.pos_setpoint - curr_encoder_B;
    
    float Pa = _Kp_A * error_a;
    
    sum_err_a += (error_a * dt); 
    float Ia = _Ki_A * sum_err_a;
    
    float Da = _Kd_A * ((error_a - err_pre_a) / dt); 
    
    float Oa = Pa + Ia + Da; 
    err_pre_a = error_a;    

    float Pb = _Kp_B * error_b;
    
    sum_err_b += (error_b * dt);
    float Ib = _Ki_B * sum_err_b;
    
    float Db = _Kd_B * ((error_b - err_pre_b) / dt);
    
    float Ob = Pb + Ib + Db; 
    err_pre_b = error_b;

    long speedA = constrain((long)Oa, -1023, 1023);
    long speedB = constrain((long)Ob, -1023, 1023);


    go(speedA, speedB);
    portEXIT_CRITICAL_ISR(&timerMUX);
    
    // Ghi chú: Ở dưới này (bên ngoài Critical Section), bạn sẽ cần thêm
    // code để giới hạn giá trị Oa, Ob trong khoảng [-255, 255]
    // và gọi hàm motor::go() để xuất lệnh chạy thật sự.
}