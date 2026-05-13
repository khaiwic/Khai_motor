#ifndef MATRIX_H
#define MATRIX_H
#include "PinConfig.h"
#include "Kinematics.h"
#include "RobotConfig.h"

//dung analog de doc gia tri nut nhat
class matrix{
private:
    int _pin;
    control _last_raw_button = control::NONE;
    unsigned long _last_change_ms = 0;
    bool _waiting_release = false;

    static constexpr int READ_SAMPLES = 8;
    static constexpr unsigned long DEBOUNCE_MS = 60;

    int read_filtered_analog();
    control classify_analog(int value);
public:
    control route[123];
    int8_t step = 0;
    unsigned long time_pre = 0;
    matrix();
    void initmatrix();
    control read_analog_matrix(); 
};
#endif
