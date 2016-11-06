/*
����� ������ ���������� ������� �� �������������� ����������,
������� ����� ��������� ������ ���� � ��������������, 
� ����� ���������� ������������� ���������� ������ ��. 
����� ����������� ��������������� ��������������� ������ ����������, ����������, ���������.
���������� ������ ���������� ���������������, �� ���� ����� ������ ����� ��������� ���������� (����� ������� �������������). 
����� ���������� (���� ��������) ������������� �������� rs232 - �� �� � ������ �� �������� 1200���. 
������� ���� � ������ ����. �������� �������� ����� ������������� ��������� ����. 
������������ ��������� ��������� ����, ������������� ����� � �������, ��������� ������.
3.�������������� ����������. ���������� ����������� ���� ���� TQ2 5V, ����������� 100��, ���� ���� TQ2-l2-5V.
������:
1)�����������. ��������� � ������� ��������(���������) � ����� ����, ������� �� ������ � �� �����. TQ2 5V
2)�����������. ��������� � ������� ��������(���������) � ����� ����, ������� �� ������ � �� �����. TQ2 5V

5) �������������. ��� ��������� ���������� � ����� ���������, ���������� ���� �� ������.
��������� � ������� �� ������������ ��������(���������) � ���������� ��������������� ����, ��������������� ������. TQ2-l2-5V 
���������� ����� �� �����������, � ��������������� 5�,

����� ����������� �������, ����� �������� ������ ������������ ����������������� - 0,5 ��� ������ �������. 
�.�. ���������� ����� ��������� ���: 
1. ���������� ���� - ����� ������ - ��� - ����� - ����. ����� ��� ������, ������ "����� 1"  � "����� 2".
2. ���������� ��������������� - ����� "+" - �� ������� �������������� �������� ������, ������������������ 0,5 ������, ���������� (+-), 
����� "-" - �� ������� �������������� �������� ������ � ��������, ������������������ 0,5 ������, ���������� (-+). 
3. ���������� ������� �������, ����������� �� ������ �� ������ "+" � "-" �������, �������� ��������� ��������� "0",
����� ���� ������� ������ "+" - �� �������� "+2", ������ ���� "-" ���� ��� - �� �������� "-3" � ��� �����, ��������� 99 ������ � ������ �������.
�������� �� ������� ��������� �������� ��� ����������/��������� ����� ����� ����������?

������� �� �������������� �������� ������������? ��� 0,5 ������, �� 0,5 �� 20. ��������� ��������� ����, � �� �������.
����� ����� ������� ������� ��� ����������� ������������� ���������� (������������ ������ ��������) - ����� �����������.

���������� 2 �� ����� (������� +- � -+) � 2 �� ����. ��������� ����� �� ������������� (��������� �� ���� � ��������),
��, �����, ���������� �� ���� ���������� ���������� �����. 

������� ����� � ������������� ���������. ����� ����� 0-255. 
����������� � �� ����� ������:
1) ������ ��� ��������� ������ (������������, ��������������)
2)����� ��, ����������/������������� ������, ����� ��������, ���� � ����� ����������, ���� - �������� ������ �������������

�� ������ �� ������  8 ������  (4 -+, 4 ���/����) 

����� ����� ����������? 
���� ������� ������ (������ ��� ��������): ��� ������, ������������/�������������, ����� �������
����� ��������� (������ �������). 
��� ���������� ������� �� ���� ��������? ���� ��, �� ������������� ��������������� �� 00:00 01/01/2001 �� ����� ���������������.

���������� ����� ������� �� ���������� SD ����� � ����������� ������� �� ������������ ����������. 
�������� �� ���������� �������� ��������� �� ����� (�� �� �����), ������������ � ���������� �������, ������������ ������� �� ��?
�� ����� ��� �������� �� �� (��� ���������� ������� �����������?)

����� ����� ������������ � ������ ��  (������������� ����� ������, ����������� ���� - ��� �����).
���� ��� ������� �� ����. ���� � ���� �������� ����� ����.
���������, ����������(����� ��������) � ������� ��������� �������� �� ��.
� ���� �������� - ����������� ����������������  ������� ������ ������ (�������� ������� - ��������, �� �������� - �� ��������).

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


// ����� ����
#define Q1  4               // ���������� ���� 1
#define Q2  5               // ���������� ���� 2  
#define Q3  6               // ���������� ���� 3  
#define Q4  7               // ���������� ���� 4
#define M1_1  A1            // ����� 1-
#define M1_2  A2            // ����� 1+
#define M2_1  A3            // ����� 2-
#define M2_2  A4            // ����� 2+

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

void sl_XBee();
void run_KN1_StatusXBee(byte funcType, word startreg, word numregs); // ����� ����������  � XBee
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs); // ����� ����������   � XBee
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs); // ����� ����������   � XBee
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs); // ����� ����������  � XBee
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs); // ����� ����������   � XBee
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs); // ����� ����������   � XBee
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs); // ����� ����������   � XBee
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs); // ����� ����������   � XBee
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
      //  {
      //    Serial.print("payload [");                   //
      //    Serial.print(i, DEC);                        //
      //    Serial.print("] is ");                       //
      //    Serial.println(rx.getData()[i], HEX);        // ���������� ��������� � rx.getData()[i]
      //  }
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
  funcType = (rx.getData()[0]);
  field1   = (rx.getData()[1] << 8) | rx.getData()[2]; 
  field2   = (rx.getData()[3] << 8) | rx.getData()[4];
//  Serial.println(rx.getData()[0], DEC);                   // ���������� ��������� � rx.getData()[i]
  switch(funcType)                                          // ��������� �������� � ������������ �����
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
  if (xbee.readPacket(500))                                              //  ����� �������� ������� TX, �� ������� ����� �������. ����� �� �������� ������� ��� ������������ ��������� 
    {
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE)      // ������� �����!  ������ ���� znet tx status    
    {
      xbee.getResponse().getZBTxStatusResponse(txStatus);
      if (txStatus.getDeliveryStatus() == SUCCESS)           // �������� ������ ��������, ����� ����
        {
        //  delay(300);
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

void run_KN1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������  � XBee
{
  word val;
  word i = 0;
  payload[0] = funcType;
  flashLed(dataLed, 1, 150); 
  EEPROM.get(address_timeMotor1, val);                      //�������� �� EEPROM ������������ ��������
  digitalWrite(M1_1, LOW);             // ����� 1-
  digitalWrite(M1_2, HIGH);            // ����� 1+
  delay(val);
  digitalWrite(M1_1, LOW);             // ����� 1-
  digitalWrite(M1_2, LOW);             // ����� 1+ 
  increase_counter(1, address_count1); // ����� �������� DataXBee[], ������� 
}
void run_KN2_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������   � XBee
{
  word val;
  word i = 0;
  payload[0] = funcType;
  flashLed(dataLed, 1, 150); 
  EEPROM.get(address_timeMotor1, val);                      //�������� �� EEPROM ������������ ��������
  digitalWrite(M1_1, HIGH);            // ����� 1-
  digitalWrite(M1_2, LOW);             // ����� 1+
  delay(val);
  digitalWrite(M1_1, LOW);             // ����� 1-
  digitalWrite(M1_2, LOW);             // ����� 1+ 
  increase_counter(3, address_count2); // ����� �������� DataXBee[], ������� 
}
void run_KN3_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������   � XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  EEPROM.get(address_timeMotor2, val);                      //�������� �� EEPROM ������������ ��������
  digitalWrite(M2_1, LOW);             // ����� 2-
  digitalWrite(M2_2, HIGH);            // ����� 2+
  delay(val);
  digitalWrite(M2_1, LOW);             // ����� 2-
  digitalWrite(M2_2, LOW);             // ����� 2+ 
  increase_counter(5, address_count3); // ����� �������� DataXBee[], ������� 
}
void run_KN4_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������  � XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150); 
  payload[0] = funcType;
  EEPROM.get(address_timeMotor2, val);                      //�������� �� EEPROM ������������ ��������
  digitalWrite(M2_1, HIGH);            // ����� 2-
  digitalWrite(M2_2, LOW);             // ����� 2+
  delay(val);
  digitalWrite(M2_1, LOW);             // ����� 2-
  digitalWrite(M2_2, LOW);             // ����� 2+ 
  increase_counter(7, address_count4); // ����� �������� DataXBee[], ������� 
}
void run_KN5_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������  � XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  rele1 =  !rele1;
  digitalWrite(Q1, rele1);              // ���������� ���� 1
  increase_counter(9, address_count5);
}
void run_KN6_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������   � XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  rele2 =  !rele2;
  digitalWrite(Q2, rele2);              // ���������� ���� 1
  increase_counter(11, address_count6);
}
void run_KN7_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������   � XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  rele3 =  !rele3;
  digitalWrite(Q3, rele3);              // ���������� ���� 1
  increase_counter(13, address_count7);
}
void run_KN8_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������   � XBee
{
  word val;
  word i = 0;
  flashLed(dataLed, 1, 150);
  payload[0] = funcType;
  rele4 =  !rele4;
  digitalWrite(Q4, rele4);              // ���������� ���� 1
  increase_counter(15, address_count8);
}
void run_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������   � XBee
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
void run_set_time2_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������   � XBee
{
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	EEPROM.put(address_koef_time2, startreg); 
	//byte hi=highByte(startreg);
	//byte low=lowByte(startreg);
	//EEPROM.write(address_koef_time2, hi);
	//EEPROM.write(address_koef_time2+1, low);
}
void motor1_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������  � XBee
{
	flashLed(dataLed, 1, 150);
	payload[0] = funcType;
	EEPROM.put(address_timeMotor1, startreg); 
}
void motor2_set_time1_StatusXBee(byte funcType, word startreg, word numregs) // ����� ����������  � XBee
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
	EEPROM.get(adr_count, count);                      //�������� �� EEPROM ��������� ��������
	count++;
	if(count >=999) count = 999;
	EEPROM.put(adr_count, count);                      //�������� � EEPROM ��������� ��������

	byte hi=highByte(count);
    byte low=lowByte(count);

	payload[dataXBee] = hi;
	payload[dataXBee+1] = low;
}

void set_count(int kn, int adr_count)
{
	int count;
	EEPROM.get(adr_count, count);                      //�������� �� EEPROM ��������� ��������
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
	set_count(17, address_koef_time1);    // ��������1
	set_count(19, address_koef_time2);    // ��������2
	set_count(21, address_timeMotor1 );   //address_timeMotor1           // 
	set_count(23, address_timeMotor2 );   //address_timeMotor2    
 	payload[24] = 0;                      // 
	payload[25] = 0;                      // 
	payload[26] =  rele1;                 // ��������� ���� 1 
	payload[27] =  rele2;                 // ��������� ���� 2
	payload[28] =  rele3;                 // ��������� ���� 3 
	payload[29] =  rele4;                 // ��������� ���� 4 
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
  pinMode(Q1, OUTPUT);                // ���������� ���� 1
  pinMode(Q2, OUTPUT);                // ���������� ���� 2  
  pinMode(Q3, OUTPUT);                // ���������� ���� 3  
  pinMode(Q4, OUTPUT);                // ���������� ���� 4
  pinMode(M1_1, OUTPUT);              // ����� 1-
  pinMode(M1_2, OUTPUT);              // ����� 1+
  pinMode(M2_1, OUTPUT);              // ����� 2-
  pinMode(M2_2, OUTPUT);              // ����� 2+

  digitalWrite(Q1, LOW);              // ���������� ���� 1
  digitalWrite(Q2, LOW);              // ���������� ���� 2  
  digitalWrite(Q3, LOW);              // ���������� ���� 3  
  digitalWrite(Q4, LOW);              // ���������� ���� 4
  digitalWrite(M1_1, LOW);            // ����� 1-
  digitalWrite(M1_2, LOW);            // ����� 1+
  digitalWrite(M2_1, LOW);            // ����� 2-
  digitalWrite(M2_2, LOW);            // ����� 2+
}


  //byte hi=highByte(value);
  //byte low=lowByte(value);

  //// ��� �� ��� hi,low ����� ��������, ��������� �� eePROM

  //int value2=(hi<<8) | low; // �������� ��� "��������� �����������"
  //int value3=word(hi,low); // ��� �������� ��� "����������"

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
	EEPROM.put(address_timeMotor1, timeMotor1);                      //�������� � EEPROM ������������ ��������
	EEPROM.put(address_timeMotor2, timeMotor2);                      //�������� � EEPROM ������������ ��������
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
