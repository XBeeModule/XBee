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

int Len_XBee = 0;
unsigned char info_XBee_data[10];
unsigned char info_XBee_data1[10];
unsigned long XBee_data2;
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
  xbee.readPacket();   // Получить пакет
	if (xbee.getResponse().isAvailable())  //Проверить наличие данных
	  {
		// есть что-то
	  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) 
		  {
			// Теперь заполнить наш класс ZB гх
			xbee.getResponse().getZBRxResponse(rx); // пакет rx заполнен, получен zb rx packet
			// Serial.println("Got an rx packet!");
			if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) 
				{
					// отправитель получил  ответ ACK
					// Serial.println("packet acknowledged");
				}  
			else 
				{
				   //Serial.println("packet not acknowledged");
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
				//	flashLed(dataLed, 10, 500);
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
	field1	= (rx.getData()[1] << 8) | rx.getData()[2];
	field2  = (rx.getData()[3] << 8) | rx.getData()[4];
	Serial.println(funcType);
	Serial.println(field1);
	Serial.println(field2);
	//generate query response based on function type
	switch(funcType)   // Выполнить действие и сформировать ответ
		{
		case KN1:
			run_KN1_StatusXBee(funcType, field1, field2);
			break;
		case KN2:
			run_KN1_StatusXBee(funcType, field1, field2);
			break;
		case KN3:
			run_KN1_StatusXBee(funcType, field1, field2);
			break;
		case KN4:
			run_KN1_StatusXBee(funcType, field1, field2);
			break;
		case KN5:
			run_KN1_StatusXBee(funcType, field1, field2);
			break;
		case KN6:
            run_KN1_StatusXBee(funcType, field1, field2);
			break;
		case KN7:
            run_KN1_StatusXBee(funcType, field1, field2);
			break;
		case KN8:
            run_KN1_StatusXBee(funcType, field1, field2); 
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
 XBeeRead();
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
/*						myGLCD.setColor(VGA_LIME);
						myGLCD.fillRoundRect (278, 92, 318, 132);
						myGLCD.setColor(255, 255, 255);
						myGLCD.drawRoundRect (278, 92, 318, 132);
						myGLCD.setBackColor(0, 0, 0);
						delay(400); 
						myGLCD.setColor(0, 0, 0);
						myGLCD.fillRoundRect (278, 92, 318, 132);
						myGLCD.setColor(0, 0, 0);
						myGLCD.drawRoundRect (278, 92, 318, 132);
						mcp_Out1.digitalWrite(Beep, LOW);     */               // 
						//delay(300);
				  }
			  else 
				  {
					// the remote XBee did not receive our packet. is it powered on?
					// Управляемый XBee не ответил. Он включен?
					// flashLed(errorLed, 3, 500);
					  //Serial.println("The remote XBee did not receive our packet. is it powered on?");  
				  }
			}
	  }
  else if (xbee.getResponse().isError())
	  {
		//Serial.print("Error reading packet.  Error code: ");  
		//Serial.println(xbee.getResponse().getErrorCode());
	  } 
  else 
	  {
		// local XBee did not provide a timely TX Status Response -- should not happen
		/*		   myGLCD.setColor(255 , 0, 0);
		myGLCD.fillRoundRect (278, 92, 318, 132);
		myGLCD.setColor(255, 255, 255);
		myGLCD.drawRoundRect (278, 92, 318, 132);
		myGLCD.setBackColor(0, 0, 0);
		delay(400); 
		myGLCD.setColor(0, 0, 0);
		myGLCD.fillRoundRect (278, 92, 318, 132);
		myGLCD.setColor(0, 0, 0);
		myGLCD.drawRoundRect (278, 92, 318, 132);
		mcp_Out1.digitalWrite(Beep, LOW);     */               // 
		//delay(200);
	  }
  delay(1000);
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
								//Serial.print(info_ZigBee_data[i10], HEX);
								info_XBee_data1[i11] = info_XBee_data[i10];
								i11--;
							  }
				
						 // Serial.println("");
						}
			  } 
		  else 
			  {
	/*			Serial.print("Command return error code: ");
				Serial.println(atResponse.getStatus(), HEX);*/
			  }
		} 
		else 
			{
		/*	  Serial.print("Expected AT response but got ");
			  Serial.println(xbee.getResponse().getApiId(), HEX);*/
			}   
	  }
  else 
	  {
		// at command failed
		if (xbee.getResponse().isError()) 
			{
			/*  Serial.print("Error reading packet.  Error code: ");  
			  Serial.println(xbee.getResponse().getErrorCode());*/
			} 
		else 
			{
			  //Serial.println("No response from radio1");  
			}
	  }
}
void sendAtCommand_ar() 
{
	int i10;
	xbee.send(arRequestMod);

	if (xbee.readPacket(5000))  // wait up to 5 seconds for the status response
	{ 
		if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) 
		{
		  xbee.getResponse().getAtCommandResponse(atResponse);

		  if (atResponse.isOk()) 
			  {
				if (atResponse.getValueLength() > 0) 
					{
						Len_XBee = atResponse.getValueLength();
						int i11=Len_XBee-1;
						info_XBee_data1[0] = 0;
						info_XBee_data1[1] = 0;
						info_XBee_data1[2] = 0;
						info_XBee_data1[3] = 0;

						for (i10 = 0; i10 < atResponse.getValueLength(); i10++) 
							{
								info_XBee_data[i10] = atResponse.getValue()[i10];
								info_XBee_data1[i11] = info_XBee_data[i10];
								i11--;
							}
					}
			  } 
		  else 
			  {
				 //   Serial.print("Command return error code: ");
				 //   Serial.println(atResponse.getStatus(), HEX);

					//myGLCD.setColor(255 , 0, 0);
					//myGLCD.fillRoundRect (278, 92, 318, 132);
					//myGLCD.setColor(255, 255, 255);
					//myGLCD.drawRoundRect (278, 92, 318, 132);
					//myGLCD.setBackColor(0, 0, 0);
					//delay(200); 
					//ZigBee_alarm();
					//delay(1000);
					//myGLCD.setColor(0, 0, 0);
					//myGLCD.fillRoundRect (278, 92, 318, 132);
					//myGLCD.setColor(0, 0, 0);
					//myGLCD.drawRoundRect (278, 92, 318, 132);
					//mcp_Out1.digitalWrite(Beep, LOW);                    // 
					//delay(300);
			  }
		} 
		else 
		{
	/*	  Serial.print("Expected AT response but got ");
			Serial.println(xbee.getResponse().getApiId(), HEX);*/
		}   
	  }
  else 
	  {
		if (xbee.getResponse().isError()) // at command failed
			{
		/*	  Serial.print("Error reading packet.  Error code: ");  
			  Serial.println(xbee.getResponse().getErrorCode());*/
			} 
		else 
			{
			  //Serial.println("No response from radio2");  
			}
	  }
}
void sendRemoteAtCommand()
{
	xbee.send(remoteAtRequest);
	if (xbee.readPacket(5000))   // wait up to 5 seconds for the status response
	{
	if (xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE) 
	{
	  xbee.getResponse().getRemoteAtCommandResponse(remoteAtResponse);

	  if (remoteAtResponse.isOk()) 
	  {
		//Serial.print("Command [");
		//Serial.print(remoteAtResponse.getCommand()[0]);
		//Serial.print(remoteAtResponse.getCommand()[1]);
		//Serial.println("] was successful!");

		if (remoteAtResponse.getValueLength() > 0) 
		{
		  //Serial.print("Command value length is ");
		  //Serial.println(remoteAtResponse.getValueLength(), DEC);
		 // Serial.print("Command value: ");
		  
		  for (int i = 0; i < remoteAtResponse.getValueLength(); i++) 
		  {
			//Serial.print(remoteAtResponse.getValue()[i], HEX);
			//Serial.print(" ");
		  }

		  //Serial.println("");
		}
	  }
	  else 
	  {
		//Serial.print("Command returned error code: ");
		//Serial.println(remoteAtResponse.getStatus(), HEX);
	  }
	}
	else 
	{
	  //Serial.print("Expected Remote AT response but got ");
	  //Serial.print(xbee.getResponse().getApiId(), HEX);
	}    
  }
  else if (xbee.getResponse().isError()) 
  {
	//Serial.print("Error reading packet.  Error code: ");  
	//Serial.println(xbee.getResponse().getErrorCode());
  }
  else 
  {
	//Serial.print("No response from radio3");  
  }
}
void set_info_XBee()
 {
	 ////Программа ввостановления данных ZigBee из памяти.
		//   byte y[4];   ; //Чтение из памяти текущих данных старшего адреса координатора
		//		y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_zigbee_coordinator_h);
		//		y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_zigbee_coordinator_h);
		//		y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_zigbee_coordinator_h);
		//		y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_zigbee_coordinator_h);
		//		XBee_Addr64_MS = (unsigned long&) y;  // Сложить восстановленные текущие данные

		////	   y[4];   ; //Чтение из памяти текущих данных младшего адреса координатора
		//		y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_zigbee_coordinator_l);
		//		y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_zigbee_coordinator_l);
		//		y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_zigbee_coordinator_l);
		//		y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_zigbee_coordinator_l);
		//		XBee_Addr64_LS = (unsigned long&) y;  // Сложить восстановленные текущие данные в 
}

void run_KN1_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	word val;
	word i = 0;

	payload[0] = funcType;

	flashLed(dataLed, startreg, numregs);


	//payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	//payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);
	//for (int i_xbee = 0;i_xbee<20;i_xbee++)
	//{
		//payload[3+i_xbee] = i2c_eeprom_read_byte( deviceaddress,adr_n_user+i_xbee);
	//}
	//payload[23] = i2c_eeprom_read_byte( deviceaddress,adr_elektro_day);
	//payload[24] = i2c_eeprom_read_byte( deviceaddress,adr_elektro_mon);
	//payload[25] = i2c_eeprom_read_byte( deviceaddress,adr_elektro_year+1);
	//payload[26] = i2c_eeprom_read_byte( deviceaddress,adr_elektro_year);
	//payload[27] = i2c_eeprom_read_byte( deviceaddress,adr_elektro_hour);
	//payload[28] = i2c_eeprom_read_byte( deviceaddress,adr_elektro_min);
	//payload[29] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_old+3);
	//payload[30] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_old+2);
	//payload[31] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_old+1);
	//payload[32] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_old);
	//payload[33] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_ok+3);
	//payload[34] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_ok+2);
	//payload[35] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_ok+1);
	//payload[36] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_ok);
	//payload[37] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_result+3);
	//payload[38] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_result+2);
	//payload[39] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_result+1);
	//payload[40] = i2c_eeprom_read_byte( deviceaddress,adr_count_electro_result);
 }
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;

	 payload[0] = funcType;
	flashLed(dataLed, startreg, numregs);
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;
	flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;
	flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;
	flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;
	flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;
	 flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;
	 flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
 {
	 word val;
	 word i = 0;
	 flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_set_time2_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, startreg, numregs);
	payload[0] = funcType;
	//payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	//payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

}
void run_set_time3_StatusXBee(byte funcType, word startreg, word numregs) // Вывод информации electro в XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, startreg, numregs);
	payload[0] = funcType;
	//payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	//payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

}




void set_pin()
{
	pinMode(led_13, OUTPUT);                             //
	digitalWrite(led_13, HIGH);                          //


	//pinMode(KN1, INPUT); 
	//pinMode(KN2, INPUT); 
	//pinMode(KN3, INPUT); 
	//pinMode(KN4, INPUT); 
	//pinMode(KN5, INPUT); 
	//pinMode(KN6, INPUT); 
	//pinMode(KN7, INPUT); 
	//pinMode(KN8, INPUT); 

	//digitalWrite(KN1, HIGH); 
	//digitalWrite(KN2, HIGH); 
	//digitalWrite(KN3, HIGH); 
	//digitalWrite(KN4, HIGH); 
	//digitalWrite(KN5, HIGH); 
	//digitalWrite(KN6, HIGH); 
	//digitalWrite(KN7, HIGH); 
	//digitalWrite(KN8, HIGH); 
}

void setup()
{
	  Serial.begin(9600);
	  xbee.setSerial(Serial);
	  set_pin();
      flashLed(statusLed, 3, 50);
}

void loop()
{
	XBeeRead();
}
