#include <XBee.h>



//int adr_zigbee_coordinator_h = 204;       //����� ������������ �������
//int adr_zigbee_coordinator_l = 208;       //����� ������������ �������
//int adr_zigbee_network       = 212;       //����� ����


// ************ ZigBee******************
//������� XBee ����������
XBee xbee = XBee();

//��� ������� ��������� ������� "response" "�����" ������������ ������ Xbee
XBeeResponse response = XBeeResponse();
//��� ������� ��������� ������� "rx" �� ������� Xbee Series 2 API ������
ZBRxResponse rx = ZBRxResponse();
//��� ������� ��������� ������� "msr" ������� associate/disassociate packets (PAN membership)
ModemStatusResponse msr = ModemStatusResponse();

ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();

//������ � �������
uint8_t payload[50] ;// = {3, 4,};
uint8_t payload1[10] ;// = {3, 4,};

//��� 32-������ ��������� th4 64-��������� �����
long XBee_Addr64_MS;// = 0x0013a200;
long XBee_Addr64_LS;// = 0x4054de2d;
//16-��������� �����
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
uint8_t shCmd[] = {'S','H'}; // ������� ���� ������
// serial low
uint8_t slCmd[] = {'S','L'}; // ������� ���� ������
// association status
uint8_t assocCmd[] = {'A','I'}; // ��������� ������������� 
								/*
								��������� ���������� � ��������� ������� ���� �� �������������:
								0x00 � ��������� ������� - ����������� ��������� ����������������/�������� ����������
								���������� � �������������� ������������� ����������.
								0x21 � ������������ �� ���������� ����
								0x22 � ������������ �� ���������� ���������� ���� � �������� ����������� SC � ID
								0x23 � ���������� ����������� ��� �������������� �������, �� ��� �� ���� ���������� ��
								������������� � ���� (������� ����� NJ)
								0x27 � ������� ������������� �� �������
								0x2A � ������ ������������ �� ������
								0xFF � ���� ����� ������������� ����������
								*/
uint8_t irCmd[]    = {'I','R'};
uint8_t opCmd[]    = {'O','P'}; // ����� ���� (PAN ID)
uint8_t IDCmd[]    = {'I','D'}; // ����� ���� (ID)
uint8_t MYCmd[]    = {'M','Y'}; // ����� ���� (16-bit Network Adress
uint8_t CHCmd[]    = {'C','H'}; // ����� �����������
uint8_t SCCmd[]    = {'S','C'}; // Scan Channel
uint8_t BDCmd[]    = {'B','D'}; // �������� ������ (Baud Rate )
uint8_t VoltCmd[]  = {'%','V'}; // ���������� ������� ��������� ���������� �� ������ Vcc. ��� �������������� ��������
								// � ��, �������� �������� �� 1023 � �������� �� 1200. �������� %V ������ 0x8FE (��� 2302 �
								// ���������� ����) ������������� 2700�� ��� 2.70�

uint8_t dhCmd[]    = {'D','H'}; // ������� ���� ������
uint8_t dlCmd[]    = {'D','L'}; // ������� ���� ������
uint8_t d0Cmd[]    = {'D','0'}; //
uint8_t WRCmd[]    = {'W','R'}; // ������ � ������ ����������
								// ����������: ���� ������� ������� WR, �� ��������� ������ "OK\r" �� ������ ��������
								// �������������� ��������
uint8_t FRCmd[]    = {'F','R'}; // ���������� ������������ �����������
uint8_t NRCmd[]    = {'N','R'}; // ���������� ���� 
								// ���� NR = 0: ����������������� ��������� ���� �� ����, ��������� �������. 
								// ���� NR = 1:��������������������������� �������� ��� ����������� ���������� �� ���� ����� ����.
uint8_t d0Value[]  = { 0x2 };
uint8_t irValue[]  = { 0xff, 0xff };
uint8_t IDValue[]  = { 0x02, 0x34 };

uint8_t command[]  = {'I','D'}; // ����� ���� (ID)
uint8_t commandValue[]  = { 0x02, 0x35 };
uint8_t commandValueLength = 0x2 ;

// SH + SL Address of receiving XBee

XBeeAddress64 addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
//��� ������� ��������� ������� "txStatus" ������� ������������� ������� Xbee Series 2 API ������
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
  xbee.readPacket();   // �������� �����
	
	if (xbee.getResponse().isAvailable())  //��������� ������� ������
	  {
		// ���� ���-��
		 //   Serial.println("Got an rx packet8888!");
	  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) 
		  {
			// ������� zb rx packet
		
			// ������ ��������� ��� ����� ZB ��
			xbee.getResponse().getZBRxResponse(rx); // ����� rx ��������
	  
			// Serial.println("Got an rx packet!");
			
			if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) 
				{
					// ����������� �������  ����� ACK
					// Serial.println("packet acknowledged");
				} 
			else 
				{
				   Serial.println("packet not acknowledged");
				}
		
					 //Serial.print("checksum is ");
					 //Serial.println(rx.getChecksum(), HEX);    // ����������� �����

					 //Serial.print("All packet length is ");
					 //Serial.println(rx.getPacketLength(), DEC); // ����� ������ ������ ������
					 //Serial.print("Data packet length is ");
					 //Serial.println(rx.getDataLength(), DEC); // ����� ������ ������ ������

				for (int i = 0; i < rx.getDataLength(); i++)    // ������� ���������� ����� ������  � rx.getDataLength()
				 {
				   //Serial.print("payload [");                   //
				   //Serial.print(i, DEC);                        //
				   //Serial.print("] is ");                       //
				   //Serial.println(rx.getData()[i], HEX);        // ���������� ��������� � rx.getData()[i]
				  }
		
				for (int i = 0; i < xbee.getResponse().getFrameDataLength(); i++) // ����� ������ � xbee.getResponse().getFrameDataLength()
				   {
					 //Serial.print("frame data [");                                //  frame data � 0 �� 7 ��������� ����� �����������
					 //Serial.print(i, DEC);
					 //Serial.print("] is ");                                       //
					 //Serial.println(xbee.getResponse().getFrameData()[i], HEX);   //  ���������� ������ � xbee.getResponse().getFrameData()[i], ����� ������ 
				   }
				Serial.println();
					//�������� ������� 32-������ ����� 64-������ �����.  64-������ ����� 802.15.4 MAC ����� ��������� 
					// ���� ����� (��������, "���������").
					XBee_Addr64_MS=(uint32_t(rx.getFrameData()[0]) << 24) + (uint32_t(rx.getFrameData()[1]) << 16) + (uint16_t(rx.getFrameData()[2]) << 8) + rx.getFrameData()[3];
					//�������� ���� 32-������ �����...
					XBee_Addr64_LS=(uint32_t(rx.getFrameData()[4]) << 24) + (uint32_t(rx.getFrameData()[5]) << 16) + (uint16_t(rx.getFrameData()[6]) << 8) + rx.getFrameData()[7];
					//��������� ��� ����� ������ ������������ ����������� ����������������� �����
					/*Serial.print("Addr64 MS: ");
					Serial.print(XBee_Addr64_MS,HEX);
					Serial.print('\n');
					Serial.print("Addr64 LS: ");
					Serial.print(XBee_Addr64_LS,HEX);
					Serial.print('\n');
					Serial.println();*/
							// IP-������ � TCP/IP. 
					XBee_Addr16=rx.getRemoteAddress16();
					/*Serial.print("Addr16: ");
					Serial.println(XBee_Addr16,HEX);
*/



		   }
	  sl_XBee();
	  } 

	 else if (xbee.getResponse().isError()) //  ������ ������
		{
		  // Serial.print("error code:");
		  // Serial.println(xbee.getResponse().getErrorCode());            // ��� ������ xbee.getResponse().getErrorCode()
		}
}

 void sl_XBee()// ����������� ����� ������������ 
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
// #define READ_ELECTRO          0x01  // ������ �� ������ � �������� XBee
// #define READ_GAZ		         0x02  // ������ �� ������ � �������� XBee
// #define READ_COLWATER 	     0x03  // ������ �� ������ � �������� XBee
// #define READ_HOTWATER	     0x04  // ������ �� ������ � �������� XBee
// #define READ_WAR_GAZ	         0x05  // ������ �� ������ � �������� XBee
// #define READ_WAR_TEMPERATURA  0x06  // ������ �� ������ � �������� XBee

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
  //��������� 10-������ ���  � ��� ����� � ��������� � �������� ��������
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

	 //  ����� �������� ������� TX, �� ������� ����� �������
	 //  ����� �� �������� ������� ��� ������������ ��������� 
 ZigBeeRead();
  if (xbee.readPacket(500))
	   // xbee.readPacket();
	  {
	  
		// ������� �����! 
		// ������ ���� znet tx status            	
		if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) 
			{
			  xbee.getResponse().getZBTxStatusResponse(txStatus);
			   // �������� ������ ��������, ����� ����
			  if (txStatus.getDeliveryStatus() == SUCCESS)
				  {
					  // �������, ����� ����������.
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
					// ����������� XBee �� �������. �� �������?
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

	                myGLCD.clrScr();   // �������� ����� CENTER
					myGLCD.setColor(0, 0, 255);
					myGLCD.fillRoundRect (2, 2, 318, 25);
					myGLCD.setColor(255, 255, 255);
					myGLCD.drawRoundRect (2, 2, 318, 25);
					myGLCD.setColor(255, 255, 255);
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("Setup XBee", CENTER, 5);
					myGLCD.print(txt_return, CENTER, 218);// ��������� �������� 
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
						if ((x>=2) && (x<=319))  // �����
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
	 //��������� �������������� ������ ZigBee �� ������.
		   byte y[4];   ; //������ �� ������ ������� ������ �������� ������ ������������
				y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_zigbee_coordinator_h);
				y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_zigbee_coordinator_h);
				y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_zigbee_coordinator_h);
				y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_zigbee_coordinator_h);
				XBee_Addr64_MS = (unsigned long&) y;  // ������� ��������������� ������� ������

		//	   y[4];   ; //������ �� ������ ������� ������ �������� ������ ������������
				y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_zigbee_coordinator_l);
				y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_zigbee_coordinator_l);
				y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_zigbee_coordinator_l);
				y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_zigbee_coordinator_l);
				XBee_Addr64_LS = (unsigned long&) y;  // ������� ��������������� ������� ������ � 
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
