# CuriePWM for Arduino101 / CurieNano

# Description

Use Timer1 on Curie to PWM on any pins,this library can't work together with CurieTimerOne or Servo library.

# Usage

1. clone this repo

2. move CuriePWM Directory to [Arduino Directory]/libraries

3. In Arduino IDE, open an example in file->examples->CuriePWM

4. just run it!

# API Description

### 1. Enable all PWMs.

void CuriePWMEnableAll();

### 2. Disable all PWMs.

void CuriePWMDisableAll();

### 3. Function: set PWM duty(0~100) on one pin

void CuriePWM(unsigned char pin, unsigned int duty);

### 4. Stop PWM on one pin, and set it LOW

void CuriePWMStop(unsigned char pin);