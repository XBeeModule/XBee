#include <UTFT.h>
#include <digitalWriteFast.h>
#include <Arduino.h>
#include "CONFIG.h"
#include "UTFTMenu.h"
#include "DS3231.h"               // подключаем часы


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// подключаем наши экраны
#include "Screen1.h"              // Главный экран
#include "Screen3.h"              //
#include "Screen4.h"              // Вызов меню установки времени и даты
#include "Screen5.h"              // Вызов установки времени
#include "Screen6.h"              // Вызов установки даты

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint32_t screenIdleTimer = 0;
bool setupDone = false;


const int ledPin = 11;

#define Serial SERIAL_PORT_USBVIRTUAL


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void screenAction(AbstractTFTScreen* screen)
{
   // какое-то действие на экране произошло.
   // тут просто сбрасываем таймер ничегонеделанья.
   screenIdleTimer = millis();
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() 
{
	//Serial.begin(9600);
	
	Serial.begin(SERIAL_SPEED);
 // while(!Serial);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  DBGLN(F("Init RTC..."));
  //RealtimeClock.begin(1);           // запускаем их на шине I2C 1 (SDA1, SCL1);
 // RealtimeClock.setTime(0,1,11,1,7,2,2018);

  DBGLN(F("Init screen..."));
  Screen.setup();

  DBGLN(F("Add screen1...")); 

  Screen.addScreen(Screen1::create());           // первый экран покажется по умолчанию
  //DBGLN(F("Add screen2..."));
  //// добавляем второй экран
  ////Screen.addScreen(Screen2::create());
  //DBGLN(F("Add screen3..."));
  //// добавляем третий экран. Переход в меню настройки
  //Screen.addScreen(Screen3::create());
  //DBGLN(F("Add screen4..."));
  //// добавляем четвертый экран. Меню установки даты и времени
  //Screen.addScreen(Screen4::create());
  //DBGLN(F("Add screen5..."));
  //// добавляем 5 экран. Установка времени
  //Screen.addScreen(Screen5::create());
  //DBGLN(F("Add screen6..."));
  //// добавляем 6 экран. Установка даты
  //Screen.addScreen(Screen6::create());
  //DBGLN(F("Add interrupt screen..."));
  //// добавляем экран с графиком прерываний
  //Screen.addScreen(InterruptScreen::create());

  // переключаемся на первый экран
  Screen.switchToScreen("Main");


  screenIdleTimer = millis();
  Screen.onAction(screenAction);

  DBGLN(F("Inited."));

  Serial.print(F("XBee "));
  Serial.println(SOFTWARE_VERSION);

  setupDone = true;

}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() 
{
 
  Screen.update();

 // DBGLN(F("Screen.update"));
  // проверяем, какой экран активен. Если активен главный экран - сбрасываем таймер ожидания. Иначе - проверяем, не истекло ли время ничегонеделанья.
  AbstractTFTScreen* activeScreen = Screen.getActiveScreen();
  //if(activeScreen == mainScreen)
  //{
  //  screenIdleTimer = millis();
  //}
  //else
  //{
  //    if(millis() - screenIdleTimer > RESET_TO_MAIN_SCREEN_DELAY)
  //    {
  //      screenIdleTimer = millis();
  //      Screen.switchToScreen(mainScreen);
  //    }
  //} // else


  //// обрабатываем входящие команды
 

}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//bool nestedYield = false;
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//void yield()
//{
//  
//  if(nestedYield || !setupDone)
//    return;
//    
// nestedYield = true;
// 
// nestedYield = false;
// 
//}
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
