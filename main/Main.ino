#include <DHT.h>

#include "Screen.h"


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
DHT dht(2,DHT11);

Screen screen;


void setup(){
  lcd.begin(16, 2);              // Inicializar el LCD
  lcd.setCursor(0,0);
  Serial.begin(9600);
  screen.printMenu(lcd);
   dht.begin();

}

  
void loop() {
  if(screen.getStart()){
    float f = dht.readHumidity();
    int t = (int) dht.readTemperature();

    screen.startInterface(lcd,t,f);
    delay(5000);
    return;
  }

   screen.menuControls(lcd);
   delay(100);
}
