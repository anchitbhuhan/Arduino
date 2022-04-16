// C++ code
//
#include <Servo.h>

Servo ESC;     // create servo object to control the ESC


int VoltPin = A1;
int motorAnalog = A2;
int readVal = 0;
float V2;
int waitT = 250;
String msg2 = "Motor PWM is: ";
String msg1 = "readVal is: ";
int motorSpeed;
void setup()
{
  
  Serial.begin(9600);
  ESC.attach(A2,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
}

void loop()
{
  readVal = analogRead(VoltPin);

  Serial.print("readVal = ");
  Serial.print(readVal);
    
   motorSpeed = map(readVal, 110,1023, 0, 150);
   if(motorSpeed < 0)
        motorSpeed = 0;
  Serial.print("  motorSpeed = ");
  Serial.println(motorSpeed);
  delay(waitT);

   ESC.write(motorSpeed);    // Send the signal to the ESC
}
