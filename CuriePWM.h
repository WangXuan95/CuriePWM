/*
  Author : WangXuan
  Date   : 2017/06/24
  Description: Use Timer1 on Curie to PWM on any pins
               this library can't work together with CurieTimerOne or Servo library
*/

#ifndef _CURIE_PWM_H_
#define _CURIE_PWM_H_

// Enable all PWMs.
void CuriePWMEnableAll();

// Disable all PWMs.
void CuriePWMDisableAll();

// Function: set PWM duty on one pin
// Parameter description:
//     pin:  PWM pin
//     duty: PWM duty, value 0~100
void CuriePWM(unsigned char pin, unsigned int duty);

// Function: stop PWM on one pin, and set it LOW
//           release this pin from PWM, in order to do other things.
void CuriePWMStop(unsigned char pin);

#endif
