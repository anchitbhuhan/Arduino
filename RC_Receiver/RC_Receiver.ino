/////*
////    DIY Arduino based RC Transmitter Project
////              == Receiver Code ==
////
////  by Dejan Nedelkovski, www.HowToMechatronics.com
////  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
////*/
//#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>
//#include <Servo.h>
//
//Servo ESC1;     // create servo object to control the ESC
//Servo ESC2;     // create servo object to control the ESC
//Servo ESC3;     // create servo object to control the ESC
//Servo ESC4;     // create servo object to control the ESC
//
//RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
//const byte address[6] = "00001";
//
//
//int motor1Analog = A0;
//int motor2Analog = A1;
//int motor3Analog = A2;
//int motor4Analog = A3;
//int motorSpeed;
//int waitT = 10;
//unsigned long lastReceiveTime = 0;
//unsigned long currentTime = 0;
//
//// Max size of this struct is 32 bytes - NRF24L01 buffer limit
//struct Data_Package {
//  byte j1PotX;
//  byte j1PotY;
//  
//  byte tSwitch1;
//
//  
//};
//
//Data_Package data; //Create a variable with the above structure
//
//void setup() {
//  Serial.begin(115200);
//  radio.begin();
//  ESC1.attach(motor1Analog,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
//  ESC2.attach(motor2Analog,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
//  ESC3.attach(motor3Analog,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
//  ESC4.attach(motor4Analog,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
//  radio.openReadingPipe(0, address);
//  radio.setAutoAck(false);
//  radio.setDataRate(RF24_2MBPS);
//  radio.setPALevel(RF24_PA_MIN);
//  radio.startListening(); //  Set the module as receiver
//  resetData();
//  
//}
//void loop() {
//  // Check whether there is data to be received
//  if (radio.available()) {
//    Serial.println("Available");
//    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
//    lastReceiveTime = millis(); // At this moment we have received the data
//  }
//  else
//  {
//    Serial.println("Not Available");
//  }
//  // Check whether we keep receving data, or we have a connection between the two modules
//  currentTime = millis();
//  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
//    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
//  }
//  // Print the data in the Serial Monitor
//  Serial.print("j1PotX: ");
//  Serial.print(data.j1PotX);
//  Serial.print("; j1PotY: ");
//  Serial.print(data.j1PotY);
//  Serial.print("; tSwitch1 ");
//  Serial.println(data.tSwitch1);
//
//
//   motorSpeed = map(data.j1PotX, 125,255, 0, 150);
//   if(motorSpeed < 0)
//        motorSpeed = 0;
//  Serial.print("  motorSpeed = ");
//  Serial.println(motorSpeed);
//  delay(waitT);
//
//  ESC1.write(motorSpeed);
//  ESC2.write(motorSpeed);
//  ESC3.write(motorSpeed);
//  ESC4.write(motorSpeed);
//  
//}
//
//void resetData() {
//  // Reset the values when there is no radio connection - Set initial default values
//  data.j1PotX = 127;
//  data.j1PotY = 127;
//  
//  data.tSwitch1 = 1;
//  
//}
//
//
//
//











//=========================Arm the ESC=====================================//
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address

int waitT = 250;
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;


//// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  byte j1PotX;
  byte j1PotY;
  byte j2PotX;
  byte j2PotY;
  byte tSwitch1;
};Data_Package data; //Create a variable with the above structure




void setup ()
{
  Serial.begin(115200);
  radio.begin();
  //NRF24L01 Setup
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
  resetData();

}


void loop()
{
     
  // Check whether there is data to be received
          if (radio.available()) {
            radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
            lastReceiveTime = millis(); // At this moment we have received the data


            currentTime = millis();
              if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    //            resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
              }
              delay(1000);
          }
          
          // Check whether we keep receving data, or we have a connection between the two modules
          
          else
          {
            Serial.println("Radio Unavailable\n");
          }
          
        
          Serial.print("j1PotX: ");
          Serial.print(data.j1PotX);
          Serial.print("; j1PotY: ");
          Serial.print(data.j1PotY);
          Serial.print("j2PotX: ");
          Serial.print(data.j2PotX);
          Serial.print("; j2PotY: ");
          Serial.print(data.j2PotY);
          Serial.print("; tSwitch1 ");
          Serial.println(data.tSwitch1);

        
}
void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.j1PotX = 127;
  data.j1PotY = 127;
  
  data.tSwitch1 = 0;
  
}
