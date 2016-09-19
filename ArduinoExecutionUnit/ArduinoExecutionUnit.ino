#include <XBee.h>



//int adr_zigbee_coordinator_h = 204;       //Адрес координатора старший
//int adr_zigbee_coordinator_l = 208;       //Адрес координатора младший
//int adr_zigbee_network       = 212;       //Адрес сети


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

		case READ_ELECTRO:
			// Serial.println("READ_ELECTRO:");
			get_READ_ELECTRO_StatusXBee(funcType, field1, field2);
			break;
		case READ_GAZ:
			//Serial.println("READ_GAZ:");
			get_READ_GAZ_StatusXBee(funcType, field1, field2);
			break;
		case READ_COLWATER:
			//Serial.println("READ_COLWATER:");
			get_READ_COLWATER_StatusXBee(funcType, field1, field2);
			break;
		case READ_HOTWATER:
			//Serial.println("READ_HOTWATER:");
			get_READ_HOTWATER_StatusXBee(funcType, field1, field2);
			break;
		case READ_WAR_GAZ:
			//Serial.println("WRITE_DO:");
			get_READ_WAR_GAZ_StatusXBee(funcType, field1, field2);
			break;
		case READ_WAR_TEMPERATURA:
			//Serial.println("WRITE_AO:");
			get_READ_WAR_TEMPERATURA_StatusXBee(funcType, field1, field2);
			break;
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
						mcp_Out1.digitalWrite(Beep, LOW);                    // 
						//delay(300);

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
					mcp_Out1.digitalWrite(Beep, LOW);                    // 
					//delay(200);

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
		while (true)
			{
				
			//	all_alarm();


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
					mcp_Out1.digitalWrite(Beep, LOW);                    // 
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



void setup()
{
	  Serial.begin(9600);
	  xbee.setSerial(Serial);
 set_info_ZigBee();
}

void loop()
{

  /* add main program code here */

}
