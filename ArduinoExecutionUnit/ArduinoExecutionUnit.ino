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
#include <SoftwareSerial.h>
#include <EEPROM.h>                   // �������� � �������. ��������� ������ 100 ����� ����������.

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

XBee xbee               = XBee();                           //������� XBee ����������
XBeeResponse response   = XBeeResponse();                   //��� ������� ��������� ������� "response" "�����" ������������ ������ Xbee
ZBRxResponse rx         = ZBRxResponse();                   //��� ������� ��������� ������� "rx" �� ������� Xbee Series 2 API ������
ModemStatusResponse msr = ModemStatusResponse();            //��� ������� ��������� ������� "msr" ������� associate/disassociate packets (PAN membership)

ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();

//������ � �������
uint8_t payload[30];                                        // = {3, 4,};

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
  xbee.readPacket();                                             // �������� �����
	if (xbee.getResponse().isAvailable())                        //��������� ������� ������
	  {
	  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)       // ���� ���-��
		  {
			xbee.getResponse().getZBRxResponse(rx);              //  ������ ��������� ��� ����� ZB ��  ����� rx ��������, ������� zb rx packet
			if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED)        // ����������� �������  ����� ACK
				{
					 Serial.println("packet acknowledged");
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
				//�������� ������� 32-������ ����� 64-������ �����.  64-������ ����� 802.15.4 MAC ����� ��������� 
			//for (int i = 0; i < rx.getDataLength(); i++)       // ������� ���������� ����� ������  � rx.getDataLength()
			//	{
			//		Serial.print("payload [");                   //
			//		Serial.print(i, DEC);                        //
			//		Serial.print("] is ");                       //
			//		Serial.println(rx.getData()[i], HEX);        // ���������� ��������� � rx.getData()[i]
			//	}
			    XBee_Addr64_MS=(uint32_t(rx.getFrameData()[0]) << 24) + (uint32_t(rx.getFrameData()[1]) << 16) + (uint16_t(rx.getFrameData()[2]) << 8) + rx.getFrameData()[3];
				//�������� ���� 32-������ �����...
				XBee_Addr64_LS=(uint32_t(rx.getFrameData()[4]) << 24) + (uint32_t(rx.getFrameData()[5]) << 16) + (uint16_t(rx.getFrameData()[6]) << 8) + rx.getFrameData()[7];
				//��������� ��� ����� ������ ������������ ����������� ����������������� �����
				XBee_Addr16=rx.getRemoteAddress16();                  // IP-������ � TCP/IP. 
				//Serial.println(XBee_Addr64_MS, HEX); 
    //            Serial.println(XBee_Addr64_LS, HEX); 
				addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
		   }
	  sl_XBee();
	  } 
	 else if (xbee.getResponse().isError())                            //  ������ ������
		{
		   Serial.print("error code:");
		   Serial.println(xbee.getResponse().getErrorCode());            // ��� ������ xbee.getResponse().getErrorCode()
		}
}
void sl_XBee()                                              // ����������� ����� ������������ 
 {
    //copy the function type from the incoming query
	funcType = (rx.getData()[0]);
	field1	 = (rx.getData()[1] << 8) | rx.getData()[2]; 
	field2   = (rx.getData()[3] << 8) | rx.getData()[4];
//	Serial.println(rx.getData()[0], DEC);                   // ���������� ��������� � rx.getData()[i]
	switch(funcType)                                        // ��������� �������� � ������������ �����
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
  if (xbee.readPacket(500))    	                                         //  ����� �������� ������� TX, �� ������� ����� �������. ����� �� �������� ������� ��� ������������ ��������� 
	  {
		if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE)      // ������� �����!  ������ ���� znet tx status    
		{
			xbee.getResponse().getZBTxStatusResponse(txStatus);
			if (txStatus.getDeliveryStatus() == SUCCESS)		    	 // �������� ������ ��������, ����� ����
				{
				//	delay(300);
				}
			else 
				{
					 Serial.println("Error reading packet.  Error code: 1");  
					 flashLed(errorLed, 10, 100);                         // ����������� XBee �� �������. �� �������?
				}
		}
	  }
  else if (xbee.getResponse().isError())
	  {
		   Serial.println("Error reading packet.  Error code: 2");  
		   flashLed(errorLed, 10, 100);                                   // ����������� XBee �� �������. �� �������?
	  } 
  else 
	  {
		  Serial.println("Error reading packet.  Error code: 3");  
			flashLed(errorLed, 10, 100);                                  // ����������� XBee �� �������. �� �������?
			delay(200); 
	  }
  delay(500);
}

void run_KN1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
void run_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
 {
	 word val;
	 word i = 0;
	 flashLed(dataLed, 1, 150);
	 payload[0] = funcType;
	 payload[1] = 0;
	 payload[2] = 9;
	 payload[29] = 2;
 }
void run_set_time2_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
{
	word val;
	word i = 0;
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	payload[1] = 0;
	payload[2] = 10;
	payload[29] = 2;
}
void run_set_time3_StatusXBee(byte funcType, word startreg, word numregs) // ����� ���������� electro � XBee
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
