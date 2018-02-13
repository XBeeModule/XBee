#include "XBeeMenu.h"
//
/*#define Serial SERIAL_PORT_USBVIRTUAL */  

XBee xbee = XBee();                                   //создаем XBee библиотеку

													  
// ++++++++++  настройки для приема и передачи пакета +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

uint8_t payload[64] = { 0 };

uint8_t shCmd[] = { 'S','H' };                // serial high Старший байт адреса куда отправляется пакет
uint8_t slCmd[] = { 'S','L' };                // serial low Младший байт адреса куда отправляется пакет
uint8_t assocCmd[] = { 'A','I' };             // association status Индикация присоединения 

											  //Считывает информацию о последнем запросе узла на присоединение:
											  //0x00 – Завершено успешно - Координатор стартовал илиМаршрутизатор/Конечное устройство
											  //обнаружило и присоединилось родительскому устройству.
											  //0x21 – Сканирование не обнаружило сети
											  //0x22 – Сканирование не обнаружило работающей сети с текущими установками SC и ID
											  //0x23 – Работающий Координатор или Маршрутизаторы найдены, но они не дали разрешение на
											  //присоединение к сети (истекло время NJ)
											  //0x27 – Попытка присоединения не удалась
											  //0x2A – Запуск Координатора не удался
											  //0xFF – Идет поиск родительского устройства

uint8_t irCmd[] = { 'I','R' };             // 
uint8_t opCmd[] = { 'O','P' };             // Номер сети (PAN ID)
uint8_t IDCmd[] = { 'I','D' };             // Номер сети (ID)
uint8_t OICmd[] = { 'O','I' };             // Operating 16-bit PAN ID(OI)
uint8_t MYCmd[] = { 'M','Y' };             // Номер сети (16-bit Network Adress
uint8_t CHCmd[] = { 'C','H' };             // Номер Радиоканала
uint8_t SCCmd[] = { 'S','C' };             // Scan Channel
uint8_t BDCmd[] = { 'B','D' };             // Скорость канала (Baud Rate )
uint8_t VoltCmd[] = { '%','V' };             // Напряжение питания Считывает напряжение на выводе Vcc. Для преобразования значения
											 // в мВ, поделите значение на 1023 и умножьте на 1200. Значение %V равное 0x8FE (или 2302 в
											 // десятичном виде) соответствует 2700мВ или 2.70В
uint8_t TPCmd[] = { 'T','P' };             // Температура
uint8_t dhCmd[] = { 'D','H' };             // Старший байт адреса
uint8_t dlCmd[] = { 'D','L' };             // Младший байт адреса
uint8_t d0Cmd[] = { 'D','0' };             //
uint8_t WRCmd[] = { 'W','R' };             // Запись в модуль параметров
										   // Примечание: Если введена команда WR, до получения ответа "OK\r" не должно вводится
										   // дополнительных символов
uint8_t FRCmd[] = { 'F','R' };             // Перезапуск программного обеспечения
uint8_t NRCmd[] = { 'N','R' };             // Перезапуск сети 
										   // Если NR = 0: Переустанавливает параметры сети на узле, вызвавшем команду. 
										   // Если NR = 1:Отправляетшироковещательную передачу для перезапуска параметров на всех узлах сети.
uint8_t PLCmd[] = { 'P','L' };             // TX Power level mW
uint8_t NDCmd[] = { 'N','D' };             // Обнаружение узла (Node Discover). Обнаруживает и сообщает обо всех
										   // найденных модулях. Следующая информация будет сообщена для каждого
										   // обнаруженного модуля:
										   // MY<CR>      16-разрядный адрес источника
										   // SH<CR>      Старшие байты серийного номера
										   // SL<CR>      Младшие байты серийного номера
										   // DB<CR>      Сила принимаемого сигнала (Received Signal Strength)
										   // NI<CR><CR>  Идентификатор узла (Node Identifier). Имя модуля

uint8_t NTCmd[] = { 'N','T' };             // Node Discovery Timeout. Set/Read the node discovery timeout. When the network
										   // discovery (ND) command is issued, the NT value is included in the transmission to
										   // provide all remote devices with a response timeout. Remote devices wait a random
										   //  time, less than NT, before sending their response.  0x3C (60d)


uint8_t d0Value[] = { 0x2 };
uint8_t irValue[] = { 0xff, 0xff };
uint8_t IDValue[] = { 0x02, 0x34 };


uint8_t command[] = { 'I','D' };             // Номер сети (ID)
uint8_t commandValue[] = { 0x02, 0x35 };
uint8_t commandValueLength = 0x2;

//Два 32-битных половинки th4 64-разрядный адрес
long XBee_Addr64_MS = 0x0013a200;
long XBee_Addr64_LS = 0; //0x40672567;

						 //Два 32-битных половинки th4 64-разрядный адрес
long XBee_Addr64_MS_tmp = 0;                    //
long XBee_Addr64_LS_tmp = 0;                    //
int XBee_Addr16;                            //16-разрядный адрес
int Len_XBee = 0;
unsigned char info_XBee_data[96];
unsigned char info_XBee_data1[96];
char* simbol_ascii[2];
char   cmd;

XBeeResponse response = XBeeResponse();               //Это создает экземпляр объекта "response" "ответ" обрабатывать пакеты Xbee
ZBRxResponse rx = ZBRxResponse();                     //Это создает экземпляр объекта "rx" на процесс Xbee Series 2 API пакеты
ModemStatusResponse msr = ModemStatusResponse();      //Это создает экземпляр объекта "msr" процесс associate/disassociate packets (PAN membership)
ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();


XBeeAddress64 addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);                                     // SH + SL Address of receiving XBee
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));                                         // Формирует пакет  zbTx с адресом отправителя и данными
ZBTxStatusResponse txStatus = ZBTxStatusResponse();                                                       // Это создает экземпляр объекта "txStatus" процесс благодарности прислал Xbee Series 2 API пакеты
AtCommandRequest atRequest = AtCommandRequest(shCmd);                                                     // XBeeAddress64 remoteAddress = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
AtCommandRequest arRequestMod = AtCommandRequest(command, commandValue, commandValueLength);
AtCommandResponse atResponse = AtCommandResponse();
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(addr64, irCmd, irValue, sizeof(irValue)); // Create a remote AT request with the IR command
RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();                                     // Create a Remote AT response object

XBeeActive RealXBeeMenu;

void XBeeActive::setup()
{
	xbee.begin(Serial1);
	DEBAG.println("\nXBee setup");
}
void XBeeActive::sendAtCommand()
{
	int i10;
	xbee.send(atRequest);
	if (xbee.readPacket(5000)) // подождите до 5 секунд для ответа состояния
	{
		if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) // Должна быть команда отклика AT
		{
			xbee.getResponse().getAtCommandResponse(atResponse);

			if (atResponse.isOk())
			{
				//DEBAG.print("Command [");
				//DEBAG.print(atResponse.getCommand()[0]);
				//DEBAG.print(atResponse.getCommand()[1]);
				//DEBAG.println("] was successful!");

				if (atResponse.getValueLength() > 0)
				{
					Len_XBee = atResponse.getValueLength();
					//DEBAG.print("\nCommand value length is - ");
					//DEBAG.println(atResponse.getValueLength(), DEC);
					//DEBAG.print("Command value: ");
					int i11 = Len_XBee - 1;
					info_XBee_data1[0] = 0;
					info_XBee_data1[1] = 0;
					info_XBee_data1[2] = 0;
					info_XBee_data1[3] = 0;

					for (i10 = 0; i10 < atResponse.getValueLength(); i10++)
					{
						info_XBee_data[i10] = atResponse.getValue()[i10];
						//DEBAG.print(info_XBee_data[i10], HEX);
						//DEBAG.print(" ");
						info_XBee_data1[i11] = info_XBee_data[i10];
						i11--;
					}
					//DEBAG.println("");
				}
			}
			else
			{
				//DEBAG.print("Command return error code: ");
				//DEBAG.println(atResponse.getStatus(), HEX);
			}
		}
		else
		{
			//DEBAG.print("Expected AT response but got ");
			//DEBAG.println(xbee.getResponse().getApiId(), HEX);
		}
	}
	else
	{
		if (xbee.getResponse().isError())             // at command failed
		{
			//DEBAG.print("Error reading packet.  Error code: ");
			//DEBAG.println(xbee.getResponse().getErrorCode());
		}
		else
		{
			//DEBAG.println("No response from radio1");
		}
	}
	delay(200);
}
void XBeeActive::sendAtCommand_ar()
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
					int i11 = Len_XBee - 1;
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

				//myGLCD.setColor(255, 0, 0);
				//myGLCD.fillRoundRect(278, 92, 318, 132);
				//myGLCD.setColor(255, 255, 255);
				//myGLCD.drawRoundRect(278, 92, 318, 132);
				//myGLCD.setBackColor(0, 0, 0);
				//delay(200);
				////XBee_alarm();
				//delay(1000);
				//myGLCD.setColor(0, 0, 0);
				//myGLCD.fillRoundRect(278, 92, 318, 132);
				//myGLCD.setColor(0, 0, 0);
				//myGLCD.drawRoundRect(278, 92, 318, 132);
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
void XBeeActive::sendRemoteAtCommand()
{
	DEBAG.println("\nSending command sendRemoteAtCommand to the XBee");
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
				DEBAG.print("Command [");
				DEBAG.print(remoteAtResponse.getCommand()[0]);
				DEBAG.print(remoteAtResponse.getCommand()[1]);
				DEBAG.println("] was successful!");

				if (remoteAtResponse.getValueLength() > 0) {
					DEBAG.print("Command value length is ");
					DEBAG.println(remoteAtResponse.getValueLength(), DEC);

					DEBAG.print("Command value: ");

					for (int i = 0; i < remoteAtResponse.getValueLength(); i++) {
						DEBAG.print(remoteAtResponse.getValue()[i], HEX);
						DEBAG.print(" ");
					}

					DEBAG.println("");
				}
			}
			else {
				DEBAG.print("Command returned error code: ");
				DEBAG.println(remoteAtResponse.getStatus(), HEX);
			}
		}
		else
		{
			DEBAG.print("Expected Remote AT response but got ");
			DEBAG.print(xbee.getResponse().getApiId(), HEX);
		}
	}
	else if (xbee.getResponse().isError())
	{
		DEBAG.print("Error reading packet.  Error code: ");
		DEBAG.println(xbee.getResponse().getErrorCode());
	}
	else
	{
		DEBAG.print("No response from radio3");
	}
}
void XBeeActive::testRemoteAtCommand()
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
void XBeeActive::test_arRequestMod()
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
void XBeeActive::search_XBee()
{
	d0Value[0] = 0xFE;
	commandValueLength = 0x1;
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


void XBeeActive::XBee_status()
{
  
  unsigned long XBee_data2;
  atRequest.setCommand(shCmd);  
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  DEBAG.print("SH " );
  DEBAG.println(String(XBee_data2, HEX));
 
  atRequest.setCommand(slCmd);  
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  DEBAG.print("SL " );
  DEBAG.println(String(XBee_data2, HEX));
  
  atRequest.setCommand(MYCmd);  
  sendAtCommand();
  delay(100);
  XBee_data2 = (unsigned long&)info_XBee_data1;
  DEBAG.print("MY ");
  DEBAG.println(String(XBee_data2, HEX));
//
//  myGLCD.setColor(255, 255, 255);
//  yXBee = yXBee + yDelta;                                        // Форматирование текста, смещение
////  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[12])));  // "Network (MY) = "
//  myGLCD.print("OI", LEFT, yXBee);
//  atRequest.setCommand(OICmd);  
//  sendAtCommand();
//  delay(100);
//  XBee_data2 = (unsigned long&)info_XBee_data1;
//  myGLCD.setColor(VGA_YELLOW);
//  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
//
//
//
//  myGLCD.setColor(255, 255, 255);
//  yXBee = yXBee + yDelta;                                        // Форматирование текста, смещение
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[13])));  // "PAN ID (OP)  = "
//  myGLCD.print(buffer, LEFT, yXBee);
//  atRequest.setCommand(opCmd);  
//  sendAtCommand();
//  delay(100);
//  XBee_data2 = (unsigned long&)info_XBee_data1;
//  myGLCD.setColor(VGA_YELLOW);
//  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
//  
//  myGLCD.setColor(255, 255, 255);
//  yXBee = yXBee + yDelta;                                        // Форматирование текста, смещение 
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[14])));  // "ID (ID)      = "
//  myGLCD.print(buffer, LEFT, yXBee);
//  atRequest.setCommand(IDCmd);  
//  sendAtCommand();
//  delay(100);
//  XBee_data2 = (unsigned long&)info_XBee_data1;
//  myGLCD.setColor(VGA_YELLOW);
//  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
//
//  myGLCD.setColor(255, 255, 255);
//  yXBee = yXBee + yDelta;// Форматирование текста, смещение
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[15])));  // "Chanel (CH)  = "
//  myGLCD.print(buffer, LEFT, yXBee);
//  atRequest.setCommand(CHCmd);  
//  sendAtCommand();
//  XBee_data2 = (unsigned long&)info_XBee_data1;
//  myGLCD.setColor(VGA_YELLOW);
//  myGLCD.print("0x",193, yXBee);
//  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
//
//  myGLCD.setColor(255, 255, 255);
//  yXBee = yXBee + yDelta;// Форматирование текста, смещение
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[16])));  
//  myGLCD.print(buffer, LEFT, yXBee);
//  atRequest.setCommand(assocCmd); 
//  sendAtCommand();
//  XBee_data2 = (unsigned long&)info_XBee_data1;
//  myGLCD.setColor(VGA_YELLOW);
//  myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
//
//
//  myGLCD.setColor(255, 255, 255);
//  yXBee = yXBee + yDelta;// Форматирование текста, смещение
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[17])));  
//  myGLCD.print(buffer, LEFT, yXBee);
//  atRequest.setCommand(BDCmd); 
//  sendAtCommand();
//  XBee_data2 = (unsigned long&)info_XBee_data1;
//  myGLCD.setColor(VGA_YELLOW);
//  switch (XBee_data2)
//    {
//    case 0:
//      XBee_data2 = 1200;
//      break;
//    case 1:
//      XBee_data2 = 2400;
//      break;
//    case 2:
//      XBee_data2 = 4800;
//      break;
//    case 3:
//      XBee_data2 = 9600;
//      break;
//    case 4:
//      XBee_data2 = 19200;
//      break;
//    case 5:
//      XBee_data2 = 38400;
//      break;
//    case 6:
//      XBee_data2 = 57600;
//      break;
//    case 7:
//      XBee_data2 = 115200;
//      break;
//      default:
//       XBee_data2 = 000000;
//    }
//
//  myGLCD.print(String(XBee_data2), RIGHT, yXBee);
//
//  myGLCD.setColor(255, 255, 255);
//  yXBee = yXBee + yDelta;// Форматирование текста, смещение
//
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[18])));   // "Volt(V) ";
//  myGLCD.print(buffer, LEFT, yXBee);
//  atRequest.setCommand(VoltCmd);   
//  sendAtCommand();
//  XBee_data2 = (unsigned long&)info_XBee_data1;
//  myGLCD.setColor(VGA_YELLOW);
//  float XBee_data3 = XBee_data2;
//  myGLCD.printNumF(XBee_data3/1000,2, RIGHT, yXBee,'.',2);
//  myGLCD.setColor(255, 255, 255);
//  yXBee = yXBee + yDelta;                                             // Форматирование текста, смещение
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[27])));       // txt_temperature
//  myGLCD.print(buffer, LEFT, yXBee);
//  atRequest.setCommand(TPCmd);                                        // Температура модуля
//  sendAtCommand();
//  delay(100);
//  XBee_data2 = (unsigned long&)info_XBee_data1;
//  myGLCD.setColor(VGA_YELLOW);
//  myGLCD.print(String(XBee_data2, DEC), RIGHT, yXBee);
//
//  myGLCD.setColor(255, 255, 255);
//  yXBee = yXBee + yDelta;                                             // Форматирование текста, смещение
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[75])));       // "TX Power mW"
//  myGLCD.print(buffer, LEFT, yXBee);
//  atRequest.setCommand(PLCmd);                                        // "TX Power mW"
//  sendAtCommand();
//  delay(100);
//  XBee_data2 = (unsigned long&)info_XBee_data1;
//  switch (XBee_data2)
//  {
//  case 0:
//    XBee_data2 = 1;
//    break;
//  case 1:
//    XBee_data2 = 25;
//    break;
//  case 2:
//    XBee_data2 = 100;
//    break;
//  case 3:
//    XBee_data2 = 200;
//    break;
//  case 4:
//    XBee_data2 = 300;
//    break;
//  default:
//    XBee_data2 = 0;
//    break;
//  }
//
//  myGLCD.setColor(VGA_YELLOW);
//  myGLCD.print(String(XBee_data2, DEC), RIGHT, yXBee);
//
//  myGLCD.setColor(0, 0, 255);                                        // Нарисовать прямоугольник для текста
//  myGLCD.fillRoundRect (2, 296, 238, 318);
//  myGLCD.setColor(255, 255, 255);
//  myGLCD.drawRoundRect (2, 296, 238, 318);
//  myGLCD.setBackColor(0, 0, 255);
//  myGLCD.setColor(255, 255, 255);
//  strcpy_P(buffer, (char*)pgm_read_word(&(table_message[19])));
//  myGLCD.print(buffer, CENTER, 299);                                // Завершить просмотр
// 

delay(300);
}

