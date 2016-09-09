


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

//++++++++++++++++++++++++++++ Переменные для цифровой клавиатуры +++++++++++++++++++++++++++++
//int x, y, z;
char stCurrent[20]    = "";                                       // Переменная хранения введенной строки
int stCurrentLen      = 0;                                        // Переменная хранения длины введенной строки
int stCurrentLen1     = 0;                                        // Переменная временного хранения длины введенной строки
char stLast[20]       = "";                                       // Данные в введенной строке строке.
//int ret               = 0;                                        // Признак прерывания операции
//-------------------------------------------------------------------------------------------------




const char  txt_botton_otmena[]     PROGMEM  = "O""\xA4\xA1""e""\xA2""a";                                       // "Отмена"
const char  txt_botton_vvod[]       PROGMEM  = "B\x97o\x99 ";                                                   // "Ввод"
const char  txt_botton_ret[]        PROGMEM  = "B""\xAB""x""o\x99" ;                                            // "Выход"
const char  txt_perepolnenie[]      PROGMEM  = "\x89""EPE""\x89O\x88HEH\x86""E!" ;                              // "Переполнение"
const char  txt_empty[]             PROGMEM  = "\x80\x8A\x8B\x8B""EP \x89\x8A""CTO\x87!";                       // "БУФФЕР ПУСТОЙ"

char buffer[30];
const char* const table_message[] PROGMEM =
{
 txt_botton_otmena,               // 0 "O""\xA4\xA1""e""\xA2""a";                                               // "Отмена"
 txt_botton_vvod,                 // 1 "B\x97o\x99 ";                                                           // "Ввод"
 txt_botton_ret,                  // 2  "B""\xAB""x";                                                           // "Вых"
 txt_perepolnenie,                // 3 "\x89""EPE""\x89O\x88HEH\x86""E!"                                        // "Переполнение"
 txt_empty                        // 4 "\x80\x8A\x8B\x8B""EP \x89\x8A""CTO\x87!"                                // "БУФФЕР ПУСТОЙ"
};



















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



void drawButtons0_1() // Отображение цифровой клавиатуры
{
	 myGLCD.setBackColor( 0, 0, 255);

	myGLCD.setColor(0, 0, 255);                    //1
	myGLCD.fillRoundRect (5, 5, 60, 60);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 5, 60, 60);
	myGLCD.printNumI(1, 25, 25);                   //"1"
	
	myGLCD.setColor(0, 0, 255);                    //2
	myGLCD.fillRoundRect (63, 5, 118, 60);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 5, 118, 60);
	myGLCD.printNumI(2, 83, 25);                   //"2"

	myGLCD.setColor(0, 0, 255);                    //3
	myGLCD.fillRoundRect (121, 5, 176, 60);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 5, 176, 60);
	myGLCD.printNumI(3, 141, 25);                  //"3"

	myGLCD.setColor(0, 0, 255);                    //4
	myGLCD.fillRoundRect (179, 5, 234, 60);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 5, 234, 60);
	myGLCD.printNumI(4, 199, 25);                  //"4"

	myGLCD.setColor(0, 0, 255);                    //5
	myGLCD.fillRoundRect (5, 63, 60, 118);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 63, 60, 118);
	myGLCD.printNumI(5, 25, 83);                   //"5"
	
	myGLCD.setColor(0, 0, 255);                    //6
	myGLCD.fillRoundRect (63, 63, 118, 118);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 63, 118, 118);
	myGLCD.printNumI(6, 83, 83);                   //"6"

	myGLCD.setColor(0, 0, 255);                    //7
	myGLCD.fillRoundRect (121, 63, 176, 118);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 63, 176, 118);
	myGLCD.printNumI(7, 141, 83);                  //"7"

	myGLCD.setColor(0, 0, 255);                    //8
	myGLCD.fillRoundRect (179, 63, 234, 118);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 63, 234, 118);
	myGLCD.printNumI(8, 199, 83);                  //"8"

	myGLCD.setColor(0, 0, 255);                    //9
	myGLCD.fillRoundRect (5, 121, 60, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 121, 60, 176);
	myGLCD.printNumI(9, 25, 141);                  //"9"

	myGLCD.setColor(0, 0, 255);                    //0
	myGLCD.fillRoundRect (63, 121, 118, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 121, 118, 176);
	myGLCD.printNumI(0, 83, 141);                  //"0"

}

void drawButtonsTXT() // Отображение кнопок управления  клавиатуры
{
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 121, 234, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 121, 234, 176);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[1])));
	myGLCD.print(buffer, 145, 141);                                 // "Ввод"
 
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5, 179, 118, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 179, 118, 234);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[0])));
	myGLCD.print(buffer, 14, 199);                                   // "Отмена"

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 179, 234, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 179, 234, 234);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
	myGLCD.print(buffer, 137, 199);                                  // Вых
	myGLCD.setBackColor (0, 0, 0);
}

void drawButtonsABCDEF() // Отображение кнопок управления  клавиатуры
{
	myGLCD.setColor(0, 0, 255);                    // A
	myGLCD.fillRoundRect (121, 121, 176, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 121, 176, 176);
	myGLCD.print("A", 141, 141);                  // "A"

	myGLCD.setColor(0, 0, 255);                    // B
	myGLCD.fillRoundRect (179, 121, 234, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 121, 234, 176);
	myGLCD.print("B", 199, 141);                   // "B"

	myGLCD.setColor(0, 0, 255);                    // C
	myGLCD.fillRoundRect (5, 179, 60, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 179, 60, 234);
	myGLCD.print("C", 25, 199);                   // "C"
	
	myGLCD.setColor(0, 0, 255);                    // D
	myGLCD.fillRoundRect (63, 179, 118, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 179, 118, 234);
	myGLCD.print("D", 83, 199);                   // "D"

	myGLCD.setColor(0, 0, 255);                    // E
	myGLCD.fillRoundRect (121, 179, 176, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 179, 176, 234);
	myGLCD.print("E", 141, 199);                  // "E"

	myGLCD.setColor(0, 0, 255);                    // F
	myGLCD.fillRoundRect (179, 179, 234, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 179, 234, 234);
	myGLCD.print("F", 199, 199);               // "F"
	
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5, 237, 118, 292);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 237, 118, 292);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
	myGLCD.print(buffer, 24, 257);                                   // "Выход"
	
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 237, 234, 292);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 237, 234, 292);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[1])));
	myGLCD.print(buffer, 145, 257);                                 // "Ввод"
 	myGLCD.setBackColor (0, 0, 0);
}


void klav1()
{
while (true)
  {
	  int x,y;
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
	  if ((y >= 5) && (y <= 60))                                    // Первый ряд
      {
       if ((x >= 5) && (x <= 60))                                   // Button: 1
        {
          waitForIt(5, 5, 60, 60);
          updateStr('1');
        }
        if ((x >= 63) && (x <= 118))                                // Button: 2
        {
          waitForIt(63, 5, 118, 60);
          updateStr('2');
        }
        if ((x >= 121) && (x <= 176))                               // Button: 3
        {
          waitForIt(121, 5, 176, 60);
          updateStr('3');
        }
        if ((x >= 179) && (x <= 234))                               // Button: 4
        {
          waitForIt(179, 5, 234, 60);
          updateStr('4');
        }
	  }

	  if ((y >= 63) && (y <= 118))                                  // Второй ряд
      {
       if ((x >= 5) && (x <= 60))                                   // Button: 5
        {
          waitForIt(5, 63, 60, 118);
          updateStr('5');
        }
        if ((x >= 63) && (x <= 118))                                // Button: 6
        {
          waitForIt(63, 63, 118, 118);
          updateStr('6');
        }
        if ((x >= 121) && (x <= 176))                               // Button: 7
        {
          waitForIt(121, 63, 176, 118);
          updateStr('7');
        }
        if ((x >= 179) && (x <= 234))                               // Button: 8
        {
          waitForIt(179, 63, 234, 118);
          updateStr('8');
        }
	  }

	  if ((y >= 121) && (y <= 176))                                 // Третий ряд
      {
       if ((x >= 5) && (x <= 60))                                   // Button: 9
        {
          waitForIt(5, 121, 60, 176);
          updateStr('9');
        }
        if ((x >= 63) && (x <= 118))                                // Button: 0
        {
          waitForIt(63, 121, 118, 176);
          updateStr('0');
        }
        if ((x >= 121) && (x <= 234))                               // Button: "Ввод"
        {
          waitForIt(121, 121, 234, 176);
           if (stCurrentLen > 0)
           {
            for (int x = 0; x < stCurrentLen + 1; x++)
            {
              stLast[x] = stCurrent[x];
            }
            stCurrent[0] = '\0';
            stLast[stCurrentLen + 1] = '\0';
            stCurrentLen1 = stCurrentLen;
            stCurrentLen = 0;
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect(0, 300, 239, 319);
            myGLCD.setColor(0, 255, 0);
            myGLCD.print(stLast, LEFT, 300);
         //  break;
          }
          else
          {
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect(0, 300, 239, 319);
            myGLCD.setColor(255, 0, 0);
			strcpy_P(buffer, (char*)pgm_read_word(&(table_message[4])));
            myGLCD.print(buffer, CENTER, 300);                                  //"БУФФЕР ПУСТОЙ!"
            delay(500);
            myGLCD.print("                ", CENTER, 300);
            delay(500);
            myGLCD.print(buffer, CENTER, 300);                                 //"БУФФЕР ПУСТОЙ!"
            delay(500);
            myGLCD.print("                ", CENTER, 300);
            myGLCD.setColor(0, 255, 0);
          }
        }
	  }

	  if ((y >= 179) && (y <= 234))                                           // Четвертый ряд
      {
        if ((x >= 5) && (x <= 118))                                           // Button: "Отмена"
        {
          waitForIt(5, 179, 118, 234);
          stCurrent[0] = '\0';
          stCurrentLen = 0;
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect(0, 300, 239, 319);                                   // Очистить строку на дисплее
        }
        if ((x >= 121) && (x <= 234)) // Button: "Выход"
        {
          waitForIt(121, 179, 234, 234);
         //myGLCD.clrScr();
          //myGLCD.setBackColor(VGA_BLACK);
          //ret = 1;
          stCurrent[0] = '\0';
          stCurrentLen = 0;
          //break;
        }
	  }
	}
  }
}


void klavABCDEF()
{
while (true)
  {
	  int x,y;
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
	  if ((y >= 5) && (y <= 60)) // Первый ряд
      {
       if ((x >= 5) && (x <= 60)) // Button: 1
        {
          waitForIt(5, 5, 60, 60);
          updateStr('1');
        }
        if ((x >= 63) && (x <= 118)) // Button: 2
        {
          waitForIt(63, 5, 118, 60);
          updateStr('2');
        }
        if ((x >= 121) && (x <= 176)) // Button: 3
        {
          waitForIt(121, 5, 176, 60);
          updateStr('3');
        }
        if ((x >= 179) && (x <= 234)) // Button: 4
        {
          waitForIt(179, 5, 234, 60);
          updateStr('4');
        }
	  }

	  if ((y >= 63) && (y <= 118))    // Второй ряд
      {
       if ((x >= 5) && (x <= 60)) // Button: 5
        {
          waitForIt(5, 63, 60, 118);
          updateStr('5');
        }
        if ((x >= 63) && (x <= 118)) // Button: 6
        {
          waitForIt(63, 63, 118, 118);
          updateStr('6');
        }
        if ((x >= 121) && (x <= 176)) // Button: 7
        {
          waitForIt(121, 63, 176, 118);
          updateStr('7');
        }
        if ((x >= 179) && (x <= 234)) // Button: 8
        {
          waitForIt(179, 63, 234, 118);
          updateStr('8');
        }
	  }

	  if ((y >= 121) && (y <= 176))    // Третий ряд
      {
       if ((x >= 5) && (x <= 60)) // Button: 9
        {
          waitForIt(5, 121, 60, 176);
          updateStr('9');
        }
        if ((x >= 63) && (x <= 118)) // Button: 0
        {
          waitForIt(63, 121, 118, 176);
          updateStr('0');
        }
        if ((x >= 121) && (x <= 176)) // Button: A
        {
          waitForIt(121, 121, 176, 176);
          updateStr('A');
        }
        if ((x >= 179) && (x <= 234)) // Button: B
        {
          waitForIt(179, 121, 234, 176);
          updateStr('B');
        }
	  }
	 
	  if ((y >= 179) && (y <= 234))    // Четвертый ряд
      {
       if ((x >= 5) && (x <= 60)) // Button: C
        {
          waitForIt(5, 179, 60, 234);
          updateStr('C');
        }
        if ((x >= 63) && (x <= 118)) // Button: D
        {
          waitForIt(63, 179, 118, 234);
          updateStr('D');
        }
        if ((x >= 121) && (x <= 176)) // Button: E
        {
          waitForIt(121, 179, 176, 234);
          updateStr('E');
        }
        if ((x >= 179) && (x <= 234)) // Button: F
        {
          waitForIt(179, 179, 234, 234);
          updateStr('F');
        }
	  }
	 
	  if ((y >= 237) && (y <= 292))                        // Пятый ряд
      {
        if ((x >= 5) && (x <= 118))                        // Button:    "Выход"
        {
          waitForIt(5, 237, 118, 292);
          //myGLCD.clrScr();
          //myGLCD.setBackColor(VGA_BLACK);
          //ret = 1;
          stCurrent[0] = '\0';
          stCurrentLen = 0;
          //break;
        }
        if ((x >= 121) && (x <= 234))                      // Button:   "Ввод"
        {
          waitForIt(121, 237, 234, 292);
           if (stCurrentLen > 0)
           {
            for (int x = 0; x < stCurrentLen + 1; x++)
            {
              stLast[x] = stCurrent[x];
            }
            stCurrent[0] = '\0';
            stLast[stCurrentLen + 1] = '\0';
            stCurrentLen1 = stCurrentLen;
            stCurrentLen = 0;
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect(0, 300, 239, 319);
            myGLCD.setColor(0, 255, 0);
            myGLCD.print(stLast, LEFT, 300);
         //  break;
          }
          else
          {
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect(0, 300, 239, 319);
            myGLCD.setColor(255, 0, 0);
			strcpy_P(buffer, (char*)pgm_read_word(&(table_message[4])));
            myGLCD.print(buffer, CENTER, 300);                                  //"БУФФЕР ПУСТОЙ!"
            delay(500);
            myGLCD.print("                 ", CENTER, 300);
            delay(500);
            myGLCD.print(buffer, CENTER, 300);                                 //"БУФФЕР ПУСТОЙ!"
            delay(500);
            myGLCD.print("                 ", CENTER, 300);
            myGLCD.setColor(0, 255, 0);
          }
        }
	  }
	}
  }
}


void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
  myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

void updateStr(int val)
{
  if (stCurrentLen < 15)
  {
    stCurrent[stCurrentLen] = val;
    stCurrent[stCurrentLen + 1] = '\0';
    stCurrentLen++;
    myGLCD.setColor(0, 255, 0);
    myGLCD.print(stCurrent, LEFT, 300);
  }
  else
  {                                                             // Вывод строки "ПЕРЕПОЛНЕНИЕ!"
	myGLCD.setColor(0, 0, 0);
	myGLCD.fillRect(0, 300, 239, 319);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[3])));
    myGLCD.setColor(255, 0, 0);
	myGLCD.print("               ", CENTER, 300);
    myGLCD.print(buffer, CENTER, 300);                         // ПЕРЕПОЛНЕНИЕ!
    delay(500);
    myGLCD.print("               ", CENTER, 300);
    delay(500);
    myGLCD.print(buffer, CENTER, 300);                         // ПЕРЕПОЛНЕНИЕ!
    delay(500);
    myGLCD.print("               ", CENTER, 300);
    myGLCD.setColor(0, 255, 0);
  }
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
	myTouch.InitTouch(0);
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
	drawButtons0_1();
	//drawButtonsTXT();
	drawButtonsABCDEF();
	Serial.println(" ");                                   //
	Serial.println("System initialization OK!.");          // Информация о завершении настройки


}

void loop()
{

 //klav1();
	klavABCDEF();
 delay(100);

}
