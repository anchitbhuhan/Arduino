#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Receiver.h"
//#include <utility/imumaths.h>

#define SAMPLE_RATE (100)

Receiver recv;

float temp = 0;
void setup() {
    Wire.begin();
    Wire.setClock(400000); // set I2C 'full-speed'
    Serial.begin(9600);
    

}

void loop() {

   float temp = recv.readRegister16(MPU6050_REG_TEMP_OUT_H);

    
   float tempC = temp/340 + 36.53;
   Serial.print(" Temp = ");
   Serial.print(tempC);
   Serial.println(" *C");
   delay(1000);
}
