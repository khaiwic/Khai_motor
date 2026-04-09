#ifndef KINEMATICS_H
#include "RobotConfig.h"
#define KINEMATICS_H

namespace xung_top{
    constexpr float pi = 3.14159;
    constexpr float cycle = robo::d * pi;
    constexpr int PPR = robo::mod * robo::per;
    constexpr int target_pos = (int)((robo::tagpos * PPR) / cycle);
}
namespace xung_re{
    constexpr int target_pivot = (int)(robo::pivot / 2);
}
#endif