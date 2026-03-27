#include "motor.h"
#include "control.h"
#include "matrix.h"

#define time_push 3000
#define space 100

unsigned long push_previous = 0;

enum State{IDLE, RECORD, PLAYING, ERROR};

button route[100];
int step = 0;
State current_state = IDLE;

void Task_1(void *parameter){
    while(1){
        button command = scan();
        unsigned long push_current = millis();
        if(command != button::NONE){
            if(push_current - push_previous > time_push){
                current_state = ERROR;
                Serial.println("Now: Error");
                delay(100);
            }
            push_previous = push_current;
        }
        switch(current_state){
            case IDLE:
            case RECORD:
            case PLAYING:
            case ERROR:
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