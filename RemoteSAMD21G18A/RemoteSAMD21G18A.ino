/*
Пульт должен передавать команды на исполнительное устройство,
которое будет управлять блоком реле и переключателей, 
а также возвращать подтверждение выполнения команд МК. 
Также разработчик предусматривает соответствующие методы фильтрации, шифрование, модуляцию.
Исполнение команд необходимо гарантированное, то есть пульт должен иметь индикацию выполнения (обмен данными двухсторонний). 
Также желательна (если возможно) односторонняя передача rs232 - от ИУ к пульту на скорости 1200бод. 
Драйвер реле и четыре реле. Возможна обратная связь подтверждения состояния реле. 
(Уточнить нагрузку и количество необходимых контактов).
Светодиодная индикация включения реле, подтверждения связи с пультом, индикация ошибки.
3.Исполнительное устройство. Управление маломощными реле типа TQ2 5V, соленоидами 100мА, реле типа TQ2-l2-5V.
Выходы:
1)Выключатель. Индикация – команда получена(выполнена) – горит диод, команда не прошла – не горит. TQ2 5V
2)Выключатель. Индикация – команда получена(выполнена) – горит диод, команда не прошла – не горит. TQ2 5V
3) Импульс заданной продолжительности на соленоид. Индикация – команда получена(выполнена) – мигнул диод, команда не прошла – не мигнул. соленоид 100мА
4) Импульс заданной продолжительности на соленоид. Индикация – команда получена(выполнена) – мигнул диод, команда не прошла – не мигнул. соленоид 100мА
5) Переключатель. При включении устройства – опрос положения, загорается один из диодов.
Индикация – команда на переключение получена(выполнена) – загорается соответствующий диод, противоположный гаснет. TQ2-l2-5V 
Управление будет не соленоидами, а микродвигателем 5в,

нужна возможность реверса, время вращения строго определенной продолжительности - 0,5 сек каждая команда. 
Т.е. управление будет выглядеть так: 
1. Управление реле - нажал иконку - вкл - нажал - выкл. Таких два выхода, иконки "канал 1"  и "канал 2".
2.Управление микродвигателем - нажал "+" - на контаты микродвигателя поступил сигнал, продолжительностью 0,5 секунд, полярность (+-), 
нажал "-" - на контаты микродвигателя поступил сигнал с реверсом, продолжительностью 0,5 секунд, полярность (-+). 
3. Желательно счетчик нажатий, отображение на иконке со знаком "+" и "-" цифрами, например начальное положение "0",
после двух нажатий иконки "+" - на счетчике "+2", следом жмем "-" пять раз - на счетчике "-3" и так далее, нумерация 99 знаков в каждую сторону.
Возможно ли хранить состояние счетчика при выключении/включении любой части устройства?

Импульс на микродвигатель возможно регулировать? Шаг 0,5 секунд, от 0,5 до 20. Индикация суммирует шаги, а не команды.
Также можно вынести разъемы для возможности механического управления (дублирования команд кнопками) - может пригодиться.

достаточно 2 на мотор (импульс +- и -+) и 2 на реле. Остальные можно не задействовать (выключить их меню в прошивке),
но, думаю, используем по мере усложнения устройства позже. 

Счетчик можно в положительном диапазоне. Пусть будет 0-255. 
Подключение к ИУ через пароль:
1) пароль при включении пульта (пользователя, администратора)
2)смену ИУ, блокировку/разблокировку кнопок, время импульса, сбор и сброс статистики, часы - проводит только администратор

На пульте на экране  8 кнопок  (4 -+, 4 вкл/откл) 

Какая нужна статистика? 
логи нажатия кнопок (кнопки под номерами): имя пульта, пользователь/администратор, время нажатия
время включения (подачи питания). 
При отключении питания ИУ часы собьются? Если да, то автоматически устанавливаются на 00:00 01/01/2001 до смены администратором.

Информацию можно хранить на встроенной SD карте с последующим чтением на персональном компьютере. 
Возможно ли статистику удаленно скидывать на пульт (на сд карту), подключенный с админскими правами, одновременно обнуляя на ИУ?
До этого она хранится на ИУ (при отключении питания сохраняется?)

Любой пульт подключается к любому ИУ  (распознавание через пинкод, графический ключ - что проще).
Ключ для каждого ИУ свой. Вход в меню настроек через ключ.
Настройки, статистика(можно обнулять) и текущее состояние хранятся на ИУ.
В меню настроек - возможность администрировать  функции каждой кнопки (поставил галочку - работает, не поставил - не работает).


КАРТА МЕНЮ

Выбор пользователя
Ввод пароля

МЕНЮ 1                                  klav_menu1()
        1 - Подключить ИУ               set_adr_device();
        - Выбор устройства
    2 - Сменить пользователя        resetFunc()

    3 - Меню файлов                 klav_menu6()
        1 - Меню SD                 klav_menu7()
        1 -  Формат SD
        2 -  Info SD
        3 -  
        4 -  
        5 - Выход
           2 - Файлы
           3 -
           4 -
           5 - Выход

       4 - Настройка системы                     (klav_menu3())
        - Вести пароль
      1- Сброс счетчика                     (klav_Menu_Reset())  - Выбрать кнопки, на которых необходимо сбросить счетчики
      2- Установить интервалы               (klav_menu5())
        1 - Интервал ms мотор 1
        2 - Интервал ms мотор 2
        3 - Интервал ms time 1
        4 - Интервал ms time 2
        5 - Выход
            3 - Блокировка кнопок   

      4 - Установить пароль                  klav_menu4()
        1 - Блокировать ввод пароля        pass_off()
        2 - Установить № пользователя      set_n_user_start();
        3 -  
        4 - Пароль администратора          set_pass_admin_start();
        5 - Выход
            5 - Выход
    5 - Выход

МЕНЮ 2                                klav_menu2()
       1 -  ИНФО XBee                 XBee_status();                                          // Информация XBee 

     2 - 

     3 - Настройки XBee             klav_menu8();            // Установки XBee
        1 - Адреса ИУ устройств   view_adr_device();       // Запись адресов устройств в память
      2 - Set Address Network   XBee_Set_Network();      // Установить адрес сети
      3 - Настройка мощности    set_power();             // Настройка мощности
      4 - Поиск устройств XBee  search_XBee();           // Поиск устройств XBee
      5 - Выход
     4 - Установить дату и время   setClock();

     5 - Выход


-----------------------------------------------------------------
Команды:
payload[0]    Возврат номера команды
payload[1]    run_KN1_StatusXBee(funcType, field1, field2);
payload[2]    run_KN2_StatusXBee(funcType, field1, field2);
payload[3]    run_KN3_StatusXBee(funcType, field1, field2);
payload[4]    run_KN4_StatusXBee(funcType, field1, field2);
payload[5]    run_KN5_StatusXBee(funcType, field1, field2);
payload[6]    run_KN6_StatusXBee(funcType, field1, field2);
payload[7]    run_KN7_StatusXBee(funcType, field1, field2);
payload[8]    run_KN8_StatusXBee(funcType, field1, field2); 
payload[9]    run_set_time1_StatusXBee(funcType, field1, field2);
payload[10]   run_set_time2_StatusXBee(funcType, field1, field2);
payload[11]   Запрос состояния
payload[12]   reset_count();
payload[13]   motor1_set_time1_StatusXBee(funcType, field1, field2);
payload[14]   motor2_set_time1_StatusXBee(funcType, field1, field2); 

Возврат информации с ИУ

set_count(1, address_count1);
set_count(3, address_count2);
set_count(5, address_count3);
set_count(7, address_count4);
set_count(9, address_count5);
set_count(11, address_count6);
set_count(13, address_count7);
set_count(15, address_count8);
set_count(17, address_koef_time1);    // Интервал1
set_count(19, address_koef_time2);    // Интервал2
set_count(21, address_timeMotor1 );   //address_timeMotor1           // 
set_count(23, address_timeMotor2 );   //address_timeMotor2    
payload[24] = 0;                      // 
payload[25] = 0;                      // 
payload[26] =  rele1;                 // Состояние реле 1 
payload[27] =  rele2;                 // Состояние реле 2
payload[28] =  rele3;                 // Состояние реле 3 
payload[29] =  rele4;                 // Состояние реле 4 







// комады сброса счетчиков

if(rx.getData()[11]!=0) EEPROM.put(address_count1, 0);   
if(rx.getData()[12]!=0) EEPROM.put(address_count2, 0);
if(rx.getData()[13]!=0) EEPROM.put(address_count3, 0);
if(rx.getData()[14]!=0) EEPROM.put(address_count4, 0);
if(rx.getData()[15]!=0) EEPROM.put(address_count5, 0);
if(rx.getData()[16]!=0) EEPROM.put(address_count6, 0);
if(rx.getData()[17]!=0) EEPROM.put(address_count7, 0);
if(rx.getData()[18]!=0) EEPROM.put(address_count8, 0);

*/

#include <Wire.h>
#include <RTClib.h>
#include <UTouch.h>
//#include <UTFT_Buttons.h>
#include <SPI.h>
#include <TFT9341.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <XBee.h>

//#include <EEPROM.h>

#define led_13 13  
#define KN1 A8   
#define KN2 A9  
#define KN3 A7 
#define KN4 A10  
#define KN5 A4  
#define KN6 A6  
#define KN7 A3  
#define KN8 A5 
#define VibMot 42 

int statusLed = 13;
int errorLed = 13;
int N_KN = 0;

bool count1 = false;
bool count2 = false;
bool count3 = false;
bool count4 = false;
bool count5 = false;
bool count6 = false;
bool count7 = false;
bool count8 = false;

int countKN1 = 0;
int countKN2 = 0;
int countKN3 = 0;
int countKN4 = 0;
int countKN5 = 0;
int countKN6 = 0;
int countKN7 = 0;
int countKN8 = 0;

int time1      = 0;            // Интервал 1 (резерв, не применяется)
int time2      = 0;            // Интервал 2 (резерв, не применяется)
int timeMotor1 = 0;            // Интервал Мотор1
int timeMotor2 = 0;            // Интервал Мотор2

bool blockKN1 = false;         // Признак блокировки кнопки KN1
bool blockKN2 = false;         // Признак блокировки кнопки KN2
bool blockKN3 = false;         // Признак блокировки кнопки KN3
bool blockKN4 = false;         // Признак блокировки кнопки KN4
bool blockKN5 = false;         // Признак блокировки кнопки KN5
bool blockKN6 = false;         // Признак блокировки кнопки KN6
bool blockKN7 = false;         // Признак блокировки кнопки KN7
bool blockKN8 = false;         // Признак блокировки кнопки KN8

int stat_rele1 = 0;            // Текущее состояние реле 1
int stat_rele2 = 0;            // Текущее состояние реле 2
int stat_rele3 = 0;            // Текущее состояние реле 3
int stat_rele4 = 0;            // Текущее состояние реле 4

bool pass_on_off        = false;    // Текущее состояние. Применение пароля при включении прибора false - пароль отключен
bool pass_on_off_t      = false;    // Временное состояние. Применение пароля при включении прибора false - пароль отключен
uint8_t power_on_off    = 0;        // Текущее состояние. Установить мощность передачи
uint8_t power_on_off_t  = 0;        // Временное состояние.  Установить мощность передачи
int adr_user            = 0;        // Адрес номера пользователя в памяти.


//********************* Настройка монитора ***********************************

TFT9341 myGLCD;                      //   Дисплей 2.4" !! Внимание! Изменены настройки UTouchCD.h

UTouch        myTouch(6, 5, 4, 3, 2);                   // Standard Arduino Mega/Due shield            : 6,5,4,3,2
#define TOUCH_ORIENTATION LANDSCAPE


//UTFT_Buttons  myButtons(&myGLCD, &myTouch);             // Finally we set up UTFT_Buttons :)

boolean default_colors       = true;                    //
uint8_t menu_redraw_required = 0;                       // Признак перезаписи дисплея
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
const char* str1[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int oldsec     = 0;
unsigned long timeF;
int flag_time = 0;
int x_delta = 8;                                     // Смещение тачскрина по Х в файле setTimeDate.ino

RTC_DS1307 RTC;                                      // define the Real Time Clock object
//**************************** Пароль **********************************************************

int  stCurrentLen_pass = 0;               // Длина вводимой строки
char pass_admin[9] ;                      // Строка с паролем Админ
char pass_user[9];                        // Строка с паролем пользователя
int pass = 0;                             // Признак правильности введенного общего пароля
int pass1 = 0;                            // Признак правильности введенного пароля пользователя
int pass2 = 0;                            // Признак правильности введенного пароля Админ
int pass3 = 0;                            // Признак правильности введенного пароля Супер Админ
int eeprom_clear = 0;
int stCurrentLen_user=0;                  // Переменная  хранения длины введенной строки пароля пользователя
int stCurrentLen_admin=0;                 // Переменная  хранения длины введенной строки пароля администратора

unsigned long var_klav123      = 0;       // Число введенное с клавиатуры         
unsigned long pass_admin2      = 0;       // Пароль администратора
unsigned long pass_super_admin = 140754;  // Пароль супер администратора

//++++++++++++++++++++++++++++ Переменные для цифровой клавиатуры +++++++++++++++++++++++++++++
int x, y, z;
char stCurrent[20]    = "";                                       // Переменная хранения введенной строки
int stCurrentLen      = 0;                                        // Переменная хранения длины введенной строки
int stCurrentLen1     = 0;                                        // Переменная временного хранения длины введенной строки
char stLast[20]       = "";                                       // Данные в введенной строке строке.
char temp_stLast[20];                                             // Переменная для временного хранения содержания строки= stLast
int ret               = 0;                                        // Признак прерывания операции
int lenStr            = 8;                                        // Длина строки XBee
int count_s           = 0;                                        // Счетчик введенных символов 

int x_dev = 16;                                                   // Признак смещения текста
int y_dev = 16;                                                   // Признак смещения текста
int deltaY=10;                                                    // Признак смещения текста

int number_menu = 0;

//------------------------------------------------------------------------------------------------- 
float power60 = 0;                       // Измерение источника питания 6,0 вольт
float power50 = 0;                       // Измерение источника питания 5,0 вольт
float power33 = 0;                       // Измерение источника питания 3,3 вольт
unsigned long currentTime;
unsigned long loopTime;
int time_power    = 1000;

//---------------------------------------------------------------------------------
//int adr_xbee_coordinator_h   = 104;       // Адрес координатора старший
//int adr_xbee_coordinator_l   = 108;       // Адрес координатора младший

int adr_pass_user            = 8;         // Адрес пароля пользователя
int adr_stCurrentLen1        = 92;        // Адрес указателя длины строки
int adr_xbee_device_h        = 112;       // Адрес устройства старший
int adr_xbee_device_l        = 116;       // Адрес устройства младший
int adr_xbee_network         = 120;       // Адрес сети
int adr_xbee_current_H       = 124;       // Адрес текущего устройства старший
int adr_xbee_current_L       = 128;       // Адрес текущего устройства младший
int adr_n_user               = 140;       // Адрес хранения № номера пользователя

int adr_blockKN1             = 161;       // Адрес хранения блокировки кнопок  
int adr_blockKN2             = 162;       // Адрес хранения блокировки кнопок 
int adr_blockKN3             = 163;       // Адрес хранения блокировки кнопок 
int adr_blockKN4             = 164;       // Адрес хранения блокировки кнопок 
int adr_blockKN5             = 165;       // Адрес хранения блокировки кнопок 
int adr_blockKN6             = 166;       // Адрес хранения блокировки кнопок 
int adr_blockKN7             = 167;       // Адрес хранения блокировки кнопок 
int adr_blockKN8             = 168;       // Адрес хранения блокировки кнопок 
int adr_pass_on_off          = 169;       // Адрес хранения признак блокировки пароля
int adr_number_device        = 170;       // Адрес хранения порядкового номера устройства (по списку)

int adr_pass_admin           = 990;       // Адрес пароля администратора

int adr_start_baseHL         = 1000;      // Стартовый адрес базы данных номеров исполнительных устройств
byte number_device           = 0;         // Номер исполнительного устройства. 
int adr_start_user           = 2000;      // Стартовый адрес базы данных номеров пользователей
byte number_user             = 0;         // Порядковый номер в списке пользователей. 
long user_number = 0;
long user_pass = 0;
//----------------------------------------------------------------------

const char  txt_botton_otmena[]                PROGMEM  = "O""\xA4\xA1""e""\xA2""a";                            // "Отмена"
const char  txt_botton_vvod[]                  PROGMEM  = "B\x97o\x99 ";                                        // "Ввод"
const char  txt_botton_ret[]                   PROGMEM  = "B""\xAB""x""o\x99" ;                                 // "Выход"
const char  txt_perepolnenie[]                 PROGMEM  = "\x89""EPE""\x89O\x88HEH\x86""E!" ;                   // "Переполнение"
const char  txt_empty[]                        PROGMEM  = "\x80\x8A\x8B\x8B""EP \x89\x8A""CTO\x87!";            // "БУФФЕР ПУСТОЙ"
const char  txt_menu1[]                        PROGMEM  = "MEH""\x94"" 1";                                      // "Переполнение"
const char  txt_menu2[]                        PROGMEM  = "MEH""\x94"" 2";                                      // "БУФФЕР ПУСТОЙ"
const char  txt_info_XBee_ALL[]                PROGMEM = "\x86\xA2\xA5o XBee";                                  // Инфо XBee
const char  txt_info_XBee_USB[]                PROGMEM = "o\xA4\xA3p""a""\x97\xA0""e""\xA2""a"" USB port";      //
const char  txt_info_XBee_MY[]                 PROGMEM = "Network Address MY";                                  //
const char  txt_info_XBee_CoordinatorAdr[]     PROGMEM = "A\x99""pec ""\xA3""y""\xA0\xAC\xA4""a";               // Адрес пульта
const char  txt_info_XBee_Serial[]             PROGMEM = "A\x99""pec ""\x86\x8A N";                             // Адрес ИУ
const char  txt_info_XBee_Network_Address[]    PROGMEM = "Network(MY)";                                         // Адрес сети 16 бит
const char  txt_info_XBee_Operating_PAN_OP[]   PROGMEM = "PAN ID (OP)";                                         // номер сети
const char  txt_info_XBee_Operating_ID[]       PROGMEM = "ID (ID)";                                             //
const char  txt_info_XBee_Chanel_CH[]          PROGMEM = "Chanel (CH)";                                         // Номер канала
const char  txt_info_XBee_Association[]        PROGMEM = "Assoc (AI)";                                          //
const char  txt_info_XBee_Baud_Rate[]          PROGMEM = "Baud(BD)";                                            //
const char  txt_info_XBee_Voltage []           PROGMEM = "Volt(V) ";                                            // Напряжение модуля XBee
const char  txt_return[]                       PROGMEM = "B""\x91""XO""\x82";                                   // ВЫХОД
const char  txt_XBee_Set[]                     PROGMEM = "Hac""\xA4""po""\x9E\x9F""a XBee";                     // Настройка XBee
const char  txt_err_pass_user[]                PROGMEM = "O\xA8\x9D\x96ka \x97\x97o\x99""a" ;                   // Ошибка ввода
const char  txt_menu2_1[]                      PROGMEM = "\x86H\x8BO XBee";                                     // Инфо XBee
const char  txt_menu2_2[]                      PROGMEM = "Coordinator SH";                                      //
const char  txt_menu2_3[]                      PROGMEM = "Coordinator SL";                                      // 
const char  txt_menu2_4[]                      PROGMEM = "Network";                                             //
const char  txt_SetAddress[]                   PROGMEM = "Set Address";                                         //
const char  txt_temperature[]                  PROGMEM = "Te""\xA1\xA3""epa""\xA4"".C";                         // Температура С
const char  txt_view_device1[]                 PROGMEM = "B""\x97""ec""\xA4\x9D"" a""\x99""peca";               // Ввести адреса
const char  txt_view_device2[]                 PROGMEM = "yc""\xA4""po""\x9E""c""\xA4\x97";                     // устройств
const char  txt_Set_device[]                   PROGMEM = "\x89""o""\x99\x9F\xA0\xAE\xA7\x9D\xA4\xAC"" ""\x86\x8A"; // Подключить ИУ
const char  txt_null[]                         PROGMEM = "===========";                                         // "==============="
const char  txt_reset_count[]                  PROGMEM = "C""\x96""poc";                                        // Сброс 
const char  txt_reset_count1[]                 PROGMEM = "C""\x80""POC";                                        // Сброс
const char  txt_set_date1[]                    PROGMEM = "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC";         // Установить
const char  txt_set_date2[]                    PROGMEM = "\x82""a""\xA4""y ""\x9D"" ""\x97""pe""\xA1\xAF";      // Дату и время 
const char  txt_menu1_41[]                     PROGMEM = "Hac""\xA4""po""\x9E\x9F""a";                          // Настройка
const char  txt_menu1_42[]                     PROGMEM = "c""\x9D""c""\xA4""e""\xA1\xAB";                       // системы
const char  txt_menu4_11[]                     PROGMEM = "C\x96poc \x99""a""\xA2\xA2\xABx";                     // Сброс данных
const char  txt_menu4_12[]                     PROGMEM = "\x89""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAC";// Пользователь
const char  txt_menu4_21[]                     PROGMEM = "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC"" N";     // Установить N
const char  txt_menu4_22[]                     PROGMEM = "\xA3""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAF";// пользователя
const char  txt_menu4_31[]                     PROGMEM = "\x89""apo\xA0\xAC";                                   // Пароль
const char  txt_menu4_32[]                     PROGMEM = "Me""\xA2\xAE";                                        // Меню
const char  txt_menu4_41[]                     PROGMEM = "\xA5""a""\x9E\xA0""o""\x97"" ""\x9D"" SD";            // файлов и SD
const char  txt_menu4_42[]                     PROGMEM = "a""\x99\xA1\x9D\xA2\x9D""c""\xA4""pa""\xA4""opa";     // администратора
const char  txt_Bxod[]                         PROGMEM = "BXO""\x82";                                           // ВХОД
const char  txt_pass_adm[]                     PROGMEM = "B""\x97""e""\x99\x9D\xA4""e ""\xA3""apo""\xA0\xAC";   // Введите пароль
const char  txt_pass_adm1[]                    PROGMEM = "\x89""o""\x97\xA4""op  ""\xA3""apo""\xA0\xAF";        // Повтор  пароля
const char  txt_interval1[]                    PROGMEM = "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC";         // Установить 
const char  txt_interval2[]                    PROGMEM = "\x9D\xA2\xA4""ep""\x97""a""\xA0\xAB";                 // интервалы
const char  txt_interval3[]                    PROGMEM = "\x86\xA2\xA4""ep""\x97""a""\xA0 ms";                  // Интервал
const char  txt_intervalM1[]                   PROGMEM = "\xA1""o""\xA4""op1-";                                 // мотор1-
const char  txt_intervalM2[]                   PROGMEM = "\xA1""o""\xA4""op2-";                                 // мотор2-
const char  txt_time1[]                        PROGMEM = "time1-";                                              // 
const char  txt_time2[]                        PROGMEM = "time2-";                                              // 
const char  txt__reset_count3[]                PROGMEM = "c""\xA7""e""\xA4\xA7\x9D\x9F""o""\x97";               // счетчиков
const char  txt__reset_user1[]                 PROGMEM = "C""\xA1""e""\xA2\x9D\xA4\xAC";                        // Сменить
const char  txt__reset_user2[]                 PROGMEM = "\xA3""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAF";// пользователя
const char  txt__blockKNa[]                    PROGMEM = "\x80\xA0""o""\x9F\x9D""po""\x97\x9F""a";              // Блокировка
const char  txt__blockKNb[]                    PROGMEM = "\x9F\xA2""o""\xA3""o""\x9F";                          // кнопок
const char  txt__resCount[]                    PROGMEM = "C""\x96""poc c""\xA7""e""\xA4\xA7\x9D\x9F""a";        // Сброс счетчика
const char  txt__SaveKN[]                      PROGMEM = "\x8A""CTAH.";                                         // УСТАН.
const char  txt__block_pass1[]                 PROGMEM = "\x80\xA0""o""\x9F\x9D""po""\x97""a""\xA4\xAC";        // Блокировать
const char  txt__block_pass2[]                 PROGMEM = "\x97\x97""o""\x99"" ""\xA3""apo""\xA0\xAF";           // ввод пароля
const char  txt__save[]                        PROGMEM = "Coxpa""\xA2";                                         // Сохран
const char  txt__no[]                          PROGMEM = "He""\xA4"" ""\xA3""apo""\xA0\xAF"" ""\x9D";           // Нет пароля и
const char  txt__SDmem[]                       PROGMEM = "SD  ""\xA3""a""\xA1\xAF\xA4\x9D";                     // SD памяти
const char  txt__SDformat[]                    PROGMEM = "\x8B""op""\xA1""a""\xA4\x9D""po""\x97""a""\xA2\x9D""e";// Форматирование
const char  txt__SDinfo[]                      PROGMEM = "\x86\xA2\xA5""op""\xA1""a""\xA6\x9D\xAF"" o";         // Информация о
const char  txt_n_user1[]                      PROGMEM = "B\x97""e\x99\x9D\xA4""e N";                           // Введите №
const char  txt_n_user2[]                      PROGMEM = "\xA3""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAF";// пользователя
const char  txt_n_user3[]                      PROGMEM = "\x89""o""\x97\xA4""op""\x9D\xA4""e N";                // Повторите N
const char  txt_n_user_pass1[]                 PROGMEM = "\x8A""c""\xA4"".N ""\xA3""o""\xA0\xAC\x9C"".";        // Уст.N польз.
const char  txt_n_user_pass2[]                 PROGMEM = "\x9D"" ""\xA3""apo""\xA0\xAC";                        // и пароль
const char  txt_tx_pover[]                     PROGMEM = "TX Power mW";                                         // "TX Power mW"
const char  txt_set_XBee1[]                    PROGMEM = "Hac""\xA4""po""\x9E\x9F\x9D";                         // Настройки
const char  txt_set_XBee2[]                    PROGMEM = "XBee";                                                // XBee
const char  txt_set_XBee3[]                    PROGMEM = "\xA1""o""\xA9\xA2""oc""\xA4\x9D";                     // мощности
const char  txt_set_lev1[]                     PROGMEM = "Lowest +10dBm";                                       // Мощность 1 mV
const char  txt_set_lev2[]                     PROGMEM = "Low    +12dBm";                                       // Мощность 25 mV
const char  txt_set_lev3[]                     PROGMEM = "Medium +14dBm";                                       // Мощность 100 mV
const char  txt_set_lev4[]                     PROGMEM = "High   +16dBm";                                       // Мощность 200 mV
const char  txt_set_lev5[]                     PROGMEM = "Highest+18dBm";                                       // Мощность 300 mV
const char  txt_search_XBee[]                  PROGMEM = "\x89""o""\x9D""c""\x9F"" XBee";                       // Поиск XBee
const char  txt_infoSD1[]                      PROGMEM = "\x86\xA2\xA5""op""\xA1""a""\xA6\x9D\xAF"" ";          // Информация 
const char  txt_infoSD2[]                      PROGMEM = "SD ""\xA3""a""\xA1\xAF\xA4\x9D";                      // SD памяти



char  txt9[6] = "B\x97o\x99";                                                               // Ввод
char  txt10[8] = "O""\xA4\xA1""e""\xA2""a";                                                 // "Отмена"
char  txt11[4] = "RET";
char  txt12[] = "B\x97""e\x99\x9D\xA4""e \xA3""apo\xA0\xAC!";                               // "Введите пароль"
char  txt_pass_ok[] = "\xA3""apo\xA0\xAC OK!";                                              // Пароль ОК!
char  txt_pass_no[] = "\xA3""apo\xA0\xAC NO!";                                              // Пароль NO!
char  txt_botton_clear[] = "C\x96poc";                                                      // Сброс
char  txt_system_clear1[] = "B\xA2\x9D\xA1""a\xA2\x9D""e!";                                 // Внимание !  
char  txt_system_clear2[] = "Bc\xAF \xA1\xA2\xA5op\xA1""a""\xA6\xA1\xAF \x96y\x99""e\xA4";  // Вся информация будет 
char  txt_system_clear3[] = "\x8A\x82""A""\x88""EHA!";                                      // УДАЛЕНА 
char  txt_set_pass_user[] = "Ho\x97\xAB\x9E \xA3""apo\xA0\xAC \xA3o\xA0\xAC\x9C.";          // "Новый пароль польз."
char  txt_rep_pass_user[] = "\x89o\x97\xA4op \xA3""apo\xA0\xAC \xA3o\xA0\xAC\x9C.";         // "Повтор пароль польз."


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
 txt_info_XBee_ALL,                // 7 "\x86\xA2\xA5op\xA1""a""\xA6\x9D\xAF XBee";                              // Информация XBee
 txt_info_XBee_USB,                // 8 "o\xA4\xA3p""a""\x97\xA0""e""\xA2""a"" USB port";                        //
 txt_info_XBee_MY,                 // 9 "Network Address MY";                                                    //
 txt_info_XBee_CoordinatorAdr,     // 10 "Addr Coordinat";                                                       //
 txt_info_XBee_Serial,             // 11 "Number SH,SL"                                                          //
 txt_info_XBee_Network_Address,    // 12 "Network (MY) = ";//
 txt_info_XBee_Operating_PAN_OP,   // 13 "PAN ID (OP)  = ";//
 txt_info_XBee_Operating_ID,       // 14 "ID (ID)      = ";//
 txt_info_XBee_Chanel_CH,          // 15 "Chanel (CH)";//
 txt_info_XBee_Association,        // 16 "Association(AI)";//
 txt_info_XBee_Baud_Rate,          // 17 "Baud Rate(BD)";//
 txt_info_XBee_Voltage,            // 18 "Voltage (%V) =";//
 txt_return,                       // 19 "B""\x91""XO""\x82";                                                     // ВЫХОД
 txt_XBee_Set,                     // 20 "Hac""\xA4""po""\x9E\x9F""a XBee";                                       // Настройка XBee
 txt_err_pass_user,                // 21 "O\xA8\x9D\x96ka \x97\x97o\x99""a" ;                                     // Ошибка ввода
 txt_menu2_1,                      // 22 "\x86H\x8BO XBee";                                                       // Инфо XBee
 txt_menu2_2,                      // 23 "Coord SH";                                                              //
 txt_menu2_3,                      // 24 "Coord SL";                                                              // 
 txt_menu2_4,                      // 25 "Network";                                                               //
 txt_SetAddress,                   // 26 "Set Address";                                                           //
 txt_temperature,                  // 27 "Te""\xA1\xA3""epa""\xA4""ypa C";                                        // Температура С
 txt_view_device1,                 // 28 "B""\x97""ec""\xA4\x9D"" a""\x99""peca";                                 // Ввести адреса
 txt_view_device2,                 // 29 "yc""\xA4""po""\x9E""c""\xA4\x97";                                       // устройств
 txt_Set_device,                   // 30 "\x89""o""\x99\x9F\xA0\xAE\xA7\x9D\xA4\xAC"" ""\x86\x8A";                // Подключить ИУ
 txt_null,                         // 31 "===========";                                                           // "==============="
 txt_reset_count,                  // 32 "C""\x96""poc" ;                                                         // Сброс 
 txt_reset_count1,                 // 33 "C""\x96""poc";                                                          // Сброс
 txt_set_date1,                    // 34 "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC";                           // Установить
 txt_set_date2,                    // 35 "\x82""a""\xA4""y ""\x9D"" ""\x97""pe""\xA1\xAF";                        // Дату и время 
 txt_menu1_41,                     // 36 "Hac""\xA4""po""\x9E\x9F""a";                                            // Настройка
 txt_menu1_42,                     // 37 "c""\x9D""c""\xA4""e""\xA1\xAB";                                         // системы
 txt_menu4_11,                     // 38 "C\x96poc \x99""a""\xA2\xA2\xABx";                                       // Сброс данных
 txt_menu4_12,                     // 39  "\x89""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAC";                 //  Пользователь
 txt_menu4_21,                     // 40  "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC"" N";                      // Установить N
 txt_menu4_22,                     // 41 "\xA3""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAF";                  // пользователя
 txt_menu4_31,                     // 42 "\x89""apo\xA0\xAC";                                                     // Пароль
 txt_menu4_32,                     // 43 "Me""\xA2\xAE";                                                          // Меню 
 txt_menu4_41,                     // 44 "\xA5""a""\x9E\xA0""o""\x97"" ""\x9D"" SD";                              // файлов и SD        
 txt_menu4_42,                     // 45 "a""\x99\xA1\x9D\xA2\x9D""c""\xA4""pa""\xA4""opa";                       // администратора
 txt_Bxod,                         // 46 "BXO""\x82";                                                             // ВХОД
 txt_pass_adm,                     // 47 "B""\x97""e""\x99\x9D\xA4""e ""\xA3""apo""\xA0\xAC";                     // Введите пароль
 txt_pass_adm1,                    // 48 "\x89""o""\x97\xA4""op  ""\xA3""apo""\xA0\xAF";                          // Повтор  пароля
 txt_interval1,                    // 49 "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC";                           // Установить 
 txt_interval2,                    // 50 "\x9D\xA2\xA4""ep""\x97""a""\xA0";                                       //  интервалы
 txt_interval3,                    // 51 "\x86\xA2\xA4""ep""\x97""a""\xA0";                                       // Интервал
 txt_intervalM1,                   // 52 "\xA1""o""\xA4""op 1";                                                   // мотор 1
 txt_intervalM2,                   // 53 "\xA1""o""\xA4""op 2";                                                   // мотор 2
 txt_time1,                        // 54 "time 1";                                                                // 
 txt_time2,                        // 55 "time 2";                                                                // 
 txt__reset_count3,                // 56 "c""\xA7""e""\xA4\xA7\x9D\x9F""o""\x97";                                 // счетчиков
 txt__reset_user1,                 // 57 "C""\xA1""e""\xA2\x9D\xA4\xAC";                                          // Сменить
 txt__reset_user2,                 // 58 "\xA3""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAF";                  // пользователя
 txt__blockKNa,                    // 59 "\x80\xA0""o""\x9F\x9D""po""\x97\x9F""a";                                // Блокировка
 txt__blockKNb,                    // 60 "\x9F\xA2""o""\xA3""o""\x9F";                                            // кнопок
 txt__resCount,                    // 61 "C""\x96""poc c""\xA7""e""\xA4\xA7\x9D\x9F""a";                          // Сброс счетчика
 txt__SaveKN,                      // 62 "\x8A""CTAH.";                                                           // УСТАН.
 txt__block_pass1,                 // 63 "\x80\xA0""o""\x9F\x9D""po""\x97""a""\xA4\xAC";                          // Блокировать
 txt__block_pass2,                 // 64 "\x97\x97""o""\x99"" ""\xA3""apo""\xA0\xAF";                             // ввод пароля
 txt__save,                        // 65 "Coxpa""\xA2";                                                           // Сохран.
 txt__no,                          // 66 "He""\xA4"" ""\xA3""apo""\xA0\xAF"" ""\x9D";                             // Нет пароля и
 txt__SDmem,                       // 67 "SD  ""\xA3""a""\xA1\xAF\xA4\x9D";                                       // SD памяти
 txt__SDformat,                    // 68 "\x8B""op""\xA1""a""\xA4\x9D""po""\x97""a""\xA2\x9D""e";                 // Форматирование
 txt__SDinfo,                      // 69 "\x86\xA2\xA5""op""\xA1""a""\xA6\x9D\xAF"" o";                           // Информация о
 txt_n_user1,                      // 70 "B\x97""e\x99\x9D\xA4""e N";                                             // Введите №
 txt_n_user2,                      // 71 "\xA3""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAF";                  // пользователя
 txt_n_user3,                      // 72 "\x89o\x97\xA4op\x9D\xA4""e"" N \xA3o\xA0\xAC\x9C.  ";                   // Повторите N
 txt_n_user_pass1,                 // 73 "\x8A""c""\xA4"".N ""\xA3""o""\xA0\xAC\x9C"".";                          // Уст.N польз.
 txt_n_user_pass2,                 // 74 "\x9D"" ""\xA3""apo""\xA0\xAC";                                          // и пароль
 txt_tx_pover,                     // 75 "TX Power mW";                                                           // "TX Power mW"
 txt_set_XBee1,                    // 76 "Hac""\xA4""po""\x9E\x9F\x9D";                                           // Настройки
 txt_set_XBee2,                    // 77 "XBee";                                                                  // XBee
 txt_set_XBee3,                    // 78 "\xA1""o""\xA9\xA2""oc""\xA4\x9D";                                       // мощности
 txt_set_lev1,                     // 79 "Mo""\xA9\xA2""oc""\xA4\xAC"" 1 mV";                                     // Мощность 1 mV
 txt_set_lev2,                     // 80 "Mo""\xA9\xA2""oc""\xA4\xAC"" 25 mV";                                    // Мощность 25 mV
 txt_set_lev3,                     // 81 "Mo""\xA9\xA2""oc""\xA4\xAC"" 100 mV";                                   // Мощность 100 mV
 txt_set_lev4,                     // 82 "Mo""\xA9\xA2""oc""\xA4\xAC"" 200 mV";                                   // Мощность 200 mV
 txt_set_lev5,                     // 83 "Mo""\xA9\xA2""oc""\xA4\xAC"" 300 mV";                                   // Мощность 300 mV
 txt_search_XBee,                  // 84 "\x89""o""\x9D""c""\x9F"" ""\x86\x8A"" XBee";                            // Поиск устройств XBee
 txt_infoSD1,                      // 85 "\x86\xA2\xA5""op""\xA1""a""\xA6\x9D\xAF"" ";                            // Информация 
 txt_infoSD2                       // 86 SD ""\xA3""a""\xA1\xAF\xA4\x9D";                                         // SD памяти

 
};


// ************ XBee******************

XBee xbee = XBee();                                   //создаем XBee библиотеку

// ++++++++++  настройки для приема и передачи пакета +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

XBeeResponse response = XBeeResponse();               //Это создает экземпляр объекта "response" "ответ" обрабатывать пакеты Xbee
ZBRxResponse rx = ZBRxResponse();                     //Это создает экземпляр объекта "rx" на процесс Xbee Series 2 API пакеты
ModemStatusResponse msr = ModemStatusResponse();      //Это создает экземпляр объекта "msr" процесс associate/disassociate packets (PAN membership)
ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();


//Строка с данными
uint8_t payload[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//uint8_t payload1[10] ;// = {3, 4,};

int XBee_Addr16;                            //16-разрядный адрес
int Len_XBee = 0;
unsigned char info_XBee_data[96];
unsigned char info_XBee_data1[96];
char* simbol_ascii[2];
char   cmd;

uint8_t shCmd[] = {'S','H'};                // serial high Старший байт адреса куда отправляется пакет
uint8_t slCmd[] = {'S','L'};                // serial low Младший байт адреса куда отправляется пакет
uint8_t assocCmd[] = {'A','I'};             // association status Индикация присоединения 
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
uint8_t irCmd[]    = {'I','R'};             // 
uint8_t opCmd[]    = {'O','P'};             // Номер сети (PAN ID)
uint8_t IDCmd[]    = {'I','D'};             // Номер сети (ID)
uint8_t OICmd[]    = {'O','I'};             // Operating 16-bit PAN ID(OI)
uint8_t MYCmd[]    = {'M','Y'};             // Номер сети (16-bit Network Adress
uint8_t CHCmd[]    = {'C','H'};             // Номер Радиоканала
uint8_t SCCmd[]    = {'S','C'};             // Scan Channel
uint8_t BDCmd[]    = {'B','D'};             // Скорость канала (Baud Rate )
uint8_t VoltCmd[]  = {'%','V'};             // Напряжение питания Считывает напряжение на выводе Vcc. Для преобразования значения
                      // в мВ, поделите значение на 1023 и умножьте на 1200. Значение %V равное 0x8FE (или 2302 в
                      // десятичном виде) соответствует 2700мВ или 2.70В
uint8_t TPCmd[]    = {'T','P'};             // Температура
uint8_t dhCmd[]    = {'D','H'};             // Старший байт адреса
uint8_t dlCmd[]    = {'D','L'};             // Младший байт адреса
uint8_t d0Cmd[]    = {'D','0'};             //
uint8_t WRCmd[]    = {'W','R'};             // Запись в модуль параметров
                      // Примечание: Если введена команда WR, до получения ответа "OK\r" не должно вводится
                      // дополнительных символов
uint8_t FRCmd[]    = {'F','R'};             // Перезапуск программного обеспечения
uint8_t NRCmd[]    = {'N','R'};             // Перезапуск сети 
                      // Если NR = 0: Переустанавливает параметры сети на узле, вызвавшем команду. 
                      // Если NR = 1:Отправляетшироковещательную передачу для перезапуска параметров на всех узлах сети.
uint8_t PLCmd[]    = {'P','L'};             // TX Power level mW
uint8_t NDCmd[]    = {'N','D'};             // Обнаружение узла (Node Discover). Обнаруживает и сообщает обо всех
                                            // найденных модулях. Следующая информация будет сообщена для каждого
                                // обнаруженного модуля:
                      // MY<CR>      16-разрядный адрес источника
                      // SH<CR>      Старшие байты серийного номера
                      // SL<CR>      Младшие байты серийного номера
                      // DB<CR>      Сила принимаемого сигнала (Received Signal Strength)
                      // NI<CR><CR>  Идентификатор узла (Node Identifier). Имя модуля

uint8_t NTCmd[]    = {'N','T'};             // Node Discovery Timeout. Set/Read the node discovery timeout. When the network
                      // discovery (ND) command is issued, the NT value is included in the transmission to
                      // provide all remote devices with a response timeout. Remote devices wait a random
                      //  time, less than NT, before sending their response.  0x3C (60d)


uint8_t d0Value[]  = { 0x2 };
uint8_t irValue[]  = { 0xff, 0xff };
uint8_t IDValue[]  = { 0x02, 0x34 };

 
uint8_t command[]  = {'I','D'};             // Номер сети (ID)
uint8_t commandValue[]  = { 0x02, 0x35 };
uint8_t commandValueLength = 0x2 ;




//Два 32-битных половинки th4 64-разрядный адрес
long XBee_Addr64_MS =  0x0013a200;
long XBee_Addr64_LS = 0 ; //0x40672567;

//Два 32-битных половинки th4 64-разрядный адрес
long XBee_Addr64_MS_tmp = 0;                    //
long XBee_Addr64_LS_tmp = 0;                    //

XBeeAddress64 addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);                                     // SH + SL Address of receiving XBee
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));                                         // Формирует пакет  zbTx с адресом отправителя и данными
ZBTxStatusResponse txStatus = ZBTxStatusResponse();                                                       // Это создает экземпляр объекта "txStatus" процесс благодарности прислал Xbee Series 2 API пакеты
AtCommandRequest atRequest = AtCommandRequest(shCmd);                                                     // XBeeAddress64 remoteAddress = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
AtCommandRequest arRequestMod = AtCommandRequest(command,commandValue, commandValueLength); 
AtCommandResponse atResponse = AtCommandResponse();
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(addr64, irCmd, irValue, sizeof(irValue)); // Create a remote AT request with the IR command
RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();                                     // Create a Remote AT response object


//********************************
byte funcType;                      // Номер функции, переданной по каналу  XBee
word field1;                        // Данные,  переданные по каналу  XBee
word field2;                        // Данные,  переданные по каналу  XBee
byte *_msg, _len;                   // Длина строки
word _baud, _crc;                   // Скорость обмена и контрольная сумма блока  


//++++++++++++++++++++++ Работа с файлами +++++++++++++++++++++++++++++++++++++++
//#define chipSelect SS
#define chipSelect 53                                             // Настройка выбора SD
SdFat sd;
File myFile;
SdFile file;
Sd2Card card;
uint32_t cardSizeBlocks;
uint16_t cardCapacityMB;

// cache for SD block
cache_t cache;
 
//------------------------------------------------------------------------------
// созданы переменные, использующие функции библиотеки SD utility library functions: +++++++++++++++
// Change spiSpeed to SPI_FULL_SPEED for better performance
// Use SPI_QUARTER_SPEED for even slower SPI bus speed
const uint8_t spiSpeed = SPI_HALF_SPEED;                       // Скорость обмена данных с SD


//++++++++++++++++++++ Назначение имени файла ++++++++++++++++++++++++++++++++++++++++++++
//const uint32_t FILE_BLOCK_COUNT = 256000;
// log file base name.  Must be six characters or less.
#define FILE_BASE_NAME "160101"
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[13]            = FILE_BASE_NAME "00.KAM";
char fileName_p[13];
char fileName_F[13];

//*********************Работа с именем файла ******************************

//byte file_name_count = 0;
char str_day_file[3];
char str_day_file0[3];
char str_day_file10[3];
char str_mon_file[3];
char str_mon_file0[3];
char str_mon_file10[3];
char str_year_file[3];

//char str0_1[10];
char str1_1[10];
char str2_1[10];

// ======================== Программа форматирования SD =============================

#define DEBUG_PRINT 1
// Serial output stream
ArduinoOutStream cout(Serial);     // Вывод данных в КОМ порт
// Переменные для работы с SD
// MBR information
uint8_t partType;
uint32_t relSector;
uint32_t partSize;

// Fake disk geometry
uint8_t numberOfHeads;
uint8_t sectorsPerTrack;

// FAT parameters
uint16_t reservedSectors;
uint8_t sectorsPerCluster;
uint32_t fatStart;
uint32_t fatSize;
uint32_t dataStart;

// constants for file system structure
uint16_t const BU16 = 128;
uint16_t const BU32 = 8192;

//  strings needed in file system structures
char noName[] = "NO NAME    ";
char fat16str[] = "FAT16   ";
char fat32str[] = "FAT32   ";
//------------------------------------------------------------------------------
#define sdError(msg) sdError_F(F(msg))               // Программа обработки ошибок

void sdError_F(const __FlashStringHelper* str)       // Программа обработки ошибок
{
  cout << F("error: ");
  cout << str << endl;
  if (card.errorCode()) 
  {
    cout << F("SD error: ") << hex << int(card.errorCode());
    cout << ',' << int(card.errorData()) << dec << endl;
  }
  while (1);
}

//------------------------------------------------------------------------------
#if DEBUG_PRINT
void debugPrint() 
{
  cout << F("FreeRam: ") << FreeRam() << endl;
  cout << F("partStart: ") << relSector << endl;
  cout << F("partSize: ") << partSize << endl;
  cout << F("reserved: ") << reservedSectors << endl;
  cout << F("fatStart: ") << fatStart << endl;
  cout << F("fatSize: ") << fatSize << endl;
  cout << F("dataStart: ") << dataStart << endl;
  cout << F("clusterCount: ");
  cout << ((relSector + partSize - dataStart) / sectorsPerCluster) << endl;
  cout << endl;
  cout << F("Heads: ") << int(numberOfHeads) << endl;
  cout << F("Sectors: ") << int(sectorsPerTrack) << endl;
  cout << F("Cylinders: ");
  cout << cardSizeBlocks / (numberOfHeads * sectorsPerTrack) << endl;
}
#endif  // DEBUG_PRINT
//------------------------------------------------------------------------------
// write cached block to the card
uint8_t writeCache(uint32_t lbn) {
  return card.writeBlock(lbn, cache.data);
}
//------------------------------------------------------------------------------
// initialize appropriate sizes for SD capacity
void initSizes() {
  if (cardCapacityMB <= 6) {
    sdError("Card is too small.");
  } else if (cardCapacityMB <= 16) {
    sectorsPerCluster = 2;
  } else if (cardCapacityMB <= 32) {
    sectorsPerCluster = 4;
  } else if (cardCapacityMB <= 64) {
    sectorsPerCluster = 8;
  } else if (cardCapacityMB <= 128) {
    sectorsPerCluster = 16;
  } else if (cardCapacityMB <= 1024) {
    sectorsPerCluster = 32;
  } else if (cardCapacityMB <= 32768) {
    sectorsPerCluster = 64;
  } else {
    // SDXC cards
    sectorsPerCluster = 128;
  }

  cout << F("Blocks/Cluster: ") << int(sectorsPerCluster) << endl;
  // set fake disk geometry
  sectorsPerTrack = cardCapacityMB <= 256 ? 32 : 63;

  if (cardCapacityMB <= 16) {
    numberOfHeads = 2;
  } else if (cardCapacityMB <= 32) {
    numberOfHeads = 4;
  } else if (cardCapacityMB <= 128) {
    numberOfHeads = 8;
  } else if (cardCapacityMB <= 504) {
    numberOfHeads = 16;
  } else if (cardCapacityMB <= 1008) {
    numberOfHeads = 32;
  } else if (cardCapacityMB <= 2016) {
    numberOfHeads = 64;
  } else if (cardCapacityMB <= 4032) {
    numberOfHeads = 128;
  } else {
    numberOfHeads = 255;
  }
}
//------------------------------------------------------------------------------
// zero cache and optionally set the sector signature
void clearCache(uint8_t addSig) {
  memset(&cache, 0, sizeof(cache));
  if (addSig) {
    cache.mbr.mbrSig0 = BOOTSIG0;
    cache.mbr.mbrSig1 = BOOTSIG1;
  }
}
//------------------------------------------------------------------------------
// zero FAT and root dir area on SD
void clearFatDir(uint32_t bgn, uint32_t count) {
  clearCache(false);
  if (!card.writeStart(bgn, count)) {
    sdError("Clear FAT/DIR writeStart failed");
  }
  for (uint32_t i = 0; i < count; i++) {
    if ((i & 0XFF) == 0) {
      cout << '.';
    }
    if (!card.writeData(cache.data)) {
      sdError("Clear FAT/DIR writeData failed");
    }
  }
  if (!card.writeStop()) {
    sdError("Clear FAT/DIR writeStop failed");
  }
  cout << endl;
}
//------------------------------------------------------------------------------
// return cylinder number for a logical block number
uint16_t lbnToCylinder(uint32_t lbn) {
  return lbn / (numberOfHeads * sectorsPerTrack);
}
//------------------------------------------------------------------------------
// return head number for a logical block number
uint8_t lbnToHead(uint32_t lbn) {
  return (lbn % (numberOfHeads * sectorsPerTrack)) / sectorsPerTrack;
}
//------------------------------------------------------------------------------
// return sector number for a logical block number
uint8_t lbnToSector(uint32_t lbn) {
  return (lbn % sectorsPerTrack) + 1;
}
//------------------------------------------------------------------------------
// format and write the Master Boot Record
void writeMbr() {
  clearCache(true);
  part_t* p = cache.mbr.part;
  p->boot = 0;
  uint16_t c = lbnToCylinder(relSector);
  if (c > 1023) {
    sdError("MBR CHS");
  }
  p->beginCylinderHigh = c >> 8;
  p->beginCylinderLow = c & 0XFF;
  p->beginHead = lbnToHead(relSector);
  p->beginSector = lbnToSector(relSector);
  p->type = partType;
  uint32_t endLbn = relSector + partSize - 1;
  c = lbnToCylinder(endLbn);
  if (c <= 1023) {
    p->endCylinderHigh = c >> 8;
    p->endCylinderLow = c & 0XFF;
    p->endHead = lbnToHead(endLbn);
    p->endSector = lbnToSector(endLbn);
  } else {
    // Too big flag, c = 1023, h = 254, s = 63
    p->endCylinderHigh = 3;
    p->endCylinderLow = 255;
    p->endHead = 254;
    p->endSector = 63;
  }
  p->firstSector = relSector;
  p->totalSectors = partSize;
  if (!writeCache(0)) {
    sdError("write MBR");
  }
}
//------------------------------------------------------------------------------
// generate serial number from card size and micros since boot
uint32_t volSerialNumber() 
{
  return (cardSizeBlocks << 8) + micros();
}
//------------------------------------------------------------------------------
// format the SD as FAT16
void makeFat16() 
{
  uint32_t nc;
  for (dataStart = 2 * BU16;; dataStart += BU16) {
    nc = (cardSizeBlocks - dataStart) / sectorsPerCluster;
    fatSize = (nc + 2 + 255) / 256;
    uint32_t r = BU16 + 1 + 2 * fatSize + 32;
    if (dataStart < r) {
      continue;
    }
    relSector = dataStart - r + BU16;
    break;
  }
  // check valid cluster count for FAT16 volume
  if (nc < 4085 || nc >= 65525) {
    sdError("Bad cluster count");
  }
  reservedSectors = 1;
  fatStart = relSector + reservedSectors;
  partSize = nc * sectorsPerCluster + 2 * fatSize + reservedSectors + 32;
  if (partSize < 32680) {
    partType = 0X01;
  } else if (partSize < 65536) {
    partType = 0X04;
  } else {
    partType = 0X06;
  }
  // write MBR
  writeMbr();
  clearCache(true);
  fat_boot_t* pb = &cache.fbs;
  pb->jump[0] = 0XEB;
  pb->jump[1] = 0X00;
  pb->jump[2] = 0X90;
  for (uint8_t i = 0; i < sizeof(pb->oemId); i++) {
    pb->oemId[i] = ' ';
  }
  pb->bytesPerSector = 512;
  pb->sectorsPerCluster = sectorsPerCluster;
  pb->reservedSectorCount = reservedSectors;
  pb->fatCount = 2;
  pb->rootDirEntryCount = 512;
  pb->mediaType = 0XF8;
  pb->sectorsPerFat16 = fatSize;
  pb->sectorsPerTrack = sectorsPerTrack;
  pb->headCount = numberOfHeads;
  pb->hidddenSectors = relSector;
  pb->totalSectors32 = partSize;
  pb->driveNumber = 0X80;
  pb->bootSignature = EXTENDED_BOOT_SIG;
  pb->volumeSerialNumber = volSerialNumber();
  memcpy(pb->volumeLabel, noName, sizeof(pb->volumeLabel));
  memcpy(pb->fileSystemType, fat16str, sizeof(pb->fileSystemType));
  // write partition boot sector
  if (!writeCache(relSector)) {
    sdError("FAT16 write PBS failed");
  }
  // clear FAT and root directory
  clearFatDir(fatStart, dataStart - fatStart);
  clearCache(false);
  cache.fat16[0] = 0XFFF8;
  cache.fat16[1] = 0XFFFF;
  // write first block of FAT and backup for reserved clusters
  if (!writeCache(fatStart)
      || !writeCache(fatStart + fatSize)) {
    sdError("FAT16 reserve failed");
  }
}
//------------------------------------------------------------------------------
// format the SD as FAT32
void makeFat32() 
{
  uint32_t nc;
  relSector = BU32;
  for (dataStart = 2 * BU32;; dataStart += BU32) {
    nc = (cardSizeBlocks - dataStart) / sectorsPerCluster;
    fatSize = (nc + 2 + 127) / 128;
    uint32_t r = relSector + 9 + 2 * fatSize;
    if (dataStart >= r) {
      break;
    }
  }
  // error if too few clusters in FAT32 volume
  if (nc < 65525) {
    sdError("Bad cluster count");
  }
  reservedSectors = dataStart - relSector - 2 * fatSize;
  fatStart = relSector + reservedSectors;
  partSize = nc * sectorsPerCluster + dataStart - relSector;
  // type depends on address of end sector
  // max CHS has lbn = 16450560 = 1024*255*63
  if ((relSector + partSize) <= 16450560) {
    // FAT32
    partType = 0X0B;
  } else {
    // FAT32 with INT 13
    partType = 0X0C;
  }
  writeMbr();
  clearCache(true);

  fat32_boot_t* pb = &cache.fbs32;
  pb->jump[0] = 0XEB;
  pb->jump[1] = 0X00;
  pb->jump[2] = 0X90;
  for (uint8_t i = 0; i < sizeof(pb->oemId); i++) {
    pb->oemId[i] = ' ';
  }
  pb->bytesPerSector = 512;
  pb->sectorsPerCluster = sectorsPerCluster;
  pb->reservedSectorCount = reservedSectors;
  pb->fatCount = 2;
  pb->mediaType = 0XF8;
  pb->sectorsPerTrack = sectorsPerTrack;
  pb->headCount = numberOfHeads;
  pb->hidddenSectors = relSector;
  pb->totalSectors32 = partSize;
  pb->sectorsPerFat32 = fatSize;
  pb->fat32RootCluster = 2;
  pb->fat32FSInfo = 1;
  pb->fat32BackBootBlock = 6;
  pb->driveNumber = 0X80;
  pb->bootSignature = EXTENDED_BOOT_SIG;
  pb->volumeSerialNumber = volSerialNumber();
  memcpy(pb->volumeLabel, noName, sizeof(pb->volumeLabel));
  memcpy(pb->fileSystemType, fat32str, sizeof(pb->fileSystemType));
  // write partition boot sector and backup
  if (!writeCache(relSector)
      || !writeCache(relSector + 6)) {
    sdError("FAT32 write PBS failed");
  }
  clearCache(true);
  // write extra boot area and backup
  if (!writeCache(relSector + 2)
      || !writeCache(relSector + 8)) {
    sdError("FAT32 PBS ext failed");
  }
  fat32_fsinfo_t* pf = &cache.fsinfo;
  pf->leadSignature = FSINFO_LEAD_SIG;
  pf->structSignature = FSINFO_STRUCT_SIG;
  pf->freeCount = 0XFFFFFFFF;
  pf->nextFree = 0XFFFFFFFF;
  // write FSINFO sector and backup
  if (!writeCache(relSector + 1)
      || !writeCache(relSector + 7)) {
    sdError("FAT32 FSINFO failed");
  }
  clearFatDir(fatStart, 2 * fatSize + sectorsPerCluster);
  clearCache(false);
  cache.fat32[0] = 0x0FFFFFF8;
  cache.fat32[1] = 0x0FFFFFFF;
  cache.fat32[2] = 0x0FFFFFFF;
  // write first block of FAT and backup for reserved clusters
  if (!writeCache(fatStart)
      || !writeCache(fatStart + fatSize)) {
    sdError("FAT32 reserve failed");
  }
}

//------------------------------------------------------------------------------
void formatCard()
{
  cout << endl;
  cout << F("Formatting\n");
  initSizes();
  if (card.type() != SD_CARD_TYPE_SDHC) 
  {
    cout << F("FAT16\n");
    makeFat16();
  } 
  else 
  {
    cout << F("FAT32\n");
    makeFat32();
  }
#if DEBUG_PRINT
  debugPrint();
#endif  // DEBUG_PRINT
  cout << F("Format done\n");
}

void formatSD()         // Информация о SD памяти
{
  if (!card.begin(chipSelect, spiSpeed)) 
  {
    cout << F(
           "\nSD initialization failure!\n"
           "Is the SD card inserted correctly?\n"
           "Is chip select correct at the top of this program?\n");
    sdError("card.begin failed");
  }
  cardSizeBlocks = card.cardSize();
  if (cardSizeBlocks == 0) 
  {
    sdError("cardSize");
  }
  cardCapacityMB = (cardSizeBlocks + 2047) / 2048;

  cout << F("Card Size: ") << cardCapacityMB;
  cout << F(" MB, (MB = 1,048,576 bytes)") << endl;
  formatCard();
}

void txt_pass_no_all();
void pass_test_start();
void pass_test();
void drawButtons1();
void klav123();
void pass_start();

void flashLed(int pin, int times, int wait);
void dateTime(uint16_t* date, uint16_t* time);

void serial_print_date();
void clock_read();
void set_time();
void drawGlavMenu();
void klav_Glav_Menu();
void wiev_count(int num);
void test_power();
void drawButtons0_1();
void drawButtonsExit();
void drawButtonsXBee();
void klav1();
void klavXBee();

void draw_menu1();
void draw_menu2();
void draw_menu3();
void klav_menu1();
void klav_menu2();
void klav_menu3();


//-----------------------------------------------------------------------------------------------
void(* resetFunc) (void) = 0;                         // объявляем функцию reset
//---------------  пароль --------------------------
void txt_pass_no_all()                               // Вывод строки  Проверка пароля не пройдена 
{
    myGLCD.clrScr();
    myGLCD.setColor(255, 255, 255);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.print(txt_pass_no, RIGHT, 280);
    delay (1000);
}
void pass_test_start()                                     // Начало проверки пароля
{  
    myGLCD.setFont(BigFont);
    myGLCD.setBackColor(0, 0, 255);
    myGLCD.clrScr();
    drawButtons1();                                    // Нарисовать клавиатуру
      
  //  myGLCD.setColor(VGA_YELLOW);                       // Мигающие строки
    myGLCD.print(txt12, CENTER, 280);                  // Вывод строки "Введите пароль!"
    delay(300);
    myGLCD.print("                   ", CENTER, 280);  // Стереть строку "Введите пароль!"
    delay(300);
    myGLCD.print(txt12, CENTER, 280);                  // Вывод строки "Введите пароль!"

}
void pass_test()                                           // Проверка паролей
{
  pass=0;                                                // Признак правильности ввода пароля 
  pass1=0;                                               // Признак правильности ввода пароля пользователя
  pass2=0;                                               // Признак правильности ввода пароля администратора
  pass3=0;                                               // Признак правильности ввода пароля 
                                                           // user_pass    пароль из памяти текущий  пароля пользователя
  if(user_pass == var_klav123)                           // Проверка пароля пользователя
  {
    pass1 = 1;                                         // Проверка пароля пройдена 
  }
  else
  {
    pass1 = 0;                                        // Проверка пароля не пройдена 
  }

  // Проверка пароля администратора 
 // EEPROM.get(adr_pass_admin,pass_admin2);             // Получить из памяти текущий  пароля администратора 
  if(pass_admin2 == var_klav123)
  {
    pass2 = 1;                                        // Проверка пароля пройдена 
  }
  else
  {
    pass2 = 0;                                       // Проверка пароля не пройдена 
  }

  if(pass_super_admin == var_klav123)                // Проверка пароля супер администратора 
  {
    pass3 = 1;                                       // Проверка пароля пройдена 
  }
  else
  {
    pass3 = 0;                                       // Проверка пароля не пройдена 
  }

  if (( pass1 == 1) || ( pass2 == 1)|| ( pass3 == 1)) // Окончание проверки пароля супер администратора

  {
    pass = 1;                                       // Проверка пароля пройдена   
  }
  else
  {
    pass = 0;                                       // Проверка пароля не пройдена   
  }

  //Serial.print("pass1 - ");              // контроль пароля -удалить
  //Serial.println(pass1);                 // контроль пароля -удалить
  //Serial.print("pass2 - ");              // контроль пароля -удалить
  //Serial.println(pass2);                 // контроль пароля -удалить
  //Serial.print("pass3 - ");              // контроль пароля -удалить
  //Serial.println(pass3);                 // контроль пароля -удалить
  //Serial.print("pass_admin - ");         // контроль пароля -удалить
  //Serial.println(pass_admin2);           // контроль пароля -удалить
  //Serial.print("var_klav123 - ");        // контроль пароля -удалить
  //Serial.println(var_klav123);           // контроль пароля -удалить
  //Serial.print("pass_super_admin - ");   // контроль пароля -удалить
  //Serial.println(pass_super_admin);      // контроль пароля -удалить
  //Serial.print("ret - ");                // контроль пароля -удалить
  //Serial.println(ret);                   // контроль пароля -удалить

}
void drawButtons1()                                                 // Отображение цифровой клавиатуры
{

  drawButtons0_1();
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
void klav123()                             // ввод данных с цифровой клавиатуры
{
  ret = 0;
  int x,y;
  while (true)
    {
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
        char **pointer;
        var_klav123 = strtoul(stLast,pointer,10);
        myGLCD.printNumI(var_klav123, LEFT, 300);
        break;
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
        stCurrent[0] = '\0';
        stCurrentLen = 0;
        ret = 1;
        break;
      }
      }
    }
    }
} 
void pass_start()                         // Ввод пароля при старте системы
{
  while(1) 
  {
    pass_test_start();                                 // Нарисовать цифровую клавиатуру
    klav123();                                          // Считать информацию с клавиатуры
    if (ret == 1)                                       // Если "Возврат" - закончить
    {
      goto bailout11;                                 // Перейти на окончание выполнения пункта меню
    }
    else                                                // Иначе выполнить пункт меню
    {
      pass_test();                                    // Проверить пароль
    }
    if ( ( pass1 == 1)||( pass2 == 1) || ( pass3 == 1)) // если верно - выполнить пункт меню
    {
      myGLCD.clrScr();                                // Очистить экран
      myGLCD.print(txt_pass_ok, RIGHT, 208); 
      delay (500);
      return;
    }
    else                                               // Пароль не верный - сообщить
    {
      txt_pass_no_all();
    }

    bailout11:                                        // Восстановить пункты меню
    myGLCD.clrScr();
    myButtons.drawButtons();
    view_adr_user();                                  // Выбор пользователя
  };
}


//**************************************************
void flashLed(int pin, int times, int wait)  // Мигание светодиода ( не задействовано)
{
  for (int i = 0; i < times; i++) 
  {
  digitalWrite(pin, HIGH);
  delay(wait);
  digitalWrite(pin, LOW);

  if (i + 1 < times) 
  {
    delay(wait);
  }
  }
}

void dateTime(uint16_t* date, uint16_t* time)                                    // Программа записи времени и даты файла
{
  DateTime now = RTC.now();

  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(now.year(), now.month(), now.day());

  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}
void print_up() // Печать верхней строчки над меню   ( не задействовано)
{
  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print("                      ", CENTER, 0);
  switch (number_menu)
  {
    case 1:
      strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
      myGLCD.print(buffer, CENTER, 0);                                 // txt_info1
      break;
    case 2:
      strcpy_P(buffer, (char*)pgm_read_word(&(table_message[3])));
      myGLCD.print(buffer, CENTER, 0);                                 // txt_info2
      break;
    case 3:
      strcpy_P(buffer, (char*)pgm_read_word(&(table_message[4])));
      myGLCD.print(buffer, CENTER, 0);                                 // txt_info3
      break;
    case 4:
      strcpy_P(buffer, (char*)pgm_read_word(&(table_message[5])));
      myGLCD.print(buffer, CENTER, 0);                                 // txt_info4
      break;
    case 5:
      strcpy_P(buffer, (char*)pgm_read_word(&(table_message[6])));
      myGLCD.print(buffer, CENTER, 0);                                 // txt_info5
      break;
  }
}
void serial_print_date()                           // Печать даты и времени, вывод на ПК
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
  Serial.println(str1[now.dayOfWeek()]);
}
void clock_read()                           // Обновить данные модуля часов
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
void set_time()                              // Синхронизировать с ПК данные часов при программировании (не задействовано)
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
void drawGlavMenu()                                                        // Отображение главного меню
{
     
   blockKN1 = i2c_eeprom_read_byte(deviceaddress,adr_blockKN1);          // Восстановить информацию о блокировке кнопок
   blockKN2 = i2c_eeprom_read_byte(deviceaddress,adr_blockKN2);          // Восстановить информацию о блокировке кнопок
   blockKN3 = i2c_eeprom_read_byte(deviceaddress,adr_blockKN3);          // Восстановить информацию о блокировке кнопок
   blockKN4 = i2c_eeprom_read_byte(deviceaddress,adr_blockKN4);          // Восстановить информацию о блокировке кнопок
   blockKN5 = i2c_eeprom_read_byte(deviceaddress,adr_blockKN5);          // Восстановить информацию о блокировке кнопок
   blockKN6 = i2c_eeprom_read_byte(deviceaddress,adr_blockKN6);          // Восстановить информацию о блокировке кнопок
   blockKN7 = i2c_eeprom_read_byte(deviceaddress,adr_blockKN7);          // Восстановить информацию о блокировке кнопок
   blockKN8 = i2c_eeprom_read_byte(deviceaddress,adr_blockKN8);          // Восстановить информацию о блокировке кнопок


  myGLCD.clrScr();                                                       // Очистить экран
  myGLCD.setColor(255, 255, 255);                                        // Цвет текста белый 
  myGLCD.setBackColor( 0, 0, 0);                                         // Цвет фона черный
  number_device = i2c_eeprom_read_byte(deviceaddress, adr_number_device);// 
//  Serial.println(number_device);                                         //                                      
  String n_dev = "N"+String(number_device) ;                             // Вывести номер устройства в списке
  myGLCD.print(n_dev,LEFT, 3);                                           //
  myGLCD.print("LS-",62, 3);                                             // 
  myGLCD.print(String(XBee_Addr64_LS,HEX), RIGHT, 3);                    // Вывести младший адрес устройства в списке

  myGLCD.setBackColor( 0, 0, 255);
  number_menu = 0;


  if(blockKN1)
  {
  //  myGLCD.setBackColor( VGA_BLACK);
    //    myGLCD.setColor(VGA_BLACK);     
  }
  else
  {
       myGLCD.setBackColor( 0, 0, 255);
     myGLCD.setColor(0, 0, 255);                       //1
  }

  myGLCD.fillRoundRect (5, 5+20, 94, 90+10);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 5+20,94, 90+10);
  myGLCD.print("+ 1", 10, 10+20); 


  
  if(blockKN3)
  {
       // myGLCD.setColor(VGA_BLACK);  
   // myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255);  
     myGLCD.setBackColor( 0, 0, 255);   //3
  }                
  myGLCD.fillRoundRect (97, 5+20, 186, 90+10);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (97, 5+20, 186, 90+10);
  myGLCD.print("+ 3", 102, 10+20);    

    if(blockKN2)
  {
      //  myGLCD.setColor(VGA_BLACK); 
   // myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255);    
     myGLCD.setBackColor( 0, 0, 255);//2
  }                 
  myGLCD.fillRoundRect (5, 93+10, 94, 178);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 93+10,94, 178);
  myGLCD.print("- 2", 10, 98+10);    

  if(blockKN4)
  {
      //  myGLCD.setColor(VGA_BLACK);
   // myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255); 
     myGLCD.setBackColor( 0, 0, 255);//4
  }                    
  myGLCD.fillRoundRect (97, 93+10, 186, 178);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (97, 93+10, 186, 178);
  myGLCD.print("- 4", 102, 98+10);                   //"4"

//------------------------------------------------------------------

  if(blockKN5)
  {
      //  myGLCD.setColor(VGA_BLACK);  
   // myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255); 
     myGLCD.setBackColor( 0, 0, 255);//5
  }
  myGLCD.fillRoundRect (5, 183, 60, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 183, 60, 243);
  myGLCD.printNumI(5, 25-x_dev, 205-y_dev);                   //"5"
  
  if(blockKN6)
  {
      //  myGLCD.setColor(VGA_BLACK); 
   // myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255);
     myGLCD.setBackColor( 0, 0, 255);//6
  }
  myGLCD.fillRoundRect (63, 183, 118, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (63, 183, 118, 243);
  myGLCD.printNumI(6, 83-x_dev, 205-y_dev);                   //"6"

  if(blockKN7)
  {
      //  myGLCD.setColor(VGA_BLACK);   
   // myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255); 
     myGLCD.setBackColor( 0, 0, 255);//7
  }
  myGLCD.fillRoundRect (121, 183, 176, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (121, 183, 176, 243);
  myGLCD.printNumI(7, 141-x_dev, 205-y_dev);                  //"7"

  if(blockKN8)
  {
      //  myGLCD.setColor(VGA_BLACK);  
   // myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255); 
     myGLCD.setBackColor( 0, 0, 255);                          //8
  }
  myGLCD.fillRoundRect (179, 183, 234, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (179, 183, 234, 243);
  myGLCD.printNumI(8, 199-x_dev, 205-y_dev);                  //"8"

  myGLCD.setBackColor( 0, 0, 255);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (5, 248, 118, 293);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 248, 118, 293);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[5])));
  myGLCD.print(buffer, 16, 262);                                   // "ВЫХОД"

  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (121, 248, 234, 293);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (121, 248, 234, 293);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[6])));
  myGLCD.print(buffer, 130, 262);                                 //"СБРОС"
  
  myGLCD.setColor(255, 255, 255);

  myGLCD.drawRoundRect (194, 70+13+20, 234, 110+13+20);
  myGLCD.setBackColor (0, 0, 0);
  payload[0] = 11;                                                // Команда "Запросить  состояние"
    XBeeWrite();                                                    // Запросить  состояние
}
void klav_Glav_Menu()
{ 
  int x,y;
  drawGlavMenu();
  while (true)
  { 
    clock_read();
    if (oldsec != second)
    {
      test_power();
      if( second==0)
      {
        myGLCD.setColor(0, 0, 0);
        myGLCD.fillRoundRect (80, 300, 108, 319);
        myGLCD.fillRoundRect (200, 300, 239, 319);
      }
      myGLCD.setColor(255, 255, 255);
      myGLCD.setBackColor (0, 0, 0);
      myGLCD.setFont(SmallFont);
      String print_data = String(day)+'/'+ String(month)+'/'+ String(year);
      myGLCD.print(print_data,6, 303);                                           //Data
      myGLCD.setFont(BigFont);
      String print_time = String(hour)+':'+ String(minute)+':'+ String(second);
      myGLCD.print(print_time,110, 300);                                         //Время
      oldsec = second;
    }
	/*
    if(digitalRead(KN1) == false)
    {
      N_KN = 1;
      if(!blockKN1)
      {
        waitForStart(5, 5+20, 94, 90+10);
        vibroM();
          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
        myGLCD.setColor(VGA_WHITE);                        // Цвет текста
        myGLCD.printNumI(1, 208, 75);                      //1
        payload[0] = 0x01;
        XBeeWrite();
      }
    }
    if(digitalRead(KN2) == LOW)
    {
      N_KN = 2;
      if(!blockKN2)
      {
        waitForStart(5, 93+10, 94, 178);
        vibroM();
          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
        myGLCD.setColor(VGA_WHITE);                        // Цвет текста    
        myGLCD.printNumI(2, 208, 75);                      // 2
        payload[0] = 0x02;
        XBeeWrite();
      }
    }
    if(digitalRead(KN3) == LOW)
    {
      N_KN = 3;
      if(!blockKN3)
      {
        waitForStart(97, 5+20, 186, 90+10);
        vibroM();
          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
        myGLCD.setColor(VGA_WHITE);                        // Цвет текста
        myGLCD.printNumI(3, 208, 75);                      // 3
        payload[0] = 0x03;
        XBeeWrite();
      }
    }
    if(digitalRead(KN4) == LOW)
    {
      N_KN = 4;
      if(!blockKN4)
      {
        waitForStart(97, 93+10, 186, 178);
        vibroM();
          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
        myGLCD.setColor(VGA_WHITE);                        // Цвет текста
        myGLCD.printNumI(4, 208, 75);                      // 4
        payload[0] = 4;
        XBeeWrite();
      }
    }
    if(digitalRead(KN5) == false)
    {
      N_KN = 5;
      if(!blockKN5)
      {
        waitForStart(5, 183, 60, 243);
        vibroM();
          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
        myGLCD.setColor(VGA_WHITE);                        // Цвет текста
        myGLCD.printNumI(5, 208, 75);                      // 5
        payload[0] = 5;
        XBeeWrite();
      }
    }
    if(digitalRead(KN6) == LOW)
    {
      N_KN = 6;
      if(!blockKN6)
      {
        waitForStart(63, 183, 118, 243);
        vibroM();
          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
        myGLCD.setColor(VGA_WHITE);                        // Цвет текста
        myGLCD.printNumI(6, 208, 75);                      // 6
        payload[0] = 6;
        XBeeWrite();
      }
    }
    if(digitalRead(KN7) == LOW)
    {
      N_KN = 7;
      if(!blockKN7)
      {
        waitForStart(121, 183, 176, 243);
        vibroM();
          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
        myGLCD.setColor(VGA_WHITE);                        // Цвет текста
        myGLCD.printNumI(7, 208, 75);                      // 7
        payload[0] = 7;
        XBeeWrite();
      }
    }
    if(digitalRead(KN8) == LOW)
    {
      N_KN = 8;
      if(!blockKN8)
      {
        waitForStart(179, 183, 234, 243);
        vibroM();
          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
        myGLCD.setColor(VGA_WHITE);                        // Цвет текста
        myGLCD.printNumI(8, 208, 75);                      // 8
        payload[0] = 8;
        XBeeWrite();
      }
    }
	*/
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY(); 

      if ((y >= 5+20) && (y <= 90+10))                                    // Первый ряд
      {
       if ((x >= 5+x_delta+6) && (x <= 94+x_delta+6))                                   // Button: 1
      {
        if(!blockKN1)
        {
          waitForStart(5, 5+20, 94, 90+10);
          vibroM();
         // myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
         // myGLCD.setColor(VGA_WHITE);                        // Цвет текста      
          N_KN = 1;                                          // 1
          myGLCD.printNumI(1, 208, 75);
          payload[0] = 1;
          XBeeWrite();
        }
      }
      if ((x >= 97+x_delta+6) && (x <= 186+x_delta+6))                                // Button: 3
      {
        if(!blockKN3)
        {
          waitForStart(97, 5+20, 186, 90+10);
          vibroM();
          //          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
          //myGLCD.setColor(VGA_WHITE);                        // Цвет текста 
          N_KN = 3;                                          // 3
          myGLCD.printNumI(3, 208, 75);
          payload[0] = 3;
          XBeeWrite();
        }
      }
      }
   
      if ((y >= 93+10) && (y <= 178))                                  // Первый ряд
      {
       if ((x >= 5+x_delta+6) && (x <= 94+x_delta+6))                                   // Button: 2
      {
        if(!blockKN2)
        {
          waitForStart(5, 93+10, 94, 178);
          vibroM();
          //          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
          //myGLCD.setColor(VGA_WHITE);                        // Цвет текста 
          N_KN = 2;                                          // 2
          myGLCD.printNumI(2, 208, 75);
          payload[0] = 2;
          XBeeWrite();
        }
      }
      if ((x >= 97+x_delta+6) && (x <= 186+x_delta+6))                              // Button: 4
      {
        if(!blockKN4)
        {
          waitForStart(97, 93+10, 186, 178);
          vibroM();
          //          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
          //myGLCD.setColor(VGA_WHITE);                        // Цвет текста 
          N_KN = 4;                                          // 
          myGLCD.printNumI(4, 208, 75);
          payload[0] = 4;
          XBeeWrite();
        }
      }
      }
   
      if ((y >= 183) && (y <= 243))                                    //  ряд
      {
       if ((x >= 5+x_delta+6) && (x <= 60+x_delta+6))                                   // Button: 5
      {
        if(!blockKN5)
        {
          waitForStart(5, 183, 60, 243);
          vibroM();
          //          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
          //myGLCD.setColor(VGA_WHITE);                        // Цвет текста 
          N_KN = 5;                                          // 5
          myGLCD.printNumI(5, 208, 75);
          payload[0] = 5;
          XBeeWrite();
        }
      }
      if ((x >= 63+x_delta+6) && (x <= 118+x_delta+6))                                // Button: 6
      {
        if(!blockKN6)
        {
          waitForStart(63, 183, 118, 243);
          vibroM();
          //          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
          //myGLCD.setColor(VGA_WHITE);                        // Цвет текста 
          N_KN = 6;                                          // 6
          myGLCD.printNumI(6, 208, 75);
          payload[0] = 6;
          XBeeWrite();
        }
      }
      if ((x >= 121+x_delta+6) && (x <= 176+x_delta+6))                               // Button: 7
      {
        if(!blockKN7)
        {
          waitForStart(121, 183, 176, 243);
          vibroM();
          //          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
          //myGLCD.setColor(VGA_WHITE);                        // Цвет текста 
          N_KN = 7;                                          // 7
          myGLCD.printNumI(7, 208, 75);
          payload[0] = 7;
          XBeeWrite();
        }
      }
      if ((x >= 179+x_delta+6) && (x <= 234+x_delta+6))                               // Button: 8
      {
        if(!blockKN8)
        {
          waitForStart(179, 183, 234, 243);
          vibroM();
          //          myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
          //myGLCD.setColor(VGA_WHITE);                        // Цвет текста 
          N_KN = 8;                                          // 8
          myGLCD.printNumI(8, 208, 75);
          payload[0] = 8;
          XBeeWrite();
        }
      }
      }

      if ((y >= 248) && (y <= 293))                                // Четвертый ряд
      {
      if ((x >= 5+x_delta+6) && (x <= 118+x_delta+6))                                // Button: Меню 1
      {
        waitForIt(5, 248, 118, 293);
        klav_menu1();
      }
      if ((x >= 121+x_delta+6) && (x <= 234+x_delta+6))                              // Button: Меню 2
      {
        waitForIt(121, 248, 234, 293);
        klav_menu2();
      }
      }
    }
  XBeeRead();
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
  myGLCD.setBackColor( 0, 0, 0);
  int power = analogRead(A1);
  // Serial.println(power);
  power60 = power * (5.0 / 1024.0 * 2*0.965);
  //  Serial.println(power60);
  if (power60 > 5.8) myGLCD.print("\xB0", 221, 25);
  else if (power60 <= 5.8 && power60 > 5.6) myGLCD.print("\xB1", 212, 25);
  else if (power60 <= 5.6 && power60 > 5.4) myGLCD.print("\xB2", 212, 25);
  else if (power60 <= 5.4 && power60 > 5.2) myGLCD.print("\xB3", 212, 25);

  else if (power60 <= 5.2)
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.print("\xB4", 212, 25);
  }
  //myGLCD.printNumF(power60, 2, 200, 40);
  //myGLCD.setColor(255, 255, 255);
  //power = analogRead(A1);
  //power50 = power * (5.0 / 1024.0*2*0.965);
  //myGLCD.printNumF(power50, 2, 200, 50);
  //power = analogRead(A2);
  //power33 = power * (5.0 / 1024.0*0.965);
  //myGLCD.printNumF(power33, 2, 200, 60);
  //myGLCD.setFont(BigFont);
  }
}
void drawButtons0_1() // Отображение цифровой клавиатуры
{
  myGLCD.clrScr();
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
void drawButtonsExit() // Отображение кнопок управления  клавиатуры
{
  drawButtons0_1();
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
void drawButtonsXBee() // Отображение кнопок управления  клавиатуры
{
  myGLCD.clrScr();
  drawButtons0_1();
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
  ret = 0;
  drawButtonsExit();
  int x,y;
  while (true)
    {
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
        break;
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
        break;
      }
      }
    }
    }
}
void klavXBee()
{
 ret = 0;
 int x,y;
 drawButtonsXBee();
 while (true)
  {
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
      updateStrXBee('1');
    }
    if ((x >= 63) && (x <= 118)) // Button: 2
    {
      waitForIt(63, 5, 118, 60);
      updateStrXBee('2');
    }
    if ((x >= 121) && (x <= 176)) // Button: 3
    {
      waitForIt(121, 5, 176, 60);
      updateStrXBee('3');
    }
    if ((x >= 179) && (x <= 234)) // Button: 4
    {
      waitForIt(179, 5, 234, 60);
      updateStrXBee('4');
    }
    }

    if ((y >= 63) && (y <= 118))    // Второй ряд
    {
     if ((x >= 5) && (x <= 60)) // Button: 5
    {
      waitForIt(5, 63, 60, 118);
      updateStrXBee('5');
    }
    if ((x >= 63) && (x <= 118)) // Button: 6
    {
      waitForIt(63, 63, 118, 118);
      updateStrXBee('6');
    }
    if ((x >= 121) && (x <= 176)) // Button: 7
    {
      waitForIt(121, 63, 176, 118);
      updateStrXBee('7');
    }
    if ((x >= 179) && (x <= 234)) // Button: 8
    {
      waitForIt(179, 63, 234, 118);
      updateStrXBee('8');
    }
    }

    if ((y >= 121) && (y <= 176))    // Третий ряд
    {
     if ((x >= 5) && (x <= 60)) // Button: 9
    {
      waitForIt(5, 121, 60, 176);
      updateStrXBee('9');
    }
    if ((x >= 63) && (x <= 118)) // Button: 0
    {
      waitForIt(63, 121, 118, 176);
      updateStrXBee('0');
    }
    if ((x >= 121) && (x <= 176)) // Button: A
    {
      waitForIt(121, 121, 176, 176);
      updateStrXBee('A');
    }
    if ((x >= 179) && (x <= 234)) // Button: B
    {
      waitForIt(179, 121, 234, 176);
      updateStrXBee('B');
    }
    }
   
    if ((y >= 179) && (y <= 234))    // Четвертый ряд
    {
     if ((x >= 5) && (x <= 60)) // Button: C
    {
      waitForIt(5, 179, 60, 234);
      updateStrXBee('C');
    }
    if ((x >= 63) && (x <= 118)) // Button: D
    {
      waitForIt(63, 179, 118, 234);
      updateStrXBee('D');
    }
    if ((x >= 121) && (x <= 176)) // Button: E
    {
      waitForIt(121, 179, 176, 234);
      updateStrXBee('E');
    }
    if ((x >= 179) && (x <= 234)) // Button: F
    {
      waitForIt(179, 179, 234, 234);
      updateStrXBee('F');
    }
    }
   
    if ((y >= 237) && (y <= 292))                        // Пятый ряд
    {
    if ((x >= 5) && (x <= 118))                        // Button:    "Выход"
    {
      waitForIt(5, 237, 118, 292);
      myGLCD.clrScr();
    //  myGLCD.setBackColor(VGA_BLACK);
      ret = 1;
      stCurrent[0] = '\0';
      stCurrentLen = 0;
      break;
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
      break;
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

void draw_menu1()
{
  number_menu = 1;
  myGLCD.clrScr();
  myGLCD.setBackColor (0, 0, 255);
  myGLCD.setColor(0, 0, 255);                    // 1
  myGLCD.fillRoundRect (5, 28, 234, 83);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 28, 234, 83);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[30])));    // Подключить ИУ
  myGLCD.print(buffer, CENTER, 48);  

 if(pass_on_off)
 {
  myGLCD.setColor(0, 0, 255);                    // 2
  myGLCD.setBackColor (0, 0, 255);
  myGLCD.fillRoundRect (5, 86, 234, 141);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 86, 234, 141); 
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[57])));  // Сменить
  myGLCD.print(buffer, CENTER, 96);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[58])));  // пользователя
  myGLCD.print(buffer, CENTER, 116);  
 }
 else
 {
  myGLCD.setColor(0, 0, 0);                    // 2
  myGLCD.fillRoundRect (5, 86, 234, 141);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 86, 234, 141); 
  myGLCD.setBackColor (0, 0, 0);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[66])));  // Нет
  myGLCD.print(buffer, CENTER, 96);                              // Нет
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[58])));  // пользователя
  myGLCD.print(buffer, CENTER, 116);  
 }
    myGLCD.setBackColor (0, 0, 255);
  myGLCD.setColor(0, 0, 255);                    // 3
  myGLCD.fillRoundRect (5, 144, 234, 199);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 144, 234, 199);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[43])));    // Меню
  myGLCD.print(buffer, CENTER, 154);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[44])));    // файлов
  myGLCD.print(buffer, CENTER, 174);  

  myGLCD.setColor(0, 0, 255);                    // 4
  myGLCD.fillRoundRect (5, 202, 234, 257);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 202, 234, 257);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[36])));    // Настройка 
  myGLCD.print(buffer, CENTER, 212);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[37])));    // системы
  myGLCD.print(buffer, CENTER, 232);  

  myGLCD.setColor(0, 0, 255);                    // 5
  myGLCD.fillRoundRect (5, 260, 234, 315);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 260, 234, 315);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));     // "Выход"
  myGLCD.print(buffer, CENTER, 280);                                 
}
void draw_menu2()
{
  myGLCD.clrScr();
  myGLCD.setBackColor (0, 0, 255);
  number_menu = 2;  
  myGLCD.setColor(0, 0, 255);                    // 1  ИНФО XBee
  myGLCD.fillRoundRect (5, 28, 234, 83);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 28, 234, 83);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[22]))); 
  myGLCD.print(buffer, CENTER, 48);  

  myGLCD.setColor(0, 0, 255);                    // 2  Адреса устройств
  myGLCD.fillRoundRect (5, 86, 234, 141);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 86, 234, 141); 
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[28])));
  //myGLCD.print(buffer, CENTER, 96);  
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[29])));
  //myGLCD.print(buffer, CENTER, 116);  

  myGLCD.setColor(0, 0, 255);                    // 3
  myGLCD.fillRoundRect (5, 144, 234, 199);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 144, 234, 199);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[76])));
  myGLCD.print(buffer, CENTER, 154);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[77])));
  myGLCD.print(buffer, CENTER, 174);  

  myGLCD.setColor(0, 0, 255);                    // 4
  myGLCD.fillRoundRect (5, 202, 234, 257);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 202, 234, 257);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[34])));
  myGLCD.print(buffer, CENTER, 212);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[35])));
  myGLCD.print(buffer, CENTER, 232);  

  myGLCD.setColor(0, 0, 255);                    // 5   Выход         
  myGLCD.fillRoundRect (5, 260, 234, 315);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 260, 234, 315);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
  myGLCD.print(buffer, CENTER, 280);         
}
void draw_menu3()
{
    number_menu = 3;                                               // Настройка системы
  myGLCD.clrScr();
  myGLCD.setBackColor (0, 0, 255);
     
  myGLCD.setColor(0, 0, 255);                                    // 1   
  myGLCD.fillRoundRect (5, 28, 234, 83);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 28, 234, 83);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[32])));  // Сброс
  myGLCD.print(buffer, CENTER, 38);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[56])));  // счетчиков
  myGLCD.print(buffer, CENTER, 58);  

  myGLCD.setColor(0, 0, 255);                                    // 2   
  myGLCD.fillRoundRect (5, 86, 234, 141);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 86, 234, 141); 
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[49])));  // Установить
  myGLCD.print(buffer, CENTER, 96);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[50])));  // Интервалы
  myGLCD.print(buffer, CENTER, 116);  

  myGLCD.setColor(0, 0, 255);                                    // 3 
  myGLCD.fillRoundRect (5, 144, 234, 199);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 144, 234, 199);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[59]))); // Блокировка
  myGLCD.print(buffer, CENTER, 154);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[60]))); // кнопок
  myGLCD.print(buffer, CENTER, 174);  

  myGLCD.setColor(0, 0, 255);                                    // 4 
  myGLCD.fillRoundRect (5, 202, 234, 257);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 202, 234, 257);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[73])));  // Уст. N польз.
  myGLCD.print(buffer, CENTER, 212);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[74])));  // и пароль
  myGLCD.print(buffer, CENTER, 232);  

  myGLCD.setColor(0, 0, 255);                                    // 5   Выход         
  myGLCD.fillRoundRect (5, 260, 234, 315);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 260, 234, 315);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
  myGLCD.print(buffer, CENTER, 280);         
}
void draw_menu4()                      // Меню установки паролей
{
  number_menu = 4;
  myGLCD.clrScr();
  myGLCD.setBackColor (0, 0, 255);
     
  myGLCD.setColor(0, 0, 255);                    // 1   
  myGLCD.fillRoundRect (5, 28, 234, 83);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 28, 234, 83);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[63])));  // Блокировать
  myGLCD.print(buffer, CENTER, 38);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[64])));  // ввод пароля
  myGLCD.print(buffer, CENTER, 58);  

  myGLCD.setColor(0, 0, 255);                    // 2   
  myGLCD.fillRoundRect (5, 86, 234, 141);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 86, 234, 141); 
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[40])));   // Установить №
  myGLCD.print(buffer, CENTER, 96);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[41])));   // пользователя
  myGLCD.print(buffer, CENTER, 116);  

  myGLCD.setColor(0, 0, 255);                    // 3
  myGLCD.fillRoundRect (5, 144, 234, 199);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 144, 234, 199);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[31])));   //  
  myGLCD.print(buffer, CENTER, 154);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[31])));   //  
  myGLCD.print(buffer, CENTER, 174);  

  myGLCD.setColor(0, 0, 255);                    // 4
  myGLCD.fillRoundRect (5, 202, 234, 257);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 202, 234, 257);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[42])));
  myGLCD.print(buffer, CENTER, 212);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[45])));
  myGLCD.print(buffer, CENTER, 232);  

  myGLCD.setColor(0, 0, 255);                    // 5   Выход         
  myGLCD.fillRoundRect (5, 260, 234, 315);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 260, 234, 315);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
  myGLCD.print(buffer, CENTER, 280);         
}
void draw_menu5()                      // Меню установки интервалов
{
  number_menu = 5;
  myGLCD.clrScr();
  myGLCD.setBackColor (0, 0, 255);
     
  myGLCD.setColor(0, 0, 255);                    // 1   
  myGLCD.fillRoundRect (5, 28, 234, 83);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 28, 234, 83);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51]))); 
  myGLCD.print(buffer, CENTER, 38);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[52]))); 
  myGLCD.print(buffer+String(timeMotor1), CENTER, 58);  

  myGLCD.setColor(0, 0, 255);                    // 2   
  myGLCD.fillRoundRect (5, 86, 234, 141);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 86, 234, 141); 
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  myGLCD.print(buffer, CENTER, 96);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[53])));
  myGLCD.print(buffer+String(timeMotor2), CENTER, 116);  

  myGLCD.setColor(0, 0, 255);                    // 3
  myGLCD.fillRoundRect (5, 144, 234, 199);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 144, 234, 199);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  myGLCD.print(buffer, CENTER, 154);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[54])));
  myGLCD.print(buffer+String(time1), CENTER, 174);  

  myGLCD.setColor(0, 0, 255);                    // 4
  myGLCD.fillRoundRect (5, 202, 234, 257);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 202, 234, 257);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  myGLCD.print(buffer, CENTER, 212);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[54])));
  myGLCD.print(buffer+String(time2), CENTER, 232);  

  myGLCD.setColor(0, 0, 255);                    // 5   Выход         
  myGLCD.fillRoundRect (5, 260, 234, 315);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 260, 234, 315);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
  myGLCD.print(buffer, CENTER, 280);         
}
void draw_menu6()                      // Меню файлов
{
  number_menu = 6;
  myGLCD.clrScr();
  myGLCD.setBackColor (0, 0, 255);
     
  myGLCD.setColor(0, 0, 255);                    // 1   
  myGLCD.fillRoundRect (5, 28, 234, 83);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 28, 234, 83);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[43]))); 
  myGLCD.print(buffer, CENTER, 38);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[86]))); 
  myGLCD.print(buffer, CENTER, 58);  

  myGLCD.setColor(0, 0, 255);                    // 2   
  myGLCD.fillRoundRect (5, 86, 234, 141);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 86, 234, 141); 
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  //myGLCD.print(buffer, CENTER, 96);  
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[53])));
  //myGLCD.print(buffer+String(timeMotor2), CENTER, 116);  

  myGLCD.setColor(0, 0, 255);                    // 3
  myGLCD.fillRoundRect (5, 144, 234, 199);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 144, 234, 199);
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  //myGLCD.print(buffer, CENTER, 154);  
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[54])));
  //myGLCD.print(buffer+String(time1), CENTER, 174);  

  myGLCD.setColor(0, 0, 255);                    // 4
  myGLCD.fillRoundRect (5, 202, 234, 257);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 202, 234, 257);
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  //myGLCD.print(buffer, CENTER, 212);  
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[54])));
  //myGLCD.print(buffer+String(time2), CENTER, 232);  

  myGLCD.setColor(0, 0, 255);                    // 5   Выход         
  myGLCD.fillRoundRect (5, 260, 234, 315);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 260, 234, 315);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
  myGLCD.print(buffer, CENTER, 280);         
}
void draw_menu7()                      //   Меню SD
{
  number_menu = 7;
  myGLCD.clrScr();
  myGLCD.setBackColor (0, 0, 255);
     
  myGLCD.setColor(0, 0, 255);                    // 1   
  myGLCD.fillRoundRect (5, 28, 234, 83);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 28, 234, 83);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[68]))); 
  myGLCD.print(buffer, CENTER, 38);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[67]))); 
  myGLCD.print(buffer, CENTER, 58);  

  myGLCD.setColor(0, 0, 255);                    // 2   
  myGLCD.fillRoundRect (5, 86, 234, 141);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 86, 234, 141); 
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[85])));
  myGLCD.print(buffer, CENTER, 96);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[86])));
  myGLCD.print(buffer, CENTER, 116);  

  myGLCD.setColor(0, 0, 255);                    // 3
  myGLCD.fillRoundRect (5, 144, 234, 199);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 144, 234, 199);
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  //myGLCD.print(buffer, CENTER, 154);  
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[54])));
  //myGLCD.print(buffer+String(time1), CENTER, 174);  

  myGLCD.setColor(0, 0, 255);                    // 4
  myGLCD.fillRoundRect (5, 202, 234, 257);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 202, 234, 257);
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  //myGLCD.print(buffer, CENTER, 212);  
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[54])));
  //myGLCD.print(buffer+String(time2), CENTER, 232);  

  myGLCD.setColor(0, 0, 255);                    // 5   Выход         
  myGLCD.fillRoundRect (5, 260, 234, 315);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 260, 234, 315);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
  myGLCD.print(buffer, CENTER, 280);         
}
void draw_menu8()                                           //  Установки XBee
{
  number_menu = 8;
  myGLCD.clrScr();
  myGLCD.setBackColor (0, 0, 255);
     
  myGLCD.setColor(0, 0, 255);                    // 1   
  myGLCD.fillRoundRect (5, 28, 234, 83);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 28, 234, 83);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[28]))); 
  myGLCD.print(buffer, CENTER, 38);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[29]))); 
  myGLCD.print(buffer, CENTER, 58);  

  myGLCD.setColor(0, 0, 255);                    // 2   
  myGLCD.fillRoundRect (5, 86, 234, 141);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 86, 234, 141); 
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[26])));
  myGLCD.print(buffer, CENTER, 96);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[25])));
  myGLCD.print(buffer, CENTER, 116);  

  myGLCD.setColor(0, 0, 255);                    // 3
  myGLCD.fillRoundRect (5, 144, 234, 199);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 144, 234, 199);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[36])));
  myGLCD.print(buffer, CENTER, 154);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[78])));
  myGLCD.print(buffer, CENTER, 174);  

  myGLCD.setColor(0, 0, 255);                    // 4
  myGLCD.fillRoundRect (5, 202, 234, 257);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 202, 234, 257);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[84])));
  myGLCD.print(buffer, CENTER, 212);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[29])));
  myGLCD.print(buffer, CENTER, 232);  

  myGLCD.setColor(0, 0, 255);                    // 5   Выход         
  myGLCD.fillRoundRect (5, 260, 234, 315);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 260, 234, 315);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
  myGLCD.print(buffer, CENTER, 280);         
}

void klav_menu1()
{
  int x,y;
  draw_menu1();
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 5) && (x <= 234))                              // Первый ряд
      {
        if ((y >= 28) && (y <= 83))                          // Button: 1
        {
         waitForIt(5, 28, 234, 83);                          // Выбор ИУ
         myGLCD.clrScr();
         set_adr_device();
         draw_menu1();
        }
        if ((y >= 86) && (y <= 141))                         // Button: 2
        {
          waitForIt(5, 86, 234, 141);                      //  
           if(pass_on_off)
           {
            resetFunc();                                 // вызываем reset для смены пользователя
           }
        }
        if ((y >= 144) && (y <= 199))                        // Button: 3
        {
          waitForIt(5, 144, 234, 199);
                    klav_menu6();
          draw_menu1();
        }
        if ((y >= 202) && (y <= 257))                        // Button: 4  Настройка системы
        {
          waitForIt(5, 202, 234, 257);                     // Настройка системы
          pass_test_start();                               // Нарисовать цифровую клавиатуру
          klav123();                                       // Считать информацию с клавиатуры
          if (ret == 1)                                    // Если "Возврат" - закончить
            {
              goto bailout13;                          // Перейти на окончание выполнения пункта меню
            }
                pass_test();                         // Проверить пароль
          if ( ( pass2 == 1) || ( pass3 == 1))             // если верно - выполнить пункт меню
            {
              myGLCD.clrScr();                         // Очистить экран
              myGLCD.print(txt_pass_ok, RIGHT, 208); 
              delay (500);
              klav_menu3();                            // "Настройка системы"
            }
          else                                             // Пароль не верный - сообщить и закончить
            {
              txt_pass_no_all();
            }

          bailout13:    
          draw_menu1();
        }
        if ((y >= 260) && (y <= 315))                               // Button: 5
        {
        waitForIt(5, 260, 234, 315);
        drawGlavMenu();
        break;
        }
      }
    }
  }
}
void klav_menu2()
{
  int x,y;
  draw_menu2();
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 5) && (x <= 234))                                     // Первый ряд
      {
        if ((y >= 28) && (y <= 83))                                 // Button: 1
        {
          waitForIt(5, 28, 234, 83);
          XBee_status();                                          // Информация XBee 
        }
        if ((y >= 86) && (y <= 141))                                // Button: 2
        {
          waitForIt(5, 86, 234, 141);
          //klav_menu8();                                           // Установки XBee
          draw_menu2();
        }
        if ((y >= 144) && (y <= 199))                               // Button: 3
        {
          waitForIt(5, 144, 234, 199);
          klav_menu8();                                           // Установки XBee
          draw_menu2();
        }
        if ((y >= 202) && (y <= 257))                               // Button: 4
        {
          waitForIt(5, 202, 234, 257);
          setClock();
          draw_menu2();
        }
        if ((y >= 260) && (y <= 315))                               // Button:Выход
        {
        waitForIt(5, 260, 234, 315);
        drawGlavMenu();
        break;
        }
      }
    }
  }
}
void klav_menu3()
{
  int x,y;                                                                // Настройка системы
  draw_menu3();
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 5) && (x <= 234))                                     // Первый ряд
      {
        if ((y >= 28) && (y <= 83))                                 // Button: 1   Меню  Сброс данных
        {
          waitForIt(5, 28, 234, 83);
          klav_Menu_Reset();                                      // Сброс счетчиков  
          draw_menu3();
        }
        if ((y >= 86) && (y <= 141))                                // Button: 2   Меню 
        {
          waitForIt(5, 86, 234, 141);
          klav_menu5();                                          // Установить интервалы
          draw_menu3();
        }
        if ((y >= 144) && (y <= 199))                              // Button: 3  Блокировка кнопок
        {
          waitForIt(5, 144, 234, 199);
          //myGLCD.clrScr();
          //delay (500);
          klav_MenuBlockKN();
          draw_menu3();
        }
        if ((y >= 202) && (y <= 257))                               // Button: 4   Установить пароль
        {
          waitForIt(5, 202, 234, 257);
          myGLCD.clrScr();
          klav_menu4();
          draw_menu3();
        }
        if ((y >= 260) && (y <= 315))                               // Button:Выход
        {
          waitForIt(5, 260, 234, 315);
          break;
        }
      }
    }
  }
 }
void klav_menu4()                                           // Меню установки паролей
{
  int x,y;
  draw_menu4();
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 5) && (x <= 234))                              // Первый ряд
      {
        if ((y >= 28) && (y <= 83))                          // Button: 1 Сброс данных
        {
          waitForIt(5, 28, 234, 83);
              pass_off();                                      // Отключить пароль
          draw_menu4();
        }

        if ((y >= 86) && (y <= 141))                         // Button: 2 Установить номер пользователя
        {
          waitForIt(5, 86, 234, 141);
          view_adr_user();                                 // Выбор пользователя

          Serial.println(user_number);
          Serial.println(user_pass);

          if (user_number == -1)
            { 
              pass1 = 1;
              goto pass_cross_user42; 
            }
          pass_test_start(); 
          klav123();
          if (ret == 1)
            {
              goto bailout42;
            }
          pass_test();
          pass_cross_user42:

          if ( ( pass1 == 1)||( pass2 == 1) || ( pass3 == 1)) 
            {
              myGLCD.clrScr(); 
              myGLCD.print(txt_pass_ok, RIGHT, 280); 
              delay (200);
              set_n_user_start();
              set_pass_user_start();
            } 
          else
            {
              txt_pass_no_all();
            }

          bailout42:
          draw_menu4();
        }
        if ((y >= 144) && (y <= 199))                        // Button: 3    
        {
          waitForIt(5, 144, 234, 199);

          draw_menu4();
        }

        if ((y >= 202) && (y <= 257))                        // Button: 4
        {
        waitForIt(5, 202, 234, 257);
        long stCurrentLen_pass_admin = 0;
    //    EEPROM.get(adr_pass_admin, stCurrentLen_pass_admin);  
        if (stCurrentLen_pass_admin == 0)
          {  
            pass2 = 1;
            pass3 = 1;
            goto pass_cross_admin;       // Пропустить проверку старого пароля
          }
          pass_test_start();               // Ввести надпись ввода пароля
          klav123();                       // Ввести старый пароль
        if (ret == 1)
            {
            goto bailout44;
            }
        pass_test();                         // Ввести предыдущий пароль
        pass_cross_admin:            
          
        if (( pass2 == 1) || ( pass3 == 1))
          {
            myGLCD.clrScr();
            myGLCD.print(txt_pass_ok, RIGHT, 280);
            delay (500);
            set_pass_admin_start();
          }
        else
          {
            txt_pass_no_all();
          }

          bailout44:
            draw_menu4();
      }
      if ((y >= 260) && (y <= 315))                               // Button:Выход
      {
        waitForIt(5, 260, 234, 315);
        break;
      }
      }
    }
  }
 }
void klav_menu5()                                                    //  Меню установки интервалов
{
  int x,y;
  draw_menu5();
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 5) && (x <= 234))                              // Первый ряд
      {
        if ((y >= 28) && (y <= 83))                          // Button: 1  
        {
          waitForIt(5, 28, 234, 83);
          set_interval(1);
        //  bailout51: // Восстановить пункты меню
          draw_menu5();
        }

        if ((y >= 86) && (y <= 141))                         // Button: 2  
        {
          waitForIt(5, 86, 234, 141);
          set_interval(2);
          //bailout52:
          draw_menu5();
        }
        if ((y >= 144) && (y <= 199))                        // Button: 3    
        {
          waitForIt(5, 144, 234, 199);
          set_interval(3);
                 /*   bailout53:*/
            draw_menu5();
        }
        if ((y >= 202) && (y <= 257))                        // Button: 4
        {
          waitForIt(5, 202, 234, 257);
          set_interval(4);
          /*bailout54:*/
          draw_menu5();
      }
      if ((y >= 260) && (y <= 315))                          // Button:Выход
      {
        waitForIt(5, 260, 234, 315);
        break;
      }
      }
    }
  }
 }
void klav_menu6()                                                    //  Меню файлов
{
  int x,y;
  draw_menu6();
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 5) && (x <= 234))                              // Первый ряд
      {
        if ((y >= 28) && (y <= 83))                          // Button: 1  
        {
          waitForIt(5, 28, 234, 83);
            klav_menu7();                                    // Меню SD памяти
          draw_menu6();
        }

        if ((y >= 86) && (y <= 141))                         // Button: 2  
        {
          waitForIt(5, 86, 234, 141);
        
          //bailout52:
          draw_menu6();
        }
        if ((y >= 144) && (y <= 199))                        // Button: 3    
        {
          waitForIt(5, 144, 234, 199);
        
                 /*   bailout53:*/
            draw_menu6();
        }
        if ((y >= 202) && (y <= 257))                        // Button: 4
        {
          waitForIt(5, 202, 234, 257);
        
          /*bailout54:*/
          draw_menu6();
      }
      if ((y >= 260) && (y <= 315))                          // Button:Выход
      {
        waitForIt(5, 260, 234, 315);
        break;
      }
      }
    }
  }
 }
void klav_menu7()                                                    //  Меню SD
{
  int x,y;
  draw_menu7();
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 5) && (x <= 234))                              // Первый ряд
      {
        if ((y >= 28) && (y <= 83))                          // Button: 1  
        {
          waitForIt(5, 28, 234, 83);
                    formatSD();                                     // Форматирование SD памяти
          draw_menu7();
        }

        if ((y >= 86) && (y <= 141))                         // Button: 2  
        {
          waitForIt(5, 86, 234, 141);
            SD_info();
          draw_menu7();
        }
        if ((y >= 144) && (y <= 199))                        // Button: 3    
        {
          waitForIt(5, 144, 234, 199);
        
                 /*   bailout53:*/
            draw_menu7();
        }
        if ((y >= 202) && (y <= 257))                        // Button: 4
        {
          waitForIt(5, 202, 234, 257);
        
          /*bailout54:*/
          draw_menu7();
      }
      if ((y >= 260) && (y <= 315))                          // Button:Выход
      {
        waitForIt(5, 260, 234, 315);
        break;
      }
      }
    }
  }
 }
void klav_menu8()                                                    //  Установки XBee
{
  int x,y;
  draw_menu8();
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((x >= 5) && (x <= 234))                              // Первый ряд
      {
        if ((y >= 28) && (y <= 83))                          // Button: 1  
        {
          waitForIt(5, 28, 234, 83);
                    view_adr_device();                               // Просмотр адресов устройств в памяти 
          draw_menu8();
        }

        if ((y >= 86) && (y <= 141))                         // Button: 2  
        {
          waitForIt(5, 86, 234, 141);
          XBee_Set_Network();                              // Установить адрес сети
          draw_menu8();
        }
        if ((y >= 144) && (y <= 199))                        // Button: 3    
        {
          waitForIt(5, 144, 234, 199);
              set_power();                                     // Настройка мощности
            draw_menu8();
        }
        if ((y >= 202) && (y <= 257))                        // Button: 4
        {
          waitForIt(5, 202, 234, 257);
          search_XBee();                                  // Поиск устройств XBee
          draw_menu8();
      }
      if ((y >= 260) && (y <= 315))                          // Button:Выход
      {
        waitForIt(5, 260, 234, 315);
        break;
      }
      }
    }
  }
 }

void set_n_user_start()
{
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.clrScr();
  drawButtons1();
  // Вывод строки "Введите номер пользователя!"
  myGLCD.setColor(255, 0, 0);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[70]))); 
  myGLCD.print(buffer, CENTER, 240);                             // Введите номер 
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[71]))); 
  myGLCD.print(buffer, CENTER, 260);                             // пользователя!
  delay(300);
  myGLCD.print("                       ", CENTER, 240);
  myGLCD.print("                       ", CENTER, 260);
  delay(300);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[70]))); 
  myGLCD.print(buffer, CENTER, 240);                            // Введите номер 
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[71]))); 
  myGLCD.print(buffer, CENTER, 260);                            // пользователя!

  klav123();
  if (ret == 1)
    {
      ret = 0;
      return;
    }

  strcpy(temp_stLast,stLast);

  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[72]))); 
  myGLCD.print(buffer, CENTER, 240);                             // Повторите 
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[71]))); 
  myGLCD.print(buffer, CENTER, 260);                             // пользователя!
  delay(300);
  myGLCD.print("                       ", CENTER, 240);
  myGLCD.print("                       ", CENTER, 260);
  delay(300);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[72]))); 
  myGLCD.print(buffer, CENTER, 240);                            // Повторите
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[71]))); 
  myGLCD.print(buffer, CENTER, 260);                            // пользователя!

  myGLCD.printNumI(var_klav123, LEFT, 280);
  myGLCD.print("            ", LEFT, 300);   
  klav123();
  if (ret == 1)
    {
      ret = 0;
      return;
    }

  if(strcmp(temp_stLast,stLast)==0)
  {
    Serial.println("pass Ok");
  //  Serial.println(adr_user);
   // EEPROM.put(adr_user, var_klav123);  

    //i2c_eeprom_write_byte(deviceaddress, i+adr_user, stLast);          // Записать в память данные 

  }
  if(strcmp(temp_stLast,stLast)!=0)
  {
    myGLCD.print("                      ", CENTER, 260);
    myGLCD.print(txt_err_pass_user, CENTER, 260);              // Ошибка ввода!
    delay(1500);
  }

}
void set_pass_user_start()
{
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.clrScr();
  drawButtons1();
    // txt_set_pass_admin  Вывод строки "Введите пароль пользователя!"
  myGLCD.setColor(255, 0, 0);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[47])));     // Введите пароль
  myGLCD.print(buffer, CENTER, 245);                                // Введите пароль пользователя!
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[41])));     // пользователя
  myGLCD.print(buffer, CENTER, 260);                                // Введите пароль пользователя!
  delay(300);
  myGLCD.print("                       ", CENTER, 245);
  myGLCD.print("                       ", CENTER, 260);
  delay(300);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[47])));     // Введите пароль
  myGLCD.print(buffer, CENTER, 245);// Введите пароль пользователя!
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[41])));     // пользователя
  myGLCD.print(buffer, CENTER, 260);// Введите пароль пользователя!
  klav123();
  if (ret == 1)             // Сбросить признак введенного пароля
    {
      ret = 0;
      return;           // Выход из ввода пароля   
    }
  //проверка верности пароля
  long var_klav123_temp = var_klav123;

    myGLCD.setColor(255, 0, 0);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[48])));     // Повторить пароль
  myGLCD.print(buffer, CENTER, 245);// Введите пароль пользователя!
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[41])));     // пользователя
  myGLCD.print(buffer, CENTER, 260);// Введите пароль пользователя!
  delay(300);
  myGLCD.print("                       ", CENTER, 245);
  myGLCD.print("                       ", CENTER, 260);
  delay(300);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[48])));     // Повторить пароль
  myGLCD.print(buffer, CENTER, 245);// Введите пароль пользователя!
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[41])));     // администраторапользователя
  myGLCD.print(buffer, CENTER, 260);// Введите пароль пользователя!
  myGLCD.printNumI(var_klav123_temp, LEFT, 285); 
  myGLCD.print("                       ", CENTER, 300);

  klav123();

  if (ret == 1)             // Сбросить признак введенного пароля
    {
      ret = 0;
      return;            // Выход из ввода пароля  
    }
    myGLCD.setColor(255, 255, 255);
    if(var_klav123_temp == var_klav123)
    {
   //   EEPROM.put(adr_user+4, var_klav123);  
      myGLCD.print("                       ", CENTER, 260);
      myGLCD.print(txt_pass_ok, CENTER, 260); 
      delay(1500);
    }
    else
    {
      strcpy_P(buffer, (char*)pgm_read_word(&(table_message[21])));     // Ошибка ввода!
      myGLCD.print("                       ", CENTER, 260);
      myGLCD.print(buffer, CENTER, 260);                                // Ошибка ввода!
      delay(2000);
    }
}

void interval_start()               // Начало установки интервалов
{  
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.clrScr();
  drawButtons1();
}
void set_interval(int adr_interval)
{
  myGLCD.clrScr();                                 // Установить интервалы
  interval_start();                                // Нарисовать цифровую клавиатуру
                                                   // Вывод строки "Введите интервал ms"
  myGLCD.setColor(255, 255, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[49])));
  myGLCD.print(buffer, CENTER, 250);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  myGLCD.print(buffer, CENTER, 270);  
  delay(300);
  myGLCD.print("                   ", CENTER, 250);
  myGLCD.print("                   ", CENTER, 270);
  delay(300);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[49])));
  myGLCD.print(buffer, CENTER, 250);  
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[51])));
  myGLCD.print(buffer, CENTER, 270);  
  klav123();                                       // Считать информацию с клавиатуры
  if (ret == 1)                                    // Если "Возврат" - закончить
    {
      return;                                  // Перейти на окончание выполнения пункта меню
    }

  byte hi=highByte(var_klav123);
    byte low=lowByte(var_klav123);
  payload[1] = hi;
  payload[2] = low;
  Serial.println(var_klav123);
  switch (adr_interval) 
  {
    case 1:
      payload[0] = 0x0D;
      break;
    case 2:
      payload[0] = 0x0E;
      break;
    case 3:
      payload[0] = 0x09;
      break;
    case 4:
      payload[0] = 0x0A;
      break;
    default:
       break;
      // выполняется, если не выбрана ни одна альтернатива
      // default необязателен
  }

    XBeeWrite();

}
void set_pass_admin_start()
{
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.clrScr();
  drawButtons1();
    // txt_set_pass_admin  Вывод строки "Введите пароль админ!"
  myGLCD.setColor(255, 0, 0);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[47])));     // Введите пароль
  myGLCD.print(buffer, CENTER, 245);// Введите пароль админ!
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[45])));     // администратора
  myGLCD.print(buffer, CENTER, 260);// Введите пароль админ!
  delay(300);
  myGLCD.print("                       ", CENTER, 245);
  myGLCD.print("                       ", CENTER, 260);
  delay(300);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[47])));     // Введите пароль
  myGLCD.print(buffer, CENTER, 245);// Введите пароль админ!
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[45])));     // администратора
  myGLCD.print(buffer, CENTER, 260);// Введите пароль админ!
  klav123();
  if (ret == 1)             // Сбросить признак введенного пароля
    {
      ret = 0;
      return;           // Выход из ввода пароля   
    }
  //проверка верности пароля
  long var_klav123_temp = var_klav123;

    myGLCD.setColor(255, 0, 0);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[48])));     // Повторить пароль
  myGLCD.print(buffer, CENTER, 245);// Введите пароль админ!
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[45])));     // администратора
  myGLCD.print(buffer, CENTER, 260);// Введите пароль админ!
  delay(300);
  myGLCD.print("                       ", CENTER, 245);
  myGLCD.print("                       ", CENTER, 260);
  delay(300);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[48])));     // Повторить пароль
  myGLCD.print(buffer, CENTER, 245);// Введите пароль админ!
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[45])));     // администратора
  myGLCD.print(buffer, CENTER, 260);// Введите пароль админ!
  myGLCD.printNumI(var_klav123_temp, LEFT, 285); 
  myGLCD.print("                       ", CENTER, 300);

  klav123();

  if (ret == 1)             // Сбросить признак введенного пароля
    {
      ret = 0;
      return;            // Выход из ввода пароля  
    }
    myGLCD.setColor(255, 255, 255);
    if(var_klav123_temp == var_klav123)
    {
   //   EEPROM.put(adr_pass_admin, var_klav123);  
      myGLCD.print("                       ", CENTER, 260);
      myGLCD.print(txt_pass_ok, CENTER, 260); 
      delay(1500);
    }
    else
    {
      strcpy_P(buffer, (char*)pgm_read_word(&(table_message[21])));     // Ошибка ввода!
      myGLCD.print("                       ", CENTER, 260);
      myGLCD.print(buffer, CENTER, 260);                                // Ошибка ввода!
      delay(2000);
    }
}
void pass_off()
{
  myGLCD.clrScr();

    view_on_off();
   
  myGLCD.setBackColor (0, 0, 255);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (5, 179, 118, 234);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 179, 118, 234);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[65])));
  myGLCD.print(buffer, 11, 199);                                   // Сохранить

  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (121, 179, 234, 234);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (121, 179, 234, 234);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
  myGLCD.print(buffer, 139, 199);                                  // Выход

  while (true)
  {
    if (pass_on_off_t != pass_on_off)             // Отображение состояния флага пароля.
    {                                             // Подпрограмма нужна для устранения мерцания на экране.
      view_on_off();                            // Отобразить при изменении состояния
      pass_on_off_t = pass_on_off;              // Зафиксировать состояние флага.
    }

    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();

      if ((y>=200-150) && (y<=239-150))                       // Buttons: ВКЛ 
      {
        if ((x>=121) && (x<=234))
        {
          waitForIt(121, 200-150, 234, 239-150);
          pass_on_off = true;
        }
        else if ((x>=5) && (x<=118))                        // ОТКЛ
        { 
          waitForIt(5, 200-150, 118, 239-150);
          pass_on_off = false;
        }
      }

      else if ((y >= 179) && (y <= 234))                        
      {
        if ((x >= 5) && (x <= 118))                         // Button: "Ввод"  Сохранить состояние
        {
          waitForIt(5, 179, 118, 234);
          EEPROM.put(adr_pass_on_off, pass_on_off); 
          delay(200);
          resetFunc();                                    // вызываем reset для смены установки признака ввода паролей
        }
        if ((x >= 121) && (x <= 234))                       // Button: "Выход"
        {
          waitForIt(121, 179, 234, 234);
          break;
        }
      }
    }
  }
}
void view_on_off()
{
  if(pass_on_off)         // пароль включен
  {
    myGLCD.setColor(0, 255, 0);                            // Установить зеленый цвет кнопки ВКЛ
    myGLCD.fillRoundRect(121, 200-150, 234, 239-150);      // Нарисовать зеленое поле кнопки
    myGLCD.setColor(255, 0, 0);                            // Установить красный цвет текста
    myGLCD.drawRoundRect(121, 200-150, 234, 239-150);      // Нарисовать красное обрамление кнопки
    myGLCD.setBackColor(0, 255, 0);                        // Установить зеленый фон текста
    myGLCD.print("BK""\x88", 151, 212-150);                // ВКЛ  Написать красным цветом.

    myGLCD.setColor(0, 0, 0);                              // Установить черный цвет кнопки ОТКЛ
    myGLCD.fillRoundRect(5, 200-150, 118, 239-150);        // Нарисовать черное поле кнопки
    myGLCD.setColor(255, 255, 255);                        // Установить белый цвет текста 
    myGLCD.drawRoundRect(5, 200-150, 118, 239-150);        // Нарисовать белое обрамление кнопки
    myGLCD.setBackColor(0, 0, 0);                          // Установить черный фон текста
    myGLCD.print("OTK""\x88", 28, 212-150);                // ОТКЛ Написать белым цветом.
  }
  else                                                       // пароль отключен
  {
    myGLCD.setColor(0, 0, 0);                              // Установить черный цвет кнопки ВКЛ
    myGLCD.fillRoundRect(121, 200-150, 234, 239-150);      // Нарисовать черное поле кнопки
    myGLCD.setColor(255, 255, 255);                        // Установить белый цвет текста 
    myGLCD.drawRoundRect(121, 200-150, 234, 239-150);      // Нарисовать белое обрамление кнопки
    myGLCD.setBackColor(0, 0, 0);                          // Установить черный фон текста
    myGLCD.print("BK""\x88", 151, 212-150);                // ВКЛ  Написать белым цветом.

    myGLCD.setColor(0, 255, 0);                            // Установить зеленый цвет кнопки ВКЛ
    myGLCD.fillRoundRect(5, 200-150, 118, 239-150);        // Нарисовать зеленое поле кнопки
    myGLCD.setColor(255, 0, 0);                            // Установить красный цвет текста
    myGLCD.drawRoundRect(5, 200-150, 118, 239-150);        // Нарисовать красное обрамление кнопки
    myGLCD.setBackColor(0, 255, 0);                        // Установить зеленый фон текста
    myGLCD.print("OTK""\x88", 28, 212-150);                // ОТКЛ  Написать красным цветом.
  }
}
void set_power()
{
  myGLCD.clrScr();
  
  myGLCD.setBackColor (0, 0, 255);
  myGLCD.setColor(0, 0, 255);                    // 1
  myGLCD.fillRoundRect (5, 30, 234, 65);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 30, 234, 65);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[79])));    //  
  myGLCD.print(buffer, CENTER, 38);  
   
  myGLCD.setBackColor (0, 0, 255);
  myGLCD.setColor(0, 0, 255);                    // 2
  myGLCD.fillRoundRect (5, 70, 234, 105);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 70, 234, 105);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[80])));    //  
  myGLCD.print(buffer, CENTER, 78);  
  
  myGLCD.setBackColor (0, 0, 255);
  myGLCD.setColor(0, 0, 255);                    // 3
  myGLCD.fillRoundRect (5, 110, 234, 145);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 110, 234, 145);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[81])));    // 
  myGLCD.print(buffer, CENTER, 118);  
 
  myGLCD.setBackColor (0, 0, 255);
  myGLCD.setColor(0, 0, 255);                    // 4
  myGLCD.fillRoundRect (5, 150, 234, 185);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 150, 234, 185);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[82])));    // 
  myGLCD.print(buffer, CENTER, 158);  
 
  myGLCD.setBackColor (0, 0, 255);
  myGLCD.setColor(0, 0, 255);                    // 5
  myGLCD.fillRoundRect (5, 190, 234, 225);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 190, 234, 225);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[83])));    //  
  myGLCD.print(buffer, CENTER, 198);  

  myGLCD.setBackColor (0, 0, 255);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (5, 179+30+40, 118, 234+30+40);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 179+30+40, 118, 234+30+40);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[65])));
  myGLCD.print(buffer, 11, 199+30+40);                                   // Сохранить

  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (121, 179+30+40, 234, 234+30+40);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (121, 179+30+40, 234, 234+30+40);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
  myGLCD.print(buffer, 139, 199+30+40);                                  // Выход

  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();

      if ((x>=5) && (x<=234))                       // Buttons: 1
      {
        if ((y>=30+5) && (y<=65+5))
        {
          waitForIt(5, 30, 234, 65);
          power_on_off_t = power_on_off; 
          power_on_off = 1;
          view_set_power(power_on_off_t, power_on_off);
          d0Value[0] =  0x0 ;

        }
        else if ((y>=70+5) && (y<=105+5))                        // 
        { 
          waitForIt(5, 70, 234, 105);
          power_on_off_t = power_on_off; 
          power_on_off = 2;
          view_set_power(power_on_off_t, power_on_off);
          d0Value[0] =  0x1 ;
        }
        else if ((y>=110+5) && (y<=145+5))                        // 
        { 
          waitForIt(5, 110, 234, 145);
          power_on_off_t = power_on_off; 
          power_on_off = 3;
          view_set_power(power_on_off_t, power_on_off);
          d0Value[0] =  0x2 ;
        }
        else if ((y>=150+5) && (y<=185+5))                        //  
        { 
          waitForIt(5, 150, 234, 185);
          power_on_off_t = power_on_off; 
          power_on_off = 4;
          view_set_power(power_on_off_t, power_on_off);
          d0Value[0] =  0x3 ;
        }
        else if ((y>=190+5) && (y<=225+5))                        //  
        { 
          waitForIt(5, 190, 234, 225);
          power_on_off_t = power_on_off; 
          power_on_off = 5;
          view_set_power(power_on_off_t, power_on_off);
          d0Value[0] =  0x4 ;

        }
      }

       if ((y >= 179+30+40+5) && (y <= 234+30+40+5))                        
      {
        if ((x >= 5) && (x <= 118))                         // Button: "Ввод"  Сохранить состояние
        {                                                    // Сохранить настройку мощности
          waitForIt(5, 179+30+40, 118, 234+30+40);

          commandValueLength = 0x1 ;
          arRequestMod.setCommand(PLCmd);
          arRequestMod.setCommandValue(d0Value);
          arRequestMod.setCommandValueLength(commandValueLength);
          sendAtCommand_ar();
          delay(250);
          atRequest.setCommand(WRCmd);  
          sendAtCommand();
          delay(250);
          arRequestMod.clearCommandValue();
        }
        if ((x >= 121) && (x <= 234))                       // Button: "Выход"
        {
          waitForIt(121, 179+30+40, 234, 234+30+40);
          break;
        }
      }
    }
  }
}
void view_set_power(int powert, int power)
{

  switch (powert) 
  {
    case 1:
    myGLCD.setBackColor (0, 0, 255);
    myGLCD.setColor(0, 0, 255);                    // 1
    myGLCD.fillRoundRect (5, 30, 234, 65);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (5, 30, 234, 65);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[79])));    //  
    myGLCD.print(buffer, CENTER, 38);  
      break;
    case 2:
    myGLCD.setBackColor (0, 0, 255);
    myGLCD.setColor(0, 0, 255);                    // 2
    myGLCD.fillRoundRect (5, 70, 234, 105);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (5, 70, 234, 105);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[80])));    //  
    myGLCD.print(buffer, CENTER, 78);  
      break;
    case 3:

    myGLCD.setBackColor (0, 0, 255);
    myGLCD.setColor(0, 0, 255);                    // 3
    myGLCD.fillRoundRect (5, 110, 234, 145);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (5, 110, 234, 145);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[81])));    // 
    myGLCD.print(buffer, CENTER, 118);  

      break;
    case 4:

    myGLCD.setBackColor (0, 0, 255);
    myGLCD.setColor(0, 0, 255);                    // 4
    myGLCD.fillRoundRect (5, 150, 234, 185);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (5, 150, 234, 185);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[82])));    // 
  myGLCD.print(buffer, CENTER, 158);  
      break;
  case 5:
 
    myGLCD.setBackColor (0, 0, 255);
    myGLCD.setColor(0, 0, 255);                    // 5
    myGLCD.fillRoundRect (5, 190, 234, 225);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (5, 190, 234, 225);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[83])));    //  
    myGLCD.print(buffer, CENTER, 198);  
      break;
   }


  switch (power) 
  {
    case 1:
    myGLCD.setBackColor (0, 255, 0);
    myGLCD.setColor(0, 255, 0);                    // 1
    myGLCD.fillRoundRect (5, 30, 234, 65);
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRoundRect (5, 30, 234, 65);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[79])));    //  
    myGLCD.print(buffer, CENTER, 38);  
      break;
    case 2:
        myGLCD.setBackColor (0, 255, 0);
    myGLCD.setColor(0, 255, 0);                    // 2
    myGLCD.fillRoundRect (5, 70, 234, 105);
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRoundRect (5, 70, 234, 105);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[80])));    //  
    myGLCD.print(buffer, CENTER, 78);  
      break;
    case 3:
      myGLCD.setBackColor (0, 255, 0);
    myGLCD.setColor(0, 255, 0);                    // 3
    myGLCD.fillRoundRect (5, 110, 234, 145);
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRoundRect (5, 110, 234, 145);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[81])));    // 
    myGLCD.print(buffer, CENTER, 118);  
      break;
    case 4:
    myGLCD.setBackColor (0, 255, 0);
    myGLCD.setColor(0, 255, 0);                    // 4
    myGLCD.fillRoundRect (5, 150, 234, 185);
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRoundRect (5, 150, 234, 185);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[82])));    // 
    myGLCD.print(buffer, CENTER, 158);  
      break;
  case 5:
      myGLCD.setBackColor (0, 255, 0);
    myGLCD.setColor(0, 255, 0);                    // 5
    myGLCD.fillRoundRect (5, 190, 234, 225);
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRoundRect (5, 190, 234, 225);
    strcpy_P(buffer, (char*)pgm_read_word(&(table_message[83])));    //  
    myGLCD.print(buffer, CENTER, 198);  
      break;
   }

}

void search_XBee()
{
  d0Value[0] =  0xFE ;
  commandValueLength = 0x1 ;
  atRequest.setCommand(NTCmd);  
  sendAtCommand();
  delay(250);
  arRequestMod.clearCommandValue();
  delay(100);
  atRequest.setCommand(NDCmd);  
  int search_list = 0;
  int i10;
  Serial.println("\nSending command search XBee");
  xbee.send(atRequest);
  while (true)
  {
  if (xbee.readPacket(5000)) // подождите до 5 секунд для ответа состояния
  { 
  if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) // Должна быть команда отклика AT
    {
      xbee.getResponse().getAtCommandResponse(atResponse);

      if (atResponse.isOk()) 
        {
          Serial.print("Command [");
          Serial.print(atResponse.getCommand()[0]);
          Serial.print(atResponse.getCommand()[1]);
          Serial.println("] was successful!");
         
          if (atResponse.getValueLength() > 0) 
            {
              Len_XBee = atResponse.getValueLength();
              Serial.print("Command value length is - ");
              Serial.println(atResponse.getValueLength(), DEC);
              Serial.print("Command value: ");
 
              for (i10 = 0; i10 < atResponse.getValueLength(); i10++) 
                {
                  info_XBee_data[i10] = atResponse.getValue()[i10];
                  Serial.print(info_XBee_data[i10], HEX);
                  Serial.print(" ");
                }
              Serial.println("");
              search_list++;
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
    if (xbee.getResponse().isError())             // at command failed
      {
        Serial.print("Error reading packet.  Error code: ");  
        Serial.println(xbee.getResponse().getErrorCode());
      } 
    else 
      {
        Serial.println("\nNo response from radio1");  
        return;
      }
    }

  } 
}

void drawMenuReset()
{
  myGLCD.clrScr();
  myGLCD.setBackColor( 0, 0, 255);

  myGLCD.setColor(0, 0, 255);                       //1
  myGLCD.fillRoundRect (5, 5, 94, 90);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 5,94, 90);
  myGLCD.print("+ 1", 10, 10); 


  
  myGLCD.setColor(0, 0, 255);                      //3
  myGLCD.fillRoundRect (97, 5, 186, 90);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (97, 5, 186, 90);
  myGLCD.print("+ 3", 102, 10);    

  myGLCD.setColor(0, 0, 255);                     //2
  myGLCD.fillRoundRect (5, 93, 94, 178);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 93,94, 178);
  myGLCD.print("- 2", 10, 98);    

  myGLCD.setColor(0, 0, 255);                     //4
  myGLCD.fillRoundRect (97, 93, 186, 178);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (97, 93, 186, 178);
  myGLCD.print("- 4", 102, 98);                   //"4"

//------------------------------------------------------------------

  myGLCD.setColor(0, 0, 255);                    //1
  myGLCD.fillRoundRect (5, 183, 60, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 183, 60, 243);
  myGLCD.printNumI(5, 25-x_dev, 205-y_dev);                   //"1"
  
  myGLCD.setColor(0, 0, 255);                    //2
  myGLCD.fillRoundRect (63, 183, 118, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (63, 183, 118, 243);
  myGLCD.printNumI(6, 83-x_dev, 205-y_dev);                   //"2"

  myGLCD.setColor(0, 0, 255);                    //3
  myGLCD.fillRoundRect (121, 183, 176, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (121, 183, 176, 243);
  myGLCD.printNumI(7, 141-x_dev, 205-y_dev);                  //"3"

  myGLCD.setColor(0, 0, 255);                      //4
  myGLCD.fillRoundRect (179, 183, 234, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (179, 183, 234, 243);
  myGLCD.printNumI(8, 199-x_dev, 205-y_dev);                  //"4"
//----------------------------------------------------------

  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (5, 248, 118, 293);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 248, 118, 293);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[19])));
  myGLCD.print(buffer, 22, 262);                                      // "Выход"

  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (121, 248, 234, 293);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (121, 248, 234, 293);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[33])));
  myGLCD.print(buffer, 135, 262);                                     //  "СБРОС"

  myGLCD.setBackColor (0, 0, 0);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[32])));
  myGLCD.print(buffer, CENTER, 298);                                  //  Сброс счетчика

}
void klav_Menu_Reset()
{
  int x,y;
  drawMenuReset();
  while (true)
  {
    myGLCD.setColor(255, 255, 255);
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((y >= 5) && (y <= 90))                                    // Первый ряд
      {
       if ((x >= 5) && (x <= 94))                                   // Button: 1
      {
        N_KN = 1;
        count1=!count1;
        if(count1)
        {
          waitForStartR(5, 5, 94, 90);
        }
        else
        {
          waitForEndR(5, 5, 94, 90);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 97) && (x <= 186))                                // Button: 3
      {
        N_KN = 3;
        count3=!count3;
        if(count3)
        {
          waitForStartR(97, 5, 186, 90);
        }
        else
        {
          waitForEndR(97, 5, 186, 90);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
    }
   
      if ((y >= 93) && (y <= 178))                                  // Второй ряд
      {
       if ((x >= 5) && (x <= 94))                                   // Button: 2
      {
        N_KN = 2;
        count2=!count2;
        if(count2)
        {
          waitForStartR(5, 93, 94, 178);
        }
        else
        {
          waitForEndR(5, 93, 94, 178);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 97) && (x <= 186))                                // Button: 4
      {
        N_KN = 4;
        count4=!count4;
        if(count4)
        {
          waitForStartR(97, 93, 186, 178);
        }
        else
        {
          waitForEndR(97, 93, 186, 178);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
    }
   
      if ((y >= 183) && (y <= 243))                                    //  ряд
      {
       if ((x >= 5) && (x <= 60))                                   // Button: 5
      {
        N_KN = 5;
        count5=!count5;
        if(count5)
        {
          waitForStartR(5, 183, 60, 243);
        }
        else
        {
          waitForEndR(5, 183, 60, 243);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 63) && (x <= 118))                                // Button: 6
      {
        N_KN = 6;
        count6=!count6;
        if(count6)
        {
          waitForStartR(63, 183, 118, 243);
        }
        else
        {
          waitForEndR(63, 183, 118, 243);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 121) && (x <= 176))                               // Button: 7
      {
        N_KN = 7;
        count7=!count7;
        if(count7)
        {
          waitForStartR(121, 183, 176, 243);
        }
        else
        {
          waitForEndR(121, 183, 176, 243);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 179) && (x <= 234))                               // Button: 8
      {
        N_KN = 8;
        count8=!count8;
        if(count8)
        {
          waitForStartR(179, 183, 234, 243);
        }
        else
        {
          waitForEndR(179, 183, 234, 243);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
    }

      if ((y >= 248) && (y <= 293))                                // Четвертый ряд
      {
      if ((x >= 5) && (x <= 118))                                // Button: Выход
      {
        waitForIt(5, 248, 118, 293);
        break;
      }
      if ((x >= 121) && (x <= 234))                              // Button: Сброс
      {
        waitForIt(121, 248, 234, 293);
  
        if(count1)                      // Сброс счетчика 1
        {
          payload[11] = 0x01;
          waitForEndR(5, 5, 94, 90); 
        }
        else
        {
          payload[11] = 0x00;
          waitForEndR(5, 5, 94, 90); 
        }

        if(count2)                      // Сброс счетчика 2
        {
          payload[12] = 0x01;
          waitForEndR(5, 93, 94, 178);
        }
        else
        {
          payload[12] = 0x00;
          waitForEndR(5, 93, 94, 178);
        }

        if(count3)                      // Сброс счетчика 3
        {
          payload[13] = 0x01;
          waitForEnd(97, 5, 186, 90);
        }
        else
        {
          payload[13] = 0x00;
          waitForEnd(97, 5, 186, 90);
        }

        if(count4)                      // Сброс счетчика 4
        {
          payload[14] = 0x01;
          waitForEndR(97, 93, 186, 178);
        }
        else
        {
          payload[14] = 0x00;
          waitForEndR(97, 93, 186, 178);
        }
        if(count5)                      // Сброс счетчика 5
        {
          payload[15] = 0x01;
          waitForEndR(5, 183, 60, 243);
        }
        else
        {
          payload[15] = 0x00;
          waitForEndR(5, 183, 60, 243);
        }

        if(count6)                      // Сброс счетчика 6
        {
          payload[16] = 0x01;
          waitForEndR(63, 183, 118, 243);
        }
        else
        {
          payload[16] = 0x00;
          waitForEndR(63, 183, 118, 243);
        }

        if(count7)                      // Сброс счетчика 7
        {
          payload[17] = 0x01;
          waitForEndR(121, 183, 176, 243);
        }
        else
        {
          payload[17] = 0x00;
          waitForEndR(121, 183, 176, 243);
        }

        if(count8)                      // Сброс счетчика 8
        {
          payload[18] = 0x01;
          waitForEndR(179, 183, 234, 243);
        }
        else
        {
          payload[18] = 0x00;
          waitForEndR(179, 183, 234, 243);
        }

        payload[0] = 12; 

        XBeeWrite();
        break;
      }
      }
    }
  XBeeRead();
  }
}
void drawMenuBlockKN()
{
  myGLCD.clrScr();
  myGLCD.setBackColor( 0, 0, 255);
  number_menu =0;
  if(blockKN1)
  {
    myGLCD.setBackColor( VGA_BLACK);
        myGLCD.setColor(VGA_BLACK);     
  }
  else
  {
       myGLCD.setBackColor( 0, 0, 255);
     myGLCD.setColor(0, 0, 255);                       //1
  }
  myGLCD.fillRoundRect (5, 5, 94, 90);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 5,94, 90);
  myGLCD.print("+ 1", 10, 10); 


  
  if(blockKN3)
  {
        myGLCD.setColor(VGA_BLACK);  
    myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255);  
     myGLCD.setBackColor( 0, 0, 255);   //3
  }                
  myGLCD.fillRoundRect (97, 5, 186, 90);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (97, 5, 186, 90);
  myGLCD.print("+ 3", 102, 10);    

    if(blockKN2)
  {
        myGLCD.setColor(VGA_BLACK); 
    myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255);    
     myGLCD.setBackColor( 0, 0, 255);//2
  }                 
  myGLCD.fillRoundRect (5, 93, 94, 178);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 93,94, 178);
  myGLCD.print("- 2", 10, 98);    

  if(blockKN4)
  {
        myGLCD.setColor(VGA_BLACK);
    myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255); 
     myGLCD.setBackColor( 0, 0, 255);//4
  }                    
  myGLCD.fillRoundRect (97, 93, 186, 178);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (97, 93, 186, 178);
  myGLCD.print("- 4", 102, 98);                   //"4"

//------------------------------------------------------------------

  if(blockKN5)
  {
        myGLCD.setColor(VGA_BLACK);  
    myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255); 
     myGLCD.setBackColor( 0, 0, 255);//5
  }
  myGLCD.fillRoundRect (5, 183, 60, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 183, 60, 243);
  myGLCD.printNumI(5, 25-x_dev, 205-y_dev);                   //"5"
  
  if(blockKN6)
  {
        myGLCD.setColor(VGA_BLACK); 
    myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255);
     myGLCD.setBackColor( 0, 0, 255);//6
  }
  myGLCD.fillRoundRect (63, 183, 118, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (63, 183, 118, 243);
  myGLCD.printNumI(6, 83-x_dev, 205-y_dev);                   //"6"

  if(blockKN7)
  {
        myGLCD.setColor(VGA_BLACK);   
    myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255); 
     myGLCD.setBackColor( 0, 0, 255);//7
  }
  myGLCD.fillRoundRect (121, 183, 176, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (121, 183, 176, 243);
  myGLCD.printNumI(7, 141-x_dev, 205-y_dev);                  //"7"

  if(blockKN8)
  {
        myGLCD.setColor(VGA_BLACK);  
    myGLCD.setBackColor( VGA_BLACK);
  }
  else
  {
     myGLCD.setColor(0, 0, 255); 
     myGLCD.setBackColor( 0, 0, 255);//8
  }
  myGLCD.fillRoundRect (179, 183, 234, 243);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (179, 183, 234, 243);
  myGLCD.printNumI(8, 199-x_dev, 205-y_dev);                  //"8"

  myGLCD.setBackColor( 0, 0, 255);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (5, 248, 118, 293);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (5, 248, 118, 293);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[19])));
  myGLCD.print(buffer, 22, 262);                                      // "Выход"

  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (121, 248, 234, 293);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (121, 248, 234, 293);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[62])));       // УСТАН.
  myGLCD.print(buffer, 135, 262);                                     

  //myGLCD.setBackColor (0, 0, 0);
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[61])));
  //myGLCD.print(buffer, CENTER, 298);                                  // Сброс счетчика

}
void klav_MenuBlockKN()
{
  int x,y;
  bool tblockKN1 = false;
  bool tblockKN2 = false;
  bool tblockKN3 = false;
  bool tblockKN4 = false;
  bool tblockKN5 = false;
  bool tblockKN6 = false;
  bool tblockKN7 = false;
  bool tblockKN8 = false;
  drawMenuBlockKN();
  while (true)
  {
    myGLCD.setColor(255, 255, 255);
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      if ((y >= 5) && (y <= 90))                                    // Первый ряд
      {
       if ((x >= 5) && (x <= 94))                                   // Button: 1
      {
        N_KN = 1;
        tblockKN1=!tblockKN1;
        if(tblockKN1)
        {
          waitForStartR(5, 5, 94, 90);
        }
        else
        {
          waitForEndR(5, 5, 94, 90);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 97) && (x <= 186))                                // Button: 3
      {
        N_KN = 3;
        tblockKN3=!tblockKN3;
        if(tblockKN3)
        {
          waitForStartR(97, 5, 186, 90);
        }
        else
        {
          waitForEndR(97, 5, 186, 90);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
    }
   
      if ((y >= 93) && (y <= 178))                                  // Второй ряд
      {
       if ((x >= 5) && (x <= 94))                                   // Button: 2
      {
        N_KN = 2;
        tblockKN2=!tblockKN2;
        if(tblockKN2)
        {
          waitForStartR(5, 93, 94, 178);
        }
        else
        {
          waitForEndR(5, 93, 94, 178);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 97) && (x <= 186))                                // Button: 4
      {
        N_KN = 4;
        tblockKN4=!tblockKN4;
        if(tblockKN4)
        {
          waitForStartR(97, 93, 186, 178);
        }
        else
        {
          waitForEndR(97, 93, 186, 178);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
    }
   
      if ((y >= 183) && (y <= 243))                                    //  ряд
      {
       if ((x >= 5) && (x <= 60))                                   // Button: 5
      {
        N_KN = 5;
        tblockKN5=!tblockKN5;
        if(tblockKN5)
        {
          waitForStartR(5, 183, 60, 243);
        }
        else
        {
          waitForEndR(5, 183, 60, 243);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 63) && (x <= 118))                                // Button: 6
      {
        N_KN = 6;
        tblockKN6=!tblockKN6;
        if(tblockKN6)
        {
          waitForStartR(63, 183, 118, 243);
        }
        else
        {
          waitForEndR(63, 183, 118, 243);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 121) && (x <= 176))                               // Button: 7
      {
        N_KN = 7;
        tblockKN7=!tblockKN7;
        if(tblockKN7)
        {
          waitForStartR(121, 183, 176, 243);
        }
        else
        {
          waitForEndR(121, 183, 176, 243);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
      if ((x >= 179) && (x <= 234))                               // Button: 8
      {
        N_KN = 8;
        tblockKN8=!tblockKN8;
        if(tblockKN8)
        {
          waitForStartR(179, 183, 234, 243);
        }
        else
        {
          waitForEndR(179, 183, 234, 243);
        }
        while (myTouch.dataAvailable())  myTouch.read();
      }
    }

      if ((y >= 248) && (y <= 293))                                // Четвертый ряд
      {
      if ((x >= 5) && (x <= 118))                                // Button: Выход
      {
        waitForIt(5, 248, 118, 293);
        break;
      }
      if ((x >= 121) && (x <= 234))                              // Button: УСТАН.
      {
        waitForIt(121, 248, 234, 293);
   
        i2c_eeprom_write_byte(deviceaddress,adr_blockKN1, tblockKN1);          // Записать в память
        i2c_eeprom_write_byte(deviceaddress,adr_blockKN2, tblockKN2);          // Записать в память
        i2c_eeprom_write_byte(deviceaddress,adr_blockKN3, tblockKN3);          // Записать в память
        i2c_eeprom_write_byte(deviceaddress,adr_blockKN4, tblockKN4);          // Записать в память
        i2c_eeprom_write_byte(deviceaddress,adr_blockKN5, tblockKN5);          // Записать в память
        i2c_eeprom_write_byte(deviceaddress,adr_blockKN6, tblockKN6);          // Записать в память
        i2c_eeprom_write_byte(deviceaddress,adr_blockKN7, tblockKN7);          // Записать в память
        i2c_eeprom_write_byte(deviceaddress,adr_blockKN8, tblockKN8);          // Записать в память
        break;
      }
      }
    }
  XBeeRead();
  }
}

void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())  myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}
void waitForIt_inv()
{
  waitForIt_page(1, 32, 239, 64);
  waitForIt_page(1, 64, 239, 96);
  waitForIt_page(1, 96, 239, 128);
  waitForIt_page(1, 128, 239, 160);
  waitForIt_page(1, 160, 239, 192);
  waitForIt_page(1, 192, 239, 224);
}
void waitForIt_page(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}
void waitForStart(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  myGLCD.drawRoundRect (x1+1, y1+1, x2-1, y2-1);
  myGLCD.drawRoundRect (x1+2, y1+2, x2-2, y2-2);
  while (myTouch.dataAvailable())  myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor( 0, 0, 0);
}
void waitForEnd(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRoundRect (x1+1, y1+1, x2-1, y2-1);
  myGLCD.drawRoundRect (x1+2, y1+2, x2-2, y2-2);
}
void waitForStartR(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  myGLCD.drawRoundRect (x1+1, y1+1, x2-1, y2-1);
  myGLCD.drawRoundRect (x1+2, y1+2, x2-2, y2-2);
  myGLCD.setColor(255, 255, 255);
}
void waitForEndR(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRoundRect (x1+1, y1+1, x2-1, y2-1);
  myGLCD.drawRoundRect (x1+2, y1+2, x2-2, y2-2);
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
  myGLCD.printNumI(stCurrentLen, RIGHT, 300);
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

void XBeeRead() 
{
  xbee.readPacket();                                                // Получить пакет
  if (xbee.getResponse().isAvailable())                           //Проверить наличие данных
    {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)        // получен zb rx packet
      {
      xbee.getResponse().getZBRxResponse(rx);                 // Теперь заполнить наш класс ZB гх  пакет rx заполнен
      if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED)           // отправитель получил  ответ ACK
        {
            Serial.println("packet acknowledged");          // пакет признал
          ////  !! Уточнить, может нужно сравнить адрес отправителя.
          //Serial.print("checksum is ");
          //Serial.println(rx.getChecksum(), HEX);          // Контрольная сумма
          //Serial.print("All packet length is ");
          //Serial.println(rx.getPacketLength(), DEC);      // Длина пакета общего пакета
          //Serial.print("Data packet length is ");
          //Serial.println(rx.getDataLength(), DEC);        // Длина пакета пакета данных

          //for (int i = 0; i < rx.getDataLength(); i++)    // Считать информацию длина пакета  в rx.getDataLength()
          //{
          //  Serial.print("payload [");                   //
          //  Serial.print(i, DEC);                        //
          //  Serial.print("] is ");                       //
          //  Serial.println(rx.getData()[i], HEX);        // Информация находится в rx.getData()[i]
          //}

          info_module();                                  // Вывести параметры модуля на экран.
        } 
      else 
        {
           Serial.println("packet not acknowledged");        // пакет не признал
        }

//        Serial.println();
        //Получаем верхние 32-битное слово 64-битный адрес.  64-битный адрес 802.15.4 MAC адрес источника 
        XBee_Addr64_MS=(uint32_t(rx.getFrameData()[0]) << 24) + (uint32_t(rx.getFrameData()[1]) << 16) + (uint16_t(rx.getFrameData()[2]) << 8) + rx.getFrameData()[3];
        //Получаем ниже 32-битное слово...
        XBee_Addr64_LS=(uint32_t(rx.getFrameData()[4]) << 24) + (uint32_t(rx.getFrameData()[5]) << 16) + (uint16_t(rx.getFrameData()[6]) << 8) + rx.getFrameData()[7];
        //Отправить две части адреса программного обеспечения последовательного порта
        //Serial.print("Addr64 MS: ");
        //Serial.print(XBee_Addr64_MS,HEX);
        //Serial.print('\n');
        //Serial.print("Addr64 LS: ");
        //Serial.print(XBee_Addr64_LS,HEX);
        //Serial.print('\n');
        //Serial.println();
        XBee_Addr16=rx.getRemoteAddress16();              // IP-адреса в TCP/IP. 
        /*Serial.print("Addr16: ");
        Serial.println(XBee_Addr16,HEX);
*/
        addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
       }
    } 

   else if (xbee.getResponse().isError())                           //  Ошибка приема
    {
       Serial.print("error code:");
       Serial.println(xbee.getResponse().getErrorCode());         // Код ошибки xbee.getResponse().getErrorCode()
    }
}
void info_module()
{
  //byte hi=highByte(value);
  //byte low=lowByte(value);

  //// тут мы эти hi,low можем сохраить, прочитать из eePROM

  //int value2=(hi<<8) | low; // собираем как "настоящие программеры"
  //int value3=word(hi,low); // или собираем как "ардуинщики"
  int delta_x = 0;
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor( 0, 0, 255);

  countKN1   = (rx.getData()[1]<<8) | rx.getData()[2];         // Счетчик нажатий кнопки №1
  countKN2   = (rx.getData()[3]<<8) | rx.getData()[4];         // Счетчик нажатий кнопки №2
  countKN3   = (rx.getData()[5]<<8) | rx.getData()[6];         // Счетчик нажатий кнопки №3
  countKN4   = (rx.getData()[7]<<8) | rx.getData()[8];         // Счетчик нажатий кнопки №4
  countKN5   = (rx.getData()[9]<<8) | rx.getData()[10];        // Счетчик нажатий кнопки №5
  countKN6   = (rx.getData()[11]<<8) | rx.getData()[12];       // Счетчик нажатий кнопки №6
  countKN7   = (rx.getData()[13]<<8) | rx.getData()[14];       // Счетчик нажатий кнопки №7
  countKN8   = (rx.getData()[15]<<8) | rx.getData()[16];       // Счетчик нажатий кнопки №8
  time1      = (rx.getData()[17]<<8) | rx.getData()[18];       // Интервал 1 (резерв, не применяется)
  time2      = (rx.getData()[19]<<8) | rx.getData()[20];       // Интервал 2 (резерв, не применяется)
  timeMotor1 = (rx.getData()[21]<<8) | rx.getData()[22];       // Интервал Мотор1
    timeMotor2 = (rx.getData()[23]<<8) | rx.getData()[24];       // Интервал Мотор2


  if(number_menu == 0)
  {

    if(rx.getData()[26] != stat_rele1)
    {
      stat_rele1 = rx.getData()[26];
      if(rx.getData()[26] == 0)   // Отображение состояния реле №1
      {

        myGLCD.setColor(0, 0, 255);                             // Цвет окраса кнопки в синий  
        myGLCD.fillRoundRect (5, 183, 60, 243);                 // Закрaшиваем кнопку
        myGLCD.setColor(VGA_WHITE);                             // Цвет текста 
        myGLCD.drawRoundRect (5, 183, 60, 243);                 // Рисуем обрамление кнопки
        myGLCD.printNumI(5, 25-x_dev, 205-y_dev);               // Отображаем состояние реле №1 (КН 5)   
      }
      else
      {
        myGLCD.setColor(0, 255, 0);                    //1
        myGLCD.fillRoundRect (5, 183, 60, 243);
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (5, 183, 60, 243);
        myGLCD.printNumI(5, 25-x_dev, 205-y_dev);  
      }
    }

    if(rx.getData()[27] != stat_rele2)
    {
      stat_rele2 = rx.getData()[27];
      if(rx.getData()[27] == 0)   // Отображение состояния реле №2
      {
        myGLCD.setColor(0, 0, 255);                    //2
        myGLCD.fillRoundRect (63, 183, 118, 243);
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (63, 183, 118, 243);
        myGLCD.printNumI(6, 83-x_dev, 205-y_dev);                   //"2"
      }
      else
      {
        myGLCD.setColor(0, 255, 0);                    //2
        myGLCD.fillRoundRect (63, 183, 118, 243);
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (63, 183, 118, 243);
        myGLCD.printNumI(6, 83-x_dev, 205-y_dev);                   //"2"
      }
    }

    if(rx.getData()[28] != stat_rele3)
    {
       stat_rele3 = rx.getData()[28];
      if(rx.getData()[28] == 0)   // Отображение состояния реле №3
      {
        myGLCD.setColor(0, 0, 255);                    //3
        myGLCD.fillRoundRect (121, 183, 176, 243);
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (121, 183, 176, 243);
        myGLCD.printNumI(7, 141-x_dev, 205-y_dev);                  //"3"
      }
      else
      {
        myGLCD.setColor(0, 255, 0);                    //3
        myGLCD.fillRoundRect (121, 183, 176, 243);
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (121, 183, 176, 243);
        myGLCD.printNumI(7, 141-x_dev, 205-y_dev);                  //"3"
      }
    }
    if(rx.getData()[29] != stat_rele4)
    {
       stat_rele4 = rx.getData()[29];
        if(rx.getData()[29] == 0)   // Отображение состояния реле №4
      {
        myGLCD.setColor(0, 0, 255);                                 //4
        myGLCD.fillRoundRect (179, 183, 234, 243);
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (179, 183, 234, 243);
        myGLCD.printNumI(8, 199-x_dev, 205-y_dev);                  //"4"
      }
      else
      {
        myGLCD.setColor(0, 255, 0);                                  //4
        myGLCD.fillRoundRect (179, 183, 234, 243);
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (179, 183, 234, 243);
        myGLCD.printNumI(8, 199-x_dev, 205-y_dev);                  //"4"
      }
    }
   
    myGLCD.setColor(VGA_WHITE);                                         // Цвет текста  
    if(!blockKN1)
    {
      myGLCD.setBackColor(0,0,255);                                   // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                                 // Цвет фона
    }
    if(countKN1 < 10) delta_x = 0;
    else if(countKN1 > 9 && countKN1 < 100) delta_x = -8;
    else if(countKN1 > 99) delta_x = -16;
    myGLCD.printNumI(countKN1, 43+delta_x, 10+40+10);

    if(!blockKN2)
    {
      myGLCD.setBackColor(0,0,255);                       // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
    }

    if(countKN2 < 10) delta_x = 0;
    else if(countKN2 > 9 && countKN2 < 100) delta_x = -8;
    else if(countKN2 > 99) delta_x = -16;
    myGLCD.printNumI(countKN2, 43+delta_x, 10+130+10); 

    if(!blockKN3)
    {
      myGLCD.setBackColor(0,0,255);                       // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
    }
  
    if(countKN3 < 10) delta_x = 0;
    else if(countKN3 > 9 && countKN3 < 100) delta_x = -8;
    else if(countKN3 > 99) delta_x = -16;
    myGLCD.printNumI(countKN3, 135+delta_x, 10+40+10);  

    if(!blockKN4)
    {
      myGLCD.setBackColor(0,0,255);                       // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
    }
    if(countKN4 < 10) delta_x = 0;
    else if(countKN4 > 9 && countKN4 < 100) delta_x = -8;
    else if(countKN4 > 99) delta_x = -16;
    myGLCD.printNumI(countKN4, 135+delta_x, 10+130+10);     
  
    if(!blockKN5)
    {
      myGLCD.setBackColor(0,0,255);                       // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
    }
    if(countKN5 < 10) delta_x = 0;
    else if(countKN5 > 9 && countKN5 < 100) delta_x = -8;
    else if(countKN5 > 99) delta_x = -16;
    myGLCD.printNumI(countKN5, 25+delta_x, 205+10);  
    
    if(!blockKN6)
    {
      myGLCD.setBackColor(0,0,255);                       // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
    }
    
    if(countKN6 < 10) delta_x = 0;
    else if(countKN6 > 9 && countKN6 < 100) delta_x = -8;
    else if(countKN6 > 99) delta_x = -16;
    myGLCD.printNumI(countKN6, 83+delta_x , 205+10); 
    
    if(!blockKN7)
    {
      myGLCD.setBackColor(0,0,255);                       // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
    }
    if(countKN7 < 10) delta_x = 0;
    else if(countKN7 > 9 && countKN7 < 100) delta_x = -8;
    else if(countKN7 > 99) delta_x = -16;
    myGLCD.printNumI(countKN7, 141+delta_x, 205+10);  
    
    if(!blockKN8)
    {
      myGLCD.setBackColor(0,0,255);                       // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
    }
    if(countKN8 < 10) delta_x = 0;
    else if(countKN8 > 9 && countKN8 < 100) delta_x = -8;
    else if(countKN8 > 99) delta_x = -16;
    myGLCD.printNumI(countKN8, 199+delta_x, 205+10); 
  
    if(!blockKN1)
    {
      myGLCD.setBackColor(0,0,255);                       // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
    }
    myGLCD.setColor(255, 255, 255);  
    int count1_2 = countKN1-countKN2;
    myGLCD.print("     ", 10, 70+10);
    if(count1_2< 0) delta_x = -24;
    else if(count1_2 >= 0 && count1_2 < 10) delta_x = 0;
    else if(count1_2 > 9 && count1_2 < 100) delta_x = -8;
    else if(count1_2 > 99) delta_x = -16;
    myGLCD.printNumI(count1_2 , 43+delta_x, 10+60+10);
    
    if(!blockKN3)
    {
      myGLCD.setBackColor(0,0,255);                       // Цвет фона синий
    }
    else
    {
      myGLCD.setBackColor(VGA_BLACK);                    // Цвет фона
    }
    count1_2 = countKN3-countKN4;
    myGLCD.print("     ", 100, 70+10);
    if(count1_2< 0) delta_x = -24;
      else if(count1_2 >= 0 && count1_2 < 10) delta_x = 0;
    else if(count1_2 > 9 && count1_2 < 100) delta_x = -8;
    else if(count1_2 > 99) delta_x = -16;
    myGLCD.printNumI(count1_2 , 135+delta_x, 10+60+10);
  
    int x_back = rx.getData()[0];
    myGLCD.setColor(255, 255, 255);
    switch( x_back)                                        //generate query response based on function type
    {
      case 1:
        waitForEnd(5, 5+20, 94, 90+10);
        break;
      case 2:
        waitForEnd(5, 93+10, 94, 178);
        break;
      case 3:
        waitForEnd(97, 5+20, 186, 90+10);
        break;
      case 4:
        waitForEnd(97, 93+10, 186, 178);
        break;
      case 5:
        waitForEnd(5, 183, 60, 243);
        break;
      case 6:
        waitForEnd(63, 183, 118, 243);
        break;
      case 7:
        waitForEnd(121, 183, 176, 243);
        break;
      case 8:
        waitForEnd(179, 183, 234, 243);
        break;
      default:
        waitForEnd(5, 5+20, 94, 90+10);
        waitForEnd(5, 93+10, 94, 178);
        waitForEnd(97, 5+20, 186, 90+10);
        waitForEnd(97, 93+10, 186, 178);
        waitForEnd(5, 183, 60, 243);
        waitForEnd(63, 183, 118, 243);
        waitForEnd(121, 183, 176, 243);
        waitForEnd(179, 183, 234, 243);
        break;
      }
  }
}
void XBeeWrite()
{
  int i10;
  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));  
  xbee.send(zbTx); 
  if (xbee.readPacket(6000))                                               //  После отправки запроса TX, мы ожидаем ответ статуса
    {
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE)     // получил ответ! // Должен быть znet tx status       
      {
        xbee.getResponse().getZBTxStatusResponse(txStatus);
        if (txStatus.getDeliveryStatus() == SUCCESS)                // Получить статус доставки, пятый байт
          {
            Serial.println("Success.  time to celebrate!");     // Успешно, можно радоваться.
            myGLCD.setColor(VGA_LIME);
            myGLCD.drawRoundRect (194, 70+13+20, 234, 110+13+20);
            myGLCD.fillRoundRect (195, 71+13+20, 233, 109+13+20);
            myGLCD.setColor(255, 255, 255);
            myGLCD.drawRoundRect (194, 70+13+20, 234, 110+13+20);
            myGLCD.setBackColor(0, 0, 0);
            delay(400); 
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRoundRect (195, 71+13+20, 233, 109+13+20);
          }
        else 
          {
            Serial.println("The remote XBee did not receive our packet. is it powered on?");    // Управляемый XBee не ответил. Он включен?
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
        Serial.println("XBee did not provide a timely TX Status Response");
    myGLCD.setColor(255 , 0, 0);
    myGLCD.fillRoundRect (195, 71+13+20, 233, 109+13+20);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (194, 70+13+20, 234, 110+13+20);
    myGLCD.setBackColor(0, 0, 0);
    delay(400); 
    myGLCD.setColor(0, 0, 0);
    myGLCD.fillRoundRect (195, 71+13+20, 233, 109+13+20);
    myGLCD.setColor(255, 255, 255);
    delay(2000);
    XBeeRead();                                         // Получить ответ от ИУ с параметрами.
    switch(N_KN)                                        //generate query response based on function type
    {
    case 1:
      waitForEnd(5, 5+20, 94, 90+10);
      break;
    case 2:
      waitForEnd(5, 93+10, 94, 178);
      break;
    case 3:
      waitForEnd(97, 5+20, 186, 90+10);
      break;
    case 4:
      waitForEnd(97, 93+10, 186, 178);
      break;
    case 5:
      waitForEnd(5, 183, 60, 243);
      break;
    case 6:
      waitForEnd(63, 183, 118, 243);
      break;
    case 7:
      waitForEnd(121, 183, 176, 243);
      break;
    case 8:
      waitForEnd(179, 183, 234, 243);
      break;
    default:
      break;
    }
  }
} 
void XBee_Setup()            //  
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
void XBee_status()
{
  time_flag_start();
  int XBee_x, XBee_y, x, y;
  unsigned long XBee_data2;
  int yXBee = 32;                                                  // Стартовая точка смещения строк текста
  int yDelta = 16;                                                 // Дельта смещения вниз

  myGLCD.clrScr();                                                 // Очистить экран CENTER
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (2, 2, 239, 25);                            // Нарисовать прямоугольник для текста
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 2, 239, 25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[7])));     // Информация XBee
  myGLCD.print(buffer, CENTER, 5);
              
  myGLCD.setBackColor(0, 0, 0);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[11])));    // Номер "Number SH,SL"
  myGLCD.print(buffer, CENTER, yXBee);
  yXBee = yXBee + yDelta;                                          // Форматирование текста, смещение  вниз
  myGLCD.setColor(0, 255, 255);
  myGLCD.print("MS", LEFT, yXBee);
  myGLCD.print(String(XBee_Addr64_MS,HEX), RIGHT, yXBee);          //
  yXBee = yXBee + yDelta;                                          // Форматирование текста, смещение  вниз
  myGLCD.print("LS", LEFT, yXBee);
  myGLCD.print(String(XBee_Addr64_LS,HEX), RIGHT, yXBee);

  yXBee = yXBee + yDelta;                                         // Форматирование текста, смещение
  myGLCD.setColor(255, 255, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[10])));   // "Addr Coordinat"
  myGLCD.print(buffer, CENTER, yXBee);
  myGLCD.setColor(0, 255, 255);
  atRequest.setCommand(shCmd);  
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  yXBee = yXBee + yDelta;                                        // Форматирование текста, смещение
  myGLCD.print("SH", LEFT, yXBee);
  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
  atRequest.setCommand(slCmd);  
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  yXBee = yXBee + yDelta;                                        // Форматирование текста, смещение
  myGLCD.print("SL", LEFT, yXBee);
  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
          
  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;                                        // Форматирование текста, смещение
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[12])));  // "Network (MY) = "
  myGLCD.print(buffer, LEFT, yXBee);
  atRequest.setCommand(MYCmd);  
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);

  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;                                        // Форматирование текста, смещение
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[12])));  // "Network (MY) = "
  myGLCD.print("OI", LEFT, yXBee);
  atRequest.setCommand(OICmd);  
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);



  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;                                        // Форматирование текста, смещение
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[13])));  // "PAN ID (OP)  = "
  myGLCD.print(buffer, LEFT, yXBee);
  atRequest.setCommand(opCmd);  
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
  
  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;                                        // Форматирование текста, смещение
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[14])));  // "ID (ID)      = "
  myGLCD.print(buffer, LEFT, yXBee);
  atRequest.setCommand(IDCmd);  
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);

  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;// Форматирование текста, смещение
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[15])));  // "Chanel (CH)  = "
  myGLCD.print(buffer, LEFT, yXBee);
  atRequest.setCommand(CHCmd);  
  sendAtCommand();
  XBee_data2 = (unsigned long&)info_XBee_data1;
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.print("0x",193, yXBee);
  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);

  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;// Форматирование текста, смещение
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[16])));  
  myGLCD.print(buffer, LEFT, yXBee);
  atRequest.setCommand(assocCmd); 
  sendAtCommand();
  XBee_data2 = (unsigned long&)info_XBee_data1;
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);


  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;// Форматирование текста, смещение
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[17])));  
  myGLCD.print(buffer, LEFT, yXBee);
  atRequest.setCommand(BDCmd); 
  sendAtCommand();
  XBee_data2 = (unsigned long&)info_XBee_data1;
  myGLCD.setColor(VGA_YELLOW);
  switch (XBee_data2)
    {
    case 0:
      XBee_data2 = 1200;
      break;
    case 1:
      XBee_data2 = 2400;
      break;
    case 2:
      XBee_data2 = 4800;
      break;
    case 3:
      XBee_data2 = 9600;
      break;
    case 4:
      XBee_data2 = 19200;
      break;
    case 5:
      XBee_data2 = 38400;
      break;
    case 6:
      XBee_data2 = 57600;
      break;
    case 7:
      XBee_data2 = 115200;
      break;
      default:
       XBee_data2 = 000000;
    }

  myGLCD.print(String(XBee_data2), RIGHT, yXBee);

  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;// Форматирование текста, смещение

  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[18])));   // "Volt(V) ";
  myGLCD.print(buffer, LEFT, yXBee);
  atRequest.setCommand(VoltCmd);   
  sendAtCommand();
  XBee_data2 = (unsigned long&)info_XBee_data1;
  myGLCD.setColor(VGA_YELLOW);
  float XBee_data3 = XBee_data2;
  myGLCD.printNumF(XBee_data3/1000,2, RIGHT, yXBee,'.',2);
  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;                                             // Форматирование текста, смещение
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[27])));       // txt_temperature
  myGLCD.print(buffer, LEFT, yXBee);
  atRequest.setCommand(TPCmd);                                        // Температура модуля
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  myGLCD.setColor(VGA_YELLOW);
  myGLCD.print(String(XBee_data2, DEC), RIGHT, yXBee);

  myGLCD.setColor(255, 255, 255);
  yXBee = yXBee + yDelta;                                             // Форматирование текста, смещение
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[75])));       // "TX Power mW"
  myGLCD.print(buffer, LEFT, yXBee);
  atRequest.setCommand(PLCmd);                                        // "TX Power mW"
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  switch (XBee_data2)
  {
  case 0:
    XBee_data2 = 1;
    break;
  case 1:
    XBee_data2 = 25;
    break;
  case 2:
    XBee_data2 = 100;
    break;
  case 3:
    XBee_data2 = 200;
    break;
  case 4:
    XBee_data2 = 300;
    break;
  default:
    XBee_data2 = 0;
    break;
  }

  myGLCD.setColor(VGA_YELLOW);
  myGLCD.print(String(XBee_data2, DEC), RIGHT, yXBee);

  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (2, 296, 238, 318);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 296, 238, 318);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.setColor(255, 255, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[19])));
  myGLCD.print(buffer, CENTER, 299);                                // Завершить просмотр

  while (myTouch.dataAvailable()) {}
  while (true)
  {
    if (myTouch.dataAvailable())
    {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();
    if ((y>=1) && (y<=319))  // Upper row  
      {
      if ((x>=1) && (x<=239))  // Выход
        {
          waitForIt(1, 1, 239, 319);

          draw_menu2();

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

void updateStrXBee(int val) // Проверка длины строки при вводе адреса XBee
{

  if (stCurrentLen < lenStr)
  {
  stCurrent[stCurrentLen]=val;
  stCurrent[stCurrentLen+1]='\0';
  stCurrentLen++;
  myGLCD.setColor(0, 255, 0);
  myGLCD.print(stCurrent, LEFT, 300);
  if(stCurrentLen > lenStr -1)  myGLCD.setColor(255, 0, 0);
  myGLCD.printNumI(stCurrentLen, RIGHT, 300);
  myGLCD.setColor(0, 255, 0);
  }
  else
  {   // Вывод строки "ПЕРЕПОЛНЕНИЕ!"
  myGLCD.setColor(255, 0, 0);
  myGLCD.print("                       ", CENTER, 300);
  myGLCD.print("\x89""EPE""\x89O\x88HEH\x86""E!", CENTER, 300);// ПЕРЕПОЛНЕНИЕ!
  delay(500);
  myGLCD.print("                       ", CENTER, 300);
  delay(500);
  myGLCD.print("\x89""EPE""\x89O\x88HEH\x86""E!", CENTER, 300);// ПЕРЕПОЛНЕНИЕ!
  delay(500);
  myGLCD.print("                       ", CENTER, 300);
  myGLCD.setColor(0, 255, 0);
  stCurrent[0]='\0';
  stCurrentLen=0;
  }
}
void XBee_SetH(int adr_xbee_h)
{
  lenStr = 8;
  int _adr_xbee_h = adr_xbee_h;
  klavXBee();
  if (ret == 1)
    {
      ret = 0;
      return;
    }
  strcpy(temp_stLast,stLast);
  long int li1 = strtol(temp_stLast, NULL, 16);                                 // преобразовать первую часть строки в значение HEX 
  byte *m = (byte *)&li1;                                                       //Разложить данные старшего адреса координатора побайтно для записи в память
  for (int i=0; i<4; i++)
    {
      i2c_eeprom_write_byte(deviceaddress, i+_adr_xbee_h+2, m[i]);          // Записать в память данные старшего адреса координатора
    }
}
void XBee_SetL(int adr_xbee_h)
{ 
  lenStr = 8;
  int _adr_xbee_h = adr_xbee_h;
  klavXBee();
  if (ret == 1)
    {
      ret = 0;
      return;
    }
  strcpy(temp_stLast,stLast);
  long int li1 = strtol(temp_stLast, NULL, 16);                                // преобразовать первую часть строки в значение HEX  
  byte *m = (byte *)&li1;                                                       //Разложить данные младшего адреса координатора побайтно для записи в память
  for (int i=0; i<4; i++)
    {
      i2c_eeprom_write_byte(deviceaddress, i+_adr_xbee_h+6, m[i]);           // Записать в память данные младшего адреса координатора
    }
 }
void XBee_Set_Network()
{
  lenStr = 4;
  klavXBee();
  if (ret == 1)
  {
    ret = 0;
    return;
  }
  strcpy(temp_stLast,stLast);
  long int li1 = strtol(temp_stLast, NULL, 16); // преобразовать первую часть строки в значение HEX 
            
  byte *m = (byte *)&li1; //Разложить данные младшего адреса координатора побайтно для записи в память
  for (int i=0; i<2; i++)
    {
      i2c_eeprom_write_byte(deviceaddress, i+adr_xbee_network, m[i]); // Записать в память данные младшего адреса координатора
    }
  commandValue[0]= i2c_eeprom_read_byte( deviceaddress, 1+adr_xbee_network);
  commandValue[1]= i2c_eeprom_read_byte( deviceaddress, 0+adr_xbee_network);

  myGLCD.print("                          ", CENTER, 300);
  myGLCD.print(" OK !", RIGHT, 300);// ОК!
  delay(1500);
  //      
  //if(strcmp(temp_stLast,stLast)!=0 ||stCurrentLen1 > 4 )
  //  {
  //    myGLCD.print("                         ", CENTER, 300);
  //    myGLCD.print(txt_err_pass_user, CENTER, 300);// Ошибка ввода!
  //  //  result_minus = 0;
  //    delay(1500);
  //    return;
  //  }
  test_arRequestMod();              // Записать данные в XBee
}

void sendAtCommand() 
{
  int i10;
  Serial.println("\nSending command sendAtCommand to the XBee");
  xbee.send(atRequest);

  if (xbee.readPacket(5000)) // подождите до 5 секунд для ответа состояния
  { 
  if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) // Должна быть команда отклика AT
    {
      xbee.getResponse().getAtCommandResponse(atResponse);

      if (atResponse.isOk()) 
        {
          Serial.print("Command [");
          Serial.print(atResponse.getCommand()[0]);
          Serial.print(atResponse.getCommand()[1]);
          Serial.println("] was successful!");
         
          if (atResponse.getValueLength() > 0) 
            {
              Len_XBee = atResponse.getValueLength();
              Serial.print("\nCommand value length is - ");
              Serial.println(atResponse.getValueLength(), DEC);
              Serial.print("Command value: ");
              int i11=Len_XBee-1;
              info_XBee_data1[0] = 0;
              info_XBee_data1[1] = 0;
              info_XBee_data1[2] = 0;
              info_XBee_data1[3] = 0;

              for (i10 = 0; i10 < atResponse.getValueLength(); i10++) 
                {
                info_XBee_data[i10] = atResponse.getValue()[i10];
                Serial.print(info_XBee_data[i10], HEX);
                Serial.print(" ");
                info_XBee_data1[i11] = info_XBee_data[i10];
                i11--;
                }
              Serial.println("");
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
    if (xbee.getResponse().isError())             // at command failed
      {
        Serial.print("Error reading packet.  Error code: ");  
        Serial.println(xbee.getResponse().getErrorCode());
      } 
    else 
      {
        Serial.println("No response from radio1");  
      }
    }
  delay(100);
} 
void sendAtCommand_ar() 
{
  int i10;

  Serial.println("\nSending command sendAtCommand_ar to the XBee");
  xbee.send(arRequestMod);      // send the command

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
          
        //  Serial.print("Command [");
        //  Serial.print(atResponse.getCommand()[0]);
        //  Serial.print(atResponse.getCommand()[1]);
        //  Serial.println("] was successful!");
         
          if (atResponse.getValueLength() > 0) 
            {
              Len_XBee = atResponse.getValueLength();
            //  Serial.print("Command value length is ");
            //  Serial.println(atResponse.getValueLength(), DEC);
            //  Serial.print("Command value: ");
              int i11=Len_XBee-1;
              info_XBee_data1[0] = 0;
              info_XBee_data1[1] = 0;
              info_XBee_data1[2] = 0;
              info_XBee_data1[3] = 0;

              for (i10 = 0; i10 < atResponse.getValueLength(); i10++) 
                {
                info_XBee_data[i10] = atResponse.getValue()[i10];
                Serial.print(info_XBee_data[i10], HEX);
                info_XBee_data1[i11] = info_XBee_data[i10];
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
          //XBee_alarm();
          delay(1000);
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRoundRect (278, 92, 318, 132);
          myGLCD.setColor(0, 0, 0);
          myGLCD.drawRoundRect (278, 92, 318, 132);
        //  mcp_Out1.digitalWrite(Beep, LOW);                    // 
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
  Serial.println("\nSending command sendRemoteAtCommand to the XBee");
  xbee.send(remoteAtRequest);

  // wait up to 5 seconds for the status response
  if (xbee.readPacket(5000)) 
  {
  // got a response!

  // should be an AT command response
  if (xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE) 
  {
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
  } 
  else 
  {
    Serial.print("Expected Remote AT response but got ");
    Serial.print(xbee.getResponse().getApiId(), HEX);
  }    
  }
  else if (xbee.getResponse().isError()) 
  {
  Serial.print("Error reading packet.  Error code: ");  
  Serial.println(xbee.getResponse().getErrorCode());
  }
  else 
  {
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
void read_HL_mem_XBee(int N_device )
 {
  //Программа ввостановления данных ZigBee из памяти.
  byte y[4];   ; //Чтение из памяти текущих данных старшего адреса координатора
    y[3]= i2c_eeprom_read_byte( deviceaddress, 3+N_device+2);
    i2c_eeprom_write_byte(deviceaddress, 3+adr_xbee_current_H, y[3]);    // Записать в память данные 
    y[2]= i2c_eeprom_read_byte( deviceaddress, 2+N_device+2);
    i2c_eeprom_write_byte(deviceaddress, 2+adr_xbee_current_H, y[2]);    // Записать в память данные 
    y[1]= i2c_eeprom_read_byte( deviceaddress, 1+N_device+2);
    i2c_eeprom_write_byte(deviceaddress, 1+adr_xbee_current_H, y[1]);    // Записать в память данные 
    y[0]= i2c_eeprom_read_byte( deviceaddress, 0+N_device+2);
    i2c_eeprom_write_byte(deviceaddress, adr_xbee_current_H, y[0]);      // Записать в память данные 
    XBee_Addr64_MS = (unsigned long&) y;  // Сложить восстановленные текущие данные


    //Чтение из памяти текущих данных младшего адреса координатора
    y[3]= i2c_eeprom_read_byte( deviceaddress, 3+N_device+6);
    i2c_eeprom_write_byte(deviceaddress, 3+adr_xbee_current_L, y[3]);    // Записать в память данные 
    y[2]= i2c_eeprom_read_byte( deviceaddress, 2+N_device+6);
    i2c_eeprom_write_byte(deviceaddress, 2+adr_xbee_current_L, y[2]);    // Записать в память данные 
    y[1]= i2c_eeprom_read_byte( deviceaddress, 1+N_device+6);
    i2c_eeprom_write_byte(deviceaddress, 1+adr_xbee_current_L, y[1]);    // Записать в память данные 
    y[0]= i2c_eeprom_read_byte( deviceaddress, 0+N_device+6);
    i2c_eeprom_write_byte(deviceaddress, adr_xbee_current_L, y[0]);    // Записать в память данные 
    XBee_Addr64_LS = (unsigned long&) y;  // Сложить восстановленные текущие данные в 
    Serial.println(XBee_Addr64_MS, HEX); 
    Serial.println(XBee_Addr64_LS, HEX); 
    addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);                                     // SH + SL Address of receiving XBee
}

void draw_view_adr_device()
{
  int XBee_x, XBee_y, x, y;
  int yXBee = 32;                                                  // Стартовая точка смещения строк текста
  int yDelta = 16;                                                 // Дельта смещения вниз
  int n_page = 1;
  myGLCD.clrScr();                                                 // Очистить экран CENTER
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (2, 2, 239, 25);                            // Нарисовать прямоугольник для текста  
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 2, 239, 25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[28])));     // Информация XBee
  myGLCD.print(buffer, CENTER, 5);

  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста 
  myGLCD.fillRoundRect (2, 233, 82, 273);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 233, 82, 273);
  
  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (87, 233, 153, 273);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (87, 233, 153, 273);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("   ", CENTER, 245);                                 //  Очистить
  myGLCD.printNumI(n_page, CENTER, 245);                            // Завершить просмотр
  myGLCD.setBackColor(0, 0, 0);

  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (158, 233, 238, 273);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (158, 233, 238, 273);


  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (2, 278, 118, 318);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 278, 118, 318);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.setColor(255, 255, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[19])));
  myGLCD.print(buffer, 20, 290);                                    // Завершить просмотр

  myGLCD.setColor(0, 0, 255);                                       // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (121, 278, 238, 318);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (121, 278, 238, 318);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.setColor(255, 255, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[62])));
  myGLCD.print(buffer, 139, 290);                                    // Ввести данные


}
void draw_view_adr_device1()
{
  int XBee_x, XBee_y, x, y;
  int yXBee = 32;                                                  // Стартовая точка смещения строк текста
  int yDelta = 16;                                                 // Дельта смещения вниз
  int n_page = 1;
  myGLCD.clrScr();                                                 // Очистить экран CENTER
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (2, 2, 239, 25);                            // Нарисовать прямоугольник для текста  
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 2, 239, 25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[28])));     // Информация XBee
  myGLCD.print(buffer, CENTER, 5);

  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста 
  myGLCD.fillRoundRect (2, 233, 82, 273);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 233, 82, 273);
  
  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (87, 233, 153, 273);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (87, 233, 153, 273);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("   ", CENTER, 245);                                 //  Очистить
  myGLCD.printNumI(n_page, CENTER, 245);                            // Завершить просмотр
  myGLCD.setBackColor(0, 0, 0);

  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (158, 233, 238, 273);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (158, 233, 238, 273);

  myGLCD.setColor(0, 0, 255);                                       // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (2, 278, 238, 318);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 278, 238, 318);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.setColor(255, 255, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[19])));
  myGLCD.print(buffer, CENTER, 290);                                    // Выход 
}
void view_adr_device()
{
  int x, y;
  int n_page = 1;
  int adr_device = 0;
  draw_view_adr_device1();
  while (myTouch.dataAvailable()) {}
  view_page(n_page);

  while (true)
  {
    if (myTouch.dataAvailable())
    {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();

       if ((y>=32) && (y<=64))                                  // Строка 1
        {
          waitForIt_inv();                                  // Убрать рамку выбора устройства
          waitForIt(1, 32, 239, 64);
          number_device = ((n_page-1) * 6)+1;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 //  Очистить
          myGLCD.printNumI(number_device, CENTER, 245);     // 
          myGLCD.setBackColor(0, 0, 0);
          adr_device = adr_start_baseHL + ((number_device-1) * 10);
          XBee_SetH(adr_device);
          XBee_SetL(adr_device);
          draw_view_adr_device1();
          //view_page(n_page);
        }
       if ((y>=64) && (y<=96))                                  // Строка 2
        {
          waitForIt_inv();                                  // Убрать рамку выбора устройства
          waitForIt(1, 64, 239, 96);
          number_device = ((n_page-1) * 6)+2;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 //  Очистить
          myGLCD.printNumI(number_device, CENTER, 245);     // 
          myGLCD.setBackColor(0, 0, 0);
          adr_device = adr_start_baseHL + ((number_device-1) * 10);
          XBee_SetH(adr_device);
          XBee_SetL(adr_device);
          draw_view_adr_device1();
          //view_page(n_page);
        }
      if ((y>=96) && (y<=128))                                  // Строка 3
        {
          waitForIt_inv();                                  // Убрать рамку выбора устройства
          waitForIt(1, 96, 239, 128);
          number_device = ((n_page-1) * 6)+3;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 //  Очистить
          myGLCD.printNumI(number_device, CENTER, 245);     // 
          myGLCD.setBackColor(0, 0, 0);
          adr_device = adr_start_baseHL + ((number_device-1) * 10);
          XBee_SetH(adr_device);
          XBee_SetL(adr_device);
          draw_view_adr_device1();
          //view_page(n_page);
        }
      if ((y>=128) && (y<=160))                                  // Строка 4
        {
          if(n_page-1 < 42)
          {
            waitForIt_inv();                                  // Убрать рамку выбора устройства
            number_device = ((n_page-1) * 6)+4;
            waitForIt(1, 128, 239, 160);
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.print("   ", CENTER, 245);                 //  Очистить
            myGLCD.printNumI(number_device, CENTER, 245);     // 
            myGLCD.setBackColor(0, 0, 0);
            adr_device = adr_start_baseHL + ((number_device-1) * 10);
            XBee_SetH(adr_device);
            XBee_SetL(adr_device);
            draw_view_adr_device1();
            //view_page(n_page);
          }
        }
      if ((y>=160) && (y<=192))                                  // Строка 5
        {
          if(n_page-1 < 42)
          {
            waitForIt_inv();                                  // Убрать рамку выбора устройства
            number_device = ((n_page-1) * 6)+5;
            waitForIt(1, 160, 239, 192);
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.print("   ", CENTER, 245);                 //  Очистить
            myGLCD.printNumI(number_device, CENTER, 245);     // 
            myGLCD.setBackColor(0, 0, 0);
            adr_device = adr_start_baseHL + ((number_device-1) * 10);
            XBee_SetH(adr_device);
            XBee_SetL(adr_device);
            draw_view_adr_device1();
            //view_page(n_page);
          }
        }
      if ((y>=192) && (y<=224))                                  // Строка 6
        {
          if(n_page-1 < 42)
          {
            waitForIt_inv();                                  // Убрать рамку выбора устройства
            number_device = ((n_page-1) * 6)+6;
            waitForIt(1, 192, 239, 224);
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.print("   ", CENTER, 245);                 //  Очистить
            myGLCD.printNumI(number_device, CENTER, 245);     // 
            myGLCD.setBackColor(0, 0, 0);
            adr_device = adr_start_baseHL + ((number_device-1) * 10);
            XBee_SetH(adr_device);
            XBee_SetL(adr_device);
            draw_view_adr_device1();
            //view_page(n_page);
          }
        }

    if ((y>=233) && (y<=273))                                     // Кнопки перелистывания списков
      {
        if ((x>=2) && (x<=82))                                  //  Предыдущий лист
        {
          waitForIt(2, 233, 82, 273);
          n_page--;
          if(n_page <1) n_page = 1;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 // Очистить
          myGLCD.printNumI(n_page, CENTER, 245);            // Завершить просмотр
          myGLCD.setBackColor(0, 0, 0);
          view_page(n_page);
        }
        if ((x>=87) && (x<=153))                                // Перейти на первый лист
        {
          waitForIt(87, 233, 153, 273);
          n_page = 1;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 // Очистить
          myGLCD.printNumI(n_page, CENTER, 245);            // Завершить просмотр
          myGLCD.setBackColor(0, 0, 0);
          view_page(n_page);
        }
        if ((x>=158) && (x<=238))                               // Следующий лист
        {
          waitForIt(158, 233, 238, 273);
          n_page++;
          if(n_page > 15) n_page = 15;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 // Очистить
          myGLCD.printNumI(n_page, CENTER, 245);            // Завершить просмотр
          myGLCD.setBackColor(0, 0, 0);
          view_page(n_page);
        }
      }
    if ((y>=278) && (y<=318))                                    //  
      {
      if ((x>=2) && (x<=238))                                  // Выход
        {
          waitForIt(2, 278, 238, 318);
          return;
        }
      }
    }
  }     
}
void view_page(int block_n)
{
  int XBee_x, XBee_y, x, y;
  int yXBee = 32;                                                  // Стартовая точка смещения строк текста
  int yDelta = 16;                                                 // Дельта смещения вниз
  int n_bl_max = 6;
  if(block_n == 43) n_bl_max = 4;
  int adr_device = adr_start_baseHL + ((block_n-1) * 10*6) ;
  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRoundRect (1, 26, 240, 232);                            // Нарисовать прямоугольник для текста
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setColor(0, 255, 255);

  for (int n_bl = 0; n_bl<n_bl_max; n_bl++)
  {
    //Serial.println(adr_device);
    read_adr_device(adr_device);
    myGLCD.printNumI(((block_n-1) * 6)+n_bl+1, 2, yXBee+8);  
    myGLCD.print("HS", 60, yXBee);
    myGLCD.print(String(XBee_Addr64_MS_tmp,HEX), RIGHT, yXBee);          //
    yXBee = yXBee + yDelta;                                          // Форматирование текста, смещение  вниз
    myGLCD.print("LS", 60, yXBee);
    myGLCD.print(String(XBee_Addr64_LS_tmp,HEX), RIGHT, yXBee);
    yXBee = yXBee + yDelta; 
    adr_device+=10;
  }
}

void draw_view_adr_user()                                            // Отображает начальный лист пользователей
{
  int XBee_x, XBee_y, x, y;
  int yXBee = 32;                                                  // Стартовая точка смещения строк текста
  int yDelta = 16;                                                 // Дельта смещения вниз
  int n_page = 1;
  myGLCD.clrScr();                                                 // Очистить экран CENTER
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (2, 2, 239, 25);                            // Нарисовать прямоугольник для текста
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 2, 239, 25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[39])));     // Пользователь
  myGLCD.print(buffer, CENTER, 5);

  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (2, 233, 82, 273);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 233, 82, 273);
  
  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (87, 233, 153, 273);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (87, 233, 153, 273);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("   ", CENTER, 245);                                 //  Очистить
  myGLCD.printNumI(n_page, CENTER, 245);                            // Завершить просмотр
  myGLCD.setBackColor(0, 0, 0);

  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (158, 233, 238, 273);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (158, 233, 238, 273);

  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
  myGLCD.fillRoundRect (2, 278, 238, 318);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (2, 278, 238, 318);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.setColor(255, 255, 255);
  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[46])));
  myGLCD.print(buffer, CENTER, 290);                                // Завершить просмотр
}
void view_adr_user()                                                  // Выбор строки с номером пользователя
{
  int x, y;
  int n_page = 1;
  draw_view_adr_user();
  while (myTouch.dataAvailable()) {}
  view_page_user(n_page);

  while (true)
  {
    if (myTouch.dataAvailable())
    {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();

       if ((y>=32+deltaY) && (y<=64+deltaY))                                  // Строка 1
        {
          waitForIt_inv();                                               // Убрать рамку выбора пользователя
          waitForIt(1, 32, 239, 64);
          number_user = ((n_page-1) * 6)+1;                              // Порядковый номер пользователя в списке
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                               //  Очистить
          myGLCD.printNumI(number_user, CENTER, 245);                     // 
          myGLCD.setBackColor(0, 0, 0);
          adr_user = adr_start_user + ((number_user-1) * 10);
          EEPROM.get(adr_user, user_number);                              // Восстановить номер пользователя
          EEPROM.get(adr_user+4, user_pass);                              // Восстановить пароль пользователя
        }
       if ((y>=64+deltaY) && (y<=96+deltaY))                                  // Строка 2
        {
          waitForIt_inv();                                               // Убрать рамку выбора пользователя
          waitForIt(1, 64, 239, 96);
          number_user = ((n_page-1) * 6)+2;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                               //  Очистить
          myGLCD.printNumI(number_user, CENTER, 245);                     // 
          myGLCD.setBackColor(0, 0, 0);
          adr_user = adr_start_user + ((number_user-1) * 10);
          EEPROM.get(adr_user, user_number);                              // Восстановить номер пользователя
          EEPROM.get(adr_user+4, user_pass);                              // Восстановить пароль пользователя
        }
      if ((y>=96+deltaY) && (y<=128+deltaY))                                  // Строка 3
        {
          waitForIt_inv();                                               // Убрать рамку выбора пользователя
          waitForIt(1, 96, 239, 128);
          number_user = ((n_page-1) * 6)+3;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                               //  Очистить
          myGLCD.printNumI(number_user, CENTER, 245);                     // 
          myGLCD.setBackColor(0, 0, 0);
          adr_user = adr_start_user + ((number_user-1) * 10);
          EEPROM.get(adr_user, user_number);                              // Восстановить номер пользователя
          EEPROM.get(adr_user+4, user_pass);                              // Восстановить пароль пользователя
        }
      if ((y>=128+deltaY) && (y<=160+deltaY))                                 // Строка 4
        {
          if(n_page-1 < 42)
          {
            number_user = ((n_page-1) * 6)+4;
            waitForIt_inv();                                               // Убрать рамку выбора пользователя
            waitForIt(1, 128, 239, 160);
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.print("   ", CENTER, 245);                           //  Очистить
            myGLCD.printNumI(number_user, CENTER, 245);                 // 
            myGLCD.setBackColor(0, 0, 0);
            adr_user = adr_start_user + ((number_user-1) * 10);
            EEPROM.get(adr_user, user_number);                          // Восстановить номер пользователя
            EEPROM.get(adr_user+4, user_pass);                          // Восстановить пароль пользователя
          }
        }
      if ((y>=160+deltaY) && (y<=192+deltaY))                                 // Строка 5
        {
          if(n_page-1 < 42)
          {
            number_user = ((n_page-1) * 6)+5;
            waitForIt_inv();                                               // Убрать рамку выбора пользователя
            waitForIt(1, 160, 239, 192);
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.print("   ", CENTER, 245);                           //  Очистить
            myGLCD.printNumI(number_user, CENTER, 245);                 // 
            myGLCD.setBackColor(0, 0, 0);
            adr_user = adr_start_user + ((number_user-1) * 10);
            EEPROM.get(adr_user, user_number);                          // Восстановить номер пользователя
            EEPROM.get(adr_user+4, user_pass);                          // Восстановить пароль пользователя
          }
        }
      if ((y>=192+deltaY) && (y<=224+deltaY))                                 // Строка 6
        {
          if(n_page-1 < 42)
          {
            number_user = ((n_page-1) * 6)+6;
            waitForIt_inv();                                               // Убрать рамку выбора пользователя
            waitForIt(1, 192, 239, 224);
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.print("   ", CENTER, 245);                           //  Очистить
            myGLCD.printNumI(number_user, CENTER, 245);                 // 
            myGLCD.setBackColor(0, 0, 0);
            adr_user = adr_start_user + ((number_user-1) * 10);
            EEPROM.get(adr_user, user_number);                          // Восстановить номер пользователя
            EEPROM.get(adr_user+4, user_pass);                          // Восстановить пароль пользователя
          }
        }

    if ((y>=233+deltaY) && (y<=273+deltaY))                                     // Кнопки перелистывания списков
      {
        if ((x>=2) && (x<=82))                                  //  Предыдущий лист
        {
          waitForIt(2, 233, 82, 273);
          n_page--;
          if(n_page <1) n_page = 1;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 // Очистить
          myGLCD.printNumI(n_page, CENTER, 245);            // Завершить просмотр
          myGLCD.setBackColor(0, 0, 0);
          view_page_user(n_page);
        }
        if ((x>=87) && (x<=153))                                // Перейти на первый лист
        {
          waitForIt(87, 233, 153, 273);
          n_page = 1;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 // Очистить
          myGLCD.printNumI(n_page, CENTER, 245);            // Завершить просмотр
          myGLCD.setBackColor(0, 0, 0);
          view_page_user(n_page);
        }
        if ((x>=158) && (x<=238))                               // Следующий лист
        {
          waitForIt(158, 233, 238, 273);
          n_page++;
          if(n_page > 10) n_page = 10;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 // Очистить
          myGLCD.printNumI(n_page, CENTER, 245);            // Завершить просмотр
          myGLCD.setBackColor(0, 0, 0);
          view_page_user(n_page);
        }
      }
    if ((y>=278+deltaY) && (y<=318))                               //  
      {
      if ((x>=2) && (x<=238))                                    // Выход
        {
          waitForIt(2, 278, 238, 318);
          return;
        }
      }
    }
  }     
}
void view_page_user(int block_n)                                        // Отображает одну страницу пользователя и пароля
{
  int User_x, User_y, x, y;
  int yUser         = 32;                                            // Стартовая точка смещения строк текста
  int yDelta        = 16;                                            // Дельта смещения вниз
  int n_bl_max      = 6;                                             // Максимальное количество строк на экране
  long user_numbert = 0;                                             // номер пользователя
    long user_passt   = 0;                                             // пароль пользователя
  int adr_user = adr_start_user + ((block_n-1) * 10*6) ;             // Вычисление адреса пользователя

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRoundRect (1, 26, 240, 232);                            // Нарисовать прямоугольник для текста
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setColor(0, 255, 255);

  for (int n_bl = 0; n_bl<n_bl_max; n_bl++)
  {
    //EEPROM.get(adr_user, user_numbert );                           // Восстановить номер пользователя
    //EEPROM.get(adr_user+4, user_passt );                           // Восстановить пароль пользователя
    myGLCD.printNumI(((block_n-1) * 6)+n_bl+1, 2, yUser+8);  
    myGLCD.print("User", 35, yUser);
    if(user_numbert == -1)                                         // Если нет номера - заштриховать.
    {
      myGLCD.print("--------", RIGHT, yUser);                    //
    }
    else
    {
      myGLCD.printNumI(user_numbert, RIGHT, yUser);              //
    }

    yUser = yUser + yDelta;                                        // Форматирование текста, смещение  вниз
    myGLCD.print("Pass", 35, yUser);
    myGLCD.print("********", RIGHT, yUser);
    //myGLCD.printNumI(user_passt, RIGHT, yUser);
    yUser = yUser + yDelta; 
    adr_user+=10;
  }
}

void set_number_user(int adr_user)  // Проработать позже 
{
  lenStr = 8;
  int _adr_user = adr_user;
  klavXBee();
  if (ret == 1)
    {
      ret = 0;
      return;
    }
  strcpy(temp_stLast,stLast);
  long int li1 = strtol(temp_stLast, NULL, 16);                                 // преобразовать первую часть строки в значение HEX 
  byte *m = (byte *)&li1;                                                       //Разложить данные старшего адреса координатора побайтно для записи в память
  for (int i=0; i<4; i++)
    {
    //  i2c_eeprom_write_byte(deviceaddress, i+_adr_xbee_h+2, m[i]);          // Записать в память данные старшего адреса координатора
    }
}

void restore_default_device()
{
byte y[4];   ; //Чтение из памяти текущих данных старшего адреса координатора
  y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_xbee_current_H);
  y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_xbee_current_H);
  y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_xbee_current_H);
  y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_xbee_current_H);
  XBee_Addr64_MS = (unsigned long&) y;  // Сложить восстановленные текущие данные

  //Чтение из памяти текущих данных младшего адреса координатора
  y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_xbee_current_L);
  y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_xbee_current_L);
  y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_xbee_current_L);
  y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_xbee_current_L);
  XBee_Addr64_LS = (unsigned long&) y;  // Сложить восстановленные текущие данные в 
  addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);                                     // SH + SL Address of receiving XBee
} 
void read_adr_device(int N_device)
{
//Программа ввостановления данных XBee из памяти.
byte y[4];   ; //Чтение из памяти текущих данных старшего адреса координатора
  y[3]= i2c_eeprom_read_byte( deviceaddress, 3+N_device+2);
  y[2]= i2c_eeprom_read_byte( deviceaddress, 2+N_device+2);
  y[1]= i2c_eeprom_read_byte( deviceaddress, 1+N_device+2);
  y[0]= i2c_eeprom_read_byte( deviceaddress, 0+N_device+2);
  XBee_Addr64_MS_tmp = (unsigned long&) y;  // Сложить восстановленные текущие данные

  //Чтение из памяти текущих данных младшего адреса координатора
  y[3]= i2c_eeprom_read_byte( deviceaddress, 3+N_device+6);
  y[2]= i2c_eeprom_read_byte( deviceaddress, 2+N_device+6);
  y[1]= i2c_eeprom_read_byte( deviceaddress, 1+N_device+6);
  y[0]= i2c_eeprom_read_byte( deviceaddress, 0+N_device+6);
  XBee_Addr64_LS_tmp = (unsigned long&) y;  // Сложить восстановленные текущие данные в 

} 
void set_adr_device()
{
  int x, y;
  int n_page = 1;
  int adr_device = 0;
  draw_view_adr_device();
  while (myTouch.dataAvailable()) {}
  view_page(n_page);

  while (true)
  {
    if (myTouch.dataAvailable())
    {
        myTouch.read();
        x=myTouch.getX();
        y=myTouch.getY();

       if ((y>=32) && (y<=64))                                  // Строка 1
        {
          waitForIt_inv();                                  // Убрать рамку выбора устройства
          waitForIt(1, 32, 239, 64);
          number_device = ((n_page-1) * 6)+1;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 //  Очистить
          myGLCD.printNumI(number_device, CENTER, 245);     // 
          myGLCD.setBackColor(0, 0, 0);
          adr_device = adr_start_baseHL + ((number_device-1) * 10);
        }
       if ((y>=64) && (y<=96))                                  // Строка 2
        {
          waitForIt_inv();                                  // Убрать рамку выбора устройства
          waitForIt(1, 64, 239, 96);
          number_device = ((n_page-1) * 6)+2;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 //  Очистить
          myGLCD.printNumI(number_device, CENTER, 245);     // 
          myGLCD.setBackColor(0, 0, 0);
          adr_device = adr_start_baseHL + ((number_device-1) * 10);
        }
      if ((y>=96) && (y<=128))                                  // Строка 3
        {
          waitForIt_inv();                                  // Убрать рамку выбора устройства
          waitForIt(1, 96, 239, 128);
          number_device = ((n_page-1) * 6)+3;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 //  Очистить
          myGLCD.printNumI(number_device, CENTER, 245);     // 
          myGLCD.setBackColor(0, 0, 0);
          adr_device = adr_start_baseHL + ((number_device-1) * 10);
        }
      if ((y>=128) && (y<=160))                                  // Строка 4
        {
          if(n_page-1 < 42)
          {
            waitForIt_inv();                                  // Убрать рамку выбора устройства
            number_device = ((n_page-1) * 6)+4;
            waitForIt(1, 128, 239, 160);
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.print("   ", CENTER, 245);                 //  Очистить
            myGLCD.printNumI(number_device, CENTER, 245);     // 
            myGLCD.setBackColor(0, 0, 0);
            adr_device = adr_start_baseHL + ((number_device-1) * 10);
          }
        }
      if ((y>=160) && (y<=192))                                  // Строка 5
        {
          if(n_page-1 < 42)
          {
            waitForIt_inv();                                  // Убрать рамку выбора устройства
            number_device = ((n_page-1) * 6)+5;
            waitForIt(1, 160, 239, 192);
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.print("   ", CENTER, 245);                 //  Очистить
            myGLCD.printNumI(number_device, CENTER, 245);     // 
            myGLCD.setBackColor(0, 0, 0);
            adr_device = adr_start_baseHL + ((number_device-1) * 10);
          }
        }
      if ((y>=192) && (y<=224))                                  // Строка 6
        {
          if(n_page-1 < 42)
          {
            waitForIt_inv();                                  // Убрать рамку выбора устройства
            number_device = ((n_page-1) * 6)+6;
            waitForIt(1, 192, 239, 224);
            myGLCD.setBackColor(0, 0, 255);
            myGLCD.print("   ", CENTER, 245);                 //  Очистить
            myGLCD.printNumI(number_device, CENTER, 245);     // 
            myGLCD.setBackColor(0, 0, 0);
            adr_device = adr_start_baseHL + ((number_device-1) * 10);
          }
        }

    if ((y>=233) && (y<=273))                                     // Листать влево
      {
        if ((x>=2) && (x<=82))                                  // 
        {
          waitForIt(2, 233, 82, 273);
          n_page--;
          if(n_page <1) n_page = 1;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 // Очистить
          myGLCD.printNumI(n_page, CENTER, 245);            // просмотр страницы
          myGLCD.setBackColor(0, 0, 0);
          view_page(n_page);
        }
        if ((x>=87) && (x<=153))                                  // Перейти в начало
        {
          waitForIt(87, 233, 153, 273);
          n_page = 1;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 //  Очистить
          myGLCD.printNumI(n_page, CENTER, 245);            //  просмотр страницы
          myGLCD.setBackColor(0, 0, 0);
          view_page(n_page);
        }
        if ((x>=158) && (x<=238))                               // Листать вправо
        {
          waitForIt(158, 233, 238, 273);
          n_page++;
          if(n_page > 43) n_page = 43;
          myGLCD.setBackColor(0, 0, 255);
          myGLCD.print("   ", CENTER, 245);                 //  Очистить
          myGLCD.printNumI(n_page, CENTER, 245);            //  просмотр страницы
          myGLCD.setBackColor(0, 0, 0);
          view_page(n_page);
        }
      }
    if ((y>=278) && (y<=318))                                    // 
      {
      if ((x>=2) && (x<=118))                                  // Выход
        {
          waitForIt(2, 278, 118, 318);
          return;
        }
      else if ((x>=121) && (x<=238))                                  // Установить
        {
          waitForIt(121, 278, 238, 318);
          i2c_eeprom_write_byte(deviceaddress, adr_number_device, number_device);   // Записать в память данные порядкового номера устройства (по списку)
          read_HL_mem_XBee(adr_device);
          return;
        }
      }
    }
  }     
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
     if (int x = i2c_eeprom_read_byte(deviceaddress,0) != 55)
      { // write a 0 to all 4096 bytes of the EEPROM
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("Format!",CENTER, 80);// "Format!"
      //delay (500);
      //myGLCD.clrScr();
      for (int i = 0; i < 4095; i++)
        {
          i2c_eeprom_write_byte(deviceaddress,i, 0);
        }
      i2c_eeprom_write_byte(deviceaddress,0, 55); 
      myGLCD.clrScr();
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("Format OK!",CENTER, 80);// "Format Ok!"
      delay (500);
      myGLCD.clrScr();
      }

       if (int x = EEPROM.read(0) != 55)
      { 
      myGLCD.setColor(255, 255, 255);
      int k = -1;
      myGLCD.print("Format EEPROM!",CENTER, 80);// "Format!"
      //delay (500);
      //myGLCD.clrScr();
      for (int i = 2000; i < 4095; i++)
        {
          EEPROM.put(i, k);  
          //EEPROM.write(i,0);
        }
      EEPROM.write(0,55); 
      myGLCD.clrScr();
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("EEPROM OK!",CENTER, 80);// "Format Ok!"
      delay (500);
      myGLCD.clrScr();
      }


}

void read_memory1()
{
  int a = 1000;
  int xp = 0;

  for (int i = 0; i < 256; i++)
    {
      Serial.print(a);
      Serial.print("  ");
      xp = i2c_eeprom_read_byte(deviceaddress,a);
      Serial.println(xp);
      a += 10;
    }

}

void FileOpen()
{
  Serial.println("FileOpen");
  int temp_file_name = 0;
  preob_num_str();
  while (sd.exists(fileName)) 
  {
  if (fileName[BASE_NAME_SIZE + 1] != '9') 
  {
    fileName[BASE_NAME_SIZE + 1]++;
  }
  else if (fileName[BASE_NAME_SIZE] != '9') 
  {
    fileName[BASE_NAME_SIZE + 1] = '0';
    fileName[BASE_NAME_SIZE]++;
  }
  else 
  {
    //regBank.set(122,1);                              // Флаг ошибки  открытия файла
  }
  }

 
  temp_file_name = ((fileName[BASE_NAME_SIZE]-48)*10) + (fileName[BASE_NAME_SIZE + 1]-48); // преобразование символьного номера файла в числа
 // regBank.set(adr_reg_file_name,temp_file_name);      
//  i2c_eeprom_write_byte(0x50, adr_file_name_count,temp_file_name);                 // при смене даты счетчик номера файла сбросить в "0"

  if (!myFile.open(fileName, O_CREAT | O_WRITE | O_EXCL)) //sdError("file.open");
  {
  //regBank.set(122,1);                              // Флаг ошибки  открытия файла
  }
  else
  {
  Serial.print(fileName);
  Serial.println(F("  Open Ok!"));

  DateTime now = RTC.now();

  //regBank.set(adr_Mic_Start_day , now.day());           // Время старта теста
  //regBank.set(adr_Mic_Start_month, now.month());
  //regBank.set(adr_Mic_Start_year, now.year());
  //regBank.set(adr_Mic_Start_hour, now.hour());
  //regBank.set(adr_Mic_Start_minute, now.minute());
  //regBank.set(adr_Mic_Start_second, now.second());
  //// Уточнить       
  //regBank.set(adr_Time_Test_day, 0); 
  //regBank.set(adr_Time_Test_hour, 0); 
  //regBank.set(adr_Time_Test_minute, 0); 
  //regBank.set(adr_Time_Test_second, 0); 
  myFile.println ("");
  myFile.print ("Report of test module Audio-1 N ");
  // Получить данные int из регистров
  //int val_3 = regBank.get(40010);
  //int val_2 = regBank.get(40011);
  //int val_1 = regBank.get(40012);
  //int val_0 = regBank.get(40013);
   
  // подготовить для преобразования побитного чтения
   //byte *x3 = (byte *)&val_3;  
   //byte *x2 = (byte *)&val_2;
   //byte *x1 = (byte *)&val_1;
   //byte *x0 = (byte *)&val_0;

   // Записать число в виде младшего byte  в массив
  //byte y[4];  
  //  y[3]= x3[0];
  //  y[2]= x2[0];
  //  y[1]= x1[0];
  //  y[0]= x0[0];

 // unsigned long *yx = (unsigned long *)&y;

 // number_audio = *yx;

 // Serial.println(number_audio);

  myFile.println ("");
  myFile.println ("");
  myFile.println ("");
  myFile.print ("Start test   ");
  file_print_date();
  myFile.println ("");
  myFile.println ("");
                                 
//  Serial.println(fileName);
   }
}
void FileClose()
{
  //Serial.println(fileName);
  myFile.println ("");
  myFile.print ("Stop test   ");
  file_print_date();
  myFile.println ("");
  myFile.close();

  if (sd.exists(fileName))
    { 
      Serial.println();
      Serial.print(fileName);
      Serial.println("  Close  OK!.");
    }
  else 
    {
      Serial.println();
      Serial.print(fileName);
      Serial.println(" doesn't exist.");  
    }
}
void list_file()
{
 while (file.openNext(sd.vwd(), O_READ))
  {
  file.printName(&Serial);
  Serial.write(' ');
  file.printModifyDateTime(&Serial);
  Serial.write(' ');
  file.printFileSize(&Serial);
  if (file.isDir()) {
    // Indicate a directory.
    Serial.write('/');
  }
  Serial.println();
  file.close();
  }
}
void load_list_files()
{

  if (!sd.begin(chipSelect)) 
    {
      Serial.println("initialization SD failed!");
    }
  else
    {
  
    while (file.openNext(sd.vwd(), O_READ))
      {
      file.printName(&Serial2);
      Serial2.println();
      file.printName(&Serial);
      Serial.println();

      file.close();
      } 
       Serial2.flush();
     }
    delay(100);
  //  Serial2.println("Files end");
  //  Serial.println("Files end");
// regBank.set(adr_control_command,0);
}
void file_name()
{

   preob_num_str();

  while (sd.exists(fileName)) 
  {
  if (fileName[BASE_NAME_SIZE + 1] != '9') 
  {
    fileName[BASE_NAME_SIZE + 1]++;
  }
  else if (fileName[BASE_NAME_SIZE] != '9') 
  {
    fileName[BASE_NAME_SIZE + 1] = '0';
    fileName[BASE_NAME_SIZE]++;
  }
  else 
  {
    Serial.println("Can't create file name");
//    sdError("Can't create file name");
  }
  }
  if (!myFile.open(fileName, O_CREAT | O_WRITE | O_EXCL)) //sdError("file.open");
  {
  }
  Serial.print(F("Logging to: "));
  Serial.println(fileName);
  myFile.close();
  Serial.println("done.");
 } 
void file_print_date()  //программа  записи даты в файл
  {
    DateTime now = RTC.now();
    myFile.print(now.day(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.year(), DEC);//Serial display time
    myFile.print(' ');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
  }
void file_del_SD()
{
  if (!sd.begin(chipSelect)) 
    {
      //Serial.println("initialization SD failed!");
      //regBank.set(125,false); 
    }
  else
    {
        myFile = sd.open(fileName_F);
        //myFile = sd.open("example.txt", FILE_WRITE);
        //myFile.close();

        // Check to see if the file exists:
        if (sd.exists(fileName_F)) 
        {
         // regBank.set(125,true); 
          sd.remove(fileName_F);
         // Serial.println("example.txt exists.");
        }
        else 
        {
         // Serial.println("example.txt doesn't exist.");
        //regBank.set(125,false); 
        }
      }
  delay(100);
}
void set_SD()
{
    if (!sd.begin(chipSelect)) 
    {
      //Serial.println("initialization SD failed!");
    }
  else
    {
        myFile = sd.open("example.txt", FILE_WRITE);
        myFile.close();

        // Check to see if the file exists:
        if (sd.exists("example.txt")) 
        {
          sd.remove("example.txt");
         // Serial.println("example.txt exists.");
        }
        else 
        {
         // Serial.println("example.txt doesn't exist.");
        }
      }

  delay(100);
}
void preob_num_str() // Программа формирования имени файла, состоящего из текущей даты и счетчика файлов
{
  DateTime now = RTC.now();
  day   = now.day();
  month = now.month();
  year  = now.year();
  int year_temp = year-2000;

  itoa (year_temp,str_year_file, 10);                                        // Преобразование даты год в строку ( 10 - десятичный формат) 

  if (month <10)
    {
       itoa (0,str_mon_file0, 10);                                         //  Преобразование даты месяц  в строку ( 10 - десятичный формат) 
       itoa (month,str_mon_file10, 10);                                    //  Преобразование числа в строку ( 10 - десятичный формат) 
       sprintf(str_mon_file, "%s%s", str_mon_file0, str_mon_file10);       // Сложение 2 строк
    }
  else
    {
       itoa (month,str_mon_file, 10);                                      // Преобразование числа в строку ( 10 - десятичный формат) 
    }
  if (day <10)
    {
       itoa (0,str_day_file0, 10);                                         // Преобразование числа в строку ( 10 - десятичный формат) 
       itoa (day,str_day_file10, 10);                                      // Преобразование числа в строку ( 10 - десятичный формат) 
       sprintf(str_day_file, "%s%s", str_day_file0, str_day_file10);       // Сложение 2 строк
    }
  else
    {
    itoa (day,str_day_file, 10);                                           // Преобразование числа в строку ( 10 - десятичный формат) 
    }
     
  sprintf(str1_1, "%s%s",str_year_file, str_mon_file);                         // Сложение 2 строк
  sprintf(str2_1, "%s%s",str1_1, str_day_file);                                // Сложение 2 строк
  sprintf(fileName, "%s%s", str2_1, "00.KAM");                                 // Получение имени файла в file_name
  //Serial.println(fileName);
  //regBank.set(adr_reg_temp_day, day);  
  //regBank.set(adr_reg_temp_mon, month); 
  //regBank.set(adr_reg_temp_year, year-2000); 
  //char* strcpy(char* fileName_p, const char* fileName);
  //Serial.println(fileName_p);
}
void vibroM()                     // Включение вибродвигателя
{
  digitalWrite(VibMot, HIGH); 
  delay(200);
  digitalWrite(VibMot, LOW); 
}

//---------- SD info--------------

// global for card size
uint32_t cardSize;

// global for card erase size
uint32_t eraseSize;
//------------------------------------------------------------------------------
// store error strings in flash
#define sdErrorMsg(msg) sdErrorMsg_F(F(msg));
void sdErrorMsg_F(const __FlashStringHelper* str) 
{
  cout << str << endl;
  if (sd.card()->errorCode()) 
  {
    cout << F("SD errorCode: ");
    cout << hex << int(sd.card()->errorCode()) << endl;
    cout << F("SD errorData: ");
    cout << int(sd.card()->errorData()) << dec << endl;
  }
}
//------------------------------------------------------------------------------
uint8_t cidDmp() 
{
  cid_t cid;
  if (!sd.card()->readCID(&cid)) {
    sdErrorMsg("readCID failed");
    return false;
  }
  cout << F("\nManufacturer ID: ");
  cout << hex << int(cid.mid) << dec << endl;
  cout << F("OEM ID: ") << cid.oid[0] << cid.oid[1] << endl;
  cout << F("Product: ");
  for (uint8_t i = 0; i < 5; i++) {
    cout << cid.pnm[i];
  }
  cout << F("\nVersion: ");
  cout << int(cid.prv_n) << '.' << int(cid.prv_m) << endl;
  cout << F("Serial number: ") << hex << cid.psn << dec << endl;
  cout << F("Manufacturing date: ");
  cout << int(cid.mdt_month) << '/';
  cout << (2000 + cid.mdt_year_low + 10 * cid.mdt_year_high) << endl;
  cout << endl;
  return true;
}
//------------------------------------------------------------------------------
uint8_t csdDmp() 
{
  csd_t csd;
  uint8_t eraseSingleBlock;
  if (!sd.card()->readCSD(&csd)) 
  {
  sdErrorMsg("readCSD failed");
  return false;
  }
  if (csd.v1.csd_ver == 0) 
  {
  eraseSingleBlock = csd.v1.erase_blk_en;
  eraseSize = (csd.v1.sector_size_high << 1) | csd.v1.sector_size_low;
  }
  else if (csd.v2.csd_ver == 1) 
  {
  eraseSingleBlock = csd.v2.erase_blk_en;
  eraseSize = (csd.v2.sector_size_high << 1) | csd.v2.sector_size_low;
  } else {
  cout << F("csd version error\n");
  return false;
  }
  eraseSize++;
  cout << F("cardSize: ") << 0.000512*cardSize;
   myGLCD.print("cardSize: ", LEFT, 45);
  myGLCD.printNumI(0.000512*cardSize, RIGHT, 5);
//  myGLCD.print("MB", RIGHT, 5);

  cout << F(" MB (MB = 1,000,000 bytes)\n");

  cout << F("flashEraseSize: ") << int(eraseSize) << F(" blocks\n");
  cout << F("eraseSingleBlock: ");
  if (eraseSingleBlock) {
  cout << F("true\n");
  } else {
  cout << F("false\n");
  }
  return true;
}
//------------------------------------------------------------------------------
// print partition table
uint8_t partDmp() 
{
  cache_t *p = sd.vol()->cacheClear();
  if (!p) {
    sdErrorMsg("cacheClear failed");
    return false;
  }
  if (!sd.card()->readBlock(0, p->data)) {
    sdErrorMsg("read MBR failed");
    return false;
  }
  for (uint8_t ip = 1; ip < 5; ip++) {
    part_t *pt = &p->mbr.part[ip - 1];
    if ((pt->boot & 0X7F) != 0 || pt->firstSector > cardSize) {
      cout << F("\nNo MBR. Assuming Super Floppy format.\n");
      return true;
    }
  }
  cout << F("\nSD Partition Table\n");
  cout << F("part,boot,type,start,length\n");
  for (uint8_t ip = 1; ip < 5; ip++) {
    part_t *pt = &p->mbr.part[ip - 1];
    cout << int(ip) << ',' << hex << int(pt->boot) << ',' << int(pt->type);
    cout << dec << ',' << pt->firstSector <<',' << pt->totalSectors << endl;
  }
  return true;
}
//------------------------------------------------------------------------------
void volDmp() 
{
  cout << F("\nVolume is FAT") << int(sd.vol()->fatType()) << endl;
  myGLCD.print("Volume is FAT", LEFT, 65);
  int volFAT = sd.vol()->fatType();
  myGLCD.printNumI(volFAT, RIGHT , 65);
  cout << F("blocksPerCluster: ") << int(sd.vol()->blocksPerCluster()) << endl;
  cout << F("clusterCount: ") << sd.vol()->clusterCount() << endl;
  cout << F("freeClusters: ");
  uint32_t volFree = sd.vol()->freeClusterCount();
  cout <<  volFree << endl;
  float fs = 0.000512*volFree*sd.vol()->blocksPerCluster();
  cout << F("freeSpace: ") << fs << F(" MB (MB = 1,000,000 bytes)\n");
  myGLCD.print("freeSpace: ", LEFT, 85);
  myGLCD.printNumI(fs, RIGHT , 85);
  //myGLCD.print("MB", RIGHT, 85);
  cout << F("fatStartBlock: ") << sd.vol()->fatStartBlock() << endl;
  cout << F("fatCount: ") << int(sd.vol()->fatCount()) << endl;
  cout << F("blocksPerFat: ") << sd.vol()->blocksPerFat() << endl;
  cout << F("rootDirStart: ") << sd.vol()->rootDirStart() << endl;
  cout << F("dataStartBlock: ") << sd.vol()->dataStartBlock() << endl;
  if (sd.vol()->dataStartBlock() % eraseSize) 
  {
    cout << F("Data area is not aligned on flash erase boundaries!\n");
    cout << F("Download and use formatter from www.sdsd.card()->org/consumer!\n");
  }
}

void SD_info()
{
  myGLCD.clrScr();
  myGLCD.setBackColor(0, 0, 0);
  uint32_t t = micros();
  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance.
 if (!sd.begin(chipSelect, SPI_HALF_SPEED))
  {
  sdErrorMsg("\ncardBegin failed");
  myGLCD.print("cardBegin failed", LEFT, 100);
  }
  t = micros() - t;
  cardSize = sd.card()->cardSize();

  if (cardSize == 0) 
  {
  sdErrorMsg("cardSize failed");
  myGLCD.print("Size failed", LEFT, 120);
  }
  cout << F("\ninit time:") << t << " us" << endl;
  myGLCD.print("Init time: ", LEFT, 25);
  myGLCD.printNumI(t, RIGHT, 25);
  // myGLCD.print("us", RIGHT, 0+5);
  cout << F("\nCard type: ");
  myGLCD.print("Card type:", LEFT, 45);
  switch (sd.card()->type()) 
  {
  case SD_CARD_TYPE_SD1:
  cout << F("SD1\n");
   myGLCD.print("SD1", RIGHT , 45);
  break;

  case SD_CARD_TYPE_SD2:
  cout << F("SD2\n");
   myGLCD.print("SD2", RIGHT , 45);
  break;

  case SD_CARD_TYPE_SDHC:
  if (cardSize < 70000000) 
  {
    cout << F("SDHC\n");
     myGLCD.print("SDHC", RIGHT , 45);
  } else {
    cout << F("SDXC\n");
     myGLCD.print("SDXC", RIGHT , 45);
  }
  break;

  default:
  cout << F("Unknown\n");
   myGLCD.print("Unknown", RIGHT , 45);
  }
  if (!cidDmp()) 
  {
  return;
  }
  if (!csdDmp()) 
  {
  return;
  }
  uint32_t ocr;
  if (!sd.card()->readOCR(&ocr)) 
  {
  sdErrorMsg("\nreadOCR failed");
  myGLCD.print("OCR failed", LEFT, 145);
  //return;
  }
  cout << F("OCR: ") << hex << ocr << dec << endl;
  if (!partDmp()) 
  {
  return;
  }
  if (!sd.fsBegin()) 
  {
  sdErrorMsg("\nFile System initialization failed.\n");
  myGLCD.print("File System failed", LEFT, 165);
  //return;
  }
  volDmp();

  myGLCD.setColor(VGA_LIME);
//  myGLCD.print(txt_info11,CENTER, 200);
  myGLCD.setColor(255, 255, 255);
  while (!myTouch.dataAvailable()){}
  while (myTouch.dataAvailable()){}
}

//-----------------------------------

void setup_pin()
{
  pinMode(led_13, OUTPUT);                             //
  digitalWrite(led_13, HIGH);                          //
  pinMode(VibMot, OUTPUT);                             //
  digitalWrite(VibMot, LOW); 
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
  myGLCD.InitLCD(0);
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  myGLCD.print("\x85""A""\x81""P""\x8A\x85""KA", CENTER, 140);       // ЗАГРУЗКА
  //strcpy_P(buffer, (char*)pgm_read_word(&(table_message[52]))); 
  myGLCD.print("C""\x86""CTEM""\x91", CENTER, 170);                  // СИСТЕМЫ
  Serial.begin(9600);                                                // Подключение к USB ПК
//  Serial1.begin(115200);                                             // Подключение к
  Serial2.begin(9600);                                               // Подключение к
  xbee.setSerial(Serial2);
  //Serial3.begin(115200);                                 // Подключение к
  Serial.println(" ");
  Serial.println(" ***** Start system  *****");
  Serial.println(" ");
 
  myTouch.InitTouch(TOUCH_ORIENTATION);
 
  delay(500);
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
  }

  pinMode(53, OUTPUT);                                          // Настройка выбора SD

   if (!sd.begin(chipSelect, SPI_HALF_SPEED))
    {
      Serial.println("initialization SD failed!");
    }
  else
    {
      Serial.println("initialization SD successfully.");
    }

  SdFile::dateTimeCallback(dateTime);                          // Настройка времени записи файла
  //SD_info();
  Serial.println();
  serial_print_date();                                         // Печать даты и времени
  setup_pin();
  Serial.print(F("FreeRam: "));
  Serial.println(FreeRam());
  restore_default_device();

  format_memory();
  Serial.println(" ");                                   //
  //EEPROM.put(adr_start_user, user_number);   
  //EEPROM.put(adr_start_user+4, user_pass);
  //EEPROM.put(adr_start_user+10, user_number);  
  //EEPROM.put(adr_start_user+14, user_pass);
  number_device = i2c_eeprom_read_byte(deviceaddress, adr_number_device);
  delay(5000);
  vibroM();
  EEPROM.get(adr_pass_on_off, pass_on_off);  
  if(pass_on_off)                                       // Если флаг пароля true - включен
  {
    view_adr_user();                                  // Выбор пользователя
    pass_start();                                     // Пароль на входе
  }
  else
  {
    user_number = 0;
    user_pass   = 0;
  }
  Serial.println("System initialization OK!.");          // Информация о завершении настройки
}
void loop()
{
  klav_Glav_Menu(); 
}
