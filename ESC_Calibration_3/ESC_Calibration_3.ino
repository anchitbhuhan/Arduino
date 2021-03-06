/* ESCcalibrator.ino
The ESCs used in the ROV will need to be calibrated to the Arduino
output signals.  For most ESCs the method of programming them is
to put the transmitter to maximum throttle, turn on the ESC and
wait for it to signal that it has the maximum setting calibrated,
then put the throttle to minimum and wait for the ESC to signal
that it has the minimum setting calibrated.
This sketch will provide the throttle motions and signal the shift
to the low setting by flashing a red LED.  A flashing green LED
will signal the end of the process.

The connections are:
7.6V onto the ESC when needed.
Servo control pin for ESC on Arduino pin D9
Red LED on Pin 13
Green LED on Pin 12

*/

#include <Servo.h>
Servo ESC;  //Servo object called "ESC"
int throttle = 0;  //Variable for the throttle setting.
//const int grnLEDpin = 12;
const int redLEDpin = LED_BUILTIN;


void setup()
{
//  pinMode(grnLEDpin,OUTPUT);
  pinMode(redLEDpin,OUTPUT);
  ESC.attach(A3,600,2250); //attach the ESC to pin 9
  //Due to problems with the ESC recognising the maximum
  //position at the default settings, the figures after
  //the pin number are the microsecond signals for the 
  //minimum and maximum that the ESC will recognise.
  // 600 and 2250 work.
  throttle = 180;  //Set the throttle to maximum
  ESC.write(throttle); //Set the ESC signal to maximum
  //At this point the ESC's power should be connected.
  delay(10000);  //Allow the user time to connect the battery to
  //the ESC.  
  redBlink();  //Jump to the Blinking red LED subroutine
  throttle = 0;  //Set the throttle to zero
  ESC.write(throttle);  //Set the ESC signal to the zero position.
  delay(10000);  // allow a 10 second delay for the ESC to signal
  //that it is done.
  throttle = 90;  //Set throttle to the neutral position.
  ESC.write(throttle);
  delay(10000);   //The ESC should now be calibrated.
}

void loop()
{
  //Blink the green LED to signal end of process
//  digitalWrite(grnLEDpin, HIGH);
//  delay(1000);
//  digitalWrite(grnLEDpin, LOW);
//  delay(1000);
}

void redBlink()
{
  //Blink the redLED to signal the imminent move to the
  //low throttle setting.
  for(int i = 1; i < 6; i++)  //do the sequence for 10 seconds.
  {
    digitalWrite(redLEDpin, HIGH);
    delay(1000);
    digitalWrite(redLEDpin, LOW);
    delay(1000);
  }
}
