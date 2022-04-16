//#define FAILURE_HANDLING 1
//#define RF24_LINUX 1
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 3); // CE, CSN
const byte address[6] = "1Node";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int button_pin = 2;
boolean button_state = 0;
  

void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT);
//  pinMode(3, OUTPUT);
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}

void loop()
{
  
    const char text[] = "Hello World";
    bool res = radio.write(&text, sizeof(text));                  //Sending the message to receiver
    Serial.println(text);
    Serial.println(res);
     delay(1000);
}
