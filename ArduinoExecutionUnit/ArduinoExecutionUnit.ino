/*
����� ������ ���������� ������� �� �������������� ����������,
������� ����� ��������� ������ ���� � ��������������, 
� ����� ���������� ������������� ���������� ������ ��. 
����� ����������� ��������������� ��������������� ������ ����������, ����������, ���������.
���������� ������ ���������� ���������������, �� ���� ����� ������ ����� ��������� ���������� (����� ������� �������������). 
����� ���������� (���� ��������) ������������� �������� rs232 - �� �� � ������ �� �������� 1200���. 
������� ���� � ������ ����. �������� �������� ����� ������������� ��������� ����. 
(�������� �������� � ���������� ����������� ���������).
������������ ��������� ��������� ����, ������������� ����� � �������, ��������� ������.
3.�������������� ����������. ���������� ����������� ���� ���� TQ2 5V, ����������� 100��, ���� ���� TQ2-l2-5V.
������:
1)�����������. ��������� � ������� ��������(���������) � ����� ����, ������� �� ������ � �� �����. TQ2 5V
2)�����������. ��������� � ������� ��������(���������) � ����� ����, ������� �� ������ � �� �����. TQ2 5V
3) ������� �������� ����������������� �� ��������. ��������� � ������� ��������(���������) � ������ ����, ������� �� ������ � �� ������. �������� 100��
4) ������� �������� ����������������� �� ��������. ��������� � ������� ��������(���������) � ������ ����, ������� �� ������ � �� ������. �������� 100��
5) �������������. ��� ��������� ���������� � ����� ���������, ���������� ���� �� ������.
��������� � ������� �� ������������ ��������(���������) � ���������� ��������������� ����, ��������������� ������. TQ2-l2-5V 
���������� ����� �� �����������, � ��������������� 5�,

����� ����������� �������, ����� �������� ������ ������������ ����������������� - 0,5 ��� ������ �������. 
�.�. ���������� ����� ��������� ���: 
1. ���������� ���� - ����� ������ - ��� - ����� - ����. ����� ��� ������, ������ "����� 1"  � "����� 2".
2.���������� ��������������� - ����� "+" - �� ������� �������������� �������� ������, ������������������ 0,5 ������, ���������� (+-), 
����� "-" - �� ������� �������������� �������� ������ � ��������, ������������������ 0,5 ������, ���������� (-+). 
3. ���������� ������� �������, ����������� �� ������ �� ������ "+" � "-" �������, �������� ��������� ��������� "0",
����� ���� ������� ������ "+" - �� �������� "+2", ������ ���� "-" ���� ��� - �� �������� "-3" � ��� �����, ��������� 99 ������ � ������ �������.
�������� �� ������� ��������� �������� ��� ����������/��������� ����� ����� ����������?

������� �� �������������� �������� ������������? ��� 0,5 ������, �� 0,5 �� 20. ��������� ��������� ����, � �� �������.
����� ����� ������� ������� ��� ����������� ������������� ���������� (������������ ������ ��������) - ����� �����������.

���������� 2 �� ����� (������� +- � -+) � 2 �� ����. ��������� ����� �� ������������� (��������� �� ���� � ��������),
��, �����, ���������� �� ���� ���������� ���������� �����. 


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

int Len_XBee = 0;
unsigned char info_XBee_data[10];
unsigned char info_XBee_data1[10];
unsigned long XBee_data2;
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
  xbee.readPacket();   // �������� �����
	if (xbee.getResponse().isAvailable())  //��������� ������� ������
	  {
		// ���� ���-��
	  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) 
		  {
			// ������ ��������� ��� ����� ZB ��
			xbee.getResponse().getZBRxResponse(rx); // ����� rx ��������, ������� zb rx packet
			// Serial.println("Got an rx packet!");
			if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) 
				{
					// ����������� �������  ����� ACK
					// Serial.println("packet acknowledged");
				}  
			else 
				{
				   //Serial.println("packet not acknowledged");
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
				//	flashLed(dataLed, 10, 500);
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
	field1	= (rx.getData()[1] << 8) | rx.getData()[2];
	field2  = (rx.getData()[3] << 8) | rx.getData()[4];
	Serial.println(funcType);
	Serial.println(field1);
	Serial.println(field2);
	//generate query response based on function type
	switch(funcType)   // ��������� �������� � ������������ �����
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
 XBeeRead();
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
					// ����������� XBee �� �������. �� �������?
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
	 ////��������� �������������� ������ ZigBee �� ������.
		//   byte y[4];   ; //������ �� ������ ������� ������ �������� ������ ������������
		//		y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_zigbee_coordinator_h);
		//		y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_zigbee_coordinator_h);
		//		y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_zigbee_coordinator_h);
		//		y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_zigbee_coordinator_h);
		//		XBee_Addr64_MS = (unsigned long&) y;  // ������� ��������������� ������� ������

		////	   y[4];   ; //������ �� ������ ������� ������ �������� ������ ������������
		//		y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_zigbee_coordinator_l);
		//		y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_zigbee_coordinator_l);
		//		y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_zigbee_coordinator_l);
		//		y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_zigbee_coordinator_l);
		//		XBee_Addr64_LS = (unsigned long&) y;  // ������� ��������������� ������� ������ � 
}

void run_KN1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;

	 payload[0] = funcType;
	flashLed(dataLed, startreg, numregs);
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;
	flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;
	flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;
	flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;
	flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;
	 flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;
	 flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;
	 flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 //payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	 //payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

 }
void run_set_time2_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, startreg, numregs);
	payload[0] = funcType;
	//payload[1] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro);
	//payload[2] = i2c_eeprom_read_byte( deviceaddress,adr_n_str_electro+1);

}
void run_set_time3_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
