/***********************************************
Transmitter
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




#include <SPI.h>      /* to handle the communication interface with the modem*/
#include <nRF24L01.h> /* to handle this particular modem driver*/
#include <RF24.h>     /* the library which helps us to control the radio modem*/
#define pot_pin A0

RF24 radio(7, 8);  // ( CE , CSN )
const byte Address[6] = " 00009 ";



void setup() {

  Serial.begin(9600);
  pinMode(pot_pin, INPUT);  // Setting A0 (POT pin) as input
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(124);
  radio.openWritingPipe(Address); /* Sets the address of transmitter to which program will send the data */
}
void loop() {

  radio.stopListening();                  /* Setting modem in transmission mode*/
  int value = analogRead(pot_pin);        /*Reading analog value at pin A0 and storing in varible 'value'*/
  //int data = map(value, 0, 1023, 0, 255); /* Convering the 10 bit value to 8 bit */
  //radio.write(&data, sizeof(data));       /* Sending data over NRF 24L01*/
  radio.write(&value, sizeof(value));       /* Sending value over NRF 24L01*/
  Serial.print("Transmitting value : ");
  Serial.println(value); /* Printing POT value on serial monitor*/
}
