/*
 * Bas on Tech - VOLTAGE SENSOR
 * This course is part of the courses on https://arduino-tutorials.net
 *  
 * (c) Copyright 2019 - Bas van Dijk / Bas on Tech
 * This code and course is copyrighted. It is not allowed to use these courses commercially
 * without explicit written approval
 * 
 * YouTube:    https://www.youtube.com/c/BasOnTech
 * Facebook:   https://www.facebook.com/BasOnTechChannel
 * Instagram:  https://www.instagram.com/BasOnTech
 * Twitter:    https://twitter.com/BasOnTech
 *
 * ---------------------------------------------------------------------------
 *  
 * PIN CONNECTIONS SENSOR
 * 
 * S --> A3  green
 * + --> 5V  red
 * - --> GND blue
 * 
 * Calculate exact values with multimeter:
 * 
 * Vin on adapter = 10.05V
 * Vout on Arduino = 2.42
 * 5V on Arduino = 5.10V
 * 
 * Vin / vOut = factor
 * 12.41 / 2.42 = 5.128
 * 
 */

const int voltageSensorPin = A7;          // sensor pin
float vIn;                                // measured voltage (3.3V = max. 16.5V, 5V = max 25V)
float vOut;
float voltageSensorVal = .0f;                   // value on pin A3 (0 - 1023)
const float factor = 5.024;               // reduction factor of the Voltage Sensor shield
const float vCC = 5.00;                   // Arduino input voltage (measurable by voltmeter)

void setup() {
  Serial.begin(9600);
  pinMode(A3, INPUT);
//  analogReference(EXTERNAL);
}

void loop() {

  voltageSensorVal = analogRead(voltageSensorPin);    // read the current sensor value (0 - 1023) 
  vOut = (voltageSensorVal / 1024) * vCC;             // convert the value to the real voltage on the analog pin
  vIn =  vOut * factor;                               // convert the voltage on the source by multiplying with the factor

//Serial.print("Vooy = ");             
//  Serial.print(vOut);
//  Serial.println("V");

  Serial.print("Voltage = ");             
  Serial.print(vIn);
  Serial.println("V");

  delay(1000);
}
