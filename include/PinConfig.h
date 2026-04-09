#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H
namespace ENCODER{
    constexpr int encoder_1A = 18;
    constexpr int encoder_1B = 8;
    constexpr int encoder_2A = 17;
    constexpr int encoder_2B = 16;

}
namespace GOAL{
    constexpr int pin = 0;
    constexpr int buzz = 0;
}
namespace MATRIX{
    constexpr int row = 3;
    constexpr int colo = 3;
    constexpr int rows[row] = {42, 41, 40};
    constexpr int colos[colo] = {38, 37, 36};

}
namespace CONTR{
    // Hệ số PD Bánh A
    constexpr float Kp_A_P = 4;
    constexpr float Kd_A_P = 0.01;
    //Hệ số PI Bánh A
    constexpr float Kp_A_V = 2;
    constexpr float Ki_A_V = 0.02;

    //Hệ số PD Bánh B
    constexpr float Kp_B_P = 4;
    constexpr float Kd_B_P = 0.01;
    // Hệ số PI Bánh B
    constexpr float Kp_B_V = 2;
    constexpr float Ki_B_V = 0.02;
}
namespace MOTOR{
    //setting
    constexpr int resol = 10;
    constexpr int freq = 20000;
    //config pinMode MotorA
    constexpr int pwma = 0;     
    constexpr int ina_1 = 0;
    constexpr int ina_2 = 0;

    //config pinMode MotorB
    constexpr int pwmb = 0;
    constexpr int inb_1 = 0;
    constexpr int inb_2 = 0;
}
#endif