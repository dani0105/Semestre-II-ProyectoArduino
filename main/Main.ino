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

bool debugON= true;

// Valores minimos y maximos para cultivo de zanahoria 

short maxTemperature = 32; // [-255,255]
short minTemperature = 25; // [-255,255]

short maxHumidity = 100; // [-255,255]
short minHumidity = 50; // [-255,255]

short maxUV = 10; // {1,2,3,4,5,6,7,8,9,10,11,12}
bool UVMin  = true;

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
  if (!gsm.begin(9600)){
    Serial.println("\nGSM=IDLE");
    while (1);  
  }
  Serial.println("\nGSM=READY");
  started=true;

  /*
  // Inicia SD Card
  if (!SD.begin(PIN_CS)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");


  File myFile;
  myFile = SD.open("params.txt");
  // read from the file until there's nothing else in it:
  String line ;
  while (myFile.available()) {
    line += (char) myFile.read();
  }
  for(short i = 0; i <= 4 ; ++i){
    String val = getValue(line, ',', i);
    switch(i){
      case 0:
        maxUV = val.toInt();
      break;
      case 1:
        maxTemperature = val.toInt();
      break;
        
      case 2:
      minTemperature = val.toInt();
       
      break;
      case 3:
       maxHumidity = val.toInt();
       
      break;
      case 4:
       minHumidity = val.toInt();
      break;
    }
  }
  myFile.close();  
  */
}  

void loop() {  
  if(started){
    float UVindex = uv.readUV();
    UVindex /= 100.0;  
    if(UVindex > 1 || UVMin){ 
      if(analogRead(PIN_RAIN) > 300){
        //Sensor DHT
        delay(30000);
        float humidity  = dht.readHumidity();
        int temperature = (int) dht.readTemperature();
        
       
        
  
         // Sensor UV
        //float vis     = uv.readVisible();
        //float ir      = uv.readIR();
        
        
        if(debugON){
          Serial.print("\nTemperatura: ");Serial.print(temperature);
          Serial.print("\nHumedad: ");Serial.print(humidity);
          
          //Serial.print("\nVis: ");Serial.print(vis);
          //Serial.print("\nIr: ");Serial.print(ir);
          Serial.print("\nUVIndex: ");Serial.print(UVindex);
        }
        
        if( temperature < minTemperature || maxTemperature < temperature){
          sendNotification("Limites de temperatura superados");     
        }else if(humidity < minHumidity || maxHumidity < humidity){
          sendNotification("Limites de humedad superados");     
        }else if(UVindex > maxUV){
           sendNotification("Limite de rayos UV superado");
        }
        delay(30000);
        delay(30000);
      }
    }
    Serial.println("Pausa de 30 minutos uv:");
    Serial.print(UVindex);
    for(short i = 0; i< 30;i++){
     delay(30000);
     delay(30000);
     Serial.println(i);
    }
   
  }
}

void sendNotification(char message[100]){
 
  sms.SendSMS("+50684527392", message);
  Serial.println("Usuario notificado ");
  
  for(short i=0; i< 30;i++){
     delay(30000);
     delay(30000);
     Serial.println(i);
  }
   Serial.println("Tiempo de espera terminado ");
}

/*
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}*/
