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

XBee xbee               = XBee();                           //������� XBee ����������
XBeeResponse response   = XBeeResponse();                   //��� ������� ��������� ������� "response" "�����" ������������ ������ Xbee
ZBRxResponse rx         = ZBRxResponse();                   //��� ������� ��������� ������� "rx" �� ������� Xbee Series 2 API ������
ModemStatusResponse msr = ModemStatusResponse();            //��� ������� ��������� ������� "msr" ������� associate/disassociate packets (PAN membership)

ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();

//������ � �������
uint8_t payload[50];                                        // = {3, 4,};
uint8_t payload1[10];                                       // = {3, 4,};

//��� 32-������ ��������� th4 64-��������� �����
long XBee_Addr64_MS;                                        // = 0x0013a200;
long XBee_Addr64_LS;                                        // = 0x4054de2d;
int XBee_Addr16;                                            // = 0xffff   //16-��������� �����

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
ZBTxStatusResponse txStatus = ZBTxStatusResponse();                    //��� ������� ��������� ������� "txStatus" ������� ������������� ������� Xbee Series 2 API ������

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
  xbee.readPacket();                                             // �������� �����
	if (xbee.getResponse().isAvailable())                        //��������� ������� ������
	  {
	  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)       // ���� ���-��
		  {
			xbee.getResponse().getZBRxResponse(rx);              //  ������ ��������� ��� ����� ZB ��  ����� rx ��������, ������� zb rx packet
			if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED)        // ����������� �������  ����� ACK
				{
					// Serial.println("packet acknowledged");
				}  
			else 
				{
				   //Serial.println("packet not acknowledged");
				}
				Serial.print("checksum is ");
				Serial.println(rx.getChecksum(), HEX);    // ����������� �����
				Serial.print("All packet length is ");
				Serial.println(rx.getPacketLength(), DEC); // ����� ������ ������ ������
				Serial.print("Data packet length is ");
				Serial.println(rx.getDataLength(), DEC); // ����� ������ ������ ������
				for (int i = 0; i < rx.getDataLength(); i++)       // ������� ���������� ����� ������  � rx.getDataLength()
				{
					Serial.print("payload [");                   //
					Serial.print(i, DEC);                        //
					Serial.print("] is ");                       //
					Serial.println(rx.getData()[i], HEX);        // ���������� ��������� � rx.getData()[i]
				}
				//for (int i = 0; i < xbee.getResponse().getFrameDataLength(); i++) // ����� ������ � xbee.getResponse().getFrameDataLength()
				//{
				//	Serial.print("frame data [");                                //  frame data � 0 �� 7 ��������� ����� �����������
				//	Serial.print(i, DEC);
				//	Serial.print("] is ");                                       //
				//	Serial.println(xbee.getResponse().getFrameData()[i], HEX);     //  ���������� ������ � xbee.getResponse().getFrameData()[i], ����� ������ 
				//}
				//�������� ������� 32-������ ����� 64-������ �����.  64-������ ����� 802.15.4 MAC ����� ��������� 
				XBee_Addr64_MS=(uint32_t(rx.getFrameData()[0]) << 24) + (uint32_t(rx.getFrameData()[1]) << 16) + (uint16_t(rx.getFrameData()[2]) << 8) + rx.getFrameData()[3];
				//�������� ���� 32-������ �����...
				XBee_Addr64_LS=(uint32_t(rx.getFrameData()[4]) << 24) + (uint32_t(rx.getFrameData()[5]) << 16) + (uint16_t(rx.getFrameData()[6]) << 8) + rx.getFrameData()[7];
				//��������� ��� ����� ������ ������������ ����������� ����������������� �����
				XBee_Addr16=rx.getRemoteAddress16();                  // IP-������ � TCP/IP. 
				//flashLed(dataLed, 5, 250);
		   }
	  sl_XBee();
	  } 
	 else if (xbee.getResponse().isError())                            //  ������ ������
		{
		  // Serial.print("error code:");
		  // Serial.println(xbee.getResponse().getErrorCode());            // ��� ������ xbee.getResponse().getErrorCode()
		}
}
void sl_XBee()                                              // ����������� ����� ������������ 
 {
    //copy the function type from the incoming query
	funcType = (rx.getData()[0]);
	field1	 = (rx.getData()[1] << 8) | rx.getData()[2];
	field2   = (rx.getData()[3] << 8) | rx.getData()[4];
	Serial.println(rx.getData()[0], HEX);        // ���������� ��������� � rx.getData()[i]
	switch(funcType)                                        // ��������� �������� � ������������ �����
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
  xbee.send(zbTx);
  if (xbee.readPacket(500))    	                                        //  ����� �������� ������� TX, �� ������� ����� �������. ����� �� �������� ������� ��� ������������ ��������� 
	  {
		if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE)     // ������� �����!  ������ ���� znet tx status    
		{
			xbee.getResponse().getZBTxStatusResponse(txStatus);
			if (txStatus.getDeliveryStatus() == SUCCESS)		    	// �������� ������ ��������, ����� ����
				{
					//flashLed(statusLed, 5, 50);                         // �������, ����� ����������.
					delay(300);
				}
			else 
				{
					flashLed(errorLed, 3, 100);                         // ����������� XBee �� �������. �� �������?
				}
		}
	  }
  else if (xbee.getResponse().isError())
	  {
		  flashLed(errorLed, 3, 100);                                   // ����������� XBee �� �������. �� �������?
	  } 
  else 
	  {
			flashLed(errorLed, 3, 100);                                  // ����������� XBee �� �������. �� �������?
			delay(200); 
	  }
  delay(1000);
}

void run_KN1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	payload[0] = funcType;

	flashLed(dataLed, 1, 300);
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
	payload[48] = 255;  // FF
	payload[49] = 8;    // 08
}
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	payload[0] = funcType;
	flashLed(dataLed, 2, 300);
	payload[1] = 0;
	payload[2] = 2;
	payload[23] = 2;
	payload[24] = 2;
	payload[25] = 2;
	payload[26] = 2;
}
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 3, 300);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 3;
	payload[23] = 3;
	payload[24] = 3;
	payload[25] = 3;
	payload[26] = 3;
}
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 4, 300);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 4;
	payload[23] = 4;
	payload[24] = 4;
	payload[25] = 4;
	payload[26] = 4;
}
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 5, 300);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 5;
	payload[4] = 5;
	payload[5] = 5;
	payload[6] = 5;
	payload[7] = 5;
}
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 6, 300);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 6;
}
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 7, 300);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 7;
}
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 8, 300);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 8;
}
void run_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;
	// flashLed(dataLed, startreg, numregs);
	 payload[0] = funcType;
	 payload[1] = 0;
	 payload[2] = 9;
 }
void run_set_time2_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	//flashLed(dataLed, startreg, numregs);
	payload[0] = funcType;
	payload[1] = 1;
	payload[2] = 1;
}
void run_set_time3_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	//flashLed(dataLed, startreg, numregs);
	payload[0] = funcType;
	payload[1] = 1;
	payload[2] = 2;
}




void set_pin()
{
	pinMode(led_13, OUTPUT);                             //
	digitalWrite(led_13, HIGH);                          //
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
