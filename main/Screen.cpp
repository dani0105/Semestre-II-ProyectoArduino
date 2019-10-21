/*
  Screen.h - Library for menu display.
  Created by Danel R. Rojas, Octeber 18, 2019.
*/

#include "Screen.h"

/************************************************
  Rutina: Screen
 
  Autor: 

  Metodos constructor de la clase. Inicializa todas
  las variables con datos.

 ***********************************************/

Screen::Screen(){ 
  select = 0;
  tempMIN = 20;
  tempMAX = 30;
  uvMIN = 2;
  uvMAX = 3;
  humiditySoilMAX = 25;
  humiditySoilMIN = 20;
  humidityAmbientMAX = 25;
  humidityAmbientMIN = 20;
  start = false;
}


/************************************************
  Rutina: printMenu
 
  Autor: 

  Imprime el menu principal del programa

 ***********************************************/
void Screen::printMenu(LiquidCrystal lcd){
  byte temp = select;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">");
  lcd.setCursor(1,0);
  lcd.print(menu[temp]);
  if (temp < 4){
    lcd.setCursor(1,1);
    lcd.print(menu[++temp]);
  }
  
}


/************************************************
  Rutina: setData
 
  Autor: 

  Por medio del ID que se le pasa por parametro, puede 
  colocar los valores minimos y maximos a cierto grupo 
  de datos.

 ***********************************************/
void Screen::setData(byte id,byte value1,byte value2){
  switch(id){
    case 1:
      this->tempMIN = value1;
      this->tempMAX = value2;
    break;
    case 2:
      this->humidityAmbientMIN = value1;
      this->humidityAmbientMAX = value2;
    break;
    case 3:
      this->humiditySoilMIN = value1;
      this->humiditySoilMAX = value2;
    break;
    case 4:
      this->uvMIN = value1;
      this->uvMAX = value2;
    break;
  }
}


/************************************************
  Rutina: setParam
 
  Autor: 

  Imprime el menu que permite la modificacion de los valores 
  minimos y maximos para el programa.

 ***********************************************/
void Screen::setParam(LiquidCrystal lcd,byte value1,byte value2,byte id){
  byte target =0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Minimo:  ");
  lcd.setCursor(9,0);
  lcd.print(value1);
  
  lcd.setCursor(0,1);
  lcd.print("Maximo:  ");
  lcd.setCursor(9,1);
  lcd.print(value2);

  lcd.setCursor(8,target);
  lcd.print(">");
  while(true){
   
    delay(100);
    byte key = readButtons();

    if (key == SELECT ){
        break;
    }
    
    if (key == UP && target == 1){
      lcd.setCursor(8,target);
      lcd.print(" ");
      target--;
      lcd.setCursor(8,target);
      lcd.print(">");
      continue;
    }

    if (key == DOWN && target == 0){
        lcd.setCursor(8,target);
        lcd.print(" ");
        target++;
        lcd.setCursor(8,target);
        lcd.print(">");
        continue;
    }
    
    switch(key){
      case RIGHT:
        lcd.setCursor(9,target);
        if(target == 0){
          if(value1 < value2){
            lcd.print(++value1);
          }else{
            lcd.print(value1);
          }
        }else{
          lcd.print(++value2); 
        }
        lcd.print(" ");
      break;
      case LEFT:
        lcd.setCursor(9,target);
        if(target == 1){
          if(value2 > value1){
            lcd.print(--value2);
          }else{
            lcd.print(value2);
          }
        }else{
          lcd.print(--value1);
        }
        lcd.print(" ");
      break;
    }
  }

  setData( id, value1, value2);
}
  

/************************************************
  Rutina: menuControls
 
  Autor: 

  Permite el movimiento por el munu, ademas de idendificar 
  en cual opcion el usuario desea entrar.

 ***********************************************/
void Screen::menuControls(LiquidCrystal lcd){
  byte key = readButtons();
  if(key == DOWN && select <4){++select;}
  else if (key == UP && select >0){--select;}
  else if (key == SELECT){
    switch(select){
      case 0:
        start = true;
      break;
      case 1:
        setParam(lcd, tempMIN, tempMAX,select);
      break;
      case 2:
        setParam(lcd, humidityAmbientMIN, humidityAmbientMAX,select);
      break;
      case 3:
        setParam(lcd, humiditySoilMIN, humiditySoilMAX,select);
      break;
      case 4:
        setParam(lcd, uvMIN, uvMAX,select);
      break;  
    }
  }

  if (key != NONE){
    printMenu(lcd);
  }
  
}


/************************************************
  Rutina: readButtons
 
  Autor: 

  Identifica cual boton el usuario utilizo y lo retorna.

 ***********************************************/
byte Screen::readButtons(){
  int key = analogRead(0);
  if ( key > 900 ) return NONE;     
  if ( key < 50  ) return RIGHT; 
  if ( key < 250 ) return UP;
  if ( key < 450 ) return DOWN;
  if ( key < 650 ) return LEFT;
  if ( key < 850 ) return SELECT; 
  return NONE; 
}

/************************************************
  Rutina: startInterface
 
  Autor: 

  muestra una interfaz cuando el usuario inicio el sistema 
  de reconocimiento de valores ambientales.

 ***********************************************/
void Screen::startInterface(LiquidCrystal lcd, int t, float f){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(t);

  lcd.setCursor(6,0);
  lcd.print("F:");
  lcd.print(f);
}

/************************************************
  Rutina: getStart
 
  Autor: 

  Se utiliza para saber el valor del atributo Start.
  Este atributo indica si el usuario inicio el programa o no.

 ***********************************************/
bool Screen::getStart(){
  return this->start;
}
