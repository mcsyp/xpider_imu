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

#include "xpider_imu.h"
XpiderIMU* XpiderIMU::instance_ = NULL;


MPU6050 XpiderIMU::mpu_;
int16_t XpiderIMU::gzOffset_ = 0;
const int16_t XpiderIMU::interrupt_time_ = 10000;
float XpiderIMU::yaw = 0;
XpiderIMU::XpiderIMU() {
  
}

XpiderIMU::~XpiderIMU() {
  
}

XpiderIMU* XpiderIMU::instance() {
  if(instance_ == NULL) {
    instance_ = new XpiderIMU();
  }

  return instance_;
}

bool XpiderIMU::Initialize() {
  //Wire.begin();
  //Wire.setClock(400000);
  pinMode(SOFT_I2C_SDA, OUTPUT);
  pinMode(SOFT_I2C_SCL, OUTPUT);
  soft_i2c_init();

  mpu_.reset();
  delay(1000);//等待数据稳定
  mpu_.initialize();
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu_.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
 
  mpu_.setDLPFMode(0);
  for(int i=0;i<50;i++){
    gzOffset_ += mpu_.getRotationZ();
    delay(50);
  }
  gzOffset_ = gzOffset_/50;

  CurieTimerOne.start(interrupt_time_,InterruptHandler);
  return true;
}

void XpiderIMU::InterruptHandler() { 
  int16_t rawGz = mpu_.getRotationZ();
  float gz = (rawGz-gzOffset_)/131.0f;//单位是°/s
  gz *= 3.1415/180;//转化单位为r/s
  yaw = yaw + gz*(interrupt_time_/1000000.0f);
}

void XpiderIMU::GetYawPitchRoll(float *in_data) {
  in_data[0] = yaw;
}
