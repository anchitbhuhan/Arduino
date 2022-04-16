#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>

RF24 radio(7,8);

BTLE btle(&radio);

void setup() {

  Serial.begin(9600);
  while (!Serial) { }
  Serial.println("BTLE advertisement sender");

  btle.begin("foobar");
}

void loop() {
  float temp = 32;
  nrf_service_data buf;

  buf.service_uuid = NRF_TEMPERATURE_SERVICE_UUID;

  buf.value = BTLE::to_nRF_Float(temp);

  
  btle.advertise(0x16, &buf, sizeof(buf));
  btle.hopChannel();

  
  Serial.print(".");
}
