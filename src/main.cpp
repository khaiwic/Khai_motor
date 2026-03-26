#include "motor.h"
#include "control.h"
#include "matrix.h"

#define time_push 3000
#define space 100

unsigned long push_previous = 0;

enum State{IDLE, RECORD, PLAYING, ERROR};

control route[100];
int step = 0;
State current_state = IDLE;

void Task_1(void *parameter){
    
}
void record(){
    char command = scan();
    unsigned long push_current = millis();
    if(command != '0'){
        if(push_current - push_previous >= time_push){
            current_state =  ERROR;
        }
        push_previous = push_current;
        if(command == '='){
            current_state = IDLE;
            step = 0;
            Serial.println("Exit Error");
            delay(50);
        }
        if(current_state = IDLE){
            if(command == '='){
                current_state = RECORD;
                Serial.println("NOW: RECORD");
            }
        }
        else if(current_state = RECORD){
            if(command = '='){
                current_state = PLAYING;
                Serial.println("NOW: PLAYING ");
            }
            else{
                if(step > 0){
                    char step_previous = route[step - 1];
                    if((step_previous == 'B' && route[step] == 'T') ||
                    (step_previous == 'R' && route[step] == 'L') ||
                    (step_previous == 'L' && route[step] == 'R') ||
                    (step_previous == 'B' && route[step] == 'T')){
                        current_state = ERROR;
                        return;
                    }
                }
            }
            if(step < 100){
                route[step] = command;
                Serial.print("Lưu hành động: ");
                Serial.println(route[step]);
                step++;
                delay(500);
            }
        }
    }       
}

void setup(){
    Serial.begin(115200);
    Serial.println("Start NOW:");
    xTaskCreatePinnedToCore(
        Task_1,
        "Matrix_Button_Scan", 
        2048,
        NULL,
        1,
        NULL,
        1
    );
    setupMatrix();
    initMotor();
}
void loop(){

}