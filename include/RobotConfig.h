#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

enum class control{
    TOP,
    BACK,
    LEFT,
    RIGHT,
    NONE,
    FINISH,
    STOP,
    OK
};

namespace robo{
    //mode xung và bánh xe
    constexpr int volts = 8; // volt cap cho Vm
    constexpr int RPM = 100; // round per minutes
    constexpr int mod = 14; //change
    constexpr int per = 298;
    constexpr float d = 43;  //mm
    //Mục điều chỉnh Mục tiêu
    constexpr float tagpos = 200; //mm
    //Xoay
    constexpr float pivot = 225;
}
#endif