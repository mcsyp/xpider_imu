/**
 * Author: Yunpeng Song <413740951@qq.com>
 * Author: Ye Tian <flymaxty@foxmail.com>
 * Copyright (c) 2016 Maker Collider Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 */

#ifndef XPIDER_IMU_H_
#define XPIDER_IMU_H_

#include "Arduino.h"

#include "xpider_pin.h"

#include "I2Cdev.h"
#include "MPU6050.h"
#include "CurieTimerOne.h"
#include "Wire.h"

class XpiderIMU {
public:
  static XpiderIMU* instance();

  bool Initialize();
  void GetYawPitchRoll(float *in_data);

private:
  static XpiderIMU* instance_;

  static MPU6050 mpu_;
  static int16_t gzOffset_;
  const static int16_t interrupt_time_;
  static float yaw;

  XpiderIMU();
  ~XpiderIMU();

  static void InterruptHandler();
};

#endif // XPIDER_IMU_H_
