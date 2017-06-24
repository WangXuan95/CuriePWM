/*
  Author : WangXuan
  Date   : 2017/06/24
*/

#include <CuriePWM.h>

const int pin = 13;

void setup(){
    // enable CuriePWM
    CuriePWMEnableAll();
}

void loop(){

    digitalWrite(pin, LOW); // set pin to low for 0.5 seconds
    delay(500);

    CuriePWM(pin, 33);      // duty = 33% for 0.5 seconds
    delay(500);
    
    CuriePWM(pin, 66);      // duty = 66% for 0.5 seconds
    delay(500);
    
    CuriePWMStop(pin);      // Don't forget to release the pin in order to do other things.
    // CuriePWM(pin, 0);    // write duty=0 can also release the pin
    
    digitalWrite(pin, HIGH);// set pin to high for 0.5 seconds
    delay(500);
    
}