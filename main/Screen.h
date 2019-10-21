/*
  Screen.h - Library for menu display.
  Created by Danel R. Rojas, Octeber 18, 2019.
*/

#ifndef Screen_h
#define Screen_h
#include "Arduino.h"
#include <LiquidCrystal.h>



class Screen
{
  
  public:
    Screen();
    void printMenu(LiquidCrystal lcd);
    void menuControls(LiquidCrystal lcd);
    bool getStart();
    void startInterface(LiquidCrystal lcd, int t, float f);
  private:
    #define RIGHT  0
    #define UP     1
    #define DOWN   2
    #define LEFT   3
    #define SELECT 4
    #define NONE   5
    bool start;
    byte tempMIN;
    byte tempMAX;
    
    byte uvMIN;
    byte uvMAX;

    byte humiditySoilMAX;
    int humiditySoilMIN;

    byte humidityAmbientMAX;
    byte humidityAmbientMIN;
    
    byte select;
    String menu[5] = {"Iniciar", "Temperatura", "Humedad Ambiente", "Humedad Suelo","Rayos UV"};
  
    byte readButtons();
    void setParam(LiquidCrystal lcd,byte value1,byte value2,byte id);
    void setData(byte id,byte value1,byte value2);
    
};
#endif
