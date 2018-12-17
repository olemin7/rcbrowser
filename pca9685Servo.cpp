/*
 * ServoCamera.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: ominenko
 */

#include "pca9685Servo.h"
#ifndef _SIMULATION_
#include <wiringPi.h>
#include "pca9685.h"
#endif
#include <iostream>
#include <string>
#include <mutex>

std::mutex mu;

pca9685_Servo::pca9685_Servo(uint8_t _pin) :
    pin_(_pin), minVal(0), maxVal(100), minPulse(0), maxPulse(2.5 * (50.0f * maxPWM / 1000))
{
}

pca9685_Servo::pca9685_Servo(uint8_t _pin, int16_t _minVal, int16_t _maxVal, uint16_t _minPulse, uint16_t _maxPulse):
    pin_(_pin), minVal(_minVal), maxVal(_maxVal), minPulse(_minPulse), maxPulse(_maxPulse)
{
}
void pca9685_Servo::init(int16_t init_val) {
  set(init_val);
}

void pca9685_Servo::set(int16_t val) {
  std::lock_guard<std::mutex> guard(mu);
  if (val <= minVal) {
    val = minVal;
  }
  if (val >= maxVal) {
    val = maxVal;
  }
  set_PWM(minPulse + static_cast<int32_t>(maxPulse - minPulse) * (val - minVal) / (maxVal - minVal));
}

void pca9685_Servo::set_PWM(uint8_t pin, uint16_t pulse) {

  if (maxPWM < pulse) {
    pulse = maxPWM;
  }
#ifdef LOG_INFO
  std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ")  pca[" << static_cast<int>(pin) << "]="
      << pulse << std::endl;
#endif
#ifndef _SIMULATION_
  pwmWrite(300 + pin, pulse);
#endif
}
//endif;
