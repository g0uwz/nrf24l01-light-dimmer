/***********************************************
Receiver
Single channel Robotdyn dimmer module, integrated with Nrf24l01 & arduino nano
 *                                             *
           NRF 24L01 Connection
            VCC  -> 3.3 V
            GND  -> GND
            SCK  -> 13
            MISO -> 12
            MOSI -> 11
            CSN  -> 8
            CE   -> 7
 ***********************************************/


#include <RBDdimmer.h>
#include <SPI.h>       // to handle the communication interface with the modem
#include <nRF24L01.h>  // to handle this particular modem driver
#include <RF24.h>      // the library which helps us to control the radio modem
#define USE_SERIAL Serial
#define outputPin 3
#define zerocross 2
dimmerLamp dimmer(outputPin);
int outVal = 0;
int value = 0;

RF24 radio(7, 8);                      // Creating instance 'radio'  ( CE , CSN )   CE -> D7 | CSN -> D8

const byte Address[6] = " 00009 ";  // Address from which data to be received

void setup() {  // put your setup code here, to run once:

  USE_SERIAL.begin(9600);
  dimmer.begin(NORMAL_MODE, ON);
  radio.begin();                      // Activate the modem
  radio.setDataRate(RF24_250KBPS);    // 250KBPS : 1MBPS : 2MBPS
  radio.openReadingPipe(1, Address);  // Sets the address of receiver from which program will receive the data
  radio.setChannel(124);
}
void loop() {

  radio.startListening();  // Setting modem in Receiver mode
  if (radio.available()) {
    while (radio.available())  // Loop until receiving valid data
    {
      radio.read(&value, sizeof(value));
      outVal = map(value, 0, 1024, 10, 80);
      Serial.print(" Received : ");
      USE_SERIAL.println(value);
      Serial.println(outVal);  // Print received value on Serial Monitor
      dimmer.setPower(outVal);
    }

  }

}
