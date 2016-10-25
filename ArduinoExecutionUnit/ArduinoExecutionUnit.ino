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
#define set_time3 11  

int address_count1     = 0;
int address_count2     = 2;
int address_count3     = 3;
int address_count4     = 4;
int address_count5     = 5;
int address_count6     = 6;
int address_count7     = 7;
int address_count8     = 8;
int address_koef_time  = 9;
int address_koef_time2 = 10;
byte count1            = 0;
byte count2            = 0;
byte count3            = 0;
byte count4            = 0;
byte count5            = 0;
byte count6            = 0;
byte count7            = 0;
byte count8            = 0;
int timeMotor1         = 500;
int timeMotor2         = 500;
byte koeff_timeMotor1  = 1;
byte koeff_timeMotor2  = 1;

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
			//	{
			//		Serial.print("payload [");                   //
			//		Serial.print(i, DEC);                        //
			//		Serial.print("] is ");                       //
			//		Serial.println(rx.getData()[i], HEX);        // Информация находится в rx.getData()[i]
			//	}
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
    //copy the function type from the incoming query
	funcType = (rx.getData()[0]);
	field1	 = (rx.getData()[1] << 8) | rx.getData()[2]; 
	field2   = (rx.getData()[3] << 8) | rx.getData()[4];
//	Serial.println(rx.getData()[0], DEC);                   // Информация находится в rx.getData()[i]
	switch(funcType)                                        // Выполнить действие и сформировать ответ
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
            run_set_time1_StatusXBee(funcType, field1, field2);
			break;
		case 11:
            run_set_time1_StatusXBee(funcType, field1, field2); 
			break;
		case 12:
           reset_count();
			break;
		case 13:
           // run_set_time1_StatusXBee(funcType, field1, field2);
			break;
		case 14:
           // run_set_time1_StatusXBee(funcType, field1, field2); 
			break;
		default:
			break;
		}
	XBeeWrite();
 }
void XBeeWrite()
{
  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));  
  xbee.send(zbTx);
  if (xbee.readPacket(500))    	                                         //  После отправки запроса TX, мы ожидаем ответ статуса. Ждать до половины секунды для реагирования состояния 
	  {
		if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE)      // получил ответ!  Должен быть znet tx status    
		{
			xbee.getResponse().getZBTxStatusResponse(txStatus);
			if (txStatus.getDeliveryStatus() == SUCCESS)		    	 // Получить статус доставки, пятый байт
				{
				//	delay(300);
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

void run_KN1_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	payload[0] = funcType;

	flashLed(dataLed, 1, 150);
	payload[1] = 0;
	payload[2] = 1;
	count1++; 
	payload[11] = count1;
	//for (int i_xbee = 0;i_xbee<20;i_xbee++)
	//{
		//payload[3+i_xbee] = i2c_eeprom_read_byte( deviceaddress,adr_n_user+i_xbee);
	//}
	payload[29] = 2;
}
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	payload[0] = funcType;
	flashLed(dataLed, 1, 150);
	payload[1] = 0;
	payload[2] = 2;
	count1--; 
	payload[11] = count1;
	payload[29] = 2;
}
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 3;
	count3++; 
	payload[13] = count3;

	payload[29] = 2;
}
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 4;
	count3--; 
	payload[13] = count3;
	payload[29] = 2;
}
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 5;
	count5++; 
	payload[15] = count5;
	payload[29] = 2;
}
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 6;
	count6++; 
	payload[16] = count6;
	payload[29] = 2;
}
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 7;
	count7++; 
	payload[17] = count7;
	payload[29] = 2;
}
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 8;
	count8++; 
	payload[18] = count8;
	payload[29] = 2;
}
void run_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;
	 flashLed(dataLed, 1, 150);
	 payload[0] = funcType;
	 payload[1] = 0;
	 payload[2] = 9;
	 payload[29] = 2;
 }
void run_set_time2_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 10;
	payload[29] = 2;
}
void run_set_time3_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 11;
	payload[29] = 2;
}
void reset_count()
{
   if(rx.getData()[11]==0) count1 = 0;
   if(rx.getData()[12]==0) count1 = 0;
   if(rx.getData()[13]==0) count3 = 0;
   if(rx.getData()[14]==0) count3 = 0;
   if(rx.getData()[15]==0) count5 = 0;
   if(rx.getData()[16]==0) count6 = 0;
   if(rx.getData()[17]==0) count7 = 0;
   if(rx.getData()[18]==0) count8 = 0;
}

void set_pin()
{
	pinMode(led_13, OUTPUT);                             //
	digitalWrite(led_13, HIGH);                          //
}

void setup()
{

	  Serial.begin(9600);
      SerialXBee.begin(9600);
	  Serial.println("Start system");
	  xbee.setSerial(SerialXBee);
	  set_pin();
      flashLed(statusLed, 3, 50);
}

void loop()
{
	XBeeRead();
}
