/******************************************************************************
arduino_mpu9250_i2c.cpp - MPU-9250 Digital Motion Processor Arduino Library 
Jim Lindblom @ SparkFun Electronics
original creation date: November 23, 2016
https://github.com/sparkfun/SparkFun_MPU9250_DMP_Arduino_Library

This library implements motion processing functions of Invensense's MPU-9250.
It is based on their Emedded MotionDriver 6.12 library.
	https://www.invensense.com/developers/software-downloads/

Development environment specifics:
Arduino IDE 1.6.12
SparkFun 9DoF Razor IMU M0

Supported Platforms:
- ATSAMD21 (Arduino Zero, SparkFun SAMD21 Breakouts)
******************************************************************************/
#include "arduino_mpu9250_i2c.h"
#ifndef _SIMULATION_
#include <sys/ioctl.h>
#include <asm/ioctl.h>
#include <linux/i2c-dev.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

static int _fd = -1;
static bool init(unsigned char slave_addr)
{
    if (-1 == _fd)
    {
        _fd = wiringPiI2CSetup(slave_addr);
    }
    return (_fd != -1);
}

int arduino_i2c_write(unsigned char slave_addr, unsigned char reg_addr,
        unsigned char length, unsigned char *data)
{
    if (false == init(slave_addr))
    {
        return -1;
    }

    return i2c_smbus_write_i2c_block_data(_fd, slave_addr, length, data);
}

int arduino_i2c_read(unsigned char slave_addr, unsigned char reg_addr,
        unsigned char length, unsigned char *data)
{
    if (false == init(slave_addr))
    {
        return -1;
    }

    return i2c_smbus_read_i2c_block_data(_fd, reg_addr, length, data);
}

#else
int arduino_i2c_write(unsigned char slave_addr, unsigned char reg_addr,
                       unsigned char length, unsigned char * data)
{
//    Wire.beginTransmission(slave_addr);
//    Wire.write(reg_addr);
//    for (unsigned char i = 0; i < length; i++)
//    {
//        Wire.write(data[i]);
//    }
//    Wire.endTransmission(true);
//
    return 0;
}

int arduino_i2c_read(unsigned char slave_addr, unsigned char reg_addr,
                       unsigned char length, unsigned char * data)
{
//    Wire.beginTransmission(slave_addr);
//    Wire.write(reg_addr);
//    Wire.endTransmission(false);
//    Wire.requestFrom(slave_addr, length);
//    for (unsigned char i = 0; i < length; i++)
//    {
//        data[i] = Wire.read();
//    }
//
    return 0;
}


#endif

