#include <Arduino.h>
#include "control.h"

QueueHandle_t Ong_Truyen_Lenh;

bool flag  = false;
bool flag_goal  = false;
void Task_2(void *parameter){
    control command_receive;
    while(1){
        xQueueReceive(Ong_Truyen_Lenh, &command_receive, portMAX_DELAY);
        if(command_receive == control::FINISH){
            flag_goal = true;
            go(control::STOP, 0);
            Serial.println("GOALLLLL");
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        else{
            flag = true;
            for(int i = 0; i <= 1023; i++){
                go(command_receive, i);
                vTaskDelay(1 / portTICK_PERIOD_MS);
            }
            go(control::STOP, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
}