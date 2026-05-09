#include <Arduino.h>
#include "PinConfig.h"
#include "Kinematics.h"
#include "RobotConfig.h"
#include "pid.h"
#include "read_command.h"

//KHAI BAO TIMER  PID

hw_timer_t *timer = NULL;
portMUX_TYPE timeMUX = portMUX_INITIALIZER_UNLOCKED;

pid myPidController;
void IRAM_ATTR on_timer()
{
    myPidController.resolve_pid();
}
/*
Doc cac gia tri cua nut nhan sau do truyen vao trajectory planning*/
/*
// --- 1. BIẾN QUẢN LÝ MẢNG LỆNH ---
const int MAX_CMDS = 50;
control command_buffer[MAX_CMDS]; 
int total_commands = 0;       // Tổng số lệnh đã ghi
int current_cmd_idx = 0;      // Đang chạy đến lệnh thứ mấy? (Thay thế cho vòng lặp for)

// --- 2. BIẾN GIAO TIẾP GIỮA QUY HOẠCH VÀ PID ---
volatile float target_speed_L = 0; // Tốc độ mong muốn tính từ quỹ đạo hình thang
volatile float target_speed_R = 0;

// Trạng thái của lệnh hiện tại (Đang chạy hay đã xong?)
bool is_command_finished = true;
*/
/*
void process_trajectory() {
    // Nếu đã chạy hết mảng lệnh thì dừng lại
    if (current_cmd_idx >= total_commands) {
        target_speed_L = 0;
        target_speed_R = 0;
        return; 
    }

    // Nếu vừa bắt đầu một lệnh mới
    if (is_command_finished) {
        control current_cmd = command_buffer[current_cmd_idx];
        
        // Khởi tạo các thông số hình thang cho lệnh này (Reset quãng đường, đặt mục tiêu)
        setup_trapezoidal_profile(current_cmd); 
        is_command_finished = false;
        Serial.print("Dang chay lenh thu: ");
        Serial.println(current_cmd_idx);
    }

    // LIÊN TỤC TÍNH TOÁN QUỸ ĐẠO HÌNH THANG CHO LỆNH HIỆN TẠI
    // Hàm này sẽ cập nhật biến target_speed_L và target_speed_R thay đổi theo thời gian
    update_trapezoidal_velocity();

    // Kiểm tra xem đã đi đủ quãng đường chưa? (Tích phân vận tốc hoặc dựa vào số xung)
    if (check_distance_reached()) {
        // ĐÃ XONG LỆNH HIỆN TẠI!
        is_command_finished = true;
        current_cmd_idx++; // CHUYỂN SANG LỆNH TIẾP THEO (Đây chính là cách thay thế vòng for!)
        
        // Dừng xe 1 chút giữa các lệnh (Tùy chọn)
        target_speed_L = 0; target_speed_R = 0;
        delay(200); 
    }
}*/
/*
// Hàm này được gọi tự động bởi Timer Interrupt (VD: 10ms/lần)
void timer_interrupt_handler() {
    // 1. Đọc xung từ Encoder
    long current_speed_L = get_pulse_L();
    long current_speed_R = get_pulse_R();
    reset_pulses();

    // 2. Tính sai số (Error = Vận tốc quy hoạch - Vận tốc thực)
    // Lưu ý: target_speed lúc này đang tạo ra hình thang
    float error_L = target_speed_L - current_speed_L;
    float error_R = target_speed_R - current_speed_R;

    // 3. Tính toán PID
    int pwm_L = calculate_PID_L(error_L);
    int pwm_R = calculate_PID_R(error_R);

    // 4. Xuất PWM
    drive_motors(pwm_L, pwm_R);
}*/
/*
void loop() {
    // 1. Nếu người dùng đang ấn nút, lưu vào mảng (record mode)
    if (state_curr == RECORD) {
        read_buttons_to_array();
    }
    
    // 2. Nếu đang chạy tự động, xử lý mảng bằng hàm quy hoạch (playing mode)
    if (state_curr == PLAYING) {
        process_trajectory(); // Liên tục xử lý index và hình thang
    }
}*/
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