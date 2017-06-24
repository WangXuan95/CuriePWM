/*
  Author : WangXuan
  Date   : 2017/06/24
*/

#include <CuriePWM.h>

const int blinkPin = 13;

void setup(){
    Serial.begin(9600);
    CuriePWMEnableAll();
}

void loop(){
    Serial.println("PWM blink: low->high duty cycle");
    for(int i=0; i<=100; i+=3){
        CuriePWM(blinkPin, i);
        delay(50);
    }
    Serial.println("PWM blink: high->low duty cycle");
    for(int i=100; i>=0; i-=3){
        CuriePWM(blinkPin, i);
        delay(50);
    }
}