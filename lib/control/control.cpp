#include <Arduino.h>
#include <control.h>
#include <motor.h>

const int setPoint = 220;
unsigned long time_pre = 0;

const float Kp_A = 10.0;
const float Ki_A = 0.0;
const float Kd_A = 0.0;
float error_number_A_pre = 0;
float error_number_A = 0;
float sum_error_number_A = 0;

const float Kp_B = 10.0;
const float Ki_B = 0.0;
const float Kd_B = 0.0;
float error_number_B_pre = 0;
float error_number_B = 0;
float sum_error_number_B = 0;


bool flag = false;
bool flag_goal = false;

void Task_2(void *parameters){
    control command_receive;
    while(1){
        if(xQueueReceive(Ong_Truyen_Lenh, &command_receive, 0) == pdTRUE){
            if(command_receive == control::FINISH){
                flag_goal = true;
                Serial.println("______GOAL______");
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            flag = true;
            unsigned long time_now = millis();
            if(time_now - time_pre >= 10){
                float dt = (time_now - time_pre) / 1000.0;
                time_pre = time_now;
                int position_A = encoderA_values;
                int position_B = encoderB_values;

                error_number_A = setPoint - position_A;
                sum_error_number_A += error_number_A * dt;
                float P_A = Kp_A * error_number_A;
                float I_A = Ki_A * sum_error_number_A;
                float D_A = Kd_A * (error_number_A - error_number_A_pre) * dt;
                error_number_A_pre = error_number_A;

                int OUTPUT_A = (int)(P_A + I_A + D_A);
                go(command_receive, OUTPUT_A);

                error_number_B = setPoint - position_B;
                sum_error_number_B += error_number_B * dt;
                float P_B = Kp_B * error_number_B;
                float I_B = Ki_B * sum_error_number_B;
                float D_B = Kd_B * (error_number_B - error_number_B_pre) * dt;
                error_number_B_pre = error_number_B;

                int OUTPUT_B = (int)(P_B + I_B + D_B);
                go(command_receive, OUTPUT_B);
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}