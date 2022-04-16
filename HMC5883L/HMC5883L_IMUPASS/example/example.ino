/*
  HMC5883L Triple Axis Digital Compass + MPU6050 (GY-86 / GY-87). Compass Example.
  Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-magnetometr-hmc5883l.html
  GIT: https://github.com/jarzebski/Arduino-HMC5883L
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <HMC5883L.h>
#include <MPU6050.h>

HMC5883L compass;
MPU6050 mpu;

void setup()
{
  Serial.begin(115200);

  // If you have GY-86 or GY-87 module.
  // To access HMC5883L you need to disable the I2C Master Mode and Sleep Mode, and enable I2C Bypass Mode

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  mpu.setI2CMasterModeEnabled(false);
  mpu.setI2CBypassEnabled(true) ;
  mpu.setSleepEnabled(false);

 compass.begin() ;


}

void loop()
{
  Vector C;
  Vector norm = compass.readNormalize();

    Vector h_b;
    h_b.XAxis = norm.XAxis - compass.B[0];
    h_b.YAxis = norm.YAxis - compass.B[1];
    h_b.ZAxis = norm.ZAxis - compass.B[2];
    
    C.XAxis = compass.A[0][0]*h_b.XAxis + compass.A[0][1]*h_b.YAxis +  compass.A[0][2]*h_b.ZAxis;
    C.YAxis = compass.A[1][0]*h_b.XAxis + compass.A[1][1]*h_b.YAxis +  compass.A[1][2]*h_b.ZAxis;
    C.ZAxis = compass.A[2][0]*h_b.XAxis + compass.A[2][1]*h_b.YAxis +  compass.A[2][2]*h_b.ZAxis;
    
    Serial.print(C.XAxis, 6);
    Serial.print(",");
    Serial.print(C.YAxis, 6);
    Serial.print(",");
    Serial.println(C.ZAxis, 6);

}
