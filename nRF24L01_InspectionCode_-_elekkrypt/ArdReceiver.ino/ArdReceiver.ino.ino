
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 3); // CE, CSN
const byte address[6] = "1Node";
boolean button_state = 0;
int led_pin = 3;

void setup()
{
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}

void loop()
{
  if (radio.available())              //Looking for the data.
  {
    char text[32] = "";                 //Saving the incoming data
    radio.read(&text, sizeof(text));    //Reading the data
    Serial.println(text);

    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);
  }
  else
  {
     Serial.println("radio unavailable");
  }
  delay(5);
}
