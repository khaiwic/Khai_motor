#include <Arduino.h>
#include "control.h"
#include "motor.h"
//setpoint đi thẳng khác hoàn toàn setpoint rẽw
const int setPoint = 2500;
unsigned long time_pre = 0;

// Hệ số PID Bánh A
const float Kp_A = 10.0;
const float Ki_A = 0.0;
const float Kd_A = 0.0;
float error_number_A_pre = 0;
float sum_error_number_A = 0;

// Hệ số PID Bánh B
const float Kp_B = 10.0;
const float Ki_B = 0.0;
const float Kd_B = 0.0;
float error_number_B_pre = 0;
float sum_error_number_B = 0;

volatile bool flag = false;
volatile bool flag_goal = false;
volatile bool is_running_step = false;

void Task_2(void *parameters){
    control command_receive;
    control current_command = control::STOP;

    while(1){
        // KHỐI 1: CHỈ ĐỌC LỆNH KHI XE ĐANG RẢNH
        if(is_running_step == false){
            if(xQueueReceive(Ong_Truyen_Lenh, &command_receive, 0) == pdTRUE){
                current_command = command_receive; 
                
                if(command_receive == control::FINISH){
                    flag_goal = true;
                    flag = false;
                    go(control::STOP, 0, 0); 
                    Serial.println("______HOÀN THÀNH TOÀN BỘ CHUỖI LỆNH______");
                }
                else {
                    is_running_step = true;
                    flag = true; 
                    flag_goal = false;
                    reset();
                    time_pre = millis(); 
                    sum_error_number_A = 0; 
                    error_number_A_pre = 0;
                    sum_error_number_B = 0; 
                    error_number_B_pre = 0;
                    
                    Serial.print(">> Xe bat dau chay lenh: ");
                    Serial.println((int)current_command);
                    vTaskDelay(1000 / portTICK_PERIOD_MS);
                }
            }
        } 
        // KHỐI 2: PID CHẠY LIÊN TỤC MỖI 10ms (CHỈ KHI ĐANG BẬN)
        if(flag == true && flag_goal == false && is_running_step == true){
            unsigned long time_now = millis();
            
            if(time_now - time_pre >= 10){
                float dt = (time_now - time_pre) / 1000.0;
                
                if (dt > 0) {
                    time_pre = time_now;
                    
                    int position_A = encoderA_values;
                    int position_B = encoderB_values;
//Motor A
                    float error_number_A = setPoint - abs(position_A);
                    sum_error_number_A += error_number_A * dt;
                    float P_A = Kp_A * error_number_A;
                    float I_A = Ki_A * sum_error_number_A;
                    float D_A = Kd_A * (error_number_A - error_number_A_pre) / dt;
                    error_number_A_pre = error_number_A;
                    int OUTPUT_A = (int)(P_A + I_A + D_A);
//Motor B
                    float error_number_B = setPoint - abs(position_B);
                    sum_error_number_B += error_number_B * dt;
                    float P_B = Kp_B * error_number_B;
                    float I_B = Ki_B * sum_error_number_B;
                    float D_B = Kd_B * (error_number_B - error_number_B_pre) / dt;
                    error_number_B_pre = error_number_B;
                    int OUTPUT_B = (int)(P_B + I_B + D_B);
//Send command to motor A, B
                    Serial.print("Banh A: PWM = "); Serial.print(OUTPUT_A); Serial.print(" | EncA = "); Serial.println(encoderA_values);
                    Serial.print("Banh B: PWM = "); Serial.print(OUTPUT_B); Serial.print(" | EncB = "); Serial.println(encoderB_values);
                    go(current_command, OUTPUT_A, OUTPUT_B);
//kiểm tra goal
                    if(error_number_A <= 5 && error_number_B <= 5){
                        go(control::STOP, 0, 0);
                        is_running_step = false;
                        
                        Serial.println(">> Done 1 buoc! Chuan bi chay buoc tiep theo...");
                        vTaskDelay(500 / portTICK_PERIOD_MS); 
                    }
                }
            }
        }
        
        // Nhường CPU 10ms
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}