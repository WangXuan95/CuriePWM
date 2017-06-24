/*
  Author : WangXuan
  Date   : 2017/06/24
  Description: Use Timer1 on Curie to PWM on any pins
               this library can't work together with CurieTimerOne or Servo library
*/

#include <Arduino.h>
#include <aux_regs.h>
#include <interrupt.h>
#include <conf.h>
#include "CuriePWM.h"

// TIMERx_CONTROL register.
const unsigned int ARC_TIMER_EN_INTR_BIT_FLAG = 0x01;        // Bit 0. Enable timer interrupt.
const unsigned int ARC_TIMER_NON_HALT_ONLY_BIT_FLAG = 0x02;  // Bit 1. Allow timer to run in Halted mode.
const unsigned int ARC_TIMER_WATCHDOG_BIT_FLAG = 0x04;       // Bit 2. Make timer a watchdog timer.
const unsigned int ARC_TIMER_INTR_PENDING_BIT_FLAG = 0x08;   // Bit 3. Interrupt pending and clearing bit.

unsigned int timerCountAddr =   ARC_V2_TMR1_COUNT;
unsigned int timerControlAddr = ARC_V2_TMR1_CONTROL;
unsigned int timerLimitAddr =   ARC_V2_TMR1_LIMIT;
unsigned int timerIrqNum =      ARCV2_IRQ_TIMER1;

void timerIrqFunc();

#define DUTY_PERIOD  100
#define UNIT_COUNT   500

#define  PIN_CNT_MAX  20
unsigned int  currentPin = 0;
unsigned int  pinCnt  = 1;

unsigned char pins[PIN_CNT_MAX] = {(unsigned char)0xff};
unsigned int dutys[PIN_CNT_MAX] = {DUTY_PERIOD};

inline void startCount(unsigned int cnt){
    aux_reg_write(timerLimitAddr, cnt);
    aux_reg_write(timerCountAddr, 0);
    aux_reg_write(timerControlAddr, ARC_TIMER_EN_INTR_BIT_FLAG | ARC_TIMER_NON_HALT_ONLY_BIT_FLAG);
}

void CuriePWMEnableAll(){
    aux_reg_write(timerControlAddr, 0);
    interrupt_disable(timerIrqNum);                 // Disable Timer at controller
    interrupt_connect(timerIrqNum, &timerIrqFunc);  // 加载中断向量
    interrupt_enable(timerIrqNum);
    startCount(UNIT_COUNT);
}

void CuriePWMDisableAll(){
    aux_reg_write(timerControlAddr, 0);
    interrupt_disable(timerIrqNum);                 // Disable Timer at controller
}

void printPins(){  // debug print pins
    Serial.print('('); Serial.print(pinCnt); Serial.print(')');
    for(unsigned int i=0; i<pinCnt; i++){
        Serial.print("   ");Serial.print(pins[i]);Serial.print(':'); Serial.print(dutys[i]); 
    }
    Serial.println();
}

void addPin(unsigned char pin, unsigned int duty){
    unsigned int i,j;
    for(i=0; i<pinCnt && dutys[i]<duty; i++);
    for(j=pinCnt; j>i; j--){
        pins[j]  = pins[j-1];
        dutys[j] = dutys[j-1];
    }
    pins[i]  = pin;
    dutys[i] = duty;
    pinCnt++;
}

void deletePin(unsigned char pin){
    unsigned int i,j;
    for(i=0; i<pinCnt && pin!=pins[i]; i++);
    if(i<pinCnt){
        for(j=i; j<pinCnt; j++){
            pins[j]  = pins[j+1];
            dutys[j] = dutys[j+1];
        }
        pinCnt--;
    }
}

void CuriePWM(unsigned char pin, unsigned int duty){
    if(pin>=PIN_CNT_MAX)
        return;
    deletePin(pin);
    pinMode(pin, OUTPUT);
    if(duty<=0){
        digitalWrite(pin, LOW);
    }else if(duty>=DUTY_PERIOD){
        digitalWrite(pin, HIGH);
    }else{
        addPin(pin, duty);
    }
}

void CuriePWMStop(unsigned char pin){
    CuriePWM(pin, 0);
}

void timerIrqFunc(){
    unsigned int nextDuty;
    if( currentPin >= (pinCnt-1) ){
        currentPin = 0;
        for(unsigned int i=0; i<pinCnt-1; i++){
            digitalWrite(pins[i], HIGH);
        }
        nextDuty = dutys[0];
    }else{
        unsigned int currentDuty = dutys[currentPin];
        for(;dutys[currentPin]==currentDuty;currentPin++){
            digitalWrite(pins[currentPin], LOW);
        }
        nextDuty = dutys[currentPin]-currentDuty;
    }
    if(nextDuty<=0)
        nextDuty = 1;
    startCount(nextDuty * UNIT_COUNT);
    unsigned int reg = aux_reg_read(timerControlAddr) & ~ARC_TIMER_INTR_PENDING_BIT_FLAG;
    aux_reg_write(timerControlAddr, reg);
}


