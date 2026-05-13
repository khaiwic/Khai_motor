#include <Arduino.h>
#include "PinConfig.h"
#include "RobotConfig.h"
#include "Kinematics.h"
#include "read_command.h"
#include "matrix.h"
#include "pid.h"
#include "trajectory.h"

#define M 100 

control route[M] = {control::NONE};
int step = 0;
pid pid_ctr;
matrix mtr;
control command = control::NONE;


// traject_class
traject trj(100.0, 50.0, 0.01); // de tam thoi cac para nay

enum State
{
    IDLE,
    RECORD,
    HANDLE,
    PLAYING,
    ERR
};

struct cmd{
    control cmd_press;
    int count;
};

cmd press_cmd[M];
int op = 0;
State state_curr = IDLE;

void optimal(){
    if(step == 0) return;
    op = 0;
    press_cmd[op].cmd_press = route[0];
    press_cmd[op].count  = 1;
    for(int i = 1; i < step; i++){
        if(press_cmd[op].cmd_press == route[i]){
            press_cmd[op].count++;
        }
        else {
            op++;
            press_cmd[op].cmd_press = route[i];
            press_cmd[op].count = 1;
        }
    }
    op++;
    Serial.println("--- DA TOI UU QUY DAO ---");
    for (int i = 0; i < op; i++) {
        Serial.print("Lenh: ");
        Serial.print((int)press_cmd[i].cmd_press);
        Serial.print(" | So lan: ");
        Serial.println(press_cmd[i].count);
    }
}

void read_command()
{
    if (state_curr == HANDLE) {
        Serial.println("Now: HANDLE - Dang xu ly...");
        optimal();
        state_curr = PLAYING; 
        Serial.println("Now: PLAYING - Bat dau chay!");
        return; 
    }

    command = mtr.read_analog_matrix();

    if (command != control::NONE)
    {
        if (state_curr == ERR && command == control::OK)
        {
            state_curr = IDLE;
            Serial.println("Now: IDLE");
            step = 0; 
            Serial.println("Dang cho record..."); 
            delay(500);
        }
        else if (state_curr == IDLE && command == control::OK)
        {
            state_curr = RECORD;
            step = 0;
            Serial.println("Now: RECORDING");
            Serial.println("Hay nhap lenh vao FSM..."); 
            delay(500);
        }
        else if (state_curr == RECORD)
        {
            if (command == control::OK) {
                state_curr = HANDLE;
                delay(500);
            } 
            else {
                if(step >= M){
                    state_curr = ERR;
                    Serial.println("Now: ERR - Tran bo nho"); 
                    delay(500);
                }
                else {
                    route[step] = command;
                    Serial.printf("Lenh so %d nhan duoc la: %d\n", step, (int)command); 
                    step++;
                    delay(300); 
                }
            }
        }
        //Playing se ngung chay khi he thong chay het lenh
        else if(state_curr == PLAYING){
            for(int i = 0; i < op; i++){
                //nap vo traject
                trj.caculate_traject(press_cmd[i].cmd_press, press_cmd[i].count); 
                Serial.println(" Dang thuc hien lenh"); delay(300);
            }
        }
    }
}