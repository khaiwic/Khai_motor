#include "matrix.h"

const int row = 3;
const int colo = 3;

button Matrix_button[row][colo] = {
    {button::NONE, button::TOP, button::NONE},
    {button::LEFT, button::OK,  button::RIGHT},
    {button::NONE, button::BACK, button::NONE},
};

//pinMode
const int rows[row] = {42, 41, 40};
const int colos[colo] = {38, 37, 36};

void setupMatrix(){
    for(int r = 0; r < row; r++){
        pinMode(rows[r], OUTPUT);
        digitalWrite(rows[r], HIGH);
    }
    for(int c = 0; c < colo; c++){
        pinMode(colos[c], INPUT_PULLUP);
    }
}
button scan(){
    for(int r = 0; r < row; r++){
        digitalWrite(rows[r], LOW);
        for(int c = 0; c < colo; c++){
            if(digitalRead(colos[c]) == LOW){
                digitalWrite(rows[r], HIGH);
                return Matrix_button[r][c];
            }
        }
        digitalWrite(rows[r], HIGH);
    }
    return button::NONE;
}