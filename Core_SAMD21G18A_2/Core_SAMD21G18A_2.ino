#include "UTFTMenu.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// подключаем наши экраны
#include "Screen1.h"
#include "Screen1_0.h"
#include "Screen1_1.h"
#include "Screen1_2.h"
#include "Screen1_3.h"
#include "Screen1_4.h"
#include "Screen2.h"
#include "Screen2_0.h"
#include "Screen2_1.h"
#include "Screen2_2.h"
#include "Screen2_3.h"
#include "Screen2_4.h"


//#include "Screen3.h"

// подключаем часики
#include "DS3231.h"
#include "XBee.h"
#include "XBeeMenu.h"



#define Serial SERIAL_PORT_USBVIRTUAL                                  // Подключаем USB порт в качестве COM порта

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() 
{
	Serial.begin(115200);
//	while (!Serial);                                                    // Wait for Serial monitor to open
	delay(1500);
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
  Screen.addScreen(Screen1_0::create());
  Screen.addScreen(Screen1_1::create());
  Screen.addScreen(Screen1_2::create());
  Screen.addScreen(Screen1_3::create());
  Screen.addScreen(Screen1_4::create());

  // добавляем второй экран
  Screen.addScreen(Screen2::create());

  //  экран МЕНЮ 2
  Screen.addScreen(Screen2_0::create());
  Screen.addScreen(Screen2_1::create());
  Screen.addScreen(Screen2_2::create());
  Screen.addScreen(Screen2_3::create());
  Screen.addScreen(Screen2_4::create());

  // добавляем третий экран
  //Screen.addScreen(Screen3::create());
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() 
{
  Screen.update();
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

