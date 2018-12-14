/*
 * CRadar.cpp
 *
 *  Created on: Oct 26, 2018
 *      Author: ominenko
 */

#include "CRadar.h"
#include <iostream>
#include <chrono>
#include <string>

using namespace std;

CRadar::CRadar(uint8_t _trig, uint8_t _echo, uint8_t _direction) :
    dir_servo(_direction, angle_min, angle_max, 103, 520) {

}

void CRadar::thread() {
  cout << "CRadar thread function e=" << angle << endl;
//hc_sr04.measure();
  if (angle_up) {
    angle += HC_SR04::MEASURING_ANGLE;
  } else {
    angle -= HC_SR04::MEASURING_ANGLE;
  }
  if (angle_min >= angle) {
    angle = angle_min;
    angle_up = true;
  }
  if (angle_max <= angle) {
    angle = angle_max;
    angle_up = false;
  }
  dir_servo.set(angle);
  std::this_thread::sleep_for(std::chrono::milliseconds(200)); //time for set servo
}

bool CRadar::start() {
  if (execute_.load(std::memory_order_acquire)) {
    stop();
  };
  execute_.store(true, std::memory_order_release);
  thd_ = std::thread([this] {
    while (execute_.load(std::memory_order_acquire)) {
      this->thread();
    }
  });
  return true;
}
void CRadar::stop() {
  execute_.store(false, std::memory_order_release);
  if (thd_.joinable())
    thd_.join();
}
