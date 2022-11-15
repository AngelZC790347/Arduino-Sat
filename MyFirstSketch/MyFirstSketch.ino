// C++ code
//
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#define CE_PIN 9 // modulos de transmisión
#define CSN_PIN 10 // modulos de transmisión
#define SIGNAL_OUT 7 // pin modulo de sensor Barrera IR
#define DO 8 // pin modulo sensor YL-80
const int trigger=5; //sensor hsro4
const int echo=6; //sensor hsro4
float dist;
RF24 radio(CE_PIN, CSN_PIN);
//const uint64_t pipe = 0xE8E8F0F0E1LL;
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
void setup()
{
  Serial.begin(9600); //un estdandar para la impresión en la pantalla
  pinMode(trigger,OUTPUT); //OUTPUT=salida
  pinMode(SIGNAL_OUT, INPUT); //PUTPUT = ENTRADAS
  pinMode(DO, INPUT);
  pinMode(echo,INPUT);  
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();    
}

void loop()
{
  int lluvia,laser; //int=toma las señales
  lluvia = digitalRead(DO);  //lee la señal de lluvia  
  laser = digitalRead(SIGNAL_OUT); //lee la señal del laser
  bool amarillo = (laser == HIGH && lluvia == HIGH); // CORREGIR PARA QUE SEA INDIVIDUALMENTE
  Serial.print("Laser: ");
  Serial.println(laser);
  Serial.print("LLuvia: ");
  Serial.println(lluvia);
  if (!amarillo){
    digitalWrite(trigger,HIGH);  
    delayMicroseconds(10);      
    digitalWrite(trigger,LOW); 
    dist=pulseIn(echo,HIGH);    
    dist = dist/58;
    Serial. println(dist);
    bool peligro = dist<=15;
    if (peligro){
      const char msg[] = "A"; 
      radio.write(&msg,sizeof(msg));
    }else{
      const char msg[] = "B"; 
      radio.write(&msg,sizeof(msg));
    
    }}else{
       const char msg[] = "C"; 
      radio.write(&msg,sizeof(msg));
        delay(500);
    }
   
  delay (1000);               
}