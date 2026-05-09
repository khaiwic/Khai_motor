#include <Arduino.h>
#include "PinConfig.h"
#include "Kinematics.h"
#include "RobotConfig.h"
#include "pid.h"
#include "read_command.h"

hw_timer_t *timer = NULL;
portMUX_TYPE timeMUX = portMUX_INITIALIZER_UNLOCKED;

pid myPidController;
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
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &on_timer, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
    Serial.println("Khoi dong thanh cong timer interrput");
    delay(1000);
}
void loop()
{
    read_command();
}