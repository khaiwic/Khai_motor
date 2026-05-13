#include <Arduino.h>
#include "PinConfig.h"
#include "Kinematics.h"
#include "RobotConfig.h"
#include "pid.h"
#include "read_command.h"

//KHAI BAO TIMER  PID

hw_timer_t *timer = NULL;
portMUX_TYPE timeMUX = portMUX_INITIALIZER_UNLOCKED;

pid myPidController;
motionManager motion;
void IRAM_ATTR on_timer()
{
    myPidController.resolve_pid();
}
void setup()
{
    Serial.begin(115200);
    delay(3000);
    Serial.println("Khoi dong xong Serial");
    delay(1000);
    //config tb6612
    Serial.println(" config dau ra motor"); delay(300);
    pinMode(MOTOR::ina_1, OUTPUT);  
    pinMode(MOTOR::ina_2, OUTPUT);
    pinMode(MOTOR::inb_1, OUTPUT);
    pinMode(MOTOR::inb_2, OUTPUT);
    pinMode(MOTOR::pwma, OUTPUT);
    pinMode(MOTOR::pwmb, OUTPUT);
    Serial.println("cai xong cac chan dau ra"); delay(100);
    ledcSetup(MOTOR::channela, MOTOR::freq, MOTOR::resol);
    ledcAttachPin(MOTOR::pwma, MOTOR::channela);
    ledcSetup(MOTOR::channelb, MOTOR::freq, MOTOR::resol);
    ledcAttachPin(MOTOR::pwmb, MOTOR::channelb);
    Serial.println("Configxong"); delay(300);
        timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &on_timer, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
    Serial.println("Khoi dong thanh cong timer interrput");
    delay(1000);
    //config tb6612
    Serial.println(" config dau ra motor"); delay(300);
    Serial.println("Xe da khoi dong xong"); delay(300);
}
void loop()
{
    read_command();
    motion.update();
}