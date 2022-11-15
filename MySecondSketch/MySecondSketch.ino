// C++ code
//
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#define CE_PIN 9
#define CSN_PIN 10
#define ALERTA 7
#define LED_VERDE 13     // modulos de led
#define LED_AMARILLO 12  // modulos de led
#define LED_ROJO 11      // modulos de led
RF24 radio(CE_PIN, CSN_PIN);
//const uint64_t pipe = 0xE8E8F0F0E1LL;
const byte address[6] = "00001";
void setup() {
  pinMode(ALERTA, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);  //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);      //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();
}

void loop() {
  delayMicroseconds(10);
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  const char message[1] = "";
  if (radio.available()) {
    radio.read(&message, sizeof message);
    Serial.println(message);
    switch (message[0]) {
       case 'A':
         tone(ALERTA, 523, 200);
         digitalWrite(LED_ROJO, HIGH);
         digitalWrite(LED_VERDE, LOW);
         digitalWrite(LED_AMARILLO, LOW);
         delay(50);
         Serial.println("ALERTA ROJO");
         break;
       case 'B':
         tone(ALERTA, 300, 200);
         Serial.println("ALERTA AMARRILLA");
         digitalWrite(LED_ROJO, LOW);
         digitalWrite(LED_VERDE, LOW);
         digitalWrite(LED_AMARILLO, HIGH);
         delay(50);
         break;
       case 'C':
         tone(ALERTA, 100, 100);
         Serial.println("ALERTA VERDE");
         digitalWrite(LED_ROJO, LOW);
         digitalWrite(LED_VERDE, HIGH);
         digitalWrite(LED_AMARILLO, LOW);
         delay(50);
             break;
         }
    }

    delay(1000);
  }