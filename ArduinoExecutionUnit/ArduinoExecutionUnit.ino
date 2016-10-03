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
				Serial.print("checksum is ");
				Serial.println(rx.getChecksum(), HEX);    // Контрольная сумма
				Serial.print("All packet length is ");
				Serial.println(rx.getPacketLength(), DEC); // Длина пакета общего пакета
				Serial.print("Data packet length is ");
				//Получаем верхние 32-битное слово 64-битный адрес.  64-битный адрес 802.15.4 MAC адрес источника 
				XBee_Addr64_MS=(uint32_t(rx.getFrameData()[0]) << 24) + (uint32_t(rx.getFrameData()[1]) << 16) + (uint16_t(rx.getFrameData()[2]) << 8) + rx.getFrameData()[3];
				//Получаем ниже 32-битное слово...
				XBee_Addr64_LS=(uint32_t(rx.getFrameData()[4]) << 24) + (uint32_t(rx.getFrameData()[5]) << 16) + (uint16_t(rx.getFrameData()[6]) << 8) + rx.getFrameData()[7];
				//Отправить две части адреса программного обеспечения последовательного порта
				XBee_Addr16=rx.getRemoteAddress16();                  // IP-адреса в TCP/IP. 
				Serial.println(XBee_Addr64_MS, HEX); 
                Serial.println(XBee_Addr64_LS, HEX); 
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
	Serial.println(rx.getData()[0], HEX);        // Информация находится в rx.getData()[i]
	switch(funcType)                                        // Выполнить действие и сформировать ответ
		{
		case KN1:
			run_KN1_StatusXBee(funcType, field1, field2);
			break;
		case KN2:
			run_KN2_StatusXBee(funcType, field1, field2);
			break;
		case KN3:
			run_KN3_StatusXBee(funcType, field1, field2);
			break;
		case KN4:
			run_KN4_StatusXBee(funcType, field1, field2);
			break;
		case KN5:
			run_KN5_StatusXBee(funcType, field1, field2);
			break;
		case KN6:
            run_KN6_StatusXBee(funcType, field1, field2);
			break;
		case KN7:
            run_KN7_StatusXBee(funcType, field1, field2);
			break;
		case KN8:
            run_KN8_StatusXBee(funcType, field1, field2); 
			break;
		case set_time1:
            run_set_time1_StatusXBee(funcType, field1, field2);
			break;
		case set_time2:
            run_set_time1_StatusXBee(funcType, field1, field2);
			break;
		case set_time3:
            run_set_time1_StatusXBee(funcType, field1, field2); 
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
					//flashLed(statusLed, 5, 50);                         // Успешно, можно радоваться.
					delay(300);
				}
			else 
				{
					 Serial.println("Error reading packet.  Error code: 1");  
					//flashLed(errorLed, 10, 100);                         // Управляемый XBee не ответил. Он включен?
				}
		}
	  }
  else if (xbee.getResponse().isError())
	  {
		   Serial.println("Error reading packet.  Error code: 2");  
		  //flashLed(errorLed, 3, 100);                                   // Управляемый XBee не ответил. Он включен?
	  } 
  else 
	  {
		  Serial.println("Error reading packet.  Error code: 3");  
			//flashLed(errorLed, 3, 100);                                  // Управляемый XBee не ответил. Он включен?
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
	//for (int i_xbee = 0;i_xbee<20;i_xbee++)
	//{
		//payload[3+i_xbee] = i2c_eeprom_read_byte( deviceaddress,adr_n_user+i_xbee);
	//}
	payload[23] = 1;
	payload[24] = 1;
	payload[25] = 1;
	payload[26] = 1;
}
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	payload[0] = funcType;
	flashLed(dataLed, 1, 150);
	payload[1] = 0;
	payload[2] = 2;
	payload[23] = 2;
}
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 3;
	payload[23] = 3;
}
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 4;
	payload[23] = 4;
}
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 5;
	payload[4] = 5;
	payload[5] = 5;
	payload[6] = 5;
	payload[7] = 5;
}
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 6;
}
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 7;
}
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 8;
}
void run_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;
	 flashLed(dataLed, 1, 150);
	 payload[0] = funcType;
	 payload[1] = 0;
	 payload[2] = 9;
 }
void run_set_time2_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 10;
}
void run_set_time3_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 11;
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
	  xbee.setSerial(SerialXBee);
	  set_pin();
      flashLed(statusLed, 3, 50);
}

void loop()
{
	XBeeRead();
}
