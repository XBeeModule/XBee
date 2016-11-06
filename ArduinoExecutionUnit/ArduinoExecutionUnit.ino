/*
Пульт должен передавать команды на исполнительное устройство,
которое будет управлять блоком реле и переключателей, 
а также возвращать подтверждение выполнения команд МК. 
Также разработчик предусматривает соответствующие методы фильтрации, шифрование, модуляцию.
Исполнение команд необходимо гарантированное, то есть пульт должен иметь индикацию выполнения (обмен данными двухсторонний). 
Также желательна (если возможно) односторонняя передача rs232 - от ИУ к пульту на скорости 1200бод. 
Драйвер реле и четыре реле. Возможна обратная связь подтверждения состояния реле. 
Светодиодная индикация включения реле, подтверждения связи с пультом, индикация ошибки.
3.Исполнительное устройство. Управление маломощными реле типа TQ2 5V, соленоидами 100мА, реле типа TQ2-l2-5V.
Выходы:
1)Выключатель. Индикация – команда получена(выполнена) – горит диод, команда не прошла – не горит. TQ2 5V
2)Выключатель. Индикация – команда получена(выполнена) – горит диод, команда не прошла – не горит. TQ2 5V

5) Переключатель. При включении устройства – опрос положения, загорается один из диодов.
Индикация – команда на переключение получена(выполнена) – загорается соответствующий диод, противоположный гаснет. TQ2-l2-5V 
Управление будет не соленоидами, а микродвигателем 5в,

нужна возможность реверса, время вращения строго определенной продолжительности - 0,5 сек каждая команда. 
Т.е. управление будет выглядеть так: 
1. Управление реле - нажал иконку - вкл - нажал - выкл. Таких два выхода, иконки "канал 1"  и "канал 2".
2. Управление микродвигателем - нажал "+" - на контаты микродвигателя поступил сигнал, продолжительностью 0,5 секунд, полярность (+-), 
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

FAN8082

      Input               |      Output     
----------------------------------------------------------------
    Pin4    |    Pin5     |   Pin2      |    Pin8     |  Motor
----------------------------------------------------------------
    Low     |    Low      |    Low      |    Low      | Stop
---------------------------------------------------------------
    High    |    Low      |    High     |    Low      | Forward
---------------------------------------------------------------
    Low     |   High      |    Low      |    High     | Reverse
---------------------------------------------------------------
    High    |   High      |    Low      |    Low      | Stop
---------------------------------------------------------------


*/






#include <XBee.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>                   // Работаем с памятью. Допустимо больше 100 тысяч перезаписи.

#define led_13 13  
#define KN1 1   
#define KN2 2  
#define KN3 3 
#define KN4 4 
#define KN5 5  
#define KN6 6  
#define KN7 7  
#define KN8 8  
#define set_time1 9  
#define set_time2 10  


// Порты реле
#define Q1  4               // Управление реле 1
#define Q2  5               // Управление реле 2  
#define Q3  6               // Управление реле 3  
#define Q4  7               // Управление реле 4
#define M1_1  A1            // Мотор 1-
#define M1_2  A2            // Мотор 1+
#define M2_1  A3            // Мотор 2-
#define M2_2  A4            // Мотор 2+

bool rele1 = false;
bool rele2 = false;
bool rele3 = false;
bool rele4 = false;

int address_count1             = 1;
int address_count2             = 3;
int address_count3             = 5;
int address_count4             = 7;
int address_count5             = 9;
int address_count6             = 11;
int address_count7             = 13;
int address_count8             = 15;
int address_koef_time1         = 17;
int address_koef_time2         = 19;
int address_timeMotor1         = 21;
int address_timeMotor2         = 23;

int timeMotor1                 = 500;
int timeMotor2                 = 500;
int koeff_timeMotor1           = 1;
int koeff_timeMotor2           = 1;

//EEPROM.update(address, val);  


// Define NewSoftSerial TX/RX pins

uint8_t ssRX = 3;           // Connect Arduino pin 3 to TX of XBee device
uint8_t ssTX = 2;           // Connect Arduino pin 2 to RX of XBee device
SoftwareSerial SerialXBee(ssRX, ssTX);

// ************ ZigBee******************

XBee xbee               = XBee();                           //создаем XBee библиотеку
XBeeResponse response   = XBeeResponse();                   //Это создает экземпляр объекта "response" "ответ" обрабатывать пакеты Xbee
ZBRxResponse rx         = ZBRxResponse();                   //Это создает экземпляр объекта "rx" на процесс Xbee Series 2 API пакеты
ModemStatusResponse msr = ModemStatusResponse();            //Это создает экземпляр объекта "msr" процесс associate/disassociate packets (PAN membership)

ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();

//Строка с данными
uint8_t payload[30];                                        // = {3, 4,};

//Два 32-битных половинки th4 64-разрядный адрес
long XBee_Addr64_MS;                                        // = 0x0013a200;
long XBee_Addr64_LS;                                        // = 0x4054de2d;
int XBee_Addr16;                                            // = 0xffff   //16-разрядный адрес

int Len_XBee = 0;
unsigned char info_XBee_data[10];
unsigned char info_XBee_data1[10];
unsigned long XBee_data2;
char* simbol_ascii[2];
char   cmd;
char * pEnd;

uint8_t commandValue[]  = { 0x02, 0x35 }; 
uint8_t commandValueLength = 0x2 ;

XBeeAddress64 addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);  // SH + SL Address of receiving XBee
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();                    //Это создает экземпляр объекта "txStatus" процесс благодарности прислал Xbee Series 2 API пакеты

//********************************
  byte funcType;
  word field1;
  word field2;
  byte *_msg, _len;
  word _baud, _crc;

//-----------------------------------------------------------------------------------------------

int statusLed = 13;
int errorLed = 13;
int dataLed = 13;

int statusRele1 = 1;
int statusRele2 = 1;
int statusRele3 = 1;
int statusRele4 = 1;

void sl_XBee();
void run_KN1_StatusXBee(byte funcType, word startreg, word numregs); // Вывод информации  в XBee
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs); // Вывод информации   в XBee
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs); // Вывод информации   в XBee
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs); // Вывод информации  в XBee
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs); // Вывод информации   в XBee
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs); // Вывод информации   в XBee
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs); // Вывод информации   в XBee
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs); // Вывод информации   в XBee
void run_set_time1_StatusXBee(byte funcType, word startreg, word numregs);
void run_set_time2_StatusXBee(byte funcType, word startreg, word numregs);
void run_set_time3_StatusXBee(byte funcType, word startreg, word numregs);
void reset_count();
void XBeeWrite();
void clear_payload();
void clear_EEPROM(int start, int stop);


void flashLed(int pin, int times, int wait) 
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
void XBeeRead()
{
  xbee.readPacket();                                             // Получить пакет
  if (xbee.getResponse().isAvailable())                        //Проверить наличие данных
    {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)       // есть что-то
      {
      xbee.getResponse().getZBRxResponse(rx);              //  Теперь заполнить наш класс ZB гх  пакет rx заполнен, получен zb rx packet
      if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED)        // отправитель получил  ответ ACK
        {
           Serial.println("packet acknowledged");
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
        //Получаем верхние 32-битное слово 64-битный адрес.  64-битный адрес 802.15.4 MAC адрес источника 
      //for (int i = 0; i < rx.getDataLength(); i++)       // Считать информацию длина пакета  в rx.getDataLength()
      //  {
      //    Serial.print("payload [");                   //
      //    Serial.print(i, DEC);                        //
      //    Serial.print("] is ");                       //
      //    Serial.println(rx.getData()[i], HEX);        // Информация находится в rx.getData()[i]
      //  }
          XBee_Addr64_MS=(uint32_t(rx.getFrameData()[0]) << 24) + (uint32_t(rx.getFrameData()[1]) << 16) + (uint16_t(rx.getFrameData()[2]) << 8) + rx.getFrameData()[3];
        //Получаем ниже 32-битное слово...
        XBee_Addr64_LS=(uint32_t(rx.getFrameData()[4]) << 24) + (uint32_t(rx.getFrameData()[5]) << 16) + (uint16_t(rx.getFrameData()[6]) << 8) + rx.getFrameData()[7];
        //Отправить две части адреса программного обеспечения последовательного порта
        XBee_Addr16=rx.getRemoteAddress16();                  // IP-адреса в TCP/IP. 
        //Serial.println(XBee_Addr64_MS, HEX); 
    //            Serial.println(XBee_Addr64_LS, HEX); 
        addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
       }
    sl_XBee();
    } 
   else if (xbee.getResponse().isError())                            //  Ошибка приема
    {
       Serial.print("error code:");
       Serial.println(xbee.getResponse().getErrorCode());            // Код ошибки xbee.getResponse().getErrorCode()
    }
}
void sl_XBee()                                              // формировать ответ Координатору 
 {
  funcType = (rx.getData()[0]);
  field1   = (rx.getData()[1] << 8) | rx.getData()[2]; 
  field2   = (rx.getData()[3] << 8) | rx.getData()[4];
//  Serial.println(rx.getData()[0], DEC);                   // Информация находится в rx.getData()[i]
  switch(funcType)                                          // Выполнить действие и сформировать ответ
    {
    case 1:
      run_KN1_StatusXBee(funcType, field1, field2);
      break;
    case 2:
      run_KN2_StatusXBee(funcType, field1, field2);
      break;
    case 3:
      run_KN3_StatusXBee(funcType, field1, field2);
      break;
    case 4:
      run_KN4_StatusXBee(funcType, field1, field2);
      break;
    case 5:
      run_KN5_StatusXBee(funcType, field1, field2);
      break;
    case 6:
            run_KN6_StatusXBee(funcType, field1, field2);
      break;
    case 7:
            run_KN7_StatusXBee(funcType, field1, field2);
      break;
    case 8:
            run_KN8_StatusXBee(funcType, field1, field2); 
      break;
    case 9:
            run_set_time1_StatusXBee(funcType, field1, field2);
      break;
    case 10:
            run_set_time2_StatusXBee(funcType, field1, field2);
      break;
    case 11:
            
      break;
    case 12:
           reset_count();
      break;
    case 13:
            motor1_set_time1_StatusXBee(funcType, field1, field2);
      break;
    case 14:
            motor2_set_time1_StatusXBee(funcType, field1, field2); 
      break;
    default:
      break;
    }
  set_payload();
  XBeeWrite();
 }
void XBeeWrite()
{
  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));  
  xbee.send(zbTx);
  if (xbee.readPacket(500))                                              //  После отправки запроса TX, мы ожидаем ответ статуса. Ждать до половины секунды для реагирования состояния 
    {
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE)      // получил ответ!  Должен быть znet tx status    
    {
      xbee.getResponse().getZBTxStatusResponse(txStatus);
      if (txStatus.getDeliveryStatus() == SUCCESS)           // Получить статус доставки, пятый байт
        {
        //  delay(300);
        }
      else 
        {
           Serial.println("Error reading packet.  Error code: 1");  
           flashLed(errorLed, 10, 100);                         // Управляемый XBee не ответил. Он включен?
        }
    }
    }
  else if (xbee.getResponse().isError())
    {
       Serial.println("Error reading packet.  Error code: 2");  
       flashLed(errorLed, 10, 100);                                   // Управляемый XBee не ответил. Он включен?
    } 
  else 
    {
      Serial.println("Error reading packet.  Error code: 3");  
      flashLed(errorLed, 10, 100);                                  // Управляемый XBee не ответил. Он включен?
      delay(200); 
    }
  delay(500);
}

void run_KN1_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации  в XBee
{
  word val;
  word i = 0;
  payload[0] = funcType;
  flashLed(dataLed, 1, 150); 
  EEPROM.get(address_timeMotor1, val);                      //Получить из EEPROM длительность импульса
  digitalWrite(M1_1, LOW);             // Мотор 1-
  digitalWrite(M1_2, HIGH);            // Мотор 1+
  delay(val);
  digitalWrite(M1_1, LOW);             // Мотор 1-
  digitalWrite(M1_2, LOW);             // Мотор 1+ 
  increase_counter(1, address_count1); // Певый параметр DataXBee[], Счетчик 
}
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации   в XBee
{
  word val;
  word i = 0;
  payload[0] = funcType;
  flashLed(dataLed, 1, 150); 
  EEPROM.get(address_timeMotor1, val);                      //Получить из EEPROM длительность импульса
  digitalWrite(M1_1, HIGH);            // Мотор 1-
  digitalWrite(M1_2, LOW);             // Мотор 1+
  delay(val);
  digitalWrite(M1_1, LOW);             // Мотор 1-
  digitalWrite(M1_2, LOW);             // Мотор 1+ 
  increase_counter(3, address_count2); // Певый параметр DataXBee[], Счетчик 
}
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации   в XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  EEPROM.get(address_timeMotor2, val);                      //Получить из EEPROM длительность импульса
  digitalWrite(M2_1, LOW);             // Мотор 2-
  digitalWrite(M2_2, HIGH);            // Мотор 2+
  delay(val);
  digitalWrite(M2_1, LOW);             // Мотор 2-
  digitalWrite(M2_2, LOW);             // Мотор 2+ 
  increase_counter(5, address_count3); // Певый параметр DataXBee[], Счетчик 
}
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации  в XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150); 
  payload[0] = funcType;
  EEPROM.get(address_timeMotor2, val);                      //Получить из EEPROM длительность импульса
  digitalWrite(M2_1, HIGH);            // Мотор 2-
  digitalWrite(M2_2, LOW);             // Мотор 2+
  delay(val);
  digitalWrite(M2_1, LOW);             // Мотор 2-
  digitalWrite(M2_2, LOW);             // Мотор 2+ 
  increase_counter(7, address_count4); // Певый параметр DataXBee[], Счетчик 
}
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации  в XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  rele1 =  !rele1;
  digitalWrite(Q1, rele1);              // Управление реле 1
  increase_counter(9, address_count5);
}
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации   в XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  rele2 =  !rele2;
  digitalWrite(Q2, rele2);              // Управление реле 1
  increase_counter(11, address_count6);
}
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации   в XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  rele3 =  !rele3;
  digitalWrite(Q3, rele3);              // Управление реле 1
  increase_counter(13, address_count7);
}
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации   в XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  rele4 =  !rele4;
  digitalWrite(Q4, rele4);              // Управление реле 1
  increase_counter(15, address_count8);
}
void run_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации   в XBee
 {
	//word val;
	//word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	EEPROM.put(address_koef_time1, startreg);     
	//byte hi=highByte(startreg);
	//byte low=lowByte(startreg);
	//EEPROM.write(address_koef_time1, hi);
	//EEPROM.write(address_koef_time1+1, low);
 }
void run_set_time2_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации   в XBee
{
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	EEPROM.put(address_koef_time2, startreg); 
	//byte hi=highByte(startreg);
	//byte low=lowByte(startreg);
	//EEPROM.write(address_koef_time2, hi);
	//EEPROM.write(address_koef_time2+1, low);
}
void motor1_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации  в XBee
{
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	EEPROM.put(address_timeMotor1, startreg); 
}
void motor2_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации  в XBee
{
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	EEPROM.put(address_timeMotor2, startreg); 

	//byte hi=highByte(startreg);
	//byte low=lowByte(startreg);
	//EEPROM.write(address_timeMotor1, hi);
	//EEPROM.write(address_timeMotor1+1, low);
}

void reset_count()
{
	//Serial.println(rx.getData()[11]);
	//Serial.println(rx.getData()[12]);
	//Serial.println(rx.getData()[13]);
	//Serial.println(rx.getData()[14]);
	//Serial.println(rx.getData()[15]);
	//Serial.println(rx.getData()[16]);
	//Serial.println(rx.getData()[17]);
	//Serial.println(rx.getData()[18]);

   if(rx.getData()[11]!=0) EEPROM.put(address_count1, 0);   
   if(rx.getData()[12]!=0) EEPROM.put(address_count2, 0);
   if(rx.getData()[13]!=0) EEPROM.put(address_count3, 0);
   if(rx.getData()[14]!=0) EEPROM.put(address_count4, 0);
   if(rx.getData()[15]!=0) EEPROM.put(address_count5, 0);
   if(rx.getData()[16]!=0) EEPROM.put(address_count6, 0);
   if(rx.getData()[17]!=0) EEPROM.put(address_count7, 0);
   if(rx.getData()[18]!=0) EEPROM.put(address_count8, 0);
}
void increase_counter(int dataXBee, int adr_count)
{
	int count;
	EEPROM.get(adr_count, count);                      //Получить из EEPROM показания счетчика
	count++;
	if(count >=999) count = 999;
	EEPROM.put(adr_count, count);                      //Записать в EEPROM показания счетчика

	byte hi=highByte(count);
    byte low=lowByte(count);

	payload[dataXBee] = hi;
	payload[dataXBee+1] = low;
}

void set_count(int kn, int adr_count)
{
	int count;
	EEPROM.get(adr_count, count);                      //Получить из EEPROM показания счетчика
	byte hi=highByte(count);
    byte low=lowByte(count);
	payload[kn] = hi;
	payload[kn+1] = low;
}

void set_payload()
{
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
}


void clear_payload()
{
	for (int i=0;i<30;i++)
	{
       payload[i] = 0;                   // 
	}
}

void clear_EEPROM(int start, int stop)
{
	for (int i= start;i<stop;i++)
	{
      EEPROM.write(i, 0);
  	}
}


void set_pin()
{
  pinMode(led_13, OUTPUT);            //
  digitalWrite(led_13, HIGH);         //
  pinMode(Q1, OUTPUT);                // Управление реле 1
  pinMode(Q2, OUTPUT);                // Управление реле 2  
  pinMode(Q3, OUTPUT);                // Управление реле 3  
  pinMode(Q4, OUTPUT);                // Управление реле 4
  pinMode(M1_1, OUTPUT);              // Мотор 1-
  pinMode(M1_2, OUTPUT);              // Мотор 1+
  pinMode(M2_1, OUTPUT);              // Мотор 2-
  pinMode(M2_2, OUTPUT);              // Мотор 2+

  digitalWrite(Q1, LOW);              // Управление реле 1
  digitalWrite(Q2, LOW);              // Управление реле 2  
  digitalWrite(Q3, LOW);              // Управление реле 3  
  digitalWrite(Q4, LOW);              // Управление реле 4
  digitalWrite(M1_1, LOW);            // Мотор 1-
  digitalWrite(M1_2, LOW);            // Мотор 1+
  digitalWrite(M2_1, LOW);            // Мотор 2-
  digitalWrite(M2_2, LOW);            // Мотор 2+
}


  //byte hi=highByte(value);
  //byte low=lowByte(value);

  //// тут мы эти hi,low можем сохраить, прочитать из eePROM

  //int value2=(hi<<8) | low; // собираем как "настоящие программеры"
  //int value3=word(hi,low); // или собираем как "ардуинщики"

void setup()
{
  Serial.begin(9600);
  SerialXBee.begin(9600);
  Serial.println("Start system");
  xbee.setSerial(SerialXBee);
  set_pin();
  flashLed(statusLed, 3, 150);
  clear_payload();
  if(EEPROM.read(0)!=56)
  {
	Serial.println("Clear EEPROM Start");
	clear_EEPROM(0, 1023);
	EEPROM.write(0, 56);
	EEPROM.put(address_timeMotor1, timeMotor1);                      //Записать в EEPROM длительность импульса
	EEPROM.put(address_timeMotor2, timeMotor2);                      //Записать в EEPROM длительность импульса
	Serial.println("Clear EEPROM End");
  }

  //flashLed(Q1, 3, 450);
  //flashLed(Q2, 3, 450);
  //flashLed(Q3, 3, 450);
  //flashLed(Q4, 3, 450);
  //flashLed(M1_1, 3, 450);
  //flashLed(M1_2, 3, 450);
  //flashLed(M2_1, 3, 450);
  //flashLed(M2_2, 3, 450);
  Serial.println("Setup End");
} 
void loop()
{
  XBeeRead();
}
