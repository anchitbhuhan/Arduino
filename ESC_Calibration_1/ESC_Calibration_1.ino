#include <Servo.h>



#define MAX_SIGNAL 2000

#define MIN_SIGNAL 1000

#define MOTOR_PIN1 A0
#define MOTOR_PIN2 A1
#define MOTOR_PIN3 A2
#define MOTOR_PIN4 A3

int DELAY = 1000;



Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;



void setup() {

  Serial.begin(9600);

  Serial.println("ESC calibration process");

  Serial.println(" ");

  delay(1500);

  Serial.println("Starting...");

  delay(1000);

  Serial.println("Alert! Motor will start spinning!");



  motor1.attach(MOTOR_PIN1);
  motor2.attach(MOTOR_PIN2);
  motor3.attach(MOTOR_PIN3);
  motor4.attach(MOTOR_PIN4);



  Serial.print("Now writing maximum output: (");Serial.print(MAX_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");

  Serial.println("Make sure power is connected to ESC, wait for 2 seconds and press any key.");

  motor1.writeMicroseconds(MAX_SIGNAL);
  motor2.writeMicroseconds(MAX_SIGNAL);
  motor3.writeMicroseconds(MAX_SIGNAL);
  motor4.writeMicroseconds(MAX_SIGNAL);



  // Wait for input

  while (!Serial.available());

  Serial.read();



  // Send min output

  Serial.println("\n");

  Serial.println("\n");

  Serial.print("Sending minimum output: (");Serial.print(MIN_SIGNAL);Serial.print(" us)");Serial.print("\n");

  motor1.writeMicroseconds(MIN_SIGNAL);
  motor2.writeMicroseconds(MIN_SIGNAL);
  motor3.writeMicroseconds(MIN_SIGNAL);
  motor4.writeMicroseconds(MIN_SIGNAL);

  Serial.println("ESC finished calibrating");

  Serial.println("----");

  Serial.println("Type any value between 1000 and 2000 and press enter");

  Serial.println("and the motor will start spinning!!!!");

  Serial.println("Sending 1000 will stop the motor and 2000 will make the motor spin to maximum speed");



}



void loop() {

   

  if (Serial.available() > 0)

  {

    int DELAY = Serial.parseInt();

    if (DELAY > 999)

    {

      

      motor1.writeMicroseconds(DELAY);
      motor2.writeMicroseconds(DELAY);
      motor3.writeMicroseconds(DELAY);
      motor4.writeMicroseconds(DELAY);

      float SPEED = (DELAY-1000)/10;

      Serial.print("\n");

      Serial.println("Motor speed:"); Serial.print("  "); Serial.print(SPEED); Serial.print("%"); 

    }     

  }

}
