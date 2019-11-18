#include <DHT.h>
//#include <SPI.h>
//#include <SD.h>

#include "sms.h"
#include "Adafruit_SI1145.h"// Para el sensor uv
#include "SIM900.h"


// Definicion de Pines
#define PIN_RAIN 2 
#define PIN_DHT 5
#define SIM900_POWER 9
#define PIN_CS 4


DHT dht(PIN_DHT,DHT22);
Adafruit_SI1145 uv = Adafruit_SI1145();
SMSGSM sms;

//Variables globales
boolean started=false;

// Valores minimos y maximos para cultivo de zanahoria 

byte maxTemperature = 23; // [-255,255]
byte minTemperature = 20; // [-255,255]

byte maxHumidity = 100; // [-255,255]
byte minHumidity = 90; // [-255,255]

byte maxUV; // {1,2,3,4,5,6,7,8,9,10,11,12}
byte minUV; // {1,2,3,4,5,6,7,8,9,10,11,12}

byte rain; // < 300

bool sendSMS = false;
bool raining = false;

String SMS="Atencion!";

String phoneNumber = "+50684527392";

void setup(){
  Serial.begin(9600);
  Serial.print("Iniciando Sistema.  ");
  
  // Power on SIM900 module
  pinMode(SIM900_POWER, OUTPUT);
  digitalWrite(SIM900_POWER, HIGH);
  delay(500);
  digitalWrite(SIM900_POWER, LOW);  
  delay(5000); 
  
  dht.begin();          //Humedad Temperatura
  uv.begin();        //Inicializar UV

  // Inicia Gsm
  if (gsm.begin(9600)){
    Serial.println("\nGSM=READY");
    started=true;
  } 
  else 
    Serial.println("\nGSM=IDLE");

/*
  // Inicia SD Card
  if (!SD.begin(PIN_CS)) {
    Serial.println("Card failed, or not present");
    //while (1);
  }
  Serial.println("card initialized.");
  */
}  

void loop() {  
  if(started){
    
    
    //Sensor DHT
    float humidity  = dht.readHumidity();
    int temperature = (int) dht.readTemperature();
    
    // Sensor UV

    
    float vis     = uv.readVisible();
    float ir      = uv.readIR();
    float UVindex = uv.readUV();
    
    
    // Sensor Rain
    int rain = analogRead(PIN_RAIN); // Leer datos del puerto analógico

    Serial.print("Temperatura: ");Serial.print(temperature);
    Serial.print("\nHumedad: ");Serial.print(humidity);
    
    Serial.print("\nVis: ");Serial.print(vis);
    Serial.print("\nIr: ");Serial.print(ir);
    Serial.print("\nUVIndex: ");Serial.print(UVindex);
    
    Serial.print("\nLluvia: ");Serial.print(rain);

    if(rain < 500)
      raining = !raining;
    
    if( temperature < minTemperature || maxTemperature < temperature){
      sendSMS = true;
      SMS += "\nTemperaduta rompio limite establecido. Temperatura= "+String(temperature);
    }

    if(humidity < minHumidity || maxHumidity < humidity){
      sendSMS = true;
      SMS += "\nHumedad rompio limite establecido. Humedad= "+String(humidity)+"%";
    }

    if(sendSMS){
      Serial.println(SMS);
      char charBuf[SMS.length()];
      SMS.toCharArray(charBuf, SMS.length()); 
      sendNotification(charBuf);
    }
  
    delay(10000);
  }
}

void sendNotification(char message){
  Serial.println("Enviando Mensaje");
  //sms.SendSMS("+50684527392", message);
  Serial.println(message);
  return;
  for(byte i = 0; i <1; i++){
    //LowPower.idle(180000);
    delay(180000);
  }
}
