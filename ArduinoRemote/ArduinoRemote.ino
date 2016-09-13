


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
#include <XBee.h>

#define led_13 13  
#define KN1 A8  
#define KN2 A9  
#define KN3 A7 
#define KN4 A10  
#define KN5 A4  
#define KN6 A6  
#define KN7 A3  
#define KN8 A5  

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

unsigned long timeF;
int flag_time = 0;


RTC_DS1307 RTC;                                       // define the Real Time Clock object

//++++++++++++++++++++++++++++ Переменные для цифровой клавиатуры +++++++++++++++++++++++++++++
//int x, y, z;
char stCurrent[20]    = "";                                       // Переменная хранения введенной строки
int stCurrentLen      = 0;                                        // Переменная хранения длины введенной строки
int stCurrentLen1     = 0;                                        // Переменная временного хранения длины введенной строки
char stLast[20]       = "";                                       // Данные в введенной строке строке.
//int ret               = 0;                                        // Признак прерывания операции
//-------------------------------------------------------------------------------------------------
float power60 = 0;                       // Измерение источника питания 6,0 вольт
float power50 = 0;                       // Измерение источника питания 5,0 вольт
float power33 = 0;                       // Измерение источника питания 3,3 вольт
unsigned long currentTime;
unsigned long loopTime;
int time_power    = 1000;

//---------------------------------------------------------------------------------
int adr_zigbee_coordinator_h = 204;       //Адрес координатора старший
int adr_zigbee_coordinator_l = 208;       //Адрес координатора младший
int adr_zigbee_network       = 212;       //Адрес сети
int adr_variant_sys          = 241;       //
int adr_n_user               = 140;                     // Адрес хранения № номера пользователя








//----------------------------------------------------------------------

const char  txt_botton_otmena[]                PROGMEM  = "O""\xA4\xA1""e""\xA2""a";                                       // "Отмена"
const char  txt_botton_vvod[]                  PROGMEM  = "B\x97o\x99 ";                                                   // "Ввод"
const char  txt_botton_ret[]                   PROGMEM  = "B""\xAB""x""o\x99" ;                                            // "Выход"
const char  txt_perepolnenie[]                 PROGMEM  = "\x89""EPE""\x89O\x88HEH\x86""E!" ;                              // "Переполнение"
const char  txt_empty[]                        PROGMEM  = "\x80\x8A\x8B\x8B""EP \x89\x8A""CTO\x87!";                       // "БУФФЕР ПУСТОЙ"
const char  txt_menu1[]                        PROGMEM  = "MEH""\x94"" 1";                                                 // "Переполнение"
const char  txt_menu2[]                        PROGMEM  = "MEH""\x94"" 2";                                                 // "БУФФЕР ПУСТОЙ"
const char  txt_info_ZigBee_ALL[]              PROGMEM = "\x86\xA2\xA5op\xA1""a""\xA6\x9D\xAF ZigBee";// Информация ZigBee
const char  txt_info_ZigBee_USB[]              PROGMEM = "o\xA4\xA3p""a""\x97\xA0""e""\xA2""a"" USB port";//
const char  txt_info_ZigBee_MY[]               PROGMEM = "Network Address MY";//
const char  txt_info_ZigBee_CoordinatorAdr[]   PROGMEM = "Address Coordinator";//
const char  txt_info_ZigBee_Serial[]           PROGMEM = "Serial Number SH,SL";//
const char  txt_info_ZigBee_Network_Address[]  PROGMEM = "Network (MY) = ";//
const char  txt_info_ZigBee_Operating_PAN_OP[] PROGMEM = "PAN ID (OP)  = ";//
const char  txt_info_ZigBee_Operating_ID[]     PROGMEM = "ID (ID)      = ";//
const char  txt_info_ZigBee_Chanel_CH[]        PROGMEM = "Chanel (CH)  = ";//
const char  txt_info_ZigBee_Association[]      PROGMEM = "Association(AI)=";//
const char  txt_info_ZigBee_Baud_Rate[]        PROGMEM = "Baud Rate(BD)=";//
const char  txt_info_ZigBee_Voltage []         PROGMEM = "Voltage (%V) =";//
const char  txt_return[]                       PROGMEM = "\x85""a\x97""ep\xA8\xA2\xA4\xAC \xA3poc\xA1o\xA4p";// Завершить просмотр


char buffer[30];
const char* const table_message[] PROGMEM =
{
 txt_botton_otmena,                // 0 "O""\xA4\xA1""e""\xA2""a";                                               // "Отмена"
 txt_botton_vvod,                  // 1 "B\x97o\x99 ";                                                           // "Ввод"
 txt_botton_ret,                   // 2  "B""\xAB""x";                                                           // "Вых"
 txt_perepolnenie,                 // 3 "\x89""EPE""\x89O\x88HEH\x86""E!"                                        // "Переполнение"
 txt_empty,                        // 4 "\x80\x8A\x8B\x8B""EP \x89\x8A""CTO\x87!"                                // "БУФФЕР ПУСТОЙ"
 txt_menu1,                        // 5 "MEH""\x94"" 1";                                                         // "МЕНЮ 1"
 txt_menu2,                        // 6 "MEH""\x94"" 2";                                                         // "МЕНЮ 2"
 txt_info_ZigBee_ALL,              // 7 "\x86\xA2\xA5op\xA1""a""\xA6\x9D\xAF ZigBee";// Информация ZigBee
 txt_info_ZigBee_USB,              // 8 "o\xA4\xA3p""a""\x97\xA0""e""\xA2""a"" USB port";//
 txt_info_ZigBee_MY,               // 9 "Network Address MY";//
 txt_info_ZigBee_CoordinatorAdr,   // 10 "Address Coordinator";//
 txt_info_ZigBee_Serial,           // 11 "Serial Number SH,SL";//
 txt_info_ZigBee_Network_Address,  // 12 "Network (MY) = ";//
 txt_info_ZigBee_Operating_PAN_OP, // 13 "PAN ID (OP)  = ";//
 txt_info_ZigBee_Operating_ID,     // 14 "ID (ID)      = ";//
 txt_info_ZigBee_Chanel_CH,        // 15 "Chanel (CH)  = ";//
 txt_info_ZigBee_Association,      // 16 "Association(AI)=";//
 txt_info_ZigBee_Baud_Rate,        // 17 "Baud Rate(BD)=";//
 txt_info_ZigBee_Voltage,          // 18 "Voltage (%V) =";//






};



// ************ ZigBee******************
//создаем XBee библиотеку
XBee xbee = XBee();

//Это создает экземпляр объекта "response" "ответ" обрабатывать пакеты Xbee
XBeeResponse response = XBeeResponse();
//Это создает экземпляр объекта "rx" на процесс Xbee Series 2 API пакеты
ZBRxResponse rx = ZBRxResponse();
//Это создает экземпляр объекта "msr" процесс associate/disassociate packets (PAN membership)
ModemStatusResponse msr = ModemStatusResponse();

ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();

//Строка с данными
uint8_t payload[50] ;// = {3, 4,};
uint8_t payload1[10] ;// = {3, 4,};

//Два 32-битных половинки th4 64-разрядный адрес
long XBee_Addr64_MS;// = 0x0013a200;
long XBee_Addr64_LS;// = 0x4054de2d;
//16-разрядный адрес
int XBee_Addr16;// = 0xffff;

int zki = 0;

int Len_ZegBee = 0;
unsigned char info_ZigBee_data[10];
unsigned char info_ZigBee_data1[10];
unsigned long ZigBee_data2;
char* simbol_ascii[2];
char   cmd;
char * pEnd;

// serial high
uint8_t shCmd[] = {'S','H'}; // Старший байт адреса
// serial low
uint8_t slCmd[] = {'S','L'}; // Младший байт адреса
// association status
uint8_t assocCmd[] = {'A','I'}; // Индикация присоединения 
								/*
								Считывает информацию о последнем запросе узла на присоединение:
								0x00 – Завершено успешно - Координатор стартовал илиМаршрутизатор/Конечное устройство
								обнаружило и присоединилось родительскому устройству.
								0x21 – Сканирование не обнаружило сети
								0x22 – Сканирование не обнаружило работающей сети с текущими установками SC и ID
								0x23 – Работающий Координатор или Маршрутизаторы найдены, но они не дали разрешение на
								присоединение к сети (истекло время NJ)
								0x27 – Попытка присоединения не удалась
								0x2A – Запуск Координатора не удался
								0xFF – Идет поиск родительского устройства
								*/
uint8_t irCmd[]    = {'I','R'};
uint8_t opCmd[]    = {'O','P'}; // Номер сети (PAN ID)
uint8_t IDCmd[]    = {'I','D'}; // Номер сети (ID)
uint8_t MYCmd[]    = {'M','Y'}; // Номер сети (16-bit Network Adress
uint8_t CHCmd[]    = {'C','H'}; // Номер Радиоканала
uint8_t SCCmd[]    = {'S','C'}; // Scan Channel
uint8_t BDCmd[]    = {'B','D'}; // Скорость канала (Baud Rate )
uint8_t VoltCmd[]  = {'%','V'}; // Напряжение питания Считывает напряжение на выводе Vcc. Для преобразования значения
								// в мВ, поделите значение на 1023 и умножьте на 1200. Значение %V равное 0x8FE (или 2302 в
								// десятичном виде) соответствует 2700мВ или 2.70В

uint8_t dhCmd[]    = {'D','H'}; // Старший байт адреса
uint8_t dlCmd[]    = {'D','L'}; // Младший байт адреса
uint8_t d0Cmd[]    = {'D','0'}; //
uint8_t WRCmd[]    = {'W','R'}; // Запись в модуль параматров
								// Примечание: Если введена команда WR, до получения ответа "OK\r" не должно вводится
								// дополнительных символов
uint8_t FRCmd[]    = {'F','R'}; // Перезапуск программного обеспечения
uint8_t NRCmd[]    = {'N','R'}; // Перезапуск сети 
								// Если NR = 0: Переустанавливает параметры сети на узле, вызвавшем команду. 
								// Если NR = 1:Отправляетшироковещательную передачу для перезапуска параметров на всех узлах сети.
uint8_t d0Value[]  = { 0x2 };
uint8_t irValue[]  = { 0xff, 0xff };
uint8_t IDValue[]  = { 0x02, 0x34 };

uint8_t command[]  = {'I','D'}; // Номер сети (ID)
uint8_t commandValue[]  = { 0x02, 0x35 };
uint8_t commandValueLength = 0x2 ;

// SH + SL Address of receiving XBee

XBeeAddress64 addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
//Это создает экземпляр объекта "txStatus" процесс благодарности прислал Xbee Series 2 API пакеты
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

//XBeeAddress64 remoteAddress = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
AtCommandRequest atRequest = AtCommandRequest(shCmd);
AtCommandRequest arRequestMod = AtCommandRequest(command,commandValue, commandValueLength);
AtCommandResponse atResponse = AtCommandResponse();
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(addr64, irCmd, irValue, sizeof(irValue));
// Create a Remote AT response object
RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();


//********************************
	byte funcType;
	word field1;
	word field2;
	byte *_msg, _len;
	word _baud, _crc;

//-----------------------------------------------------------------------------------------------
















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


void drawGlavMenu()
{
	 myGLCD.setBackColor( 0, 0, 255);

	myGLCD.setColor(0, 0, 255);                    //1
	myGLCD.fillRoundRect (5, 5, 94, 90);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 5,94, 90);
	myGLCD.printNumI(1, 10, 10);                   //"1"
	
	myGLCD.setColor(0, 0, 255);                    //2
	myGLCD.fillRoundRect (97, 5, 186, 90);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (97, 5, 186, 90);
	myGLCD.printNumI(3, 102, 10);                  //"2"

	myGLCD.setColor(0, 0, 255);                    //3
	myGLCD.fillRoundRect (5, 93, 94, 178);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 93,94, 178);
	myGLCD.printNumI(2, 10, 98);                   //"3"
	
	myGLCD.setColor(0, 0, 255);                    //4
	myGLCD.fillRoundRect (97, 93, 186, 178);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (97, 93, 186, 178);
	myGLCD.printNumI(4, 102, 98);                   //"4"
//------------------------------------------------------------------
	myGLCD.setColor(0, 0, 255);                    //1
	myGLCD.fillRoundRect (5, 183, 60, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 183, 60, 243);
	myGLCD.printNumI(1, 25, 205);                   //"1"
	
	myGLCD.setColor(0, 0, 255);                    //2
	myGLCD.fillRoundRect (63, 183, 118, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 183, 118, 243);
	myGLCD.printNumI(2, 83, 205);                   //"2"

	myGLCD.setColor(0, 0, 255);                    //3
	myGLCD.fillRoundRect (121, 183, 176, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 183, 176, 243);
	myGLCD.printNumI(3, 141, 205);                  //"3"

	myGLCD.setColor(0, 0, 255);                    //4
	myGLCD.fillRoundRect (179, 183, 234, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 183, 234, 243);
	myGLCD.printNumI(4, 199, 205);                  //"4"
//----------------------------------------------------------
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5, 248, 118, 293);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 248, 118, 293);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[5])));
	myGLCD.print(buffer, 16, 262);                                      // "МЕНЮ 1"

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 248, 234, 293);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 248, 234, 293);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[6])));
	myGLCD.print(buffer, 130, 262);                                     //"МЕНЮ 2"
	myGLCD.setBackColor (0, 0, 0);
}

void klav_Glav_Menu()
{
while (true)
  {

	  	myGLCD.setColor(255, 255, 255);
	if(digitalRead(KN1) == false)
		{
			myGLCD.printNumI(1, 200, 60);
	    }
	if(digitalRead(KN2) == LOW)
		{
			myGLCD.printNumI(2, 200, 60);
	}
	if(digitalRead(KN3) == LOW)
		{
			myGLCD.printNumI(3, 200, 60);
	}
	if(digitalRead(KN4) == LOW)
		{
			myGLCD.printNumI(4, 200, 60);
	}
	if(digitalRead(KN5) == false)
		{
			myGLCD.printNumI(5, 200, 60);
	    }
	if(digitalRead(KN6) == LOW)
		{
			myGLCD.printNumI(6, 200, 60);
	}
	if(digitalRead(KN7) == LOW)
		{
			myGLCD.printNumI(7, 200, 60);
	}
	if(digitalRead(KN8) == LOW)
		{
			myGLCD.printNumI(8, 200, 60);
	}


	int x,y;
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
	  if ((y >= 5) && (y <= 90))                                    // Первый ряд
      {
       if ((x >= 5) && (x <= 94))                                   // Button: 1
        {
          waitForIt(5, 5, 94, 90);
         // updateStr('1');
        }
        if ((x >= 97) && (x <= 186))                                // Button: 2
        {
          waitForIt(97, 5, 186, 90);
        //  updateStr('2');
        }
	  }
	 
	  if ((y >= 93) && (y <= 178))                                    // Первый ряд
      {
       if ((x >= 5) && (x <= 94))                                   // Button: 1
        {
          waitForIt(5, 93, 94, 178);
       //   updateStr('3');
        }
        if ((x >= 97) && (x <= 186))                                // Button: 2
        {
          waitForIt(97, 93, 186, 178);
        //  updateStr('4');
        }
	  }
	 
	  if ((y >= 183) && (y <= 243))                                    // Nh ряд
      {
       if ((x >= 5) && (x <= 60))                                   // Button: 1
        {
          waitForIt(5, 183, 60, 243);
        //  updateStr('1');
        }
        if ((x >= 63) && (x <= 118))                                // Button: 2
        {
          waitForIt(63, 183, 118, 243);
        //  updateStr('2');
        }
        if ((x >= 121) && (x <= 176))                               // Button: 3
        {
          waitForIt(121, 183, 176, 243);
        //  updateStr('3');
        }
        if ((x >= 179) && (x <= 234))                               // Button: 4
        {
          waitForIt(179, 183, 234, 243);
         // updateStr('4');
        }
	  }

	  if ((y >= 248) && (y <= 293))                                           // Четвертый ряд
      {
        if ((x >= 5) && (x <= 118))                                           // Button:
        {
          waitForIt(5, 248, 118, 293);
  
        }
        if ((x >= 121) && (x <= 234)) // Button: 
        {
          waitForIt(121, 248, 234, 293);
 
        }
	  }





	}
  }



}

void test_power()
{
  currentTime = millis();                           // считываем время, прошедшее с момента запуска программы
  if (currentTime >= (loopTime + time_power))
  { // сравниваем текущий таймер с переменной loopTime + 1 секунда
    loopTime = currentTime;                          // в loopTime записываем новое значение
    myGLCD.setFont(SmallFont);
    myGLCD.setColor(0, 255, 0);
    int power = analogRead(A11);
    // Serial.println(power);
    power60 = power * (5.0 / 1024.0 * 2*0.965);
    //  Serial.println(power60);
    if (power60 > 5.8) myGLCD.print("\xB0", 221, 5);
    else if (power60 <= 5.8 && power60 > 5.6) myGLCD.print("\xB1", 212, 5);
    else if (power60 <= 5.6 && power60 > 5.4) myGLCD.print("\xB2", 212, 5);
    else if (power60 <= 5.4 && power60 > 5.2) myGLCD.print("\xB3", 212, 5);

    else if (power60 <= 5.2)
    {
      myGLCD.setColor(255, 0, 0);
      myGLCD.print("\xB4", 212, 5);
    }
    myGLCD.printNumF(power60, 2, 200, 20);
    myGLCD.setColor(255, 255, 255);
    power = analogRead(A1);
    power50 = power * (5.0 / 1024.0*2*0.965);
    myGLCD.printNumF(power50, 2, 200, 30);
    power = analogRead(A2);
    power33 = power * (5.0 / 1024.0*0.965);
    myGLCD.printNumF(power33, 2, 200, 40);
    myGLCD.setFont(BigFont);
  }
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

void ZigBeeRead()
{
  xbee.readPacket();   // Получить пакет
	
	if (xbee.getResponse().isAvailable())  //Проверить наличие данных
	  {
		// есть что-то
		 //   Serial.println("Got an rx packet8888!");
	  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) 
		  {
			// получен zb rx packet
		
			// Теперь заполнить наш класс ZB гх
			xbee.getResponse().getZBRxResponse(rx); // пакет rx заполнен
	  
			// Serial.println("Got an rx packet!");
			
			if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) 
				{
					// отправитель получил  ответ ACK
					// Serial.println("packet acknowledged");
				} 
			else 
				{
				   Serial.println("packet not acknowledged");
				}
		
					 //Serial.print("checksum is ");
					 //Serial.println(rx.getChecksum(), HEX);    // Контрольная сумма

					 //Serial.print("All packet length is ");
					 //Serial.println(rx.getPacketLength(), DEC); // Длина пакета общего пакета
					 //Serial.print("Data packet length is ");
					 //Serial.println(rx.getDataLength(), DEC); // Длина пакета пакета данных

				for (int i = 0; i < rx.getDataLength(); i++)    // Считать информацию длина пакета  в rx.getDataLength()
				 {
				   //Serial.print("payload [");                   //
				   //Serial.print(i, DEC);                        //
				   //Serial.print("] is ");                       //
				   //Serial.println(rx.getData()[i], HEX);        // Информация находится в rx.getData()[i]
				  }
		
				for (int i = 0; i < xbee.getResponse().getFrameDataLength(); i++) // Длина пакета в xbee.getResponse().getFrameDataLength()
				   {
					 //Serial.print("frame data [");                                //  frame data с 0 по 7 находится адрес отправителя
					 //Serial.print(i, DEC);
					 //Serial.print("] is ");                                       //
					 //Serial.println(xbee.getResponse().getFrameData()[i], HEX);   //  Информация пакета в xbee.getResponse().getFrameData()[i], длина пакета 
				   }
				Serial.println();
					//Получаем верхние 32-битное слово 64-битный адрес.  64-битный адрес 802.15.4 MAC адрес источника 
					// слоя адрес (например, "сожженные").
					XBee_Addr64_MS=(uint32_t(rx.getFrameData()[0]) << 24) + (uint32_t(rx.getFrameData()[1]) << 16) + (uint16_t(rx.getFrameData()[2]) << 8) + rx.getFrameData()[3];
					//Получаем ниже 32-битное слово...
					XBee_Addr64_LS=(uint32_t(rx.getFrameData()[4]) << 24) + (uint32_t(rx.getFrameData()[5]) << 16) + (uint16_t(rx.getFrameData()[6]) << 8) + rx.getFrameData()[7];
					//Отправить две части адреса программного обеспечения последовательного порта
					/*Serial.print("Addr64 MS: ");
					Serial.print(XBee_Addr64_MS,HEX);
					Serial.print('\n');
					Serial.print("Addr64 LS: ");
					Serial.print(XBee_Addr64_LS,HEX);
					Serial.print('\n');
					Serial.println();*/
							// IP-адреса в TCP/IP. 
					XBee_Addr16=rx.getRemoteAddress16();
					/*Serial.print("Addr16: ");
					Serial.println(XBee_Addr16,HEX);
*/



		   }
	  sl_XBee();
	  } 

	 else if (xbee.getResponse().isError()) //  Ошибка приема
		{
		  // Serial.print("error code:");
		  // Serial.println(xbee.getResponse().getErrorCode());            // Код ошибки xbee.getResponse().getErrorCode()
		}
}
void sl_XBee()// формировать ответ Координатору 
 {
 //copy the function type from the incoming query
	funcType = (rx.getData()[0]);

	//copy field 1 from the incoming query
	field1	= (rx.getData()[1] << 8) | rx.getData()[2];

	//copy field 2 from the incoming query
	field2  = (rx.getData()[3] << 8) | rx.getData()[4];
	
	//generate query response based on function type
	switch(funcType)
		{
// #define READ_ELECTRO          0x01  // чтение из памяти и передача XBee
// #define READ_GAZ		         0x02  // чтение из памяти и передача XBee
// #define READ_COLWATER 	     0x03  // чтение из памяти и передача XBee
// #define READ_HOTWATER	     0x04  // чтение из памяти и передача XBee
// #define READ_WAR_GAZ	         0x05  // чтение из памяти и передача XBee
// #define READ_WAR_TEMPERATURA  0x06  // чтение из памяти и передача XBee

		//case READ_ELECTRO:
		//	// Serial.println("READ_ELECTRO:");
		//	get_READ_ELECTRO_StatusXBee(funcType, field1, field2);
		//	break;
		//case READ_GAZ:
		//	//Serial.println("READ_GAZ:");
		//	get_READ_GAZ_StatusXBee(funcType, field1, field2);
		//	break;
		//case READ_COLWATER:
		//	//Serial.println("READ_COLWATER:");
		//	get_READ_COLWATER_StatusXBee(funcType, field1, field2);
		//	break;
		//case READ_HOTWATER:
		//	//Serial.println("READ_HOTWATER:");
		//	get_READ_HOTWATER_StatusXBee(funcType, field1, field2);
		//	break;
		//case READ_WAR_GAZ:
		//	//Serial.println("WRITE_DO:");
		//	get_READ_WAR_GAZ_StatusXBee(funcType, field1, field2);
		//	break;
		//case READ_WAR_TEMPERATURA:
		//	//Serial.println("WRITE_AO:");
		//	get_READ_WAR_TEMPERATURA_StatusXBee(funcType, field1, field2);
		//	break;
		default:
			return;
			break;
		}
//	Serial.println(field1, HEX);   
//	Serial.println(field2, HEX);   
	ZigBeeWrite();
 }
void ZigBeeWrite()
 {
  // break down 10-bit reading into two bytes and place in payload
  //разложить 10-битный код  в два байта и поместить в полезной нагрузке
  //pin5 = analogRead(5);
 /* pin5 = 1023;
  payload[0] = pin5 >> 8 & 0xff;
  payload[1] = pin5 & 0xff;
*/

	/* zki++;
		 if (zki == 254)
		 {
			 zki = 0;
		 }
	  payload[0] = zki;*/

  xbee.send(zbTx);

	 //  После отправки запроса TX, мы ожидаем ответ статуса
	 //  Ждать до половины секунды для реагирования состояния 
 ZigBeeRead();
  if (xbee.readPacket(500))
	   // xbee.readPacket();
	  {
	  
		// получил ответ! 
		// Должен быть znet tx status            	
		if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) 
			{
			  xbee.getResponse().getZBTxStatusResponse(txStatus);
			   // Получить статус доставки, пятый байт
			  if (txStatus.getDeliveryStatus() == SUCCESS)
				  {
					  // Успешно, можно радоваться.
					  // Serial.println("Success.  time to celebrate!");  
					  // flashLed(statusLed, 5, 50);
						myGLCD.setColor(VGA_LIME);
						myGLCD.fillRoundRect (278, 92, 318, 132);
						myGLCD.setColor(255, 255, 255);
						myGLCD.drawRoundRect (278, 92, 318, 132);
						myGLCD.setBackColor(0, 0, 0);
						delay(400); 
						myGLCD.setColor(0, 0, 0);
						myGLCD.fillRoundRect (278, 92, 318, 132);
						myGLCD.setColor(0, 0, 0);
						myGLCD.drawRoundRect (278, 92, 318, 132);
				  }
			  else 
				  {
					// the remote XBee did not receive our packet. is it powered on?
					// Управляемый XBee не ответил. Он включен?
					// flashLed(errorLed, 3, 500);
					  Serial.println("The remote XBee did not receive our packet. is it powered on?");  
				  }
			}
	  }
  else if (xbee.getResponse().isError())
	  {
		Serial.print("Error reading packet.  Error code: ");  
		Serial.println(xbee.getResponse().getErrorCode());
	  } 
  else 
	  {
		// local XBee did not provide a timely TX Status Response -- should not happen
		myGLCD.setColor(255 , 0, 0);
		myGLCD.fillRoundRect (278, 92, 318, 132);
		myGLCD.setColor(255, 255, 255);
		myGLCD.drawRoundRect (278, 92, 318, 132);
		myGLCD.setBackColor(0, 0, 0);
		delay(400); 
		myGLCD.setColor(0, 0, 0);
		myGLCD.fillRoundRect (278, 92, 318, 132);
		myGLCD.setColor(0, 0, 0);
		myGLCD.drawRoundRect (278, 92, 318, 132);
	  }

  delay(1000);
}
void XBee_Setup()
 {
	myGLCD.clrScr();   // Очистить экран CENTER
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (2, 2, 318, 25);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (2, 2, 318, 25);
	myGLCD.setColor(255, 255, 255);
	myGLCD.setBackColor(0, 0, 255);
	myGLCD.print("Setup XBee", CENTER, 5);
	myGLCD.print(txt_return, CENTER, 218);// Завершить просмотр 
	int x, y;
		while (true)
			{
				if (Serial2.available()) 
					{
						int inByte = Serial2.read();
						Serial.write(inByte);
					}
				
				// read from port 0, send to port 2:
			  if (Serial.available())
				    {
						int inByte = Serial.read();
						Serial2.write(inByte);
					}


				   
			  if (myTouch.dataAvailable())
					 {
						  myTouch.read();
						  x=myTouch.getX();
						  y=myTouch.getY();

					 if ((y>=2) && (y<=240))  // Upper row
					  {
						if ((x>=2) && (x<=319))  // Выход
						  {

							  waitForIt(10, 10, 60, 60);
							 return;
						  }
					   }
					}

		  }	
 }
void ZigBee_status()
{
	time_flag_start();
	int ZigBee_x, ZigBee_y, x, y;
	myGLCD.clrScr();   // Очистить экран CENTER
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (2, 2, 318, 25);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (2, 2, 318, 25);
	myGLCD.setColor(255, 255, 255);
	myGLCD.setBackColor(0, 0, 255);
	myGLCD.print(txt_info_ZigBee_ALL, CENTER, 5);

	int yZigBee = 32;
	int yDelta = 16;
							
	myGLCD.setBackColor(0, 0, 0);
	myGLCD.print(txt_info_ZigBee_CoordinatorAdr, CENTER, yZigBee);
	yZigBee = yZigBee + yDelta; // Форматирование текста, смещение
	myGLCD.setColor(0, 255, 255);
	myGLCD.print(String(XBee_Addr64_MS,HEX), 35, yZigBee);
	myGLCD.print(String(XBee_Addr64_LS,HEX), 165, yZigBee);
	yZigBee = yZigBee + yDelta;// Форматирование текста, смещение
	myGLCD.setColor(255, 255, 255);
	myGLCD.print(txt_info_ZigBee_Serial, CENTER, yZigBee);
	myGLCD.setColor(0, 255, 255);
	atRequest.setCommand(shCmd);  
	sendAtCommand();
	ZigBee_data2 = (unsigned long&)info_ZigBee_data1;
	yZigBee = yZigBee + yDelta;// Форматирование текста, смещение
	myGLCD.print(String(ZigBee_data2, HEX), 35, yZigBee);
					
	atRequest.setCommand(slCmd);  
	sendAtCommand();
	ZigBee_data2 = (unsigned long&)info_ZigBee_data1;
	myGLCD.print(String(ZigBee_data2, HEX), 165, yZigBee);
				  
	myGLCD.setColor(255, 255, 255);
	yZigBee = yZigBee + yDelta;// Форматирование текста, смещение
	myGLCD.print(txt_info_ZigBee_Network_Address, LEFT, yZigBee);
	atRequest.setCommand(MYCmd);  
	sendAtCommand();
	ZigBee_data2 = (unsigned long&)info_ZigBee_data1;
	//myGLCD.setColor(VGA_RED);
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(ZigBee_data2, HEX), RIGHT, yZigBee);

	myGLCD.setColor(255, 255, 255);
	yZigBee = yZigBee + yDelta;// Форматирование текста, смещение
	myGLCD.print(txt_info_ZigBee_Operating_PAN_OP, LEFT, yZigBee);
	atRequest.setCommand(opCmd);  
	sendAtCommand();
	ZigBee_data2 = (unsigned long&)info_ZigBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(ZigBee_data2, HEX), RIGHT, yZigBee);

	myGLCD.setColor(255, 255, 255);
	yZigBee = yZigBee + yDelta;// Форматирование текста, смещение
	myGLCD.print(txt_info_ZigBee_Operating_ID, LEFT, yZigBee);
	atRequest.setCommand(IDCmd);  
	sendAtCommand();
	ZigBee_data2 = (unsigned long&)info_ZigBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(ZigBee_data2, HEX), RIGHT, yZigBee);


	myGLCD.setColor(255, 255, 255);
	yZigBee = yZigBee + yDelta;// Форматирование текста, смещение
	myGLCD.print(txt_info_ZigBee_Chanel_CH, LEFT, yZigBee);
	atRequest.setCommand(CHCmd);  
	sendAtCommand();
	ZigBee_data2 = (unsigned long&)info_ZigBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print("0x",258, yZigBee);
	myGLCD.print(String(ZigBee_data2, HEX), RIGHT, yZigBee);

	myGLCD.setColor(255, 255, 255);
	yZigBee = yZigBee + yDelta;// Форматирование текста, смещение
	myGLCD.print(txt_info_ZigBee_Association, LEFT, yZigBee);
	atRequest.setCommand(assocCmd); 
	sendAtCommand();
	ZigBee_data2 = (unsigned long&)info_ZigBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(ZigBee_data2, HEX), RIGHT, yZigBee);


	myGLCD.setColor(255, 255, 255);
	yZigBee = yZigBee + yDelta;// Форматирование текста, смещение
	myGLCD.print(txt_info_ZigBee_Baud_Rate, LEFT, yZigBee);
	atRequest.setCommand(BDCmd); 
	sendAtCommand();
	ZigBee_data2 = (unsigned long&)info_ZigBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	switch (ZigBee_data2)
		{
		case 0:
			ZigBee_data2 = 1200;
			break;
		case 1:
			ZigBee_data2 = 2400;
			break;
		case 2:
			ZigBee_data2 = 4800;
			break;
		case 3:
			ZigBee_data2 = 9600;
			break;
		case 4:
			ZigBee_data2 = 19200;
			break;
		case 5:
			ZigBee_data2 = 38400;
			break;
		case 6:
			ZigBee_data2 = 57600;
			break;
		case 7:
			ZigBee_data2 = 115200;
			break;
						
		}
	myGLCD.print(String(ZigBee_data2), RIGHT, yZigBee);

	myGLCD.setColor(255, 255, 255);
	yZigBee = yZigBee + yDelta;// Форматирование текста, смещение
	myGLCD.print(txt_info_ZigBee_Voltage, LEFT, yZigBee);
	atRequest.setCommand(VoltCmd);   
	sendAtCommand();
	ZigBee_data2 = (unsigned long&)info_ZigBee_data1;
	myGLCD.setColor(VGA_YELLOW);

	float ZigBee_data3 = ZigBee_data2;

	myGLCD.printNumF(ZigBee_data3/1023*1200/1000,2, RIGHT, yZigBee,'.',2);
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (2, 216, 318, 238);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (2, 216, 318, 238);
	myGLCD.setBackColor(0, 0, 255);
	myGLCD.setColor(255, 255, 255);
	myGLCD.print(txt_return, CENTER, 218);// Завершить просмотр
					
		 while (true)
			{
			   if (myTouch.dataAvailable())
				{
					  myTouch.read();
					  x=myTouch.getX();
					  y=myTouch.getY();

				// if ((y>=216) && (y<=240))  // Upper row   
				if ((y>=2) && (y<=240))  // Upper row  
				  {
					if ((x>=2) && (x<=319))  // Выход
					  {
							waitForIt(10, 10, 60, 60);

							/*Serial.println();	  
							Serial.println("Info ZigBee");
							Serial.println();	
							Serial.print("Address Coordinator MS ");
							Serial.println(XBee_Addr64_MS,HEX);	
							Serial.print("Address Coordinator LS ");
							Serial.println(XBee_Addr64_LS,HEX);
							*/

							//// get SH
							//Serial.print("Serial Number (SH) ");
							//sendAtCommand();
							//                         
							//// set command to SL
							//Serial.print("Serial Number (SL) ");
							//atRequest.setCommand(slCmd);  
							//sendAtCommand();
						
							

							//// set command to AI
							//Serial.print("Association Indication (AI) ");
							//atRequest.setCommand(assocCmd);  
							//sendAtCommand();

							//Serial.print("Operating PAN ID (OP) ");
							//atRequest.setCommand(opCmd);  
							//sendAtCommand();

						/*	Serial.print("16-bit Network Address(MY) ");
							atRequest.setCommand(MYCmd);   
							sendAtCommand();
*/
					/*		Serial.print("Operating Chanel (CH) 0x");
							atRequest.setCommand(CHCmd);  
							sendAtCommand();
							*/

							//Serial.println("(0x0B-2405, 0x0C-2410, 0x0D-2415, 0x0E-2420, 0x0F-2425, 0x10-2430, 0x11-2435, 0x12-2440)");
							
							//Serial.println("0x13-2445, 0x14-2450, 0x15-2455, 0x16-2460, 0x17-2465, 0x18-2470, 0x19-2475, 0x1A-2480");//
						/*
							Serial.print("Scan Chanels (SC) ");
							atRequest.setCommand(SCCmd);  
							sendAtCommand();*/
				/*
							Serial.print("Baud Rate (BD) ");
							atRequest.setCommand(BDCmd);  
							sendAtCommand();
							Serial.println("(0-1200, 1-2400, 2-4800, 3-9600, 4-19200, 5-38400, 6-57600, 7-115200)");
*/
							/*Serial.print("Supply Voltage (%V) ");
							atRequest.setCommand(VoltCmd);  
							sendAtCommand();*/
						/*	  
							Serial.print("Destination Address High (DH) ");
							atRequest.setCommand(dhCmd);  
							sendAtCommand();

							Serial.print("Destination Address Low (DL) ");
							atRequest.setCommand(dlCmd);  
							sendAtCommand();*/
						   return;
					  }
				   }
				}

		  }				

 }
void time_flag_start()
 {
	 timeF = millis();
	 if (timeF>60000) flag_time = 1;
 }
void sendAtCommand() 
{
	int i10;

 // Serial.println("Sending command to the XBee");

  // send the command
  xbee.send(atRequest);

  // wait up to 5 seconds for the status response
  if (xbee.readPacket(5000)) 
    { 

	// should be an AT command response
	if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) 
		{
		  xbee.getResponse().getAtCommandResponse(atResponse);

		  if (atResponse.isOk()) 
			  {
				//	Serial.print("Command [");
				//	Serial.print(atResponse.getCommand()[0]);
				//	Serial.print(atResponse.getCommand()[1]);
				//	Serial.println("] was successful!");
				 
					if (atResponse.getValueLength() > 0) 
						{
							Len_ZegBee = atResponse.getValueLength();
						//  Serial.print("Command value length is ");
						//  Serial.println(atResponse.getValueLength(), DEC);
						//  Serial.print("Command value: ");
							int i11=Len_ZegBee-1;
							info_ZigBee_data1[0] = 0;
							info_ZigBee_data1[1] = 0;
							info_ZigBee_data1[2] = 0;
							info_ZigBee_data1[3] = 0;

						  for (i10 = 0; i10 < atResponse.getValueLength(); i10++) 
							  {
								info_ZigBee_data[i10] = atResponse.getValue()[i10];
								//Serial.print(info_ZigBee_data[i10], HEX);
								info_ZigBee_data1[i11] = info_ZigBee_data[i10];
								i11--;
							  }
				
						 // Serial.println("");
						}
			  } 
		  else 
			  {
				Serial.print("Command return error code: ");
				Serial.println(atResponse.getStatus(), HEX);
			  }
		} 
		else 
			{
			  Serial.print("Expected AT response but got ");
			  Serial.println(xbee.getResponse().getApiId(), HEX);
			}   
	  }
  else 
	  {
		// at command failed
		if (xbee.getResponse().isError()) 
			{
			  Serial.print("Error reading packet.  Error code: ");  
			  Serial.println(xbee.getResponse().getErrorCode());
			} 
		else 
			{
			  Serial.println("No response from radio1");  
			}
	  }
}
void sendAtCommand_ar() 
{
	int i10;

 // Serial.println("Sending command to the XBee");

  // send the command
  xbee.send(arRequestMod);

  // wait up to 5 seconds for the status response
  if (xbee.readPacket(5000)) 
  { 

	// should be an AT command response
	if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) 
		{
		  xbee.getResponse().getAtCommandResponse(atResponse);

		  if (atResponse.isOk()) 
			  {

					//myGLCD.setColor(255 , 0, 0);
					
				//	Serial.print("Command [");
				//	Serial.print(atResponse.getCommand()[0]);
				//	Serial.print(atResponse.getCommand()[1]);
				//	Serial.println("] was successful!");
				 
					if (atResponse.getValueLength() > 0) 
						{
							Len_ZegBee = atResponse.getValueLength();
						//  Serial.print("Command value length is ");
						//  Serial.println(atResponse.getValueLength(), DEC);
						//  Serial.print("Command value: ");
							int i11=Len_ZegBee-1;
							info_ZigBee_data1[0] = 0;
							info_ZigBee_data1[1] = 0;
							info_ZigBee_data1[2] = 0;
							info_ZigBee_data1[3] = 0;

						  for (i10 = 0; i10 < atResponse.getValueLength(); i10++) 
							  {
								info_ZigBee_data[i10] = atResponse.getValue()[i10];
								//Serial.print(info_ZigBee_data[i10], HEX);
								info_ZigBee_data1[i11] = info_ZigBee_data[i10];
								i11--;
							  }
				
						 // Serial.println("");
						}
			  } 
		  else 
			  {
				    Serial.print("Command return error code: ");
				    Serial.println(atResponse.getStatus(), HEX);

					myGLCD.setColor(255 , 0, 0);
					myGLCD.fillRoundRect (278, 92, 318, 132);
					myGLCD.setColor(255, 255, 255);
					myGLCD.drawRoundRect (278, 92, 318, 132);
					myGLCD.setBackColor(0, 0, 0);
					delay(200); 
					ZigBee_alarm();
					delay(1000);
					myGLCD.setColor(0, 0, 0);
					myGLCD.fillRoundRect (278, 92, 318, 132);
					myGLCD.setColor(0, 0, 0);
					myGLCD.drawRoundRect (278, 92, 318, 132);
				//	mcp_Out1.digitalWrite(Beep, LOW);                    // 
					delay(300);
			  }
		} 
		else 
			{
			  Serial.print("Expected AT response but got ");
			  Serial.println(xbee.getResponse().getApiId(), HEX);
			}   
	  }
  else 
	  {
		// at command failed
		if (xbee.getResponse().isError()) 
			{
			  Serial.print("Error reading packet.  Error code: ");  
			  Serial.println(xbee.getResponse().getErrorCode());
			} 
		else 
			{
			  Serial.println("No response from radio2");  
			}
	  }
}
void sendRemoteAtCommand()
{
  Serial.println("Sending command to the XBee");

  // send the command
  xbee.send(remoteAtRequest);

  // wait up to 5 seconds for the status response
  if (xbee.readPacket(5000)) {
	// got a response!

	// should be an AT command response
	if (xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE) {
	  xbee.getResponse().getRemoteAtCommandResponse(remoteAtResponse);

	  if (remoteAtResponse.isOk()) {
		Serial.print("Command [");
		Serial.print(remoteAtResponse.getCommand()[0]);
		Serial.print(remoteAtResponse.getCommand()[1]);
		Serial.println("] was successful!");

		if (remoteAtResponse.getValueLength() > 0) {
		  Serial.print("Command value length is ");
		  Serial.println(remoteAtResponse.getValueLength(), DEC);

		  Serial.print("Command value: ");
		  
		  for (int i = 0; i < remoteAtResponse.getValueLength(); i++) {
			Serial.print(remoteAtResponse.getValue()[i], HEX);
			Serial.print(" ");
		  }

		  Serial.println("");
		}
	  } else {
		Serial.print("Command returned error code: ");
		Serial.println(remoteAtResponse.getStatus(), HEX);
	  }
	} else {
	  Serial.print("Expected Remote AT response but got ");
	  Serial.print(xbee.getResponse().getApiId(), HEX);
	}    
  } else if (xbee.getResponse().isError()) {
	Serial.print("Error reading packet.  Error code: ");  
	Serial.println(xbee.getResponse().getErrorCode());
  } else {
	Serial.print("No response from radio3");  
  }
}
void testRemoteAtCommand()
 {
	// sendRemoteAtCommand();
  
  // Теперь повторно тот же объект для команды DIO0
  remoteAtRequest.setCommand(IDCmd);
  remoteAtRequest.setCommandValue(IDValue);
  remoteAtRequest.setCommandValueLength(sizeof(IDValue));

  sendRemoteAtCommand();
  
  // it's a good idea to clear the set value so that the object can be reused for a query
  //это хорошая идея, чтобы очистить установленное значение, чтобы объект можно повторно использовать для запроса 
  remoteAtRequest.clearCommandValue();
  
  // we're done
 // while (1) {};
 }
void test_arRequestMod()
 {
//AtCommandRequest arRequestMod = AtCommandRequest(command,commandValue, commandValueLength);
//AtCommandRequest.setCommand(IDCmd);
//uint8_t command[]  = {'I','D'}; // Номер сети (ID)
//uint8_t commandValue[]  = { 0x02, 0x35 };
//uint8_t commandValueLength = 2;

arRequestMod.setCommand(command);
arRequestMod.setCommandValue(commandValue);
arRequestMod.setCommandValueLength(commandValueLength);
sendAtCommand_ar();
delay(250);
atRequest.setCommand(WRCmd);  
sendAtCommand();
delay(250);
atRequest.setCommand(assocCmd);  
sendAtCommand();

arRequestMod.clearCommandValue();


 }
void set_info_ZigBee()
 {
	 //Программа ввостановления данных ZigBee из памяти.
		   byte y[4];   ; //Чтение из памяти текущих данных старшего адреса координатора
				y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_zigbee_coordinator_h);
				y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_zigbee_coordinator_h);
				y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_zigbee_coordinator_h);
				y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_zigbee_coordinator_h);
				XBee_Addr64_MS = (unsigned long&) y;  // Сложить восстановленные текущие данные

		//	   y[4];   ; //Чтение из памяти текущих данных младшего адреса координатора
				y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_zigbee_coordinator_l);
				y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_zigbee_coordinator_l);
				y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_zigbee_coordinator_l);
				y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_zigbee_coordinator_l);
				XBee_Addr64_LS = (unsigned long&) y;  // Сложить восстановленные текущие данные в 
}
void ZigBee_alarm()
{
	 //word val;
	 //word i = 0;
	 //funcType = 9;
	 //clock_read();
	 //payload[0] = funcType;
	 //payload[1] = 0;//i2c_eeprom_read_byte( deviceaddress,adr_level_war_gaz_max+1);
	 //payload[2] = 0;//i2c_eeprom_read_byte( deviceaddress,adr_level_war_gaz_max);

	 //for (int i_xbee = 0;i_xbee<20;i_xbee++)
	 //{
  //  	 payload[3+i_xbee] = i2c_eeprom_read_byte( deviceaddress,adr_n_user+i_xbee);
	 //}

	 //payload[23] = date;
	 //payload[24] = mon;
	 //byte *x = (byte *)&year;     //Разложить данные  побайтно для записи в память
	 //payload[25] = x[0];
	 //payload[26] = x[1];
	 //payload[27] = hour;
	 //payload[28] = min;
	 //stCurrentLen_telef = i2c_eeprom_read_byte( deviceaddress,adr_n_telef-2);// Чтение номера пользователя
		//			
		//	for (int z=0; z<stCurrentLen_telef; z++)
		//		{
		//			payload[29+z] = i2c_eeprom_read_byte( deviceaddress,adr_n_telef+z);
		//		} 
	 //ZigBeeWrite();

}

byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress )
{

	byte rdata = 0xFF;
	Wire.beginTransmission(deviceaddress);
	Wire.write((int)(eeaddress >> 8)); // MSB
	Wire.write((int)(eeaddress & 0xFF)); // LSB
	Wire.endTransmission();
	Wire.requestFrom(deviceaddress,1);
	if (Wire.available()) rdata = Wire.read();
	//delay(10);
	return rdata;
	
}
void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data )
{
	int rdata = data;
	Wire.beginTransmission(deviceaddress);
	Wire.write((int)(eeaddress >> 8)); // MSB
	Wire.write((int)(eeaddress & 0xFF)); // LSB
	Wire.write(rdata);
	Wire.endTransmission();
	delay(20);
}
void format_memory()
{
	   if (int x = i2c_eeprom_read_byte(deviceaddress,510) != 5)

		  {	// write a 0 to all 500 bytes of the EEPROM
			myGLCD.setColor(255, 255, 255);
			myGLCD.print("Format!",CENTER, 80);// "Format!"
			//delay (500);
			//myGLCD.clrScr();
			for (int i = 0; i < 500; i++)
				{
				  i2c_eeprom_write_byte(deviceaddress,i, 0);
				}
			i2c_eeprom_write_byte(deviceaddress,510, 5); 
			myGLCD.clrScr();
			myGLCD.setColor(255, 255, 255);
			myGLCD.print("Format OK!",CENTER, 80);// "Format Ok!"
			delay (500);
			myGLCD.clrScr();
		  }
}





void setup_pin()
{
	pinMode(led_13, OUTPUT);                             //
	digitalWrite(led_13, HIGH);                          //
	pinMode(KN1, INPUT); 
	pinMode(KN2, INPUT); 
	pinMode(KN3, INPUT); 
	pinMode(KN4, INPUT); 
	pinMode(KN5, INPUT); 
	pinMode(KN6, INPUT); 
	pinMode(KN7, INPUT); 
	pinMode(KN8, INPUT); 

	digitalWrite(KN1, HIGH); 
	digitalWrite(KN2, HIGH); 
	digitalWrite(KN3, HIGH); 
	digitalWrite(KN4, HIGH); 
	digitalWrite(KN5, HIGH); 
	digitalWrite(KN6, HIGH); 
	digitalWrite(KN7, HIGH); 
	digitalWrite(KN8, HIGH); 
}


void setup()
{
	Serial.begin(9600);                                    // Подключение к USB ПК
	Serial1.begin(115200);                                 // Подключение к
	Serial2.begin(115200);                                 // Подключение к
	Serial3.begin(115200);                                 // Подключение к
	Serial.println(" ");
	Serial.println(" ***** Start system  *****");
	Serial.println(" ");
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
	format_memory();

	//drawButtons0_1();
	//drawButtonsTXT();
	//drawButtonsABCDEF();

	drawGlavMenu();

	Serial.println(" ");                                   //
	Serial.println("System initialization OK!.");          // Информация о завершении настройки
}

void loop()
{
	test_power();
	klav_Glav_Menu();
	//klav1();
	//klavABCDEF();
	delay(100);

}