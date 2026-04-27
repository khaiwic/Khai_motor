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
    matrix();
    void initmatrix();
    void read_analog_matrix(); 
};
#endif