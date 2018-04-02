#include <SdFatTestSuite.h>
#include "UTFTMenu.h"
#include "DS3231.h"
#include "XBee.h"
#include "XBeeMenu.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// подключаем наши экраны
#include "Screen1.h"              // Главный экран
#include "Screen2.h"              // Вызов меню настроек
#include "Screen3.h"              //
#include "Screen4.h"              // Вызов меню установки времени и даты
#include "Screen5.h"              // Вызов установки времени
#include "Screen6.h"              // Вызов установки даты
//#include "InterruptScreen.h"      // экран с графиком прерывания
//#include "Buttons.h"              // наши железные кнопки
//#include "InfoDiodes.h"           // информационные диоды
//#include "FileUtils.h"
//#include "Settings.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint32_t screenIdleTimer = 0;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void screenAction(AbstractTFTScreen* screen)
{
	// какое-то действие на экране произошло.
	// тут просто сбрасываем таймер ничегонеделанья.
	screenIdleTimer = millis();
}



#define Serial SERIAL_PORT_USBVIRTUAL                                  // Подключаем USB порт в качестве COM порта

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() 
{
	Serial.begin(115200);
	//while (!Serial);                                                    // Wait for Serial monitor to open
	delay(500);
    Serial.println("*** Setup system ***");
	//delay(500);
  // настраиваем часики
  RealtimeClock.begin(1); // запускаем их на шине I2C 1 (SDA1, SCL1);

  Serial1.begin(9600);                                                 // Подключение к

  RealXBeeMenu.setup();

  Screen.setup();
  // первый экран покажется по умолчанию
  Screen.addScreen(Screen1::create());
  //  экран МЕНЮ 1
 
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() 
{
  Screen.update();
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

