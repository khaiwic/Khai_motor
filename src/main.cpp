#include "motor.h"
#include "control.h"
#include "matrix.h"

#define time_push 3000
#define space 100

unsigned long push_previous = 0;

enum State{IDLE, RECORD, PLAYING, ERROR};

button route[100];
int step = 0;
State current_state = IDLE;

void Task_1(void *parameter){
    while(1){
        button command = scan();
        unsigned long push_current = millis();
        
        if(command != button::NONE){
            if(push_current - push_previous > time_push){
                current_state = ERROR;
                Serial.println("Now: Error");
                vTaskDelay(100 / portTICK_PERIOD_MS);
            }
            push_previous = push_current;
        }

        if(command != button::NONE){    
            
            vTaskDelay(20 / portTICK_PERIOD_MS);
            
            if(scan() == command) { 
                
                switch(current_state){
                    case IDLE:
                        if(command == button::OK){
                            current_state = RECORD;
                            Serial.println("Now: RECORD");
                        }
                        break;
                        
                    case RECORD:
                        if(command == button::OK){
                            current_state = PLAYING;
                            Serial.println("Now: PLAYING");
                        } 
                        else { 
                            if(step > 0){
                                button step_previous = route[step - 1];
                                if( (step_previous == button::TOP && command == button::BACK) ||
                                    (step_previous == button::BACK && command == button::TOP) ||
                                    (step_previous == button::RIGHT && command == button::LEFT) ||
                                    (step_previous == button::LEFT && command == button::RIGHT) )
                                {
                                    current_state = ERROR;
                                    Serial.println("Now: ERROR");
                                    vTaskDelay(100 / portTICK_PERIOD_MS); 
                                    break; // Thoát case
                                }
                            }
                            
                            if(step < 100){
                                route[step] = command; 
                                
                                // SỬA Ở ĐÂY: In ra màn hình chuẩn C++
                                Serial.print("Buoc so "); Serial.println(step);
                                Serial.print("Di "); Serial.println((int)command);
                                
                                step++;
                            }
                        }
                        break; 
                        
                    case ERROR:
                        if(command == button::OK){
                            step = 0;
                            current_state = IDLE;
                            Serial.println("Now: IDLE");
                        }
                        break;
                        
                    case PLAYING:
                        break;
                }

                while(scan() != button::NONE) {
                    vTaskDelay(20 / portTICK_PERIOD_MS);
                }
            }
        }
        if (current_state == PLAYING) {

            step = 0;
            current_state = IDLE;
            Serial.println("Now: IDLE");
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
}

void setup(){
    Serial.begin(115200);
    Serial.println("Start NOW:");
    xTaskCreatePinnedToCore(
        Task_1,
        "Matrix_Button_Scan", 
        2048,
        NULL,
        1,
        NULL,
        1
    );
    setupMatrix();
    initMotor();
}
void loop(){

}