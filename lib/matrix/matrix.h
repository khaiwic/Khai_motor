#ifndef MATRIX_H
#define MATRIX_H
#include "PinConfig.h"
#include "Kinematics.h"
#include "RobotConfig.h"

//dung analog de doc gia tri nut nhat
class matrix{
private:
    int _pin;
public:
    control route[123];
    int8_t step = 0;
    unsigned long time_pre = 0;
    matrix();
    void initmatrix();
    control read_analog_matrix(); 
};
#endif