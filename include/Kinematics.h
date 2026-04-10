#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "RobotConfig.h" // Nhúng Config vào ngay sau khiên bảo vệ

namespace xung_top {
    constexpr float pi = 3.14159f;  // Thêm chữ 'f' để ép kiểu float, chạy nhanh hơn
    constexpr float cycle = robo::d * pi;
    constexpr int PPR = robo::mod * robo::per;
    constexpr int target_pos = (int)((robo::tagpos * PPR) / cycle);
}

namespace xung_re {
    // 1. Tính quãng đường bánh xe phải lăn để xoay thân xe 90 độ (pi/2)
    // S = (pivot / 2) * (pi / 2) = (pivot * pi) / 4
    constexpr float arc_length_90 = (robo::pivot * xung_top::pi) / 4.0f;

    // 2. Chuyển quãng đường đó thành số xung (dùng lại PPR và cycle ở trên)
    constexpr int target_pivot = (int)((arc_length_90 * xung_top::PPR) / xung_top::cycle);
}

#endif // KINEMATICS_H