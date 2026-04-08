#include <Arduino.h>
#include "control.h"
#include "motor.h"
//setpoint đi thẳng khác hoàn toàn setpoint rẽ
const int Target_pos = 2500; //setpoint speed
const int Target_vel = 2000; //setpoint speed_turn
unsigned long time_pre = 0;

// Hệ số PD Bánh A
const float Kp_A_P = 3.0;
const float Kd_A_P = 5.0;
float er_A = 0;
float er_A_pre = 0;

//Hệ số PI Bánh A
const float Kp_A_V = 0;
const float Ki_A_V = 0;
float er_A_v = 0;
float sum_er_A = 0;
int posA_pre = 0;

//Hệ số PD Bánh B
const float Kp_B_P = 0;
const float Kd_B_P = 0;
float er_B = 0;
float er_B_pre = 0;

// Hệ số PI Bánh B
const float Kp_B_V = 3.0;
const float Ki_B_V = 0.01;
float er_B_v = 0;
float sum_er_B = 0;
int posB_pre = 0;


volatile bool flag = false;
volatile bool flag_goal = false;
volatile bool flag_running = false;

void Task_2(void *parameters){
    control command_receive;
    control current_command = control::STOP;

    while(1){
        // KHỐI 1: CHỈ ĐỌC LỆNH KHI XE ĐANG RẢNH
        if(flag_running == false){
            if(xQueueReceive(Ong_Truyen_Lenh, &command_receive, 0) == pdTRUE){
                current_command = command_receive; 
                
                if(command_receive == control::FINISH){
                    flag_goal = true;
                    flag = false;
                    go(control::STOP, 0, 0); 
                    Serial.println("______HOÀN THÀNH TOÀN BỘ CHUỖI LỆNH______");
                    vTaskDelay(1000 / portTICK_PERIOD_MS);
                }
                else {
                    flag_running= true;
                    flag = true; 
                    flag_goal = false;
                    reset();// reset lệnh cũ
                    time_pre = millis(); 
                    sum_er_A = 0; 
                    er_A_pre = 0;
                    sum_er_B = 0; 
                    er_B_pre = 0;
                    
                    Serial.print(">> Xe bat dau chay lenh: ");
                    Serial.println((int)current_command);
                    vTaskDelay(1000 / portTICK_PERIOD_MS);
                }
            }
        } 
        // KHỐI 2: PID CHẠY LIÊN TỤC MỖI 10ms (CHỈ KHI ĐANG BẬN)
        if(flag == true && flag_goal == false && flag_running == true){ // xem xét
            unsigned long time_now = millis();
            // tăng nhịp tim cho pid
            if(time_now - time_pre >= 50){
                float dt = (time_now - time_pre) / 1000.0;
                
                if (dt > 0) {
                    time_pre = time_now;
                    int pos_A = encoderA_values;
                    int pos_B = encoderB_values;
    //velocity current
                    int ds_A = pos_A - posA_pre;
                    int ds_B = pos_B - posB_pre;
                    posA_pre = pos_A;
                    posB_pre = pos_B;

                    //PD a & b
                    er_A = Target_pos - abs(pos_A);
                    er_B = Target_pos -  abs(pos_B);
                    float P_posA = Kp_A_P * er_A;
                    float p_posB = Kp_B_P * er_B;
                    float D_posA = Kd_A_P * (er_A - er_A_pre) / dt;
                    er_A_pre = er_A;
                    float D_posB = Kd_B_P * (er_B - er_B_pre) / dt;
                    er_B_pre = er_B;
                    int OP_A_P = (int)(P_posA + D_posA); //output a position = target_velocity_A
                    int OP_B_P = (int)(p_posB + D_posB); //output b position = target_velocity_B

                    OP_A_P = constrain(OP_A_P, -600, 600);
                    OP_B_P = constrain(OP_B_P, -600, 600);

                    er_A_v = OP_A_P - ds_A;
                    er_B_v = OP_B_P - ds_B;
                    sum_er_A += er_A_v * dt;
                    sum_er_B += er_B_v * dt;
                    //germini
                    sum_er_A = constrain(sum_er_A, -1000, 1000);
                    sum_er_B = constrain(sum_er_B, -1000, 1000);

                    float P_velA = Kp_A_V*er_A_v;
                    float P_velB = Kp_B_V*er_B_v;
                    float I_velA = Ki_A_V * sum_er_A;
                    float I_velB= Ki_B_V * sum_er_B;
                    int OP_A_V = (int)(P_velA + I_velA);
                    int OP_B_V = (int)(P_velB + I_velB);
                    //germini
                    OP_A_V = constrain(OP_A_V, -1023, 1023);
                    OP_B_V = constrain(OP_B_V, -1023, 1023);
                    
                    go(current_command, OP_A_V,  OP_B_V);

                    if(abs(er_A) <= 10 && abs(er_B) <= 10){
                        go(control::STOP, 0, 0);
                        flag_running = false;
                        
                        Serial.println(">> Done 1 buoc! Chuan bi chay buoc tiep theo...");
                        vTaskDelay(500 / portTICK_PERIOD_MS); 
                    }
                }
            }
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}