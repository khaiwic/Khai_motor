#include <Arduino.h>
#include "pid.h"
#include "Kinematics.h"
#include "RobotConfig.h"
#include "PinConfig.h"
#include "motor.h"
#include "trajectory.h"

pid::pid(){
    _Kp_A = 0;
    _Ki_A = 0;
    _Kd_A = 0;
    //
    _Kp_B = 0;
    _Ki_B = 0;
    _Kd_B = 0;
}   
void IRAM_ATTR pid::resolve_pid() {
    // Ngăn chặn CPU hoặc các task khác đọc/ghi đè biến trong lúc đang tính toán
    portENTER_CRITICAL_ISR(&timerMUX);
    //PID
    int curr_encoder_A = encoder_1_val;
    int curr_encoder_B = encoder_2_val;
    
    // Bước B: Tính toán Sai số (Error)
    // int error = target_setpoint - current_position;
    int er_A = 
    
    // Bước C: Tính các khâu P, I, D     // P_term = _Kp_A * error;
    // I_term += _Ki_A * error; (Nhớ thêm code chống Wind-up cho khâu I)
    // D_term = _Kd_A * (error - error_pre);
    
    // Bước D: Tính tổng tín hiệu xuất ra
    // int output = P_term + I_term + D_term;
    
    // Bước E: Lưu lại sai số cho lần tính D tiếp theo
    // error_pre = error;

    // ==========================================
    // 3. XUẤT TÍN HIỆU RA ĐỘNG CƠ
    // ==========================================
    // motor_drive(output);

    // 4. MỞ KHÓA BỘ NHỚ
    portEXIT_CRITICAL_ISR(&timerMUX);
}