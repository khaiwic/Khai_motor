//cơ bản là đã xong
#include "motor.h"
//motorA
const int pwma = 9;
const int ina_1 = 10;
const int ina_2 = 11;

//motorB
const int pwmb = 12;
const int inb_1 = 14; 
const int inb_2 = 13; 

volatile int encoderA_values = 0;
volatile int encoderB_values = 0;
//he thong
#define freq 20000
#define resolution 10

//setupMotor
void initMotor(){  
    //MotorA
    pinMode(ina_1, OUTPUT);
    pinMode(ina_2, OUTPUT);
    ledcAttach(pwma, freq, resolution);
    
    //MotorB
    pinMode(inb_1, OUTPUT);
    pinMode(inb_2, OUTPUT);
    ledcAttach(pwmb, freq, resolution);
}
//setupEncoder
void initEncoder(){
    pinMode(encoder_1A, INPUT_PULLUP);
    pinMode(encoder_1B, INPUT_PULLUP);
    pinMode(encoder_2A, INPUT_PULLUP);
    pinMode(encoder_2B, INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(encoder_1A), positionA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoder_2A), positionB, CHANGE);
}
//interrupt encoder A
void IRAM_ATTR positionA(){
    int A = digitalRead(encoder_1A);
    int B = digitalRead(encoder_1B);
    if((A == HIGH) != (B == LOW)){
        encoderA_values --;
    }
    else{
        encoderA_values ++;
    }
}
//interrupt encoder B
void IRAM_ATTR positionB(){
    int A = digitalRead(encoder_2A);
    int B = digitalRead(encoder_2B);
    if((A == HIGH) != (B == LOW)){
        encoderB_values ++;
    }
    else{
        encoderB_values --;
    }
}
//reset
void reset(){
    encoderA_values = 0;
    encoderB_values = 0;
}
//receive speed
void go(control next, int speedA, int speedB) {
    // 1. NẾU LỆNH LÀ STOP -> CẮT ĐIỆN TOÀN BỘ NGAY LẬP TỨC
    if (next == control::STOP) {
        digitalWrite(ina_1, LOW); digitalWrite(ina_2, LOW);
        digitalWrite(inb_1, LOW); digitalWrite(inb_2, LOW);
        ledcWrite(pwma, 0);
        ledcWrite(pwmb, 0);
        return; // Thoát hàm luôn
    }

    // 2. KHI ĐANG CHẠY -> ĐỂ CHO TOÁN HỌC (DẤU CỦA SPEED) QUYẾT ĐỊNH HƯỚNG

    // ================= XỬ LÝ BÁNH A =================
    if (speedA > 0) {
        digitalWrite(ina_1, HIGH); digitalWrite(ina_2, LOW); // Tới
    } 
    else if (speedA < 0) {
        digitalWrite(ina_1, LOW); digitalWrite(ina_2, HIGH); // Lùi
    } 
    else {
        digitalWrite(ina_1, LOW); digitalWrite(ina_2, LOW);  // Phanh mềm
    }
    
    // Lấy trị tuyệt đối để băm xung (vì ledcWrite không hiểu số âm)
    int pwm_A = abs(speedA);
    if (pwm_A > 1023) pwm_A = 1023; // Ép giới hạn sức mạnh phần cứng
    ledcWrite(pwma, pwm_A);


    // ================= XỬ LÝ BÁNH B =================
    if (speedB > 0) {
        digitalWrite(inb_1, HIGH); digitalWrite(inb_2, LOW); // Tới
    } 
    else if (speedB < 0) {
        digitalWrite(inb_1, LOW); digitalWrite(inb_2, HIGH); // Lùi
    } 
    else {
        digitalWrite(inb_1, LOW); digitalWrite(inb_2, LOW);  // Phanh mềm
    }
    
    int pwm_B = abs(speedB);
    if (pwm_B > 1023) pwm_B = 1023; 
    ledcWrite(pwmb, pwm_B);
}