


#include <Wire.h>
#include <RTClib.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <UTFT.h>
#include <UTouch.h>
#include <UTFT_Buttons.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>


#define led_13 13   


//********************* Настройка монитора ***********************************
UTFT          myGLCD(ITDB24E_8, 38, 39, 40, 41);        // Дисплей 2.4" !! Внимание! Изменены настройки UTouchCD.h
UTouch        myTouch(6, 5, 4, 3, 2);                   // Standard Arduino Mega/Due shield            : 6,5,4,3,2
UTFT_Buttons  myButtons(&myGLCD, &myTouch);             // Finally we set up UTFT_Buttons :)

boolean default_colors = true;                          //
uint8_t menu_redraw_required = 0;
// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];
extern uint8_t SmallSymbolFont[];
//+++++++++++++++++++++++++++++ Внешняя память +++++++++++++++++++++++++++++++++++++++
int deviceaddress        = 80;                          // Адрес микросхемы памяти
unsigned int eeaddress   =  0;                          // Адрес ячейки памяти

//+++++++++++++++++++++++++++ Настройка часов +++++++++++++++++++++++++++++++
uint8_t second = 0;                                    //Initialization time
uint8_t minute = 10;
uint8_t hour   = 10;
uint8_t dow    = 2;
uint8_t day    = 15;
uint8_t month  = 3;
uint16_t year  = 16;
const char* str1[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

RTC_DS1307 RTC;                                       // define the Real Time Clock object


void dateTime(uint16_t* date, uint16_t* time)                                    // Программа записи времени и даты файла
{
  DateTime now = RTC.now();

  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(now.year(), now.month(), now.day());

  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

void serial_print_date()                           // Печать даты и времени
{
  DateTime now = RTC.now();
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print("  ");
  Serial.println(str1[now.dayOfWeek() - 1]);
}
void clock_read()
{
  DateTime now = RTC.now();
  second = now.second();
  minute = now.minute();
  hour   = now.hour();
  dow    = now.dayOfWeek();
  day    = now.day();
  month  = now.month();
  year   = now.year();
}

void set_time()
{
  RTC.adjust(DateTime(__DATE__, __TIME__));
  DateTime now = RTC.now();
  second = now.second();       //Initialization time
  minute = now.minute();
  hour   = now.hour();
  day    = now.day();
  day++;
  if (day > 31)day = 1;
  month  = now.month();
  year   = now.year();
  DateTime set_time = DateTime(year, month, day, hour, minute, second); // Занести данные о времени в строку "set_time"
  RTC.adjust(set_time);
}



void drawButtons() // Отображение цифровой клавиатуры
{
	int x ;
	 myGLCD.setBackColor( 0, 0, 255);
  // Draw the upper row of buttons
  for (x = 0; x < 4; x++)
  {
    myGLCD.setColor(0, 0, 255);
    myGLCD.fillRoundRect (5 + (x * 58), 5, 60 + (x * 58), 60);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (5 + (x * 58), 5, 60 + (x * 58), 60);
    myGLCD.printNumI(x + 1, 24 + (x * 58), 25);
  }

  for (x = 0; x < 4; x++)
  {
    myGLCD.setColor(0, 0, 255);
    myGLCD.fillRoundRect (5 + (x * 58), 66, 60 + (x * 58), 120);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (5 + (x * 58), 66, 60 + (x * 58), 120);
    myGLCD.printNumI(x + 5, 24 + (x * 58), 85);
  }

  for (x = 0; x < 2; x++)
  {
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5 + (x * 58), 127, 60 + (x * 58), 180);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5 + (x * 58), 127, 60 + (x * 58), 180);
	if (x < 1)
	myGLCD.printNumI(x + 9, 24 + (x * 58), 145);
	if (x > 0)
	myGLCD.printNumI(0, 24 + (x * 58), 145);
  }

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (122, 127, 234, 180);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (122, 127, 234, 180);

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5, 187, 118, 240);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 187, 118, 240);

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (122, 187, 234, 240);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (122, 187, 234, 240);




  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[8])));
  //myGLCD.print(buffer, 20, 147);                                   // "Отмена"


  //myGLCD.setColor(0, 0, 255);
  //myGLCD.fillRoundRect (130, 130, 240, 180);
  //myGLCD.setColor(255, 255, 255);
  //myGLCD.drawRoundRect (130, 130, 240, 180);
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[9])));
  //myGLCD.print(buffer, 155, 147);                                 // "Ввод"


  //myGLCD.setColor(0, 0, 255);
  //myGLCD.fillRoundRect (250, 130, 300, 180);
  //myGLCD.setColor(255, 255, 255);
  //myGLCD.drawRoundRect (250, 130, 300, 180);
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[10])));
  //myGLCD.print(buffer, 252, 147);                                  // Вых
  //myGLCD.setBackColor (0, 0, 0);
}





void setup_pin()
{
  pinMode(led_13, OUTPUT);                             //
  digitalWrite(led_13, HIGH);                          //
 
}


void setup()
{
	myGLCD.InitLCD(0);
	myGLCD.clrScr();
	myGLCD.setFont(BigFont);
	myTouch.InitTouch();
	delay(1000);
	//myTouch.setPrecision(PREC_MEDIUM);
	myTouch.setPrecision(PREC_HI);
	//myTouch.setPrecision(PREC_EXTREME);
	myButtons.setTextFont(BigFont);
	myButtons.setSymbolFont(Dingbats1_XL);
	Serial.begin(9600);                                    // Подключение к USB ПК
	Serial1.begin(115200);                                 // Подключение к
	Serial2.begin(115200);                                 // Подключение к
	Serial3.begin(115200);                                 // Подключение к
	Serial.println(" ");
	Serial.println(" ***** Start system  *****");
	Serial.println(" ");
	Wire.begin();
	if (!RTC.begin())                                      // Настройка часов
	{
	Serial.println("RTC failed");
	while (1);
	};
    serial_print_date();                           // Печать даты и времени
	setup_pin();
	Serial.print(F("FreeRam: "));
	Serial.println(FreeRam());
	drawButtons();
	Serial.println(" ");                                   //
	Serial.println("System initialization OK!.");          // Информация о завершении настройки


}

void loop()
{

  /* add main program code here */

}
