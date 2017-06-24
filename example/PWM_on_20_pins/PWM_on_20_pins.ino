/*
  Author : WangXuan
  Date   : 2017/06/24
*/

#include <CuriePWM.h>

void setup(){

    // pin 0: duty  0%
    // pin 1: duty  5%
    // pin 2: duty 10%
    // pin 3: duty 15%
    // ......
    for(int i=0;i<20;i++){
        CuriePWM(i,5*i);
    }
    
    CuriePWMEnableAll();
}

void loop(){
}
