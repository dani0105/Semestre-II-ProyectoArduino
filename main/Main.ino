#include <DHT.h>
#include "Adafruit_SI1145.h"// Para el sensor uv
#include "Screen.h"
#include <SoftwareSerial.h>

#define PIN_ANALOG_RAIN_SENSOR 3  // Entrada analógica para la señal del sensor lluvia
#define PIN_DIGITAL_RAIN_SENSOR 5  // Entrada digital para la señal del sensor de lluvia


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
DHT dht(2,DHT22);
SoftwareSerial mySerial(10, 11);
Adafruit_SI1145 uv = Adafruit_SI1145();

Screen screen;

bool enviar = true;
void setup(){
  lcd.begin(16, 2);              // Inicializar el LCD
  lcd.setCursor(0,0);
  Serial.begin(9600);
  screen.printMenu(lcd); 
   dht.begin();          //Humedad Temperatura
   uv.begin();        //Inicializar UV

   mySerial.begin(9600);   // Setting the baud rate of GSM Module 

    
}  

void loop() {  
  if(enviar){
    SendMessage();
    enviar = false;
  }
  if(!screen.getStart()){
    float f = dht.readHumidity();
    int t = (int) dht.readTemperature();

    screen.startInterface(lcd,t,f);
    // Sensor UV
    Serial.println("-----------");
    Serial.print("Vis: "); Serial.println(uv.readVisible());
    Serial.print("IR: "); Serial.println(uv.readIR());
    
    float UVindex = uv.readUV();
    // the index is multiplied by 100 so to get the
    // integer index, divide by 100!
    UVindex /= 100.0;
    Serial.print("UV: ");  Serial.println(UVindex);

    int sensorValue = analogRead(PIN_ANALOG_RAIN_SENSOR); // Leer datos del puerto analógico
   Serial.print("Lluvia analog value: "); 
   Serial.println(sensorValue); // Salida de valor analógico al monitor de puerto
   delay(5000);
   
    return;
    
  }

   screen.menuControls(lcd);
   delay(100);
}

 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+50684527392\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
