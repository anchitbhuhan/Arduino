///*
//        DIY Arduino based RC Transmitter
//  by Dejan Nedelkovski, www.HowToMechatronics.com
//  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
//*/
//
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>


// Define the digital inputs

#define t1 2   // Toggle switch 1
#define J1_X A1 //Joystick 1 X
#define J1_Y A0 //Joystick 1 Y


RF24 radio(4, 3);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {

      byte j1PotX;
      byte j1PotY;
      byte tSwitch1;

};

Data_Package data; //Create a variable with the above structure

void setup() {

  Serial.begin(9600);



  // Define the radio communication
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MIN);

  // Activate the Arduino internal pull-up resistors

  pinMode(t1, INPUT_PULLUP);

  // Set initial default values
  data.j1PotX = 127; // Values from 0 to 255. When Joystick is in resting position, the value is in the middle, or 127. We actually map the pot value from 0 to 1023 to 0 to 255 because that's one BYTE value
  data.j1PotY = 127;

  data.tSwitch1 = 1;

}
void loop() {
  // Read all analog inputs and map them to one Byte value
  data.j1PotX = map(analogRead( J1_X), 0, 1023, 0, 255); // Convert the analog read value from 0 to 1023 into a BYTE value from 0 to 255
  data.j1PotY = map(analogRead(J1_Y), 0, 1023, 0, 255);

  // Read all digital inputs
  data.tSwitch1 = digitalRead(t1);


  // Send the whole data from the structure to the receiver
  bool res = radio.write(&data, sizeof(Data_Package));
  if(res==1)
    Serial.print("Sent Data    ");
    Serial.print("X = ");
    Serial.print(data.j1PotX);

    Serial.print(" Y = ");
    Serial.print(data.j1PotY);

    Serial.print(" Switch= ");
    Serial.println(data.tSwitch1);

}



/*
        DIY Arduino based RC Transmitter
  by Dejan Nedelkovski, www.HowToMechatronics.com
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

//#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>
//#include <Wire.h>
//
//
//// Define the digital inputs
//
//#define t1 2   // Toggle switch 1
//#define J1_X A1 //Joystick 1 X
//#define J1_Y A0 //Joystick 1 Y
//
//
//RF24 radio(4, 3);   // nRF24L01 (CE, CSN)
//const byte address[6] = "1Node";
//
//// Max size of this struct is 32 bytes - NRF24L01 buffer limit
////struct Data_Package {
////  String s;
////};
//String s;
//
////Data_Package data; //Create a variable with the above structure
//
//void setup() {
//
//  Serial.begin(9600);
//
//  // Define the radio communication
//  radio.begin();
//  //  radio.setAutoAck(false);
//  //  radio.setDataRate(RF24_250KBPS);
//  radio.openWritingPipe(address);
//  radio.setPALevel(RF24_PA_MIN);
//  radio.stopListening();
//
//  // Activate the Arduino internal pull-up resistors
//
//  //  pinMode(t1, INPUT_PULLUP);
//  s = "";
//  //  data.s = "";
//
//}
//void loop() {
////    Serial.println("To send");
//  if (Serial.available()) {
//    s = Serial.readString();
//    byte buffer[100];
//    s.toCharArray(buffer, s.length() + 1);
//    
//    //    bool res = radio.write(&data, sizeof(Data_Package));
//    bool res = radio.write(buffer, sizeof(s));
//    if (res == 1)
//    {
//      Serial.print("Sent Data    ");
//      Serial.println(s);
//    }
//  }
//
//  //  const char text[] = "Hello World!!";
//  //  bool res = radio.write(&text, sizeof(text));
//  //  if (res == 1)
//  //  {
//  //    Serial.print("Sent Data    ");
//  //    Serial.println(text);
//  //  }
//  delay(100);
//}
