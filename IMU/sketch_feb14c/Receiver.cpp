#include "Receiver.h"
#include <Wire.h>


int Receiver::readRegister16(byte reg)
{
    int value;
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(reg);

    Wire.endTransmission();

    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.requestFrom(MPU6050_ADDRESS, 2);
    while(!Wire.available()) {};
    byte vha = Wire.read();
    byte vla = Wire.read();
    Wire.endTransmission();

    value = vha << 8 | vla;

    return value;
}
