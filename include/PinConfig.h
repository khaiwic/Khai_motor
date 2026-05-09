#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H
namespace ENCODER
{
    constexpr int encoder_1A = 18;
    constexpr int encoder_1B = 8;
    constexpr int encoder_2A = 17;
    constexpr int encoder_2B = 16;

}
namespace GOAL
{
    constexpr int pin = 1;
    constexpr int buzz = 2;
}
namespace MATRIX
{
    constexpr int analog_button = 0;
}
namespace MOTOR
{
    // setting
    constexpr int resol = 10;
    constexpr int freq = 20000;
    // config pinMode MotorA
    constexpr int pwma = 9;
    constexpr int ina_1 = 10;
    constexpr int ina_2 = 11;

    // config pinMode MotorB
    constexpr int pwmb = 12;
    constexpr int inb_1 = 14;
    constexpr int inb_2 = 13;
}
#endif