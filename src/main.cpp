#include <Arduino.h>
#include "PinConfig.h"
#include "Kinematics.h"
#include "RobotConfig.h"

void setup(){
    Serial.begin(115200);
    delay(3000);
    Serial.println("Khoi dong xong Serial");
}
void loop(){
    vTaskDelete(NULL);
}