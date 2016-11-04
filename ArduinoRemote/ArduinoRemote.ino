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




*/


#include <Wire.h>
#include <RTClib.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <UTFT.h>
#include <UTouch.h>
#include <UTFT_Buttons.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <XBee.h>
#include <EEPROM.h>
//#include <OneWire.h>



#define led_13 13  
#define KN1 A8   
#define KN2 A9  
#define KN3 A7 
#define KN4 A10  
#define KN5 A4  
#define KN6 A6  
#define KN7 A3  
#define KN8 A5 
int statusLed = 13;
int errorLed = 13;
int N_KN = 0;

bool count1 = false;
bool count2 = false;
bool count3 = false;
bool count4 = false;
bool count5 = false;
bool count6 = false;
bool count7 = false;
bool count8 = false;

//********************* ��������� �������� ***********************************
UTFT          myGLCD(ITDB24E_8, 38, 39, 40, 41);        // ������� 2.4" !! ��������! �������� ��������� UTouchCD.h
UTouch        myTouch(6, 5, 4, 3, 2);                   // Standard Arduino Mega/Due shield            : 6,5,4,3,2
UTFT_Buttons  myButtons(&myGLCD, &myTouch);             // Finally we set up UTFT_Buttons :)

boolean default_colors = true;                          //
uint8_t menu_redraw_required = 0;
// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];
extern uint8_t SmallSymbolFont[];
//+++++++++++++++++++++++++++++ ������� ������ +++++++++++++++++++++++++++++++++++++++
int deviceaddress        = 80;                          // ����� ���������� ������
unsigned int eeaddress   =  0;                          // ����� ������ ������

//+++++++++++++++++++++++++++ ��������� ����� +++++++++++++++++++++++++++++++
uint8_t second = 0;                                    //Initialization time
uint8_t minute = 10;
uint8_t hour   = 10;
uint8_t dow    = 2;
uint8_t day    = 15;
uint8_t month  = 3;
uint16_t year  = 16;
const char* str1[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int oldsec     = 0;
unsigned long timeF;
int flag_time = 0;
int x_delta = 8;                                     // �������� ��������� �� � � ����� setTimeDate.ino

RTC_DS1307 RTC;                                       // define the Real Time Clock object
//**************************** ������ **********************************************************

int  stCurrentLen_pass = 0;              // ����� �������� ������
char pass_super_admin[8] = {'1', '4', '0', '7','5','4','\0'}; // ������ ����� �����.
char pass_admin[20] ;                     //������ � ������� �����
char pass_user[20];                       // ������ � ������� ������������
int pass = 0;                             // ������� ������������ ���������� ������ ������
int pass1 = 0;                            // ������� ������������ ���������� ������ ������������
int pass2 = 0;                            // ������� ������������ ���������� ������ �����
int pass3 = 0;                            // ������� ������������ ���������� ������ ����� �����
int eeprom_clear = 0;
int stCurrentLen_user=0;                  // ����������  �������� ����� ��������� ������ ������ ������������
int stCurrentLen_admin=0;                 // ����������  �������� ����� ��������� ������ ������ ��������������

//++++++++++++++++++++++++++++ ���������� ��� �������� ���������� +++++++++++++++++++++++++++++
int x, y, z;
char stCurrent[20]    = "";                                       // ���������� �������� ��������� ������
int stCurrentLen      = 0;                                        // ���������� �������� ����� ��������� ������
int stCurrentLen1     = 0;                                        // ���������� ���������� �������� ����� ��������� ������
char stLast[20]       = "";                                       // ������ � ��������� ������ ������.
char temp_stLast[20];                                             // ���������� ��� ���������� �������� ���������� ������= stLast
int ret               = 0;                                        // ������� ���������� ��������
int lenStr            = 8;                                        // ����� ������ XBee
int count_s           = 0;                                        // ������� ��������� �������� 

int x_dev = 16;
int y_dev = 16;
//-------------------------------------------------------------------------------------------------
float power60 = 0;                       // ��������� ��������� ������� 6,0 �����
float power50 = 0;                       // ��������� ��������� ������� 5,0 �����
float power33 = 0;                       // ��������� ��������� ������� 3,3 �����
unsigned long currentTime;
unsigned long loopTime;
int time_power    = 1000;

//---------------------------------------------------------------------------------
//int adr_xbee_coordinator_h   = 104;       // ����� ������������ �������
//int adr_xbee_coordinator_l   = 108;       // ����� ������������ �������

int adr_pass_user            = 8;         // ����� ������ ������������
int adr_stCurrentLen1        = 92;        // ����� ��������� ����� ������
int adr_xbee_device_h        = 112;       // ����� ���������� �������
int adr_xbee_device_l        = 116;       // ����� ���������� �������
int adr_pass_admin           = 118;       // ����� ������ ��������������
int adr_xbee_network         = 120;       // ����� ����
int adr_xbee_current_H       = 124;       // ����� �������� ���������� �������
int adr_xbee_current_L       = 128;       // ����� �������� ���������� �������
int adr_n_user               = 140;       // ����� �������� � ������ ������������

int adr_start_baseHL         = 1000;      // ��������� ����� ���� ������ ������� �������������� ���������
byte number_device           = 0;         // ����� ��������������� ����������. 


//----------------------------------------------------------------------

const char  txt_botton_otmena[]                PROGMEM  = "O""\xA4\xA1""e""\xA2""a";                            // "������"
const char  txt_botton_vvod[]                  PROGMEM  = "B\x97o\x99 ";                                        // "����"
const char  txt_botton_ret[]                   PROGMEM  = "B""\xAB""x""o\x99" ;                                 // "�����"
const char  txt_perepolnenie[]                 PROGMEM  = "\x89""EPE""\x89O\x88HEH\x86""E!" ;                   // "������������"
const char  txt_empty[]                        PROGMEM  = "\x80\x8A\x8B\x8B""EP \x89\x8A""CTO\x87!";            // "������ ������"
const char  txt_menu1[]                        PROGMEM  = "MEH""\x94"" 1";                                      // "������������"
const char  txt_menu2[]                        PROGMEM  = "MEH""\x94"" 2";                                      // "������ ������"
const char  txt_info_XBee_ALL[]                PROGMEM = "\x86\xA2\xA5o XBee";                                  // ���� XBee
const char  txt_info_XBee_USB[]                PROGMEM = "o\xA4\xA3p""a""\x97\xA0""e""\xA2""a"" USB port";      //
const char  txt_info_XBee_MY[]                 PROGMEM = "Network Address MY";                                  //
const char  txt_info_XBee_CoordinatorAdr[]     PROGMEM = "A\x99""pec ""\xA3""y""\xA0\xAC\xA4""a";               // ����� ������
const char  txt_info_XBee_Serial[]             PROGMEM = "A\x99""pec ""\x86\x8A N";                             // ����� ��
const char  txt_info_XBee_Network_Address[]    PROGMEM = "Network(MY)";                                         // ����� ���� 16 ���
const char  txt_info_XBee_Operating_PAN_OP[]   PROGMEM = "PAN ID (OP)";                                         // ����� ����
const char  txt_info_XBee_Operating_ID[]       PROGMEM = "ID (ID)";                                             //
const char  txt_info_XBee_Chanel_CH[]          PROGMEM = "Chanel (CH)";                                         // ����� ������
const char  txt_info_XBee_Association[]        PROGMEM = "Assoc (AI)";                                          //
const char  txt_info_XBee_Baud_Rate[]          PROGMEM = "Baud(BD)";                                            //
const char  txt_info_XBee_Voltage []           PROGMEM = "Volt(V) ";                                            // ���������� ������ XBee
const char  txt_return[]                       PROGMEM = "B""\x91""XO""\x82";                                   // �����
const char  txt_XBee_Set[]                     PROGMEM = "Hac""\xA4""po""\x9E\x9F""a XBee";                     // ��������� XBee
const char  txt_err_pass_user[]                PROGMEM = "O\xA8\x9D\x96ka \x97\x97o\x99""a" ;                   // ������ �����
const char  txt_menu2_1[]                      PROGMEM = "\x86H\x8BO XBee";                                     // ���� XBee
const char  txt_menu2_2[]                      PROGMEM = "Coordinator SH";                                      //
const char  txt_menu2_3[]                      PROGMEM = "Coordinator SL";                                      // 
const char  txt_menu2_4[]                      PROGMEM = "Network";                                             //
const char  txt_SetAddress[]                   PROGMEM = "Set Addrress";                                        //
const char  txt_temperature[]                  PROGMEM = "Te""\xA1\xA3""epa""\xA4"".C";                         // ����������� �
const char  txt_view_device1[]                 PROGMEM = "A\x99""peca";                                         // ������ 
const char  txt_view_device2[]                 PROGMEM = "yc""\xA4""po""\x9E""c""\xA4\x97";                     // ���������
const char  txt_Set_device[]                   PROGMEM = "\x89""o""\x99\x9F\xA0\xAE\xA7\x9D\xA4\xAC"" ""\x86\x8A"; // ���������� ��
const char  txt_null[]                         PROGMEM = "===========";                                         // "==============="
const char  txt_reset_count[]                  PROGMEM = "C""\x96""poc c""\xA7""e""\xA4\xA7\x9D\x9F""a";        // ����� ��������
const char  txt_reset_count1[]                 PROGMEM = "C""\x80""POC";                                        // �����
const char  txt_set_date1[]                    PROGMEM = "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC";         // ����������
const char  txt_set_date2[]                    PROGMEM = "\x82""a""\xA4""y ""\x9D"" ""\x97""pe""\xA1\xAF";      // ���� � ����� 
const char  txt_menu1_41[]                     PROGMEM = "Hac""\xA4""po""\x9E\x9F""a";                          // ���������
const char  txt_menu1_42[]                     PROGMEM = "c""\x9D""c""\xA4""e""\xA1\xAB";                       // �������
const char  txt_menu4_11[]                     PROGMEM = "C\x96poc \x99""a""\xA2\xA2\xABx";                     // ����� ������
const char  txt_menu4_12[]                     PROGMEM = " ";                     //  
const char  txt_menu4_21[]                     PROGMEM = "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC"" N";     // ���������� N
const char  txt_menu4_22[]                     PROGMEM = "\xA3""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAF";// ������������
const char  txt_menu4_31[]                     PROGMEM = "\x89""apo\xA0\xAC";                                   // ������
const char  txt_menu4_32[]                     PROGMEM = "Me""\xA2\xAE";                                        // ����
const char  txt_menu4_41[]                     PROGMEM = "\xA5""a""\x9E\xA0""o""\x97";                          // ������ 
const char  txt_menu4_42[]                     PROGMEM = "a""\x99\xA1\x9D\xA2\x9D""c""\xA4""pa""\xA4""opa";     // ��������������







char  txt9[6] = "B\x97o\x99"; //����
char  txt10[8] = "O""\xA4\xA1""e""\xA2""a"; //"������"
char  txt11[4] = "RET";
char  txt12[] = "B\x97""e\x99\x9D\xA4""e \xA3""apo\xA0\xAC!";//"������� ������"
char  txt_pass_ok[] = "\xA3""apo\xA0\xAC OK!"; // ������ ��!
char  txt_pass_no[] = "\xA3""apo\xA0\xAC NO!"; // ������ NO!
char  txt_botton_clear[] = "C\x96poc";         // �����
char  txt_system_clear1[] = "B\xA2\x9D\xA1""a\xA2\x9D""e!"; //�������� !  
char  txt_system_clear2[] = "Bc\xAF \xA1\xA2\xA5op\xA1""a""\xA6\xA1\xAF \x96y\x99""e\xA4";  // ��� ���������� ����� 
char  txt_system_clear3[] = "\x8A\x82""A""\x88""EHA!"; // ������� 
char  txt_n_user[] = "B\x97""e\x99\x9D\xA4""e N \xA3o\xA0\xAC\x9C."; // ������� � �����.
char  txt_rep_user[] = "\x89o\x97\xA4op\x9D\xA4""e"" N \xA3o\xA0\xAC\x9C.  "; //��������� � �����.
char  txt_set_pass_user[] = "Ho\x97\xAB\x9E \xA3""apo\xA0\xAC \xA3o\xA0\xAC\x9C.";  //      "����� ������ �����."
char  txt_set_pass_admin[] = "Ho\x97\xAB\x9E \xA3""apo\xA0\xAC  a\x99\xA1\x9D\xA2.";// ����� ������ �����.
char  txt_rep_pass_user[] = "\x89o\x97\xA4op \xA3""apo\xA0\xAC \xA3o\xA0\xAC\x9C."; //   "������ ������ �����."
char  txt_err_pass_user1[] = "O\xA8\x9D\x96ka \x97\x97o\x99""a" ;//������ �����
char  txt_rep_pass_admin[] = "\x89o\x97\xA4op \xA3""apo\xA0\xAC a\x99\xA1\x9D\xA2."; //   "������ ������ �����"


char buffer[30];
const char* const table_message[] PROGMEM =
{
 txt_botton_otmena,                // 0 "O""\xA4\xA1""e""\xA2""a";                                               // "������"
 txt_botton_vvod,                  // 1 "B\x97o\x99 ";                                                           // "����"
 txt_botton_ret,                   // 2  "B""\xAB""x";                                                           // "���"
 txt_perepolnenie,                 // 3 "\x89""EPE""\x89O\x88HEH\x86""E!"                                        // "������������"
 txt_empty,                        // 4 "\x80\x8A\x8B\x8B""EP \x89\x8A""CTO\x87!"                                // "������ ������"
 txt_menu1,                        // 5 "MEH""\x94"" 1";                                                         // "���� 1"
 txt_menu2,                        // 6 "MEH""\x94"" 2";                                                         // "���� 2"
 txt_info_XBee_ALL,                // 7 "\x86\xA2\xA5op\xA1""a""\xA6\x9D\xAF XBee";                              // ���������� XBee
 txt_info_XBee_USB,                // 8 "o\xA4\xA3p""a""\x97\xA0""e""\xA2""a"" USB port";                        //
 txt_info_XBee_MY,                 // 9 "Network Address MY";                                                    //
 txt_info_XBee_CoordinatorAdr,     // 10 "Addr Coordinat";                                                       //
 txt_info_XBee_Serial,             // 11 "Number SH,SL"                                                          //
 txt_info_XBee_Network_Address,    // 12 "Network (MY) = ";//
 txt_info_XBee_Operating_PAN_OP,   // 13 "PAN ID (OP)  = ";//
 txt_info_XBee_Operating_ID,       // 14 "ID (ID)      = ";//
 txt_info_XBee_Chanel_CH,          // 15 "Chanel (CH)";//
 txt_info_XBee_Association,        // 16 "Association(AI)";//
 txt_info_XBee_Baud_Rate,          // 17 "Baud Rate(BD)";//
 txt_info_XBee_Voltage,            // 18 "Voltage (%V) =";//
 txt_return,                       // 19 "B""\x91""XO""\x82";                                                     // �����
 txt_XBee_Set,                     // 20 "Hac""\xA4""po""\x9E\x9F""a XBee";                                       // ��������� XBee
 txt_err_pass_user,                // 21 "O\xA8\x9D\x96ka \x97\x97o\x99""a" ;                                     // ������ �����
 txt_menu2_1,                      // 22 "\x86H\x8BO XBee";                                                       // ���� XBee
 txt_menu2_2,                      // 23 "Coord SH";                                                              //
 txt_menu2_3,                      // 24 "Coord SL";                                                              // 
 txt_menu2_4,                      // 25 "Network";                                                               //
 txt_SetAddress,                   // 26 "Set Addrress";                                                          //
 txt_temperature,                  // 27 "Te""\xA1\xA3""epa""\xA4""ypa C";                                        // ����������� �
 txt_view_device1,                 // 28 "A\x99""peca yc""\xA4""po""\x9E""c""\xA4\x97";                           // ������
 txt_view_device2,                 // 29 "yc""\xA4""po""\x9E""c""\xA4\x97";                                       // ���������
 txt_Set_device,                   // 30 "\x89""o""\x99\x9F\xA0\xAE\xA7\x9D\xA4\xAC"" ""\x86\x8A";                // ���������� ��
 txt_null,                         // 31 "===========";                                                           // "==============="
 txt_reset_count,                  // 32 "C""\x96""poc""\x9D\xA4\xAC"" c""\xA7""e""\xA4\xA7\x9D\x9F";             // ����� ��������
 txt_reset_count1,                 // 33 "C""\x96""poc";                                                          // �����
 txt_set_date1,                    // 34 "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC";                           // ����������
 txt_set_date2,                    // 35 "\x82""a""\xA4""y ""\x9D"" ""\x97""pe""\xA1\xAF";                        // ���� � ����� 
 txt_menu1_41,                     // 36 "Hac""\xA4""po""\x9E\x9F""a";                                            // ���������
 txt_menu1_42,                     // 37 "c""\x9D""c""\xA4""e""\xA1\xAB";                                         // �������
 txt_menu4_11,                     // 38 "C\x96poc \x99""a""\xA2\xA2\xABx";                                       // ����� ������
 txt_menu4_12,                     // 39 "C\x96poc \x99""a""\xA2\xA2\xABx";                                       // ����� ������
 txt_menu4_21,                     // 40  "\x8A""c""\xA4""a""\xA2""o""\x97\x9D\xA4\xAC"" N";                      // ���������� N
 txt_menu4_22,                     // 41 "\xA3""o""\xA0\xAC\x9C""o""\x97""a""\xA4""e""\xA0\xAF";                  // ������������
 txt_menu4_31,                     // 42 "\x89""apo\xA0\xAC";                                                     // ������
 txt_menu4_32,                     // 43 "Me""\xA2\xAE";                                                          // ���� 
 txt_menu4_41,                     // 44 "\xA5""a""\x9E\xA0""o""\x97";                                            // ������         
 txt_menu4_42                      // 45 "a""\x99\xA1\x9D\xA2\x9D""c""\xA4""pa""\xA4""opa";                       //  ��������������
};

//++++++++++++++++++++++ ������ � ������� +++++++++++++++++++++++++++++++++++++++
//#define chipSelect SS
#define chipSelect 53                                             // ��������� ������ SD
SdFat sd;
File myFile;
SdFile file;
Sd2Card card;
uint32_t cardSizeBlocks;
uint16_t cardCapacityMB;

// cache for SD block
cache_t cache;
 
//------------------------------------------------------------------------------
// ������� ����������, ������������ ������� ���������� SD utility library functions: +++++++++++++++
// Change spiSpeed to SPI_FULL_SPEED for better performance
// Use SPI_QUARTER_SPEED for even slower SPI bus speed
const uint8_t spiSpeed = SPI_HALF_SPEED;


//++++++++++++++++++++ ���������� ����� ����� ++++++++++++++++++++++++++++++++++++++++++++
//const uint32_t FILE_BLOCK_COUNT = 256000;
// log file base name.  Must be six characters or less.
#define FILE_BASE_NAME "160101"
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[13]            = FILE_BASE_NAME "00.KAM";
char fileName_p[13];
char fileName_F[13];

//*********************������ � ������ ����� ******************************

//byte file_name_count = 0;
char str_day_file[3];
char str_day_file0[3];
char str_day_file10[3];
char str_mon_file[3];
char str_mon_file0[3];
char str_mon_file10[3];
char str_year_file[3];

//char str0_1[10];
char str1_1[10];
char str2_1[10];









void txt_pass_no_all();
void pass_test_start();
void pass_test();
void drawButtons1();
void klav123();
void pass_start();

void flashLed(int pin, int times, int wait);
void dateTime(uint16_t* date, uint16_t* time);

void serial_print_date();
void clock_read();
void set_time();
void drawGlavMenu();
void klav_Glav_Menu();
void wiev_count(int num);
void test_power();
void drawButtons0_1();
void drawButtonsExit();
void drawButtonsXBee();
void klav1();
void klavXBee();

void draw_menu1();
void draw_menu2();
void draw_menu3();
void klav_menu1();
void klav_menu2();
void klav_menu3();






// ************ XBee******************

XBee xbee = XBee();                                   //������� XBee ����������

// ++++++++++  ��������� ��� ������ � �������� ������ +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

XBeeResponse response = XBeeResponse();               //��� ������� ��������� ������� "response" "�����" ������������ ������ Xbee
ZBRxResponse rx = ZBRxResponse();                     //��� ������� ��������� ������� "rx" �� ������� Xbee Series 2 API ������
ModemStatusResponse msr = ModemStatusResponse();      //��� ������� ��������� ������� "msr" ������� associate/disassociate packets (PAN membership)
ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();


//������ � �������
uint8_t payload[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//uint8_t payload1[10] ;// = {3, 4,};

int XBee_Addr16;                            //16-��������� �����
int Len_XBee = 0;
unsigned char info_XBee_data[10];
unsigned char info_XBee_data1[10];
char* simbol_ascii[2];
char   cmd;

uint8_t shCmd[] = {'S','H'};                // serial high ������� ���� ������ ���� ������������ �����
uint8_t slCmd[] = {'S','L'};                // serial low ������� ���� ������ ���� ������������ �����
uint8_t assocCmd[] = {'A','I'};             // association status ��������� ������������� 
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
uint8_t opCmd[]    = {'O','P'};             // ����� ���� (PAN ID)
uint8_t IDCmd[]    = {'I','D'};             // ����� ���� (ID)
uint8_t OICmd[]    = {'O','I'};             // Operating 16-bit PAN ID(OI)
uint8_t MYCmd[]    = {'M','Y'};             // ����� ���� (16-bit Network Adress
uint8_t CHCmd[]    = {'C','H'};             // ����� �����������
uint8_t SCCmd[]    = {'S','C'};             // Scan Channel
uint8_t BDCmd[]    = {'B','D'};             // �������� ������ (Baud Rate )
uint8_t VoltCmd[]  = {'%','V'};             // ���������� ������� ��������� ���������� �� ������ Vcc. ��� �������������� ��������
											// � ��, �������� �������� �� 1023 � �������� �� 1200. �������� %V ������ 0x8FE (��� 2302 �
											// ���������� ����) ������������� 2700�� ��� 2.70�
uint8_t TPCmd[]    = {'T','P'};             // �����������
uint8_t dhCmd[]    = {'D','H'};             // ������� ���� ������
uint8_t dlCmd[]    = {'D','L'};             // ������� ���� ������
uint8_t d0Cmd[]    = {'D','0'};             //
uint8_t WRCmd[]    = {'W','R'};             // ������ � ������ ����������
											// ����������: ���� ������� ������� WR, �� ��������� ������ "OK\r" �� ������ ��������
											// �������������� ��������
uint8_t FRCmd[]    = {'F','R'};             // ���������� ������������ �����������
uint8_t NRCmd[]    = {'N','R'};             // ���������� ���� 
											// ���� NR = 0: ����������������� ��������� ���� �� ����, ��������� �������. 
											// ���� NR = 1:��������������������������� �������� ��� ����������� ���������� �� ���� ����� ����.
uint8_t d0Value[]  = { 0x2 };
uint8_t irValue[]  = { 0xff, 0xff };
uint8_t IDValue[]  = { 0x02, 0x34 };

uint8_t command[]  = {'I','D'};              // ����� ���� (ID)
uint8_t commandValue[]  = { 0x02, 0x35 };
uint8_t commandValueLength = 0x2 ;



//��� 32-������ ��������� th4 64-��������� �����
long XBee_Addr64_MS = 0 ; //0x0013a200;
long XBee_Addr64_LS = 0 ; //0x40672567;

//��� 32-������ ��������� th4 64-��������� �����
long XBee_Addr64_MS_tmp = 0;                    //
long XBee_Addr64_LS_tmp = 0;                    //

XBeeAddress64 addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);                                     // SH + SL Address of receiving XBee
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));                                         // ��������� �����  zbTx � ������� ����������� � �������
ZBTxStatusResponse txStatus = ZBTxStatusResponse();                                                       // ��� ������� ��������� ������� "txStatus" ������� ������������� ������� Xbee Series 2 API ������
AtCommandRequest atRequest = AtCommandRequest(shCmd);                                                     // XBeeAddress64 remoteAddress = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
AtCommandRequest arRequestMod = AtCommandRequest(command,commandValue, commandValueLength); 
AtCommandResponse atResponse = AtCommandResponse();
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(addr64, irCmd, irValue, sizeof(irValue)); // Create a remote AT request with the IR command
RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();                                     // Create a Remote AT response object


//********************************
byte funcType;
word field1;
word field2;
byte *_msg, _len;
word _baud, _crc;

//-----------------------------------------------------------------------------------------------

//---------------  ������ --------------------------
void txt_pass_no_all()
{
		myGLCD.clrScr();
		myGLCD.setColor(255, 255, 255);
		myGLCD.setBackColor(0, 0, 0);
		myGLCD.print(txt_pass_no, RIGHT, 208);
		delay (1000);
}
void pass_test_start() // ������ �������� ������
{  
		myGLCD.setFont(BigFont);
		myGLCD.setBackColor(0, 0, 255);
		myGLCD.clrScr();
		drawButtons1();
			// ����� ������ "������� ������!"
		myGLCD.setColor(255, 0, 0);
		myGLCD.print(txt12, CENTER, 280);// ������� ������!"
		delay(300);
		myGLCD.print("                   ", CENTER, 280);
		delay(300);
		myGLCD.print(txt12, CENTER, 280);// ������� ������!"

}
void pass_test()
{
	pass=0;
	pass1=0;
	pass2=0;
	pass3=0;
	
			//������� ������ pass_user �� ������
			int  stCurrentLen_pass_user = i2c_eeprom_read_byte( deviceaddress,adr_pass_user-2);  //������� ����� ������  �� ������
			//	Serial.print("stCurrentLen_pass - ");// �������� ������ -�������
			//  Serial.println(stCurrentLen_pass);// �������� ������ -�������
			
		// if ((stCurrentLen_pass == 0) stCurrentLen_pass_user = 1))
			
				for (int z=0; z<stCurrentLen_pass_user; z++)
				{
					pass_user[z] = i2c_eeprom_read_byte( deviceaddress,adr_pass_user+z);
				}
				pass_user[stCurrentLen_pass_user]  =  '\0';  
	
			// �������� ������ ������������
				if(strcmp(pass_user,stLast)==0)
				{
					pass1 = 1;
					//  pass2 = 0;
					//  pass3 = 0;
				}
				if(strcmp(pass_user,stLast)!=0)
				{
					pass1 = 0;
				}
			// ��������� �������� ������ ������������
	

			//�������������� ����� ������ ������ ��������������
			int stCurrentLen_pass_admin = i2c_eeprom_read_byte( deviceaddress,adr_pass_admin-2);  //������� ����� ������  �� ������
			// �������������� ������ ��������������
			for (int z=0; z<stCurrentLen_pass_admin; z++)
			{
				pass_admin[z] = i2c_eeprom_read_byte( deviceaddress,adr_pass_admin+z);
			}
			pass_admin[stCurrentLen_pass_admin]  =  '\0';  

			// �������� ������ �������������� 
				if(strcmp(pass_admin,stLast)==0)
				{
					//  pass1 = 0;
					pass2 = 1;
					// pass3 = 0;
				}
				if(strcmp(pass_admin,stLast)!=0)
				{
					pass2 = 0;
				}

	// ��������� �������� ������ ��������������

		// �������� ������ ����� �������������� 

				if(strcmp(pass_super_admin,stLast)==0)
				{
					// pass1 = 0;
					// pass2 = 0;
					pass3 = 1;

				}
				if(strcmp(pass_super_admin,stLast)!=0)
				{
					pass3 = 0;
				}

				// ��������� �������� ������ ����� ��������������
	
			if (( pass1 == 1) || ( pass2 == 1)|| ( pass3 == 1))

				{
					pass = 1;
				}
				else
				{
					pass = 0;
				}
		  
	//  }
/*
	Serial.print("pass1 - ");// �������� ������ -�������
	Serial.println(pass1);// �������� ������ -�������
	Serial.print("pass2 - ");// �������� ������ -�������
	Serial.println(pass2);// �������� ������ -�������
	Serial.print("pass3 - ");// �������� ������ -�������
	Serial.println(pass3);// �������� ������ -�������
	Serial.print("pass_admin - ");// �������� ������ -�������
	Serial.println(pass_admin);// �������� ������ -�������
	Serial.print("stLast - ");// �������� ������ -�������
	Serial.println(stLast);// �������� ������ -�������
	Serial.print("pass_super_admin - ");// �������� ������ -�������
	Serial.println(pass_super_admin);// �������� ������ -�������
	Serial.print("ret - ");// �������� ������ -�������
	Serial.println(ret);// �������� ������ -�������
*/
}
void drawButtons1() // ����������� �������� ����������
{

	drawButtons0_1();
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 121, 234, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 121, 234, 176);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[1])));
	myGLCD.print(buffer, 145, 141);                                 // "����"
 
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5, 179, 118, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 179, 118, 234);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[0])));
	myGLCD.print(buffer, 14, 199);                                   // "������"

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 179, 234, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 179, 234, 234);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
	myGLCD.print(buffer, 137, 199);                                  // ���
	myGLCD.setBackColor (0, 0, 0);
}
void klav123() // ���� ������ � �������� ����������
{
	ret = 0;
	int x,y;
	while (true)
	  {
		if (myTouch.dataAvailable())
		{
		  myTouch.read();
		  x = myTouch.getX();
		  y = myTouch.getY();
		  if ((y >= 5) && (y <= 60))                                    // ������ ���
		  {
		   if ((x >= 5) && (x <= 60))                                   // Button: 1
			{
			  waitForIt(5, 5, 60, 60);
			  updateStr('1');
			}
			if ((x >= 63) && (x <= 118))                                // Button: 2
			{
			  waitForIt(63, 5, 118, 60);
			  updateStr('2');
			}
			if ((x >= 121) && (x <= 176))                               // Button: 3
			{
			  waitForIt(121, 5, 176, 60);
			  updateStr('3');
			}
			if ((x >= 179) && (x <= 234))                               // Button: 4
			{
			  waitForIt(179, 5, 234, 60);
			  updateStr('4');
			}
		  }

		  if ((y >= 63) && (y <= 118))                                  // ������ ���
		  {
		   if ((x >= 5) && (x <= 60))                                   // Button: 5
			{
			  waitForIt(5, 63, 60, 118);
			  updateStr('5');
			}
			if ((x >= 63) && (x <= 118))                                // Button: 6
			{
			  waitForIt(63, 63, 118, 118);
			  updateStr('6');
			}
			if ((x >= 121) && (x <= 176))                               // Button: 7
			{
			  waitForIt(121, 63, 176, 118);
			  updateStr('7');
			}
			if ((x >= 179) && (x <= 234))                               // Button: 8
			{
			  waitForIt(179, 63, 234, 118);
			  updateStr('8');
			}
		  }

		  if ((y >= 121) && (y <= 176))                                 // ������ ���
		  {
		   if ((x >= 5) && (x <= 60))                                   // Button: 9
			{
			  waitForIt(5, 121, 60, 176);
			  updateStr('9');
			}
			if ((x >= 63) && (x <= 118))                                // Button: 0
			{
			  waitForIt(63, 121, 118, 176);
			  updateStr('0');
			}
			if ((x >= 121) && (x <= 234))                               // Button: "����"
			{
			  waitForIt(121, 121, 234, 176);
			   if (stCurrentLen > 0)
			   {
				for (int x = 0; x < stCurrentLen + 1; x++)
				{
				  stLast[x] = stCurrent[x];
				}
				stCurrent[0] = '\0';
				stLast[stCurrentLen + 1] = '\0';
				stCurrentLen1 = stCurrentLen;
				stCurrentLen = 0;
				myGLCD.setColor(0, 0, 0);
				myGLCD.fillRect(0, 300, 239, 319);
				myGLCD.setColor(0, 255, 0);
				myGLCD.print(stLast, LEFT, 300);
				break;
			  }
			  else
			  {
				myGLCD.setColor(0, 0, 0);
				myGLCD.fillRect(0, 300, 239, 319);
				myGLCD.setColor(255, 0, 0);
				strcpy_P(buffer, (char*)pgm_read_word(&(table_message[4])));
				myGLCD.print(buffer, CENTER, 300);                                  //"������ ������!"
				delay(500);
				myGLCD.print("                ", CENTER, 300);
				delay(500);
				myGLCD.print(buffer, CENTER, 300);                                 //"������ ������!"
				delay(500);
				myGLCD.print("                ", CENTER, 300);
				myGLCD.setColor(0, 255, 0);
			  }
			}
		  }

		  if ((y >= 179) && (y <= 234))                                           // ��������� ���
		  {
			if ((x >= 5) && (x <= 118))                                           // Button: "������"
			{
			  waitForIt(5, 179, 118, 234);
			  stCurrent[0] = '\0';
			  stCurrentLen = 0;
			  myGLCD.setColor(0, 0, 0);
			  myGLCD.fillRect(0, 300, 239, 319);                                   // �������� ������ �� �������
			}
			if ((x >= 121) && (x <= 234)) // Button: "�����"
			{
			  waitForIt(121, 179, 234, 234);
			 //myGLCD.clrScr();
			  //myGLCD.setBackColor(VGA_BLACK);
			  //ret = 1;
			  stCurrent[0] = '\0';
			  stCurrentLen = 0;
			  break;
			}
		  }
		}
	  }
} 
void pass_start()
{
	while(1) 
	{
		pass_test_start();                // ���������� �������� ����������
		klav123();                        // ������� ���������� � ����������
		if (ret == 1)                     // ���� "�������" - ���������
		{
			goto bailout11;               // ������� �� ��������� ���������� ������ ����
		}
		else                              // ����� ��������� ����� ����
		{
			pass_test();                  // ��������� ������
		}
		if ( ( pass1 == 1)||( pass2 == 1) || ( pass3 == 1)) // ���� ����� - ��������� ����� ����
		{
			myGLCD.clrScr();              // �������� �����
			myGLCD.print(txt_pass_ok, RIGHT, 208); 
			delay (500);
			return;
		}
		else                              // ������ �� ������ - ��������
		{
			txt_pass_no_all();
		}

		bailout11:                       // ������������ ������ ����
		myGLCD.clrScr();
		myButtons.drawButtons();
	};
}


//**************************************************
void flashLed(int pin, int times, int wait) {

  for (int i = 0; i < times; i++) {
	digitalWrite(pin, HIGH);
	delay(wait);
	digitalWrite(pin, LOW);

	if (i + 1 < times) {
	  delay(wait);
	}
  }
}

void dateTime(uint16_t* date, uint16_t* time)                                    // ��������� ������ ������� � ���� �����
{
  DateTime now = RTC.now();

  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(now.year(), now.month(), now.day());

  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

void serial_print_date()                           // ������ ���� � �������
{
  DateTime now = RTC.now();
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print("  ");
  Serial.println(str1[now.dayOfWeek()]);
}
void clock_read()
{
  DateTime now = RTC.now();
  second = now.second();
  minute = now.minute();
  hour   = now.hour();
  dow    = now.dayOfWeek();
  day    = now.day();
  month  = now.month();
  year   = now.year();
}
void set_time()
{
  RTC.adjust(DateTime(__DATE__, __TIME__));
  DateTime now = RTC.now();
  second = now.second();       //Initialization time
  minute = now.minute();
  hour   = now.hour();
  day    = now.day();
  day++;
  if (day > 31)day = 1;
  month  = now.month();
  year   = now.year();
  DateTime set_time = DateTime(year, month, day, hour, minute, second); // ������� ������ � ������� � ������ "set_time"
  RTC.adjust(set_time);
}
void drawGlavMenu()
{
	myGLCD.clrScr();
	myGLCD.setBackColor( 0, 0, 255);

	myGLCD.setColor(0, 0, 255);                       //1
	myGLCD.fillRoundRect (5, 5, 94, 90);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 5,94, 90);
	//myGLCD.printNumI(1, 10, 10);                   //"1"
	myGLCD.print("+ 1", 10, 10); 


	
	myGLCD.setColor(0, 0, 255);                      //3
	myGLCD.fillRoundRect (97, 5, 186, 90);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (97, 5, 186, 90);
//	myGLCD.printNumI(3, 102, 10);                   //"3"
	myGLCD.print("+ 3", 102, 10);    

	myGLCD.setColor(0, 0, 255);                     //2
	myGLCD.fillRoundRect (5, 93, 94, 178);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 93,94, 178);
	//myGLCD.printNumI(2, 10, 98);                  //"2"
	myGLCD.print("- 2", 10, 98);    

	myGLCD.setColor(0, 0, 255);                     //4
	myGLCD.fillRoundRect (97, 93, 186, 178);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (97, 93, 186, 178);
	//myGLCD.printNumI(4, 102, 98);                 //"4"
	myGLCD.print("- 4", 102, 98);                   //"4"

//------------------------------------------------------------------

	myGLCD.setColor(0, 0, 255);                    //1
	myGLCD.fillRoundRect (5, 183, 60, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 183, 60, 243);
	myGLCD.printNumI(5, 25-x_dev, 205-y_dev);                   //"1"
	
	myGLCD.setColor(0, 0, 255);                    //2
	myGLCD.fillRoundRect (63, 183, 118, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 183, 118, 243);
	myGLCD.printNumI(6, 83-x_dev, 205-y_dev);                   //"2"

	myGLCD.setColor(0, 0, 255);                    //3
	myGLCD.fillRoundRect (121, 183, 176, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 183, 176, 243);
	myGLCD.printNumI(7, 141-x_dev, 205-y_dev);                  //"3"

	myGLCD.setColor(0, 0, 255);                      //4
	myGLCD.fillRoundRect (179, 183, 234, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 183, 234, 243);
	myGLCD.printNumI(8, 199-x_dev, 205-y_dev);                  //"4"


	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5, 248, 118, 293);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 248, 118, 293);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[5])));
	myGLCD.print(buffer, 16, 262);                                      // "�����"

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 248, 234, 293);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 248, 234, 293);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[6])));
	myGLCD.print(buffer, 130, 262);                                     //"�����"
	
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (194, 70, 234, 110);
	myGLCD.setBackColor (0, 0, 0);
}
void klav_Glav_Menu()
{
	int x,y;
	drawGlavMenu();
	while (true)
	{
		clock_read();
		if (oldsec != second)
		{
			test_power();
			if( second==0)
			{
				myGLCD.setColor(0, 0, 0);
				myGLCD.fillRoundRect (80, 300, 108, 319);
				myGLCD.fillRoundRect (200, 300, 239, 319);
			}
			myGLCD.setColor(255, 255, 255);
			myGLCD.setBackColor (0, 0, 0);
			myGLCD.setFont(SmallFont);
			String print_data = String(day)+'/'+ String(month)+'/'+ String(year);
			myGLCD.print(print_data,6, 303);                                           //Data
			myGLCD.setFont(BigFont);
			String print_time = String(hour)+':'+ String(minute)+':'+ String(second);
			myGLCD.print(print_time,110, 300);                                         //�����
			oldsec = second;
		}

		if(digitalRead(KN1) == false)
		{
			N_KN = 1;
			waitForStart(5, 5, 94, 90);
			myGLCD.printNumI(1, 208, 51);
			payload[0] = 0x01;
			//payload[1] = 0x00;
			//payload[2] = 0x0A;
			//payload[3] = 0x00;
			//payload[4] = 0x1F;

			XBeeWrite();
		}
		if(digitalRead(KN2) == LOW)
		{
			N_KN = 2;
			waitForStart(5, 93, 94, 178);
			myGLCD.printNumI(2, 208, 51);
			payload[0] = 0x02;
			//payload[1] = 0x00;
			//payload[2] = 0x0A;
			//payload[3] = 0x00;
			//payload[4] = 0x1F;
			XBeeWrite();
		}
		if(digitalRead(KN3) == LOW)
		{
			N_KN = 3;
			waitForStart(97, 5, 186, 90);
			myGLCD.printNumI(3, 208, 51);
			payload[0] = 0x03;
			//payload[1] = 0x00;
			//payload[2] = 0x0A;
			//payload[3] = 0x00;
			//payload[4] = 0x1F;
			XBeeWrite();
		}
		if(digitalRead(KN4) == LOW)
		{
			N_KN = 4;
			waitForStart(97, 93, 186, 178);
			myGLCD.printNumI(4, 208, 51);
			payload[0] = 4;
			//payload[1] = 0x00;
			//payload[2] = 0x0A;
			//payload[3] = 0x00;
			//payload[4] = 0x1F;
			XBeeWrite();
		}
		if(digitalRead(KN5) == false)
		{
			N_KN = 5;
			waitForStart(5, 183, 60, 243);
			myGLCD.printNumI(5, 208, 51);
			payload[0] = 5;
			//payload[1] = 0x00;
			//payload[2] = 0x0A;
			//payload[3] = 0x00;
			//payload[4] = 0x1F;
			XBeeWrite();
		}
		if(digitalRead(KN6) == LOW)
		{
			N_KN = 6;
			waitForStart(63, 183, 118, 243);
			myGLCD.printNumI(6, 208, 51);
			payload[0] = 6;
			//payload[1] = 0x00;
			//payload[2] = 0x0A;
			//payload[3] = 0x00;
			//payload[4] = 0x1F;
			XBeeWrite();
		}
		if(digitalRead(KN7) == LOW)
		{
			N_KN = 7;
			waitForStart(121, 183, 176, 243);
			myGLCD.printNumI(7, 208, 51);
			payload[0] = 7;
			//payload[1] = 0x00;
			//payload[2] = 0x0A;
			//payload[3] = 0x00;
			//payload[4] = 0x1F;
			XBeeWrite();
		}
		if(digitalRead(KN8) == LOW)
		{
			N_KN = 8;
			waitForStart(179, 183, 234, 243);
			myGLCD.printNumI(8, 208, 51);
			payload[0] = 8;
			//payload[1] = 0x00;
			//payload[2] = 0x0A;
			//payload[3] = 0x00;
			//payload[4] = 0x1F;
			XBeeWrite(); 
		}

		if (myTouch.dataAvailable())
		{
		  myTouch.read();
		  x = myTouch.getX();
		  y = myTouch.getY(); 

		  if ((y >= 5) && (y <= 90))                                    // ������ ���
		  {
		   if ((x >= 5) && (x <= 94))                                   // Button: 1
			{
				waitForStart(5, 5, 94, 90);
				N_KN = 1;
				myGLCD.printNumI(1, 208, 51);
				payload[0] = 1;
				//payload[1] = 0x00;
				//payload[2] = 0x0A;
				//payload[3] = 0x00;
				//payload[4] = 0x1F;
				XBeeWrite();
			}
			if ((x >= 97) && (x <= 186))                                // Button: 3
			{
				waitForStart(97, 5, 186, 90);
				N_KN = 3;
				myGLCD.printNumI(3, 208, 51);
				payload[0] = 3;
				//payload[1] = 0x00;
				//payload[2] = 0x0A;
				//payload[3] = 0x00;
				//payload[4] = 0x1F;
				XBeeWrite();
			}
		  }
	 
		  if ((y >= 93) && (y <= 178))                                    // ������ ���
		  {
		   if ((x >= 5) && (x <= 94))                                   // Button: 2
			{
				waitForStart(5, 93, 94, 178);
				N_KN = 2;
				myGLCD.printNumI(2, 208, 51);
				payload[0] = 2;
				//payload[1] = 0x00;
				//payload[2] = 0x0A;
				//payload[3] = 0x00;
				//payload[4] = 0x1F;
				XBeeWrite();
			}
			if ((x >= 97) && (x <= 186))                                // Button: 4
			{
				waitForStart(97, 93, 186, 178);
				N_KN = 4;
				myGLCD.printNumI(4, 208, 51);
				payload[0] = 4;
				//payload[1] = 0x00;
				//payload[2] = 0x0A;
				//payload[3] = 0x00;
				//payload[4] = 0x1F;
				XBeeWrite();
			}
		  }
	 
		  if ((y >= 183) && (y <= 243))                                    //  ���
		  {
		   if ((x >= 5) && (x <= 60))                                   // Button: 5
			{
				waitForStart(5, 183, 60, 243);
				N_KN = 5;
				myGLCD.printNumI(5, 208, 51);
				payload[0] = 5;
				//payload[1] = 0x00;
				//payload[2] = 0x0A;
				//payload[3] = 0x00;
				//payload[4] = 0x1F;
				XBeeWrite();
			}
			if ((x >= 63) && (x <= 118))                                // Button: 6
			{
				waitForStart(63, 183, 118, 243);
				N_KN = 6;
				myGLCD.printNumI(6, 208, 51);
				payload[0] = 6;
				//payload[1] = 0x00;
				//payload[2] = 0x0A;
				//payload[3] = 0x00;
				//payload[4] = 0x1F;
				XBeeWrite();
			}
			if ((x >= 121) && (x <= 176))                               // Button: 7
			{
				waitForStart(121, 183, 176, 243);
				N_KN = 7;
				myGLCD.printNumI(7, 208, 51);
				payload[0] = 7;
				//payload[1] = 0x00;
				//payload[2] = 0x0A;
				//payload[3] = 0x00;
				//payload[4] = 0x1F;
				XBeeWrite();
			}
			if ((x >= 179) && (x <= 234))                               // Button: 8
			{
				waitForStart(179, 183, 234, 243);
				N_KN = 8;
				myGLCD.printNumI(8, 208, 51);
				payload[0] = 8;
				//payload[1] = 0x00;
				//payload[2] = 0x0A;
				//payload[3] = 0x00;
				//payload[4] = 0x1F;
				XBeeWrite();
			}
		  }

		  if ((y >= 248) && (y <= 293))                                // ��������� ���
		  {
			if ((x >= 5) && (x <= 118))                                // Button: ���� 1
			{
			  waitForIt(5, 248, 118, 293);
			  klav_menu1();
			}
			if ((x >= 121) && (x <= 234))                              // Button: ���� 2
			{
			  waitForIt(121, 248, 234, 293);
			  klav_menu2();
			}
		  }
		}
	XBeeRead();
	wiev_count(N_KN);
	//XBeeRead();
	//myGLCD.setColor(255, 255, 255);
	//myGLCD.setBackColor( 0, 0, 255);
	//Serial.println(rx.getData()[11],HEX);
	//myGLCD.printNumI(rx.getData()[11], 10+33, 10+40); 
	//myGLCD.printNumI(2, 10+33, 98+40);
	//myGLCD.printNumI(rx.getData()[13], 102+33, 10+40);    
	//myGLCD.printNumI(4, 102+33, 98+40);      
	//myGLCD.printNumI(5, 25 , 205+10 );   
	//myGLCD.printNumI(6, 83 , 205+10 );    
	//myGLCD.printNumI(7, 141, 205+10 );       
	//myGLCD.printNumI(8, 199, 205+10 ); 
	}
}
void wiev_count(int num)
{
//	XBeeRead();
	myGLCD.setColor(255, 255, 255);
	myGLCD.setBackColor( 0, 0, 255);


//	Serial.println(rx.getData()[11],HEX);

	switch(num)                                        //generate query response based on function type
	{
	case 1:
		myGLCD.printNumI(rx.getData()[11], 10+33, 10+40); 
		break;
	case 2:
		myGLCD.printNumI(rx.getData()[11], 10+33, 10+40); 
		break;
	case 3:
		myGLCD.printNumI(rx.getData()[13], 102+33, 10+40);    
		break;
	case 4:
		myGLCD.printNumI(rx.getData()[13], 102+33, 10+40);     
		break;
	case 5:
		myGLCD.printNumI(rx.getData()[15], 25 , 205+10 );   
		break;
	case 6:
		myGLCD.printNumI(rx.getData()[16], 83 , 205+10 ); 
		break;
	case 7:
		myGLCD.printNumI(rx.getData()[17], 141, 205+10 );       
		break;
	case 8:
		myGLCD.printNumI(rx.getData()[18], 199, 205+10 ); 
		break;
	default:
		break;
	}



}
void test_power()
{
  currentTime = millis();                           // ��������� �����, ��������� � ������� ������� ���������
  if (currentTime >= (loopTime + time_power))
  { // ���������� ������� ������ � ���������� loopTime + 1 �������
	loopTime = currentTime;                          // � loopTime ���������� ����� ��������
	myGLCD.setFont(SmallFont);
	myGLCD.setColor(0, 255, 0);
	myGLCD.setBackColor( 0, 0, 0);
	int power = analogRead(A11);
	// Serial.println(power);
	power60 = power * (5.0 / 1024.0 * 2*0.965);
	//  Serial.println(power60);
	if (power60 > 5.8) myGLCD.print("\xB0", 221, 5);
	else if (power60 <= 5.8 && power60 > 5.6) myGLCD.print("\xB1", 212, 5);
	else if (power60 <= 5.6 && power60 > 5.4) myGLCD.print("\xB2", 212, 5);
	else if (power60 <= 5.4 && power60 > 5.2) myGLCD.print("\xB3", 212, 5);

	else if (power60 <= 5.2)
	{
	  myGLCD.setColor(255, 0, 0);
	  myGLCD.print("\xB4", 212, 5);
	}
	myGLCD.printNumF(power60, 2, 200, 20);
	myGLCD.setColor(255, 255, 255);
	power = analogRead(A1);
	power50 = power * (5.0 / 1024.0*2*0.965);
	myGLCD.printNumF(power50, 2, 200, 30);
	power = analogRead(A2);
	power33 = power * (5.0 / 1024.0*0.965);
	myGLCD.printNumF(power33, 2, 200, 40);
	myGLCD.setFont(BigFont);
  }
}
void drawButtons0_1() // ����������� �������� ����������
{
	myGLCD.clrScr();
	myGLCD.setBackColor( 0, 0, 255);

	myGLCD.setColor(0, 0, 255);                    //1
	myGLCD.fillRoundRect (5, 5, 60, 60);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 5, 60, 60);
	myGLCD.printNumI(1, 25, 25);                   //"1"
	
	myGLCD.setColor(0, 0, 255);                    //2
	myGLCD.fillRoundRect (63, 5, 118, 60);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 5, 118, 60);
	myGLCD.printNumI(2, 83, 25);                   //"2"

	myGLCD.setColor(0, 0, 255);                    //3
	myGLCD.fillRoundRect (121, 5, 176, 60);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 5, 176, 60);
	myGLCD.printNumI(3, 141, 25);                  //"3"

	myGLCD.setColor(0, 0, 255);                    //4
	myGLCD.fillRoundRect (179, 5, 234, 60);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 5, 234, 60);
	myGLCD.printNumI(4, 199, 25);                  //"4"

	myGLCD.setColor(0, 0, 255);                    //5
	myGLCD.fillRoundRect (5, 63, 60, 118);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 63, 60, 118);
	myGLCD.printNumI(5, 25, 83);                   //"5"
	
	myGLCD.setColor(0, 0, 255);                    //6
	myGLCD.fillRoundRect (63, 63, 118, 118);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 63, 118, 118);
	myGLCD.printNumI(6, 83, 83);                   //"6"

	myGLCD.setColor(0, 0, 255);                    //7
	myGLCD.fillRoundRect (121, 63, 176, 118);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 63, 176, 118);
	myGLCD.printNumI(7, 141, 83);                  //"7"

	myGLCD.setColor(0, 0, 255);                    //8
	myGLCD.fillRoundRect (179, 63, 234, 118);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 63, 234, 118);
	myGLCD.printNumI(8, 199, 83);                  //"8"

	myGLCD.setColor(0, 0, 255);                    //9
	myGLCD.fillRoundRect (5, 121, 60, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 121, 60, 176);
	myGLCD.printNumI(9, 25, 141);                  //"9"

	myGLCD.setColor(0, 0, 255);                    //0
	myGLCD.fillRoundRect (63, 121, 118, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 121, 118, 176);
	myGLCD.printNumI(0, 83, 141);                  //"0"

}
void drawButtonsExit() // ����������� ������ ����������  ����������
{
	drawButtons0_1();
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 121, 234, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 121, 234, 176);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[1])));
	myGLCD.print(buffer, 145, 141);                                 // "����"
 
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5, 179, 118, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 179, 118, 234);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[0])));
	myGLCD.print(buffer, 14, 199);                                   // "������"

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 179, 234, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 179, 234, 234);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
	myGLCD.print(buffer, 137, 199);                                  // ���
	myGLCD.setBackColor (0, 0, 0);
}
void drawButtonsXBee() // ����������� ������ ����������  ����������
{
	myGLCD.clrScr();
	drawButtons0_1();
	myGLCD.setColor(0, 0, 255);                    // A
	myGLCD.fillRoundRect (121, 121, 176, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 121, 176, 176);
	myGLCD.print("A", 141, 141);                  // "A"

	myGLCD.setColor(0, 0, 255);                    // B
	myGLCD.fillRoundRect (179, 121, 234, 176);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 121, 234, 176);
	myGLCD.print("B", 199, 141);                   // "B"

	myGLCD.setColor(0, 0, 255);                    // C
	myGLCD.fillRoundRect (5, 179, 60, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 179, 60, 234);
	myGLCD.print("C", 25, 199);                   // "C"
	
	myGLCD.setColor(0, 0, 255);                    // D
	myGLCD.fillRoundRect (63, 179, 118, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 179, 118, 234);
	myGLCD.print("D", 83, 199);                   // "D"

	myGLCD.setColor(0, 0, 255);                    // E
	myGLCD.fillRoundRect (121, 179, 176, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 179, 176, 234);
	myGLCD.print("E", 141, 199);                  // "E"

	myGLCD.setColor(0, 0, 255);                    // F
	myGLCD.fillRoundRect (179, 179, 234, 234);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 179, 234, 234);
	myGLCD.print("F", 199, 199);               // "F"
	
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5, 237, 118, 292);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 237, 118, 292);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
	myGLCD.print(buffer, 24, 257);                                   // "�����"
	
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 237, 234, 292);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 237, 234, 292);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[1])));
	myGLCD.print(buffer, 145, 257);                                 // "����"
	myGLCD.setBackColor (0, 0, 0);
}
void klav1()
{
	ret = 0;
	drawButtonsExit();
	int x,y;
	while (true)
	  {
		if (myTouch.dataAvailable())
		{
		  myTouch.read();
		  x = myTouch.getX();
		  y = myTouch.getY();
		  if ((y >= 5) && (y <= 60))                                    // ������ ���
		  {
		   if ((x >= 5) && (x <= 60))                                   // Button: 1
			{
			  waitForIt(5, 5, 60, 60);
			  updateStr('1');
			}
			if ((x >= 63) && (x <= 118))                                // Button: 2
			{
			  waitForIt(63, 5, 118, 60);
			  updateStr('2');
			}
			if ((x >= 121) && (x <= 176))                               // Button: 3
			{
			  waitForIt(121, 5, 176, 60);
			  updateStr('3');
			}
			if ((x >= 179) && (x <= 234))                               // Button: 4
			{
			  waitForIt(179, 5, 234, 60);
			  updateStr('4');
			}
		  }

		  if ((y >= 63) && (y <= 118))                                  // ������ ���
		  {
		   if ((x >= 5) && (x <= 60))                                   // Button: 5
			{
			  waitForIt(5, 63, 60, 118);
			  updateStr('5');
			}
			if ((x >= 63) && (x <= 118))                                // Button: 6
			{
			  waitForIt(63, 63, 118, 118);
			  updateStr('6');
			}
			if ((x >= 121) && (x <= 176))                               // Button: 7
			{
			  waitForIt(121, 63, 176, 118);
			  updateStr('7');
			}
			if ((x >= 179) && (x <= 234))                               // Button: 8
			{
			  waitForIt(179, 63, 234, 118);
			  updateStr('8');
			}
		  }

		  if ((y >= 121) && (y <= 176))                                 // ������ ���
		  {
		   if ((x >= 5) && (x <= 60))                                   // Button: 9
			{
			  waitForIt(5, 121, 60, 176);
			  updateStr('9');
			}
			if ((x >= 63) && (x <= 118))                                // Button: 0
			{
			  waitForIt(63, 121, 118, 176);
			  updateStr('0');
			}
			if ((x >= 121) && (x <= 234))                               // Button: "����"
			{
			  waitForIt(121, 121, 234, 176);
			   if (stCurrentLen > 0)
			   {
				for (int x = 0; x < stCurrentLen + 1; x++)
				{
				  stLast[x] = stCurrent[x];
				}
				stCurrent[0] = '\0';
				stLast[stCurrentLen + 1] = '\0';
				stCurrentLen1 = stCurrentLen;
				stCurrentLen = 0;
				myGLCD.setColor(0, 0, 0);
				myGLCD.fillRect(0, 300, 239, 319);
				myGLCD.setColor(0, 255, 0);
				myGLCD.print(stLast, LEFT, 300);
				break;
			  }
			  else
			  {
				myGLCD.setColor(0, 0, 0);
				myGLCD.fillRect(0, 300, 239, 319);
				myGLCD.setColor(255, 0, 0);
				strcpy_P(buffer, (char*)pgm_read_word(&(table_message[4])));
				myGLCD.print(buffer, CENTER, 300);                                  //"������ ������!"
				delay(500);
				myGLCD.print("                ", CENTER, 300);
				delay(500);
				myGLCD.print(buffer, CENTER, 300);                                 //"������ ������!"
				delay(500);
				myGLCD.print("                ", CENTER, 300);
				myGLCD.setColor(0, 255, 0);
			  }
			}
		  }

		  if ((y >= 179) && (y <= 234))                                           // ��������� ���
		  {
			if ((x >= 5) && (x <= 118))                                           // Button: "������"
			{
			  waitForIt(5, 179, 118, 234);
			  stCurrent[0] = '\0';
			  stCurrentLen = 0;
			  myGLCD.setColor(0, 0, 0);
			  myGLCD.fillRect(0, 300, 239, 319);                                   // �������� ������ �� �������
			}
			if ((x >= 121) && (x <= 234)) // Button: "�����"
			{
			  waitForIt(121, 179, 234, 234);
			 //myGLCD.clrScr();
			  //myGLCD.setBackColor(VGA_BLACK);
			  //ret = 1;
			  stCurrent[0] = '\0';
			  stCurrentLen = 0;
			  break;
			}
		  }
		}
	  }
}
void klavXBee()
{
 ret = 0;
 int x,y;
 drawButtonsXBee();
 while (true)
  {
	if (myTouch.dataAvailable())
	{
	  myTouch.read();
	  x = myTouch.getX();
	  y = myTouch.getY();
	  if ((y >= 5) && (y <= 60)) // ������ ���
	  {
	   if ((x >= 5) && (x <= 60)) // Button: 1
		{
		  waitForIt(5, 5, 60, 60);
		  updateStrXBee('1');
		}
		if ((x >= 63) && (x <= 118)) // Button: 2
		{
		  waitForIt(63, 5, 118, 60);
		  updateStrXBee('2');
		}
		if ((x >= 121) && (x <= 176)) // Button: 3
		{
		  waitForIt(121, 5, 176, 60);
		  updateStrXBee('3');
		}
		if ((x >= 179) && (x <= 234)) // Button: 4
		{
		  waitForIt(179, 5, 234, 60);
		  updateStrXBee('4');
		}
	  }

	  if ((y >= 63) && (y <= 118))    // ������ ���
	  {
	   if ((x >= 5) && (x <= 60)) // Button: 5
		{
		  waitForIt(5, 63, 60, 118);
		  updateStrXBee('5');
		}
		if ((x >= 63) && (x <= 118)) // Button: 6
		{
		  waitForIt(63, 63, 118, 118);
		  updateStrXBee('6');
		}
		if ((x >= 121) && (x <= 176)) // Button: 7
		{
		  waitForIt(121, 63, 176, 118);
		  updateStrXBee('7');
		}
		if ((x >= 179) && (x <= 234)) // Button: 8
		{
		  waitForIt(179, 63, 234, 118);
		  updateStrXBee('8');
		}
	  }

	  if ((y >= 121) && (y <= 176))    // ������ ���
	  {
	   if ((x >= 5) && (x <= 60)) // Button: 9
		{
		  waitForIt(5, 121, 60, 176);
		  updateStrXBee('9');
		}
		if ((x >= 63) && (x <= 118)) // Button: 0
		{
		  waitForIt(63, 121, 118, 176);
		  updateStrXBee('0');
		}
		if ((x >= 121) && (x <= 176)) // Button: A
		{
		  waitForIt(121, 121, 176, 176);
		  updateStrXBee('A');
		}
		if ((x >= 179) && (x <= 234)) // Button: B
		{
		  waitForIt(179, 121, 234, 176);
		  updateStrXBee('B');
		}
	  }
	 
	  if ((y >= 179) && (y <= 234))    // ��������� ���
	  {
	   if ((x >= 5) && (x <= 60)) // Button: C
		{
		  waitForIt(5, 179, 60, 234);
		  updateStrXBee('C');
		}
		if ((x >= 63) && (x <= 118)) // Button: D
		{
		  waitForIt(63, 179, 118, 234);
		  updateStrXBee('D');
		}
		if ((x >= 121) && (x <= 176)) // Button: E
		{
		  waitForIt(121, 179, 176, 234);
		  updateStrXBee('E');
		}
		if ((x >= 179) && (x <= 234)) // Button: F
		{
		  waitForIt(179, 179, 234, 234);
		  updateStrXBee('F');
		}
	  }
	 
	  if ((y >= 237) && (y <= 292))                        // ����� ���
	  {
		if ((x >= 5) && (x <= 118))                        // Button:    "�����"
		{
		  waitForIt(5, 237, 118, 292);
		  myGLCD.clrScr();
		  myGLCD.setBackColor(VGA_BLACK);
		  ret = 1;
		  stCurrent[0] = '\0';
		  stCurrentLen = 0;
		  break;
		}
		if ((x >= 121) && (x <= 234))                      // Button:   "����"
		{
		  waitForIt(121, 237, 234, 292);
		   if (stCurrentLen > 0)
		   {
			for (int x = 0; x < stCurrentLen + 1; x++)
			{
			  stLast[x] = stCurrent[x];
			}
			stCurrent[0] = '\0';
			stLast[stCurrentLen + 1] = '\0';
			stCurrentLen1 = stCurrentLen;
			stCurrentLen = 0;
			myGLCD.setColor(0, 0, 0);
			myGLCD.fillRect(0, 300, 239, 319);
			myGLCD.setColor(0, 255, 0);
			myGLCD.print(stLast, LEFT, 300);
			break;
		  }
		  else
		  {
			myGLCD.setColor(0, 0, 0);
			myGLCD.fillRect(0, 300, 239, 319);
			myGLCD.setColor(255, 0, 0);
			strcpy_P(buffer, (char*)pgm_read_word(&(table_message[4])));
			myGLCD.print(buffer, CENTER, 300);                                  //"������ ������!"
			delay(500);
			myGLCD.print("                 ", CENTER, 300);
			delay(500);
			myGLCD.print(buffer, CENTER, 300);                                 //"������ ������!"
			delay(500);
			myGLCD.print("                 ", CENTER, 300);
			myGLCD.setColor(0, 255, 0);
		  }
		}
	  }
	}
  }
}

void draw_menu1()
{
	myGLCD.clrScr();
	myGLCD.setBackColor (0, 0, 255);

	myGLCD.setColor(0, 0, 255);                    // 1
	myGLCD.fillRoundRect (5, 28, 234, 83);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 28, 234, 83);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[30])));
	myGLCD.print(buffer, CENTER, 48);  

	myGLCD.setColor(0, 0, 255);                    // 1
	myGLCD.fillRoundRect (5, 86, 234, 141);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 86, 234, 141);	
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[32])));
	myGLCD.print(buffer, CENTER, 106);  

	myGLCD.setColor(0, 0, 255);                    // 1
	myGLCD.fillRoundRect (5, 144, 234, 199);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 144, 234, 199);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[31])));
	myGLCD.print(buffer, CENTER, 164);  

	myGLCD.setColor(0, 0, 255);                    // 1
	myGLCD.fillRoundRect (5, 202, 234, 257);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 202, 234, 257);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[36])));
	myGLCD.print(buffer, CENTER, 212);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[37])));
	myGLCD.print(buffer, CENTER, 232);  

	myGLCD.setColor(0, 0, 255);                    // 1
	myGLCD.fillRoundRect (5, 260, 234, 315);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 260, 234, 315);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
	myGLCD.print(buffer, CENTER, 280);                                   // "�����"
}
void draw_menu2()
{
	myGLCD.clrScr();
	myGLCD.setBackColor (0, 0, 255);
	   
	myGLCD.setColor(0, 0, 255);                    // 1  ���� XBee
	myGLCD.fillRoundRect (5, 28, 234, 83);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 28, 234, 83);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[22]))); 
	myGLCD.print(buffer, CENTER, 48);  

	myGLCD.setColor(0, 0, 255);                    // 2  ������ ���������
	myGLCD.fillRoundRect (5, 86, 234, 141);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 86, 234, 141);	
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[28])));
	myGLCD.print(buffer, CENTER, 96);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[29])));
	myGLCD.print(buffer, CENTER, 116);  

	myGLCD.setColor(0, 0, 255);                    // 3
	myGLCD.fillRoundRect (5, 144, 234, 199);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 144, 234, 199);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[26])));
	myGLCD.print(buffer, CENTER, 154);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[25])));
	myGLCD.print(buffer, CENTER, 174);  

	myGLCD.setColor(0, 0, 255);                    // 4
	myGLCD.fillRoundRect (5, 202, 234, 257);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 202, 234, 257);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[34])));
	myGLCD.print(buffer, CENTER, 212);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[35])));
	myGLCD.print(buffer, CENTER, 232);  

	myGLCD.setColor(0, 0, 255);                    // 5   �����         
	myGLCD.fillRoundRect (5, 260, 234, 315);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 260, 234, 315);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
	myGLCD.print(buffer, CENTER, 280);         
}
void draw_menu3()
{
	myGLCD.clrScr();
	myGLCD.setBackColor (0, 0, 255);
	   
	myGLCD.setColor(0, 0, 255);                    // 1   
	myGLCD.fillRoundRect (5, 28, 234, 83);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 28, 234, 83);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[38]))); 
	myGLCD.print(buffer, CENTER, 48);  

	myGLCD.setColor(0, 0, 255);                    // 2   
	myGLCD.fillRoundRect (5, 86, 234, 141);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 86, 234, 141);	
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[40])));
//	myGLCD.print(buffer, CENTER, 96);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[41])));
//	myGLCD.print(buffer, CENTER, 116);  

	myGLCD.setColor(0, 0, 255);                    // 3
	myGLCD.fillRoundRect (5, 144, 234, 199);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 144, 234, 199);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[43])));
	myGLCD.print(buffer, CENTER, 154);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[44])));
	myGLCD.print(buffer, CENTER, 174);  

	myGLCD.setColor(0, 0, 255);                    // 4
	myGLCD.fillRoundRect (5, 202, 234, 257);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 202, 234, 257);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[34])));
	myGLCD.print(buffer, CENTER, 212);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[42])));
	myGLCD.print(buffer, CENTER, 232);  

	myGLCD.setColor(0, 0, 255);                    // 5   �����         
	myGLCD.fillRoundRect (5, 260, 234, 315);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 260, 234, 315);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
	myGLCD.print(buffer, CENTER, 280);         
}
void draw_menu4()
{
	myGLCD.clrScr();
	myGLCD.setBackColor (0, 0, 255);
	   
	myGLCD.setColor(0, 0, 255);                    // 1   
	myGLCD.fillRoundRect (5, 28, 234, 83);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 28, 234, 83);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[38]))); 
	myGLCD.print(buffer, CENTER, 48);  

	myGLCD.setColor(0, 0, 255);                    // 2   
	myGLCD.fillRoundRect (5, 86, 234, 141);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 86, 234, 141);	
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[40])));
	myGLCD.print(buffer, CENTER, 96);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[41])));
	myGLCD.print(buffer, CENTER, 116);  

	myGLCD.setColor(0, 0, 255);                    // 3
	myGLCD.fillRoundRect (5, 144, 234, 199);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 144, 234, 199);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[42])));
	myGLCD.print(buffer, CENTER, 154);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[41])));
	myGLCD.print(buffer, CENTER, 174);  

	myGLCD.setColor(0, 0, 255);                    // 4
	myGLCD.fillRoundRect (5, 202, 234, 257);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 202, 234, 257);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[42])));
	myGLCD.print(buffer, CENTER, 212);  
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[45])));
	myGLCD.print(buffer, CENTER, 232);  

	myGLCD.setColor(0, 0, 255);                    // 5   �����         
	myGLCD.fillRoundRect (5, 260, 234, 315);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 260, 234, 315);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[2])));
	myGLCD.print(buffer, CENTER, 280);         
}

void klav_menu1()
{
	int x,y;
	draw_menu1();
	while (true)
	{
		if (myTouch.dataAvailable())
		{
			myTouch.read();
			x = myTouch.getX();
			y = myTouch.getY();
			if ((x >= 5) && (x <= 234))                                  // ������ ���
			{
				if ((y >= 28) && (y <= 83))                                   // Button: 1
				{
				 waitForIt(5, 28, 234, 83);
				 myGLCD.clrScr();
				 set_adr_device();
				 draw_menu1();
				}
				if ((y >= 86) && (y <= 141))                                // Button: 2
				{
				 waitForIt(5, 86, 234, 141);
				 myGLCD.clrScr();
				 klav_Menu_Reset();
//				 draw_menu1();
				}
				if ((y >= 144) && (y <= 199))                               // Button: 3
				{
				waitForIt(5, 144, 234, 199);
 
				}
				if ((y >= 202) && (y <= 257))                               // Button: 4
				{
				waitForIt(5, 202, 234, 257);
					klav_menu3();
					draw_menu1();
				}
				if ((y >= 260) && (y <= 315))                               // Button: 5
				{
				waitForIt(5, 260, 234, 315);
				drawGlavMenu();
				break;
				}
			}
		}
	}
}
void klav_menu2()
{
	int x,y;
	draw_menu2();
	while (true)
	{
		if (myTouch.dataAvailable())
		{
			myTouch.read();
			x = myTouch.getX();
			y = myTouch.getY();
			if ((x >= 5) && (x <= 234))                                     // ������ ���
			{
				if ((y >= 28) && (y <= 83))                                 // Button: 1
				{
					waitForIt(5, 28, 234, 83);
					XBee_status();                                          // ���������� XBee 
				}
				if ((y >= 86) && (y <= 141))                                // Button: 2
				{
					waitForIt(5, 86, 234, 141);
					view_adr_device();                                      // �������� ������� ��������� � ������ 
					draw_menu2();
				}
				if ((y >= 144) && (y <= 199))                               // Button: 3
				{
					waitForIt(5, 144, 234, 199);
					XBee_Set_Network();
					draw_menu2();
				}
				if ((y >= 202) && (y <= 257))                               // Button: 4
				{
					waitForIt(5, 202, 234, 257);
					setClock();
					draw_menu2();
				}
				if ((y >= 260) && (y <= 315))                               // Button:�����
				{
				waitForIt(5, 260, 234, 315);
				drawGlavMenu();
				break;
				}
			}
		}
	}
}
void klav_menu3()
{
	int x,y;
	draw_menu3();
	while (true)
	{
		if (myTouch.dataAvailable())
		{
			myTouch.read();
			x = myTouch.getX();
			y = myTouch.getY();
			if ((x >= 5) && (x <= 234))                                     // ������ ���
			{
				if ((y >= 28) && (y <= 83))                                 // Button: 1
				{
					waitForIt(5, 28, 234, 83);
					pass_test_start();  // ���������� �������� ����������
					klav123();          // ������� ���������� � ����������
					if (ret == 1)        // ���� "�������" - ���������
						{
							goto bailout14;  // ������� �� ��������� ���������� ������ ����
						}
				//   else                 // ����� ��������� ����� ����
					//   {
							pass_test();     // ��������� ������
					//   }
					if ( ( pass2 == 1) || ( pass3 == 1)) // ���� ����� - ��������� ����� ����
						{
							myGLCD.clrScr();   // �������� �����
							myGLCD.print(txt_pass_ok, RIGHT, 208); 
							delay (500);
							eeprom_clear = 1; // ��������� ������� ����������
					//		system_clear_start(); // ���� ����� - ��������� ����� ����
						}
					else  // ������ �� ������ - �������� � ���������
						{
							txt_pass_no_all();
						}

						bailout14: // ������������ ������ ����
						/*myGLCD.clrScr();
						myButtons.drawButtons();
						print_up();
*/

					    draw_menu3();
				}
				if ((y >= 86) && (y <= 141))                                // Button: 2
				{
					waitForIt(5, 86, 234, 141);
					myGLCD.clrScr();
					delay (500);
	
					draw_menu3();
				}
				if ((y >= 144) && (y <= 199))                               // Button: 3
				{
					waitForIt(5, 144, 234, 199);
					myGLCD.clrScr();
					delay (500);
			
					draw_menu3();
				}
				if ((y >= 202) && (y <= 257))                               // Button: 4
				{
					waitForIt(5, 202, 234, 257);
					myGLCD.clrScr();
					klav_menu4();
					draw_menu3();
				}
				if ((y >= 260) && (y <= 315))                               // Button:�����
				{
					waitForIt(5, 260, 234, 315);
					break;
				}
			}
		}
	}
 }
void klav_menu4()   // ���� ��������� �������
{
	int x,y;
	draw_menu4();
	while (true)
	{
		if (myTouch.dataAvailable())
		{
			myTouch.read();
			x = myTouch.getX();
			y = myTouch.getY();
			if ((x >= 5) && (x <= 234))                                     // ������ ���
			{
				if ((y >= 28) && (y <= 83))                                 // Button: 1
				{
					waitForIt(5, 28, 234, 83);
					pass_test_start();  // ���������� �������� ����������
					klav123();          // ������� ���������� � ����������
					if (ret == 1)        // ���� "�������" - ���������
						{
							goto bailout14;  // ������� �� ��������� ���������� ������ ����
						}
				//   else                 // ����� ��������� ����� ����
					//   {
							pass_test();     // ��������� ������
					//   }
					if ( ( pass2 == 1) || ( pass3 == 1)) // ���� ����� - ��������� ����� ����
						{
							myGLCD.clrScr();   // �������� �����
							myGLCD.print(txt_pass_ok, RIGHT, 208); 
							delay (500);
							eeprom_clear = 1; // ��������� ������� ����������
					//		system_clear_start(); // ���� ����� - ��������� ����� ����
						}
					else  // ������ �� ������ - �������� � ���������
						{
							txt_pass_no_all();
						}

						bailout14: // ������������ ������ ����
						/*myGLCD.clrScr();
						myButtons.drawButtons();
						print_up();
*/

					    draw_menu3();
				}
				if ((y >= 86) && (y <= 141))                                // Button: 2
				{
					waitForIt(5, 86, 234, 141);
					pass_test_start();
					klav123();
				if (ret == 1)
					{
						goto bailout24;
					}
				else
					{
						pass_test();
					}
				if ( ( pass1 == 1)||( pass2 == 1) || ( pass3 == 1))
					{
						myGLCD.clrScr();
						myGLCD.print(txt_pass_ok, RIGHT, 208);
						delay (500);
						set_n_user_start();
					}
				else
					{
						txt_pass_no_all();
					}

					bailout24:
			/*		myGLCD.clrScr();
					myButtons.drawButtons();
					print_up();
*/
					draw_menu3();
				}
				if ((y >= 144) && (y <= 199))                               // Button: 3
				{
					waitForIt(5, 144, 234, 199);
					int  stCurrentLen_pass_user = i2c_eeprom_read_byte( deviceaddress,adr_pass_user-2);  //������� ����� ������  �� ������
					if (stCurrentLen_pass_user == 0)
						{ 
								pass1 = 1;
								goto pass_cross_user; 
						}
						pass_test_start();
						klav123();
					if (ret == 1)
						{
							goto bailout34;
						}
						pass_test();
						pass_cross_user:

					if ( ( pass1 == 1)||( pass2 == 1) || ( pass3 == 1))
						{
							myGLCD.clrScr();
							myGLCD.print(txt_pass_ok, RIGHT, 208);
							delay (500);
							set_pass_user_start();
						}
					else
						{
							txt_pass_no_all();
						}

						bailout34:
					/*		myGLCD.clrScr();
							myButtons.drawButtons();
							print_up();*/
					draw_menu3();
				}
				if ((y >= 202) && (y <= 257))                               // Button: 4
				{
					waitForIt(5, 202, 234, 257);
						int stCurrentLen_pass_admin = i2c_eeprom_read_byte( deviceaddress,adr_pass_admin-2);
						if (stCurrentLen_pass_admin == 0)
							{  
							   pass2 = 1;
							   pass3 = 1;
							   goto pass_cross_admin; 
							}
							pass_test_start();
							klav123();
						if (ret == 1)
							 {
							   goto bailout44;
							 }
							 pass_test();
							 pass_cross_admin:
				  
						if (( pass2 == 1) || ( pass3 == 1))
							{
								myGLCD.clrScr();
								myGLCD.print(txt_pass_ok, RIGHT, 208);
								delay (500);
								set_pass_admin_start();
							}
						else
							{
								txt_pass_no_all();
							}

							bailout44:
							//myGLCD.clrScr();
							//myButtons.drawButtons();
							//print_up();
					draw_menu4();
				}
				if ((y >= 260) && (y <= 315))                               // Button:�����
				{
					waitForIt(5, 260, 234, 315);
					break;
				}
			}
		}
	}
 }



void set_n_user_start()
{
	myGLCD.setFont(BigFont);
	myGLCD.setBackColor(0, 0, 255);
	myGLCD.clrScr();
	drawButtons1();
	// ����� ������ "������� ����� ������������!"
	myGLCD.setColor(255, 0, 0);
	myGLCD.print(txt_n_user, CENTER, 280);// ������� ����� ������������!
	delay(300);
	myGLCD.print("                       ", CENTER, 280);
	delay(300);
	myGLCD.print(txt_n_user, CENTER, 280);// ������� ����� ������������!
	klav123();
	if (ret == 1)
		{
			ret = 0;
			return;
		}

	strcpy(temp_stLast,stLast);

	myGLCD.setColor(255, 0, 0);
	myGLCD.print("                         ", CENTER, 280);
	myGLCD.print(txt_rep_user, CENTER, 280);// ������� ����� ������������!
	delay(300);
	myGLCD.print("                         ", CENTER, 280);
	delay(300);
	myGLCD.print(txt_rep_user, CENTER, 280);// ������� ����� ������������!

	klav123();
	if (ret == 1)
		{
			ret = 0;
			return;
		}

	if(strcmp(temp_stLast,stLast)==0)
	{
		stCurrentLen1 = i2c_eeprom_read_byte( deviceaddress,adr_stCurrentLen1);// ������ ������ ������������
			 
		for (x=0; x<stCurrentLen1+1; x++)
		{ 
			i2c_eeprom_write_byte(deviceaddress, adr_n_user+x, stLast[x]);
		}
		i2c_eeprom_write_byte(deviceaddress, adr_n_user-2, stCurrentLen1);
	
	}
	if(strcmp(temp_stLast,stLast)!=0)
	{
		myGLCD.print("                      ", CENTER, 280);
		myGLCD.print(txt_err_pass_user, CENTER, 280);// ������ �����!
		delay(1500);
	}

}
void set_pass_user_start()
{
	myGLCD.setFont(BigFont);
	myGLCD.setBackColor(0, 0, 255);
	myGLCD.clrScr();
	drawButtons1();
		// txt_set_pass_user  ����� ������ "������� ������ ������������!"
	myGLCD.setColor(255, 0, 0);
	myGLCD.print(txt_set_pass_user, CENTER, 280);     // ������� ������ ������������!
	delay(300);
	myGLCD.print("                         ", CENTER, 280);
	delay(300);
	myGLCD.print(txt_set_pass_user, CENTER, 280);      // ������� ������ ������������!
	
	klav123();
	if (ret == 1)
		{
			ret = 0;
			return;
		}

	//�������� �������� ������
	 
	strcpy(temp_stLast,stLast);

		// txt_set_pass_user  ����� ������ "������� ������ ������������!"
	myGLCD.setColor(255, 0, 0);
	myGLCD.print(txt_rep_pass_user, CENTER, 280);// ������ ������ ������������!
	delay(300);
	myGLCD.print("                        ", CENTER, 280);
	delay(300);
	myGLCD.print(txt_rep_pass_user, CENTER, 280);// ������ ������ ������������!

		klav123();
		if (ret == 1)
		{
			ret = 0;
			return;
		}

		if(strcmp(temp_stLast,stLast)==0)
		{

		for (x=0; x<stCurrentLen1+1; x++)
		{
			i2c_eeprom_write_byte(deviceaddress, adr_pass_user+x, stLast[x]);
		}
			i2c_eeprom_write_byte(deviceaddress, adr_pass_user-2, stCurrentLen1);
			myGLCD.print("                      ", CENTER, 280);
			myGLCD.print(txt_pass_ok, RIGHT, 208);
			delay(1500);
		}

		if(strcmp(temp_stLast,stLast)!=0)
		{
			myGLCD.print("                      ", CENTER, 280);
			myGLCD.print(txt_err_pass_user, CENTER, 280);// ������ �����!
			delay(1500);
		}


}

void set_pass_admin_start()
{
	myGLCD.setFont(BigFont);
	myGLCD.setBackColor(0, 0, 255);
	myGLCD.clrScr();
	drawButtons1();
		// txt_set_pass_admin  ����� ������ "������� ������ �����!"
	myGLCD.setColor(255, 0, 0);
	myGLCD.print(txt_set_pass_admin, CENTER, 280);// ������� ������ �����!
	delay(300);
	myGLCD.print("                       ", CENTER, 280);
	delay(300);
	myGLCD.print(txt_set_pass_admin, CENTER, 280);// ������� ������ �����!
	//char* temp_stLast = "";
	klav123();
	if (ret == 1)
		{
			ret = 0;
			return;
		}
	//�������� �������� ������
	
	strcpy(temp_stLast,stLast);

// txt_set_pass_admin  ����� ������ "������� ������ �����!"
	myGLCD.setColor(255, 0, 0);
	myGLCD.print(txt_rep_pass_admin, CENTER, 280);// ������ ������ �����!
	delay(300);
	myGLCD.print("                       ", CENTER, 280);
	delay(300);
	myGLCD.print(txt_rep_pass_admin, CENTER, 280);// ������ ������ �����!
	klav123();

			if (ret == 1)
				{
					ret = 0;
					return;
				}
		if(strcmp(temp_stLast,stLast)==0)
		{
			for (x=0; x<stCurrentLen1+1; x++)
		{
					i2c_eeprom_write_byte(deviceaddress, adr_pass_admin+x, stLast[x]);
		}
			i2c_eeprom_write_byte(deviceaddress, adr_pass_admin-2, stCurrentLen1);
			myGLCD.print("                       ", CENTER, 280);
			myGLCD.print(txt_pass_ok, RIGHT, 208);
			delay(1500);
		}

		else
		{
			myGLCD.print("                       ", CENTER, 280);
			myGLCD.print(txt_err_pass_user, CENTER, 280);// ������ �����!
			delay(1500);
		}

}

void drawMenuReset()
{
	myGLCD.clrScr();
	myGLCD.setBackColor( 0, 0, 255);

	myGLCD.setColor(0, 0, 255);                       //1
	myGLCD.fillRoundRect (5, 5, 94, 90);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 5,94, 90);
	myGLCD.print("+ 1", 10, 10); 


	
	myGLCD.setColor(0, 0, 255);                      //3
	myGLCD.fillRoundRect (97, 5, 186, 90);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (97, 5, 186, 90);
	myGLCD.print("+ 3", 102, 10);    

	myGLCD.setColor(0, 0, 255);                     //2
	myGLCD.fillRoundRect (5, 93, 94, 178);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 93,94, 178);
	myGLCD.print("- 2", 10, 98);    

	myGLCD.setColor(0, 0, 255);                     //4
	myGLCD.fillRoundRect (97, 93, 186, 178);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (97, 93, 186, 178);
	myGLCD.print("- 4", 102, 98);                   //"4"

//------------------------------------------------------------------

	myGLCD.setColor(0, 0, 255);                    //1
	myGLCD.fillRoundRect (5, 183, 60, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 183, 60, 243);
	myGLCD.printNumI(5, 25-x_dev, 205-y_dev);                   //"1"
	
	myGLCD.setColor(0, 0, 255);                    //2
	myGLCD.fillRoundRect (63, 183, 118, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (63, 183, 118, 243);
	myGLCD.printNumI(6, 83-x_dev, 205-y_dev);                   //"2"

	myGLCD.setColor(0, 0, 255);                    //3
	myGLCD.fillRoundRect (121, 183, 176, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 183, 176, 243);
	myGLCD.printNumI(7, 141-x_dev, 205-y_dev);                  //"3"

	myGLCD.setColor(0, 0, 255);                      //4
	myGLCD.fillRoundRect (179, 183, 234, 243);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (179, 183, 234, 243);
	myGLCD.printNumI(8, 199-x_dev, 205-y_dev);                  //"4"
//----------------------------------------------------------

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (5, 248, 118, 293);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (5, 248, 118, 293);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[19])));
	myGLCD.print(buffer, 22, 262);                                      // "�����"

	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (121, 248, 234, 293);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (121, 248, 234, 293);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[33])));
	myGLCD.print(buffer, 135, 262);                                     //  "�����"

	myGLCD.setBackColor (0, 0, 0);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[32])));
	myGLCD.print(buffer, CENTER, 298);                                  //  ����� ��������

}
void klav_Menu_Reset()
{
	int x,y;
	drawMenuReset();
	while (true)
	{
		myGLCD.setColor(255, 255, 255);
		if (myTouch.dataAvailable())
		{
		  myTouch.read();
		  x = myTouch.getX();
		  y = myTouch.getY();
		  if ((y >= 5) && (y <= 90))                                    // ������ ���
		  {
		   if ((x >= 5) && (x <= 94))                                   // Button: 1
			{
				N_KN = 1;
				count1=!count1;
				if(count1)
				{
					waitForStartR(5, 5, 94, 90);
				}
				else
				{
					waitForEndR(5, 5, 94, 90);
				}
				while (myTouch.dataAvailable())  myTouch.read();
			}
			if ((x >= 97) && (x <= 186))                                // Button: 3
			{
				N_KN = 3;
				count3=!count3;
				if(count3)
				{
					waitForStartR(97, 5, 186, 90);
				}
				else
				{
					waitForEndR(97, 5, 186, 90);
				}
				while (myTouch.dataAvailable())  myTouch.read();
			}
		}
	 
		  if ((y >= 93) && (y <= 178))                                  // ������ ���
		  {
		   if ((x >= 5) && (x <= 94))                                   // Button: 2
			{
				N_KN = 2;
				count2=!count2;
				if(count2)
				{
					waitForStartR(5, 93, 94, 178);
				}
				else
				{
					waitForEndR(5, 93, 94, 178);
				}
				while (myTouch.dataAvailable())  myTouch.read();
			}
			if ((x >= 97) && (x <= 186))                                // Button: 4
			{
				N_KN = 4;
				count4=!count4;
				if(count4)
				{
					waitForStartR(97, 93, 186, 178);
				}
				else
				{
					waitForEndR(97, 93, 186, 178);
				}
				while (myTouch.dataAvailable())  myTouch.read();
			}
		}
	 
		  if ((y >= 183) && (y <= 243))                                    //  ���
		  {
		   if ((x >= 5) && (x <= 60))                                   // Button: 5
			{
				N_KN = 5;
				count5=!count5;
				if(count5)
				{
					waitForStartR(5, 183, 60, 243);
				}
				else
				{
					waitForEndR(5, 183, 60, 243);
				}
				while (myTouch.dataAvailable())  myTouch.read();
			}
			if ((x >= 63) && (x <= 118))                                // Button: 6
			{
				N_KN = 6;
				count6=!count6;
				if(count6)
				{
					waitForStartR(63, 183, 118, 243);
				}
				else
				{
					waitForEndR(63, 183, 118, 243);
				}
				while (myTouch.dataAvailable())  myTouch.read();
			}
			if ((x >= 121) && (x <= 176))                               // Button: 7
			{
				N_KN = 7;
				count7=!count7;
				if(count7)
				{
					waitForStartR(121, 183, 176, 243);
				}
				else
				{
					waitForEndR(121, 183, 176, 243);
				}
				while (myTouch.dataAvailable())  myTouch.read();
			}
			if ((x >= 179) && (x <= 234))                               // Button: 8
			{
				N_KN = 8;
				count8=!count8;
				if(count8)
				{
					waitForStartR(179, 183, 234, 243);
				}
				else
				{
					waitForEndR(179, 183, 234, 243);
				}
				while (myTouch.dataAvailable())  myTouch.read();
			}
		}

		  if ((y >= 248) && (y <= 293))                                // ��������� ���
		  {
			if ((x >= 5) && (x <= 118))                                // Button: �����
			{
			  waitForIt(5, 248, 118, 293);
			  draw_menu1();
			  break;
			}
			if ((x >= 121) && (x <= 234))                              // Button: �����
			{
				waitForIt(121, 248, 234, 293);
	
				if(count1)
				{
					payload[11] = 0x00;
					waitForEndR(5, 5, 94, 90); 
				}

				if(count2)
				{
					payload[12] = 0x00;
					waitForEndR(5, 93, 94, 178);
				}

				if(count3)
				{
					payload[13] = 0x00;
					waitForEnd(97, 5, 186, 90);
				}

				if(count4)
				{
					payload[14] = 0x00;
					waitForEndR(97, 93, 186, 178);
				}

				if(count5)
				{
					payload[15] = 0x00;
					waitForEndR(5, 183, 60, 243);
				}

				if(count6)
				{
					payload[16] = 0x00;
					waitForEndR(63, 183, 118, 243);
				}

				if(count7)
				{
					payload[17] = 0x00;
					waitForEndR(121, 183, 176, 243);
				}

				if(count8)
				{
					payload[18] = 0x00;
					waitForEndR(179, 183, 234, 243);
				}

				payload[0] = 12; 
				XBeeWrite();
				//delay(1000);
				draw_menu1();
				break;
			}
		  }
		}
	XBeeRead();
	}
}

void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())  myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

void waitForStart(int x1, int y1, int x2, int y2)
{
	myGLCD.setColor(255, 0, 0);
	myGLCD.drawRoundRect (x1, y1, x2, y2);
	myGLCD.drawRoundRect (x1+1, y1+1, x2-1, y2-1);
	myGLCD.drawRoundRect (x1+2, y1+2, x2-2, y2-2);
	while (myTouch.dataAvailable())  myTouch.read();
	myGLCD.setColor(255, 255, 255);
	myGLCD.setBackColor( 0, 0, 0);
}
void waitForEnd(int x1, int y1, int x2, int y2)
{
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (x1, y1, x2, y2);
	myGLCD.setColor(0, 0, 255);
	myGLCD.drawRoundRect (x1+1, y1+1, x2-1, y2-1);
	myGLCD.drawRoundRect (x1+2, y1+2, x2-2, y2-2);
}
void waitForStartR(int x1, int y1, int x2, int y2)
{
	myGLCD.setColor(255, 0, 0);
	myGLCD.drawRoundRect (x1, y1, x2, y2);
	myGLCD.drawRoundRect (x1+1, y1+1, x2-1, y2-1);
	myGLCD.drawRoundRect (x1+2, y1+2, x2-2, y2-2);
	myGLCD.setColor(255, 255, 255);
}
void waitForEndR(int x1, int y1, int x2, int y2)
{
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (x1, y1, x2, y2);
	myGLCD.setColor(0, 0, 255);
	myGLCD.drawRoundRect (x1+1, y1+1, x2-1, y2-1);
	myGLCD.drawRoundRect (x1+2, y1+2, x2-2, y2-2);
}

void updateStr(int val)
{
  if (stCurrentLen < 15)
  {
	stCurrent[stCurrentLen] = val;
	stCurrent[stCurrentLen + 1] = '\0';
	stCurrentLen++;
	myGLCD.setColor(0, 255, 0);
	myGLCD.print(stCurrent, LEFT, 300);
	myGLCD.printNumI(stCurrentLen, RIGHT, 300);
  }
  else
  {                                                             // ����� ������ "������������!"
	myGLCD.setColor(0, 0, 0);
	myGLCD.fillRect(0, 300, 239, 319);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[3])));
	myGLCD.setColor(255, 0, 0);
	myGLCD.print("               ", CENTER, 300);
	myGLCD.print(buffer, CENTER, 300);                         // ������������!
	delay(500);
	myGLCD.print("               ", CENTER, 300);
	delay(500);
	myGLCD.print(buffer, CENTER, 300);                         // ������������!
	delay(500);
	myGLCD.print("               ", CENTER, 300);
	myGLCD.setColor(0, 255, 0);
  }
}

void XBeeRead() 
{
  xbee.readPacket();                                          // �������� �����
	if (xbee.getResponse().isAvailable())                     //��������� ������� ������
	  {
	  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) 			// ������� zb rx packet
		  {
			xbee.getResponse().getZBRxResponse(rx);           // ������ ��������� ��� ����� ZB ��  ����� rx ��������
			if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED)     // ����������� �������  ����� ACK
				{
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

				//for (int i = 0; i < rx.getDataLength(); i++)       // ������� ���������� ����� ������  � rx.getDataLength()
				//{
				//	Serial.print("payload [");                   //
				//	Serial.print(i, DEC);                        //
				//	Serial.print("] is ");                       //
				//	Serial.println(rx.getData()[i], HEX);        // ���������� ��������� � rx.getData()[i]
				//}

				int x_back = rx.getData()[0];

			//	Serial.println(x_back);
				myGLCD.setColor(255, 255, 255);
				switch( x_back)                                        //generate query response based on function type
				{
					case 1:
						waitForEnd(5, 5, 94, 90);
						break;
					case 2:
						waitForEnd(5, 93, 94, 178);
						break;
					case 3:
						waitForEnd(97, 5, 186, 90);
						break;
					case 4:
						waitForEnd(97, 93, 186, 178);
						break;
					case 5:
						waitForEnd(5, 183, 60, 243);
						break;
					case 6:
						waitForEnd(63, 183, 118, 243);
						break;
					case 7:
						waitForEnd(121, 183, 176, 243);
						break;
					case 8:
						waitForEnd(179, 183, 234, 243);
						break;
					default:
					//	return;
						break;
					}
//				Serial.println();
				//�������� ������� 32-������ ����� 64-������ �����.  64-������ ����� 802.15.4 MAC ����� ��������� 
				XBee_Addr64_MS=(uint32_t(rx.getFrameData()[0]) << 24) + (uint32_t(rx.getFrameData()[1]) << 16) + (uint16_t(rx.getFrameData()[2]) << 8) + rx.getFrameData()[3];
				//�������� ���� 32-������ �����...
				XBee_Addr64_LS=(uint32_t(rx.getFrameData()[4]) << 24) + (uint32_t(rx.getFrameData()[5]) << 16) + (uint16_t(rx.getFrameData()[6]) << 8) + rx.getFrameData()[7];
				//��������� ��� ����� ������ ������������ ����������� ����������������� �����
				//Serial.print("Addr64 MS: ");
				//Serial.print(XBee_Addr64_MS,HEX);
				//Serial.print('\n');
				//Serial.print("Addr64 LS: ");
				//Serial.print(XBee_Addr64_LS,HEX);
				//Serial.print('\n');
				//Serial.println();
				XBee_Addr16=rx.getRemoteAddress16();         		  // IP-������ � TCP/IP. 
				/*Serial.print("Addr16: ");
				Serial.println(XBee_Addr16,HEX);
*/
				addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);

		   }
	//  sl_XBee();
	  } 

	 else if (xbee.getResponse().isError())                           //  ������ ������
		{
		   Serial.print("error code:");
		   Serial.println(xbee.getResponse().getErrorCode());       // ��� ������ xbee.getResponse().getErrorCode()
		}
}

void sl_XBee()                                              // ����������� �����  ��
 {
	funcType = (rx.getData()[0]);                           //copy the function type from the incoming query
	field1	= (rx.getData()[1] << 8) | rx.getData()[2];     //copy field 1 from the incoming query
	field2  = (rx.getData()[3] << 8) | rx.getData()[4];     //copy field 2 from the incoming query
	switch(funcType)                                        //generate query response based on function type
		{
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		default:
			return;
			break;
		}
	//XBeeWrite();
 }
void XBeeWrite()
{
	zbTx = ZBTxRequest(addr64, payload, sizeof(payload));  
	xbee.send(zbTx); 
	if (xbee.readPacket(700))                                               //  ����� �������� ������� TX, �� ������� ����� �������
		{
		if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) 		// ������� �����! // ������ ���� znet tx status       
			{
				xbee.getResponse().getZBTxStatusResponse(txStatus);
				if (txStatus.getDeliveryStatus() == SUCCESS)                // �������� ������ ��������, ����� ����
					{
						Serial.println("Success.  time to celebrate!");     // �������, ����� ����������.
						myGLCD.setColor(VGA_LIME);
						myGLCD.fillRoundRect (195, 71, 233, 109);
						myGLCD.setColor(255, 255, 255);
						myGLCD.drawRoundRect (194, 70, 234, 110);
						myGLCD.setBackColor(0, 0, 0);
						delay(400); 
						myGLCD.setColor(0, 0, 0);
						myGLCD.fillRoundRect (195, 71, 233, 109);
					}
				else 
					{
						Serial.println("The remote XBee did not receive our packet. is it powered on?");  	// ����������� XBee �� �������. �� �������?
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
        Serial.println("XBee did not provide a timely TX Status Response");
		myGLCD.setColor(255 , 0, 0);
		myGLCD.fillRoundRect (195, 71, 233, 109);
		myGLCD.setColor(255, 255, 255);
		myGLCD.drawRoundRect (194, 70, 234, 110);
		myGLCD.setBackColor(0, 0, 0);
		delay(400); 
		myGLCD.setColor(0, 0, 0);
		myGLCD.fillRoundRect (195, 71, 233, 109);
		myGLCD.setColor(255, 255, 255);
		
		switch(N_KN)                                        //generate query response based on function type
		{
		case 1:
			waitForEnd(5, 5, 94, 90);
			break;
		case 2:
			waitForEnd(5, 93, 94, 178);
			break;
		case 3:
			waitForEnd(97, 5, 186, 90);
			break;
		case 4:
			waitForEnd(97, 93, 186, 178);
			break;
		case 5:
			waitForEnd(5, 183, 60, 243);
			break;
		case 6:
			waitForEnd(63, 183, 118, 243);
			break;
		case 7:
			waitForEnd(121, 183, 176, 243);
			break;
		case 8:
			waitForEnd(179, 183, 234, 243);
			break;
		default:
			break;
		}
	}
	delay(300);
} 
void XBee_Setup()            //  
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
	int x, y;
	while (true)
	{
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
void XBee_status()
{
	time_flag_start();
	int XBee_x, XBee_y, x, y;
	unsigned long XBee_data2;
	int yXBee = 32;                                                  // ��������� ����� �������� ����� ������
	int yDelta = 16;                                                 // ������ �������� ����

	myGLCD.clrScr();                                                 // �������� ����� CENTER
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (2, 2, 239, 25);                            // ���������� ������������� ��� ������
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (2, 2, 239, 25);
	myGLCD.setColor(255, 255, 255);
	myGLCD.setBackColor(0, 0, 255);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[7])));     // ���������� XBee
	myGLCD.print(buffer, CENTER, 5);
							
	myGLCD.setBackColor(0, 0, 0);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[11])));    // ����� "Number SH,SL"
	myGLCD.print(buffer, CENTER, yXBee);
	yXBee = yXBee + yDelta;                                          // �������������� ������, ��������  ����
	myGLCD.setColor(0, 255, 255);
	myGLCD.print("MS", LEFT, yXBee);
	myGLCD.print(String(XBee_Addr64_MS,HEX), RIGHT, yXBee);          //
	yXBee = yXBee + yDelta;                                          // �������������� ������, ��������  ����
	myGLCD.print("LS", LEFT, yXBee);
	myGLCD.print(String(XBee_Addr64_LS,HEX), RIGHT, yXBee);

	yXBee = yXBee + yDelta;                                         // �������������� ������, ��������
	myGLCD.setColor(255, 255, 255);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[10])));   // "Addr Coordinat"
	myGLCD.print(buffer, CENTER, yXBee);
	myGLCD.setColor(0, 255, 255);
	atRequest.setCommand(shCmd);  
	sendAtCommand();
	delay(100);
	XBee_data2 = (unsigned long&)info_XBee_data1;
	yXBee = yXBee + yDelta;                                        // �������������� ������, ��������
	myGLCD.print("SH", LEFT, yXBee);
	myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
	atRequest.setCommand(slCmd);  
	sendAtCommand();
	delay(100);
	XBee_data2 = (unsigned long&)info_XBee_data1;
	yXBee = yXBee + yDelta;                                        // �������������� ������, ��������
	myGLCD.print("SL", LEFT, yXBee);
	myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
				  
	myGLCD.setColor(255, 255, 255);
	yXBee = yXBee + yDelta;                                        // �������������� ������, ��������
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[12])));  // "Network (MY) = "
	myGLCD.print(buffer, LEFT, yXBee);
	atRequest.setCommand(MYCmd);  
	sendAtCommand();
	delay(100);
	XBee_data2 = (unsigned long&)info_XBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);

	myGLCD.setColor(255, 255, 255);
	yXBee = yXBee + yDelta;                                        // �������������� ������, ��������
//	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[12])));  // "Network (MY) = "
	myGLCD.print("OI", LEFT, yXBee);
	atRequest.setCommand(OICmd);  
	sendAtCommand();
	delay(100);
	XBee_data2 = (unsigned long&)info_XBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);



	myGLCD.setColor(255, 255, 255);
	yXBee = yXBee + yDelta;                                        // �������������� ������, ��������
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[13])));  // "PAN ID (OP)  = "
	myGLCD.print(buffer, LEFT, yXBee);
	atRequest.setCommand(opCmd);  
	sendAtCommand();
	delay(100);
	XBee_data2 = (unsigned long&)info_XBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);
	
	myGLCD.setColor(255, 255, 255);
	yXBee = yXBee + yDelta;                                        // �������������� ������, ��������
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[14])));  // "ID (ID)      = "
	myGLCD.print(buffer, LEFT, yXBee);
	atRequest.setCommand(IDCmd);  
	sendAtCommand();
	delay(100);
	XBee_data2 = (unsigned long&)info_XBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);

	myGLCD.setColor(255, 255, 255);
	yXBee = yXBee + yDelta;// �������������� ������, ��������
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[15])));  // "Chanel (CH)  = "
	myGLCD.print(buffer, LEFT, yXBee);
	atRequest.setCommand(CHCmd);  
	sendAtCommand();
	XBee_data2 = (unsigned long&)info_XBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print("0x",193, yXBee);
	myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);

	myGLCD.setColor(255, 255, 255);
	yXBee = yXBee + yDelta;// �������������� ������, ��������
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[16])));  
	myGLCD.print(buffer, LEFT, yXBee);
	atRequest.setCommand(assocCmd); 
	sendAtCommand();
	XBee_data2 = (unsigned long&)info_XBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(XBee_data2, HEX), RIGHT, yXBee);


	myGLCD.setColor(255, 255, 255);
	yXBee = yXBee + yDelta;// �������������� ������, ��������
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[17])));  
	myGLCD.print(buffer, LEFT, yXBee);
	atRequest.setCommand(BDCmd); 
	sendAtCommand();
	XBee_data2 = (unsigned long&)info_XBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	switch (XBee_data2)
		{
		case 0:
			XBee_data2 = 1200;
			break;
		case 1:
			XBee_data2 = 2400;
			break;
		case 2:
			XBee_data2 = 4800;
			break;
		case 3:
			XBee_data2 = 9600;
			break;
		case 4:
			XBee_data2 = 19200;
			break;
		case 5:
			XBee_data2 = 38400;
			break;
		case 6:
			XBee_data2 = 57600;
			break;
		case 7:
			XBee_data2 = 115200;
			break;
			default:
		   XBee_data2 = 000000;
		}

	myGLCD.print(String(XBee_data2), RIGHT, yXBee);

	myGLCD.setColor(255, 255, 255);
	yXBee = yXBee + yDelta;// �������������� ������, ��������

	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[18])));   // "Volt(V) ";
	myGLCD.print(buffer, LEFT, yXBee);
	atRequest.setCommand(VoltCmd);   
	sendAtCommand();
	XBee_data2 = (unsigned long&)info_XBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	float XBee_data3 = XBee_data2;
	myGLCD.printNumF(XBee_data3/1023*1200/1000,2, RIGHT, yXBee,'.',2);
	myGLCD.setColor(255, 255, 255);
	yXBee = yXBee + yDelta;                                             // �������������� ������, ��������
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[27])));       // txt_temperature
	myGLCD.print(buffer, LEFT, yXBee);
	atRequest.setCommand(TPCmd);                                        // ����������� ������
	sendAtCommand();
	delay(100);
	XBee_data2 = (unsigned long&)info_XBee_data1;
	myGLCD.setColor(VGA_YELLOW);
	myGLCD.print(String(XBee_data2, DEC), RIGHT, yXBee);

	myGLCD.setColor(0, 0, 255);                                        // ���������� ������������� ��� ������
	myGLCD.fillRoundRect (2, 296, 238, 318);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (2, 296, 238, 318);
	myGLCD.setBackColor(0, 0, 255);
	myGLCD.setColor(255, 255, 255);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[19])));
	myGLCD.print(buffer, CENTER, 299);                                // ��������� ��������

	while (myTouch.dataAvailable()) {}
	while (true)
	{
		if (myTouch.dataAvailable())
		{
				myTouch.read();
				x=myTouch.getX();
				y=myTouch.getY();
		if ((y>=1) && (y<=319))  // Upper row  
			{
			if ((x>=1) && (x<=239))  // �����
				{
					waitForIt(1, 1, 239, 319);

					draw_menu2();

					return;
				}
			}
		}

	}				

 }
void time_flag_start()
 {
	 timeF = millis();
	 if (timeF>60000) flag_time = 1;
 }

void XBeeReadCount()
{
	zbTx = ZBTxRequest(addr64, payload, sizeof(payload));  
	xbee.send(zbTx); 
	if (xbee.readPacket(700))                                               //  ����� �������� ������� TX, �� ������� ����� �������
		{
		if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) 		// ������� �����! // ������ ���� znet tx status       
			{
				xbee.getResponse().getZBTxStatusResponse(txStatus);
				if (txStatus.getDeliveryStatus() == SUCCESS)                // �������� ������ ��������, ����� ����
					{
						Serial.println("Success.  time to celebrate!");     // �������, ����� ����������.
						myGLCD.setColor(VGA_LIME);
						myGLCD.fillRoundRect (195, 71, 233, 109);
						myGLCD.setColor(255, 255, 255);
						myGLCD.drawRoundRect (194, 70, 234, 110);
						myGLCD.setBackColor(0, 0, 0);
						delay(400); 
						myGLCD.setColor(0, 0, 0);
						myGLCD.fillRoundRect (195, 71, 233, 109);
						myGLCD.setColor(255, 255, 255);
	
						myGLCD.printNumI(1, 10+10, 10+10); 
						myGLCD.printNumI(1, 10+10, 98+10);
						myGLCD.printNumI(3, 102+10, 10+10);    
						myGLCD.printNumI(4, 102+10, 98+10);      
						myGLCD.printNumI(5, 25 , 205 );   
						myGLCD.printNumI(6, 83 , 205 );    
						myGLCD.printNumI(7, 141, 205 );       
						myGLCD.printNumI(8, 199, 205 );   

					}
				else 
					{
						Serial.println("The remote XBee did not receive our packet. is it powered on?");  	// ����������� XBee �� �������. �� �������?
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
		myGLCD.fillRoundRect (195, 71, 233, 109);
		myGLCD.setColor(255, 255, 255);
		myGLCD.drawRoundRect (194, 70, 234, 110);
		myGLCD.setBackColor(0, 0, 0);
		delay(400); 
		myGLCD.setColor(0, 0, 0);
		myGLCD.fillRoundRect (195, 71, 233, 109);
		myGLCD.setColor(255, 255, 255);
	}
} 

// -----------------------------------------------------------------------------------

void updateStrXBee(int val) // �������� ����� ������ ��� ����� ������ XBee
{

  if (stCurrentLen < lenStr)
  {
	stCurrent[stCurrentLen]=val;
	stCurrent[stCurrentLen+1]='\0';
	stCurrentLen++;
	myGLCD.setColor(0, 255, 0);
	myGLCD.print(stCurrent, LEFT, 300);
	if(stCurrentLen > lenStr -1)  myGLCD.setColor(255, 0, 0);
	myGLCD.printNumI(stCurrentLen, RIGHT, 300);
	myGLCD.setColor(0, 255, 0);
  }
  else
  {   // ����� ������ "������������!"
	myGLCD.setColor(255, 0, 0);
	myGLCD.print("                       ", CENTER, 300);
	myGLCD.print("\x89""EPE""\x89O\x88HEH\x86""E!", CENTER, 300);// ������������!
	delay(500);
	myGLCD.print("                       ", CENTER, 300);
	delay(500);
	myGLCD.print("\x89""EPE""\x89O\x88HEH\x86""E!", CENTER, 300);// ������������!
	delay(500);
	myGLCD.print("                       ", CENTER, 300);
	myGLCD.setColor(0, 255, 0);
	stCurrent[0]='\0';
	stCurrentLen=0;
  }
}
void XBee_SetH(int adr_xbee_h)
{
	lenStr = 8;
	int _adr_xbee_h = adr_xbee_h;
	klavXBee();
	if (ret == 1)
		{
			ret = 0;
			return;
		}
	strcpy(temp_stLast,stLast);
	long int li1 = strtol(temp_stLast, NULL, 16);                                     // ������������� ������ ����� ������ � �������� HEX	
	byte *m = (byte *)&li1;                                                       //��������� ������ �������� ������ ������������ �������� ��� ������ � ������
	for (int i=0; i<4; i++)
		{
			i2c_eeprom_write_byte(deviceaddress, i+_adr_xbee_h+2, m[i]);          // �������� � ������ ������ �������� ������ ������������
		}
}
void XBee_SetL(int adr_xbee_h)
{ 
	lenStr = 8;
	int _adr_xbee_h = adr_xbee_h;
	klavXBee();
	if (ret == 1)
		{
			ret = 0;
			return;
		}
	strcpy(temp_stLast,stLast);
	long int li1 = strtol(temp_stLast, NULL, 16);                                // ������������� ������ ����� ������ � �������� HEX	
	byte *m = (byte *)&li1;                                                       //��������� ������ �������� ������ ������������ �������� ��� ������ � ������
	for (int i=0; i<4; i++)
		{
			i2c_eeprom_write_byte(deviceaddress, i+_adr_xbee_h+6, m[i]);           // �������� � ������ ������ �������� ������ ������������
		}
 }
void XBee_Set_Network()
{
	lenStr = 4;
	klavXBee();
	if (ret == 1)
	{
		ret = 0;
		return;
	}
	strcpy(temp_stLast,stLast);
	long int li1 = strtol(temp_stLast, NULL, 16); // ������������� ������ ����� ������ � �������� HEX	
						
	byte *m = (byte *)&li1; //��������� ������ �������� ������ ������������ �������� ��� ������ � ������
	for (int i=0; i<2; i++)
		{
			i2c_eeprom_write_byte(deviceaddress, i+adr_xbee_network, m[i]); // �������� � ������ ������ �������� ������ ������������
		}
	commandValue[0]= i2c_eeprom_read_byte( deviceaddress, 1+adr_xbee_network);
	commandValue[1]= i2c_eeprom_read_byte( deviceaddress, 0+adr_xbee_network);

	myGLCD.print("                          ", CENTER, 300);
	myGLCD.print(" OK !", RIGHT, 300);// ��!
	delay(1500);
	//		  
	//if(strcmp(temp_stLast,stLast)!=0 ||stCurrentLen1 > 4 )
	//	{
	//		myGLCD.print("                         ", CENTER, 300);
	//		myGLCD.print(txt_err_pass_user, CENTER, 300);// ������ �����!
	//	//	result_minus = 0;
	//		delay(1500);
	//		return;
	//	}
	test_arRequestMod();              // �������� ������ � XBee
}

void sendAtCommand() 
{
	int i10;

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
  delay(100);
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
					Serial.print("Command return error code: ");
					Serial.println(atResponse.getStatus(), HEX);

					myGLCD.setColor(255 , 0, 0);
					myGLCD.fillRoundRect (278, 92, 318, 132);
					myGLCD.setColor(255, 255, 255);
					myGLCD.drawRoundRect (278, 92, 318, 132);
					myGLCD.setBackColor(0, 0, 0);
					delay(200); 
					XBee_alarm();
					delay(1000);
					myGLCD.setColor(0, 0, 0);
					myGLCD.fillRoundRect (278, 92, 318, 132);
					myGLCD.setColor(0, 0, 0);
					myGLCD.drawRoundRect (278, 92, 318, 132);
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
void testRemoteAtCommand()
 {
	// sendRemoteAtCommand();
  
  // ������ �������� ��� �� ������ ��� ������� DIO0
  remoteAtRequest.setCommand(IDCmd);
  remoteAtRequest.setCommandValue(IDValue);
  remoteAtRequest.setCommandValueLength(sizeof(IDValue));

  sendRemoteAtCommand();
  
  // it's a good idea to clear the set value so that the object can be reused for a query
  //��� ������� ����, ����� �������� ������������� ��������, ����� ������ ����� �������� ������������ ��� ������� 
  remoteAtRequest.clearCommandValue();
  
  // we're done
 // while (1) {};
 }
void test_arRequestMod()
{
//AtCommandRequest arRequestMod = AtCommandRequest(command,commandValue, commandValueLength);
//AtCommandRequest.setCommand(IDCmd);
//uint8_t command[]  = {'I','D'}; // ����� ���� (ID)
//uint8_t commandValue[]  = { 0x02, 0x35 };
//uint8_t commandValueLength = 2;

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
void read_HL_mem_XBee(int N_device )
 {
	//��������� �������������� ������ ZigBee �� ������.
	byte y[4];   ; //������ �� ������ ������� ������ �������� ������ ������������
		y[3]= i2c_eeprom_read_byte( deviceaddress, 3+N_device+2);
		i2c_eeprom_write_byte(deviceaddress, 3+adr_xbee_current_H, y[3]);    // �������� � ������ ������ 
		y[2]= i2c_eeprom_read_byte( deviceaddress, 2+N_device+2);
		i2c_eeprom_write_byte(deviceaddress, 2+adr_xbee_current_H, y[2]);    // �������� � ������ ������ 
		y[1]= i2c_eeprom_read_byte( deviceaddress, 1+N_device+2);
		i2c_eeprom_write_byte(deviceaddress, 1+adr_xbee_current_H, y[1]);    // �������� � ������ ������ 
		y[0]= i2c_eeprom_read_byte( deviceaddress, 0+N_device+2);
		i2c_eeprom_write_byte(deviceaddress, adr_xbee_current_H, y[0]);      // �������� � ������ ������ 
		XBee_Addr64_MS = (unsigned long&) y;  // ������� ��������������� ������� ������


		//������ �� ������ ������� ������ �������� ������ ������������
		y[3]= i2c_eeprom_read_byte( deviceaddress, 3+N_device+6);
		i2c_eeprom_write_byte(deviceaddress, 3+adr_xbee_current_L, y[3]);    // �������� � ������ ������ 
		y[2]= i2c_eeprom_read_byte( deviceaddress, 2+N_device+6);
		i2c_eeprom_write_byte(deviceaddress, 2+adr_xbee_current_L, y[2]);    // �������� � ������ ������ 
		y[1]= i2c_eeprom_read_byte( deviceaddress, 1+N_device+6);
		i2c_eeprom_write_byte(deviceaddress, 1+adr_xbee_current_L, y[1]);    // �������� � ������ ������ 
		y[0]= i2c_eeprom_read_byte( deviceaddress, 0+N_device+6);
		i2c_eeprom_write_byte(deviceaddress, adr_xbee_current_L, y[0]);    // �������� � ������ ������ 
		XBee_Addr64_LS = (unsigned long&) y;  // ������� ��������������� ������� ������ � 
		Serial.println(XBee_Addr64_MS, HEX); 
		Serial.println(XBee_Addr64_LS, HEX); 
		addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);                                     // SH + SL Address of receiving XBee
}
void draw_view_adr_device()
{
	int XBee_x, XBee_y, x, y;
	int yXBee = 32;                                                  // ��������� ����� �������� ����� ������
	int yDelta = 16;                                                 // ������ �������� ����
	int n_page = 1;
	//int adr_device = 0;
	myGLCD.clrScr();                                                 // �������� ����� CENTER
	myGLCD.setColor(0, 0, 255);
	myGLCD.fillRoundRect (2, 2, 239, 25);                            // ���������� ������������� ��� ������
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (2, 2, 239, 25);
	myGLCD.setColor(255, 255, 255);
	myGLCD.setBackColor(0, 0, 255);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[28])));     // ���������� XBee
	myGLCD.print(buffer, CENTER, 5);

	myGLCD.setColor(0, 0, 255);                                        // ���������� ������������� ��� ������
	myGLCD.fillRoundRect (2, 233, 82, 273);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (2, 233, 82, 273);
	
	myGLCD.setColor(0, 0, 255);                                        // ���������� ������������� ��� ������
	myGLCD.fillRoundRect (87, 233, 153, 273);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (87, 233, 153, 273);
	myGLCD.setBackColor(0, 0, 255);
	myGLCD.print("   ", CENTER, 245);                                 //  ��������
	myGLCD.printNumI(n_page, CENTER, 245);                            // ��������� ��������
	myGLCD.setBackColor(0, 0, 0);

	myGLCD.setColor(0, 0, 255);                                        // ���������� ������������� ��� ������
	myGLCD.fillRoundRect (158, 233, 238, 273);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (158, 233, 238, 273);

	myGLCD.setColor(0, 0, 255);                                        // ���������� ������������� ��� ������
	myGLCD.fillRoundRect (2, 278, 238, 318);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect (2, 278, 238, 318);
	myGLCD.setBackColor(0, 0, 255);
	myGLCD.setColor(255, 255, 255);
	strcpy_P(buffer, (char*)pgm_read_word(&(table_message[19])));
	myGLCD.print(buffer, CENTER, 290);                                // ��������� ��������
}

void view_adr_device()
{
	int x, y;
	int n_page = 1;
	int adr_device = 0;
	draw_view_adr_device();
	while (myTouch.dataAvailable()) {}
	view_page(n_page);

	while (true)
	{
		if (myTouch.dataAvailable())
		{
				myTouch.read();
				x=myTouch.getX();
				y=myTouch.getY();

			 if ((y>=32) && (y<=64))                                  // ������ 1
				{
					waitForIt(1, 32, 239, 64);
					number_device = ((n_page-1) * 6)+1;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(number_device, CENTER, 245);     // 
					myGLCD.setBackColor(0, 0, 0);
					adr_device = adr_start_baseHL + ((number_device-1) * 10);
					XBee_SetH(adr_device);
					XBee_SetL(adr_device);
					Serial.println(adr_device);
					draw_view_adr_device();
					view_page(n_page);
				}
			 if ((y>=64) && (y<=96))                                  // ������ 2
				{
					waitForIt(1, 64, 239, 96);
					number_device = ((n_page-1) * 6)+2;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(number_device, CENTER, 245);     // 
					myGLCD.setBackColor(0, 0, 0);
					adr_device = adr_start_baseHL + ((number_device-1) * 10);
					XBee_SetH(adr_device);
					XBee_SetL(adr_device);
					Serial.println(adr_device);
					draw_view_adr_device();
					view_page(n_page);
				}
			if ((y>=96) && (y<=128))                                  // ������ 3
				{
					waitForIt(1, 96, 239, 128);
					number_device = ((n_page-1) * 6)+3;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(number_device, CENTER, 245);     // 
					myGLCD.setBackColor(0, 0, 0);
					adr_device = adr_start_baseHL + ((number_device-1) * 10);
					XBee_SetH(adr_device);
					XBee_SetL(adr_device);
					Serial.println(adr_device);
					draw_view_adr_device();
					view_page(n_page);
				}
			if ((y>=128) && (y<=160))                                  // ������ 4
				{
					if(n_page-1 < 42)
					{
						number_device = ((n_page-1) * 6)+4;
						waitForIt(1, 128, 239, 160);
						myGLCD.setBackColor(0, 0, 255);
						myGLCD.print("   ", CENTER, 245);                 //  ��������
						myGLCD.printNumI(number_device, CENTER, 245);     // 
						myGLCD.setBackColor(0, 0, 0);
						adr_device = adr_start_baseHL + ((number_device-1) * 10);
						XBee_SetH(adr_device);
						XBee_SetL(adr_device);
						Serial.println(adr_device);
						draw_view_adr_device();
						view_page(n_page);
					}
				}
			if ((y>=160) && (y<=192))                                  // ������ 5
				{
					if(n_page-1 < 42)
					{
						number_device = ((n_page-1) * 6)+5;
						waitForIt(1, 160, 239, 192);
						myGLCD.setBackColor(0, 0, 255);
						myGLCD.print("   ", CENTER, 245);                 //  ��������
						myGLCD.printNumI(number_device, CENTER, 245);     // 
						myGLCD.setBackColor(0, 0, 0);
						adr_device = adr_start_baseHL + ((number_device-1) * 10);
						XBee_SetH(adr_device);
						XBee_SetL(adr_device);
						Serial.println(adr_device);
						draw_view_adr_device();
						view_page(n_page);
					}
				}
			if ((y>=192) && (y<=224))                                  // ������ 6
				{
					if(n_page-1 < 42)
					{
						number_device = ((n_page-1) * 6)+6;
						waitForIt(1, 192, 239, 224);
						myGLCD.setBackColor(0, 0, 255);
						myGLCD.print("   ", CENTER, 245);                 //  ��������
						myGLCD.printNumI(number_device, CENTER, 245);     // 
						myGLCD.setBackColor(0, 0, 0);
						adr_device = adr_start_baseHL + ((number_device-1) * 10);
						XBee_SetH(adr_device);
						XBee_SetL(adr_device);
						Serial.println(adr_device);
						draw_view_adr_device();
						view_page(n_page);
					}
				}

		if ((y>=233) && (y<=273))                                     // Upper row  
			{
			  if ((x>=2) && (x<=82))                                  // �����
				{
					waitForIt(2, 233, 82, 273);
					n_page--;
					if(n_page <1) n_page = 1;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(n_page, CENTER, 245);            // ��������� ��������
					myGLCD.setBackColor(0, 0, 0);
					view_page(n_page);
				}
			  if ((x>=87) && (x<=153))                                  // �����
				{
					waitForIt(87, 233, 153, 273);
					n_page = 1;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(n_page, CENTER, 245);            // ��������� ��������
					myGLCD.setBackColor(0, 0, 0);
					view_page(n_page);
				}
			  if ((x>=158) && (x<=238))                               // �����
				{
					waitForIt(158, 233, 238, 273);
					n_page++;
					if(n_page > 43) n_page = 43;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(n_page, CENTER, 245);            // ��������� ��������
					myGLCD.setBackColor(0, 0, 0);
					view_page(n_page);
				}
			}
		if ((y>=278) && (y<=318))                                    // Upper row  
			{
			if ((x>=2) && (x<=238))                                  // �����
				{
					waitForIt(2, 278, 238, 318);
					return;
				}
			}
		}
	}			
}
void view_page(int block_n)
{
	int XBee_x, XBee_y, x, y;
	int yXBee = 32;                                                  // ��������� ����� �������� ����� ������
	int yDelta = 16;                                                 // ������ �������� ����
	int n_bl_max = 6;
	if(block_n == 43) n_bl_max = 4;
	int adr_device = adr_start_baseHL + ((block_n-1) * 10*6) ;
	myGLCD.setColor(0, 0, 0);
	myGLCD.fillRoundRect (1, 26, 240, 232);                            // ���������� ������������� ��� ������
	myGLCD.setBackColor(0, 0, 0);
	myGLCD.setColor(0, 255, 255);

	for (int n_bl = 0; n_bl<n_bl_max; n_bl++)
	{
		Serial.println(adr_device);
		read_adr_device(adr_device);
		myGLCD.printNumI(((block_n-1) * 6)+n_bl+1, 2, yXBee+8);  
		myGLCD.print("HS", 60, yXBee);
		myGLCD.print(String(XBee_Addr64_MS_tmp,HEX), RIGHT, yXBee);          //
		yXBee = yXBee + yDelta;                                          // �������������� ������, ��������  ����
		myGLCD.print("LS", 60, yXBee);
		myGLCD.print(String(XBee_Addr64_LS_tmp,HEX), RIGHT, yXBee);
		yXBee = yXBee + yDelta; 
		adr_device+=10;
	}
}
void restore_default_device()
{
byte y[4];   ; //������ �� ������ ������� ������ �������� ������ ������������
	y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_xbee_current_H);
	y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_xbee_current_H);
	y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_xbee_current_H);
	y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_xbee_current_H);
	XBee_Addr64_MS = (unsigned long&) y;  // ������� ��������������� ������� ������

	//������ �� ������ ������� ������ �������� ������ ������������
	y[3]= i2c_eeprom_read_byte( deviceaddress, 3+adr_xbee_current_L);
	y[2]= i2c_eeprom_read_byte( deviceaddress, 2+adr_xbee_current_L);
	y[1]= i2c_eeprom_read_byte( deviceaddress, 1+adr_xbee_current_L);
	y[0]= i2c_eeprom_read_byte( deviceaddress, 0+adr_xbee_current_L);
	XBee_Addr64_LS = (unsigned long&) y;  // ������� ��������������� ������� ������ � 
	addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);                                     // SH + SL Address of receiving XBee
}
void read_adr_device(int N_device)
{
//��������� �������������� ������ XBee �� ������.
byte y[4];   ; //������ �� ������ ������� ������ �������� ������ ������������
	y[3]= i2c_eeprom_read_byte( deviceaddress, 3+N_device+2);
	y[2]= i2c_eeprom_read_byte( deviceaddress, 2+N_device+2);
	y[1]= i2c_eeprom_read_byte( deviceaddress, 1+N_device+2);
	y[0]= i2c_eeprom_read_byte( deviceaddress, 0+N_device+2);
	XBee_Addr64_MS_tmp = (unsigned long&) y;  // ������� ��������������� ������� ������

	//������ �� ������ ������� ������ �������� ������ ������������
	y[3]= i2c_eeprom_read_byte( deviceaddress, 3+N_device+6);
	y[2]= i2c_eeprom_read_byte( deviceaddress, 2+N_device+6);
	y[1]= i2c_eeprom_read_byte( deviceaddress, 1+N_device+6);
	y[0]= i2c_eeprom_read_byte( deviceaddress, 0+N_device+6);
	XBee_Addr64_LS_tmp = (unsigned long&) y;  // ������� ��������������� ������� ������ � 

}
void set_adr_device()
{
	int x, y;
	int n_page = 1;
	int adr_device = 0;
	draw_view_adr_device();
	while (myTouch.dataAvailable()) {}
	view_page(n_page);

	while (true)
	{
		if (myTouch.dataAvailable())
		{
				myTouch.read();
				x=myTouch.getX();
				y=myTouch.getY();

			 if ((y>=32) && (y<=64))                                  // ������ 1
				{
					waitForIt(1, 32, 239, 64);
					number_device = ((n_page-1) * 6)+1;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(number_device, CENTER, 245);     // 
					myGLCD.setBackColor(0, 0, 0);
					adr_device = adr_start_baseHL + ((number_device-1) * 10);
					read_HL_mem_XBee(adr_device);
					Serial.println(adr_device);
					draw_view_adr_device();
					view_page(n_page);
				}
			 if ((y>=64) && (y<=96))                                  // ������ 2
				{
					waitForIt(1, 64, 239, 96);
					number_device = ((n_page-1) * 6)+2;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(number_device, CENTER, 245);     // 
					myGLCD.setBackColor(0, 0, 0);
					adr_device = adr_start_baseHL + ((number_device-1) * 10);
					read_HL_mem_XBee(adr_device);
					Serial.println(adr_device);
					draw_view_adr_device();
					view_page(n_page);
				}
			if ((y>=96) && (y<=128))                                  // ������ 3
				{
					waitForIt(1, 96, 239, 128);
					number_device = ((n_page-1) * 6)+3;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(number_device, CENTER, 245);     // 
					myGLCD.setBackColor(0, 0, 0);
					adr_device = adr_start_baseHL + ((number_device-1) * 10);
					read_HL_mem_XBee(adr_device);
					Serial.println(adr_device);
					draw_view_adr_device();
					view_page(n_page);
				}
			if ((y>=128) && (y<=160))                                  // ������ 4
				{
					if(n_page-1 < 42)
					{
						number_device = ((n_page-1) * 6)+4;
						waitForIt(1, 128, 239, 160);
						myGLCD.setBackColor(0, 0, 255);
						myGLCD.print("   ", CENTER, 245);                 //  ��������
						myGLCD.printNumI(number_device, CENTER, 245);     // 
						myGLCD.setBackColor(0, 0, 0);
						adr_device = adr_start_baseHL + ((number_device-1) * 10);
						read_HL_mem_XBee(adr_device);
						Serial.println(adr_device);
						draw_view_adr_device();
						view_page(n_page);
					}
				}
			if ((y>=160) && (y<=192))                                  // ������ 5
				{
					if(n_page-1 < 42)
					{
						number_device = ((n_page-1) * 6)+5;
						waitForIt(1, 160, 239, 192);
						myGLCD.setBackColor(0, 0, 255);
						myGLCD.print("   ", CENTER, 245);                 //  ��������
						myGLCD.printNumI(number_device, CENTER, 245);     // 
						myGLCD.setBackColor(0, 0, 0);
						adr_device = adr_start_baseHL + ((number_device-1) * 10);
						read_HL_mem_XBee(adr_device);
						Serial.println(adr_device);
						draw_view_adr_device();
						view_page(n_page);
					}
				}
			if ((y>=192) && (y<=224))                                  // ������ 6
				{
					if(n_page-1 < 42)
					{
						number_device = ((n_page-1) * 6)+6;
						waitForIt(1, 192, 239, 224);
						myGLCD.setBackColor(0, 0, 255);
						myGLCD.print("   ", CENTER, 245);                 //  ��������
						myGLCD.printNumI(number_device, CENTER, 245);     // 
						myGLCD.setBackColor(0, 0, 0);
						adr_device = adr_start_baseHL + ((number_device-1) * 10);
						read_HL_mem_XBee(adr_device);
						Serial.println(adr_device);
						draw_view_adr_device();
						view_page(n_page);
					}
				}

		if ((y>=233) && (y<=273))                                     // Upper row  
			{
			  if ((x>=2) && (x<=82))                                  // �����
				{
					waitForIt(2, 233, 82, 273);
					n_page--;
					if(n_page <1) n_page = 1;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(n_page, CENTER, 245);            // ��������� ��������
					myGLCD.setBackColor(0, 0, 0);
					view_page(n_page);
				}
			  if ((x>=87) && (x<=153))                                  // �����
				{
					waitForIt(87, 233, 153, 273);
					n_page = 1;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(n_page, CENTER, 245);            // ��������� ��������
					myGLCD.setBackColor(0, 0, 0);
					view_page(n_page);
				}
			  if ((x>=158) && (x<=238))                               // �����
				{
					waitForIt(158, 233, 238, 273);
					n_page++;
					if(n_page > 43) n_page = 43;
					myGLCD.setBackColor(0, 0, 255);
					myGLCD.print("   ", CENTER, 245);                 //  ��������
					myGLCD.printNumI(n_page, CENTER, 245);            // ��������� ��������
					myGLCD.setBackColor(0, 0, 0);
					view_page(n_page);
				}
			}
		if ((y>=278) && (y<=318))                                    // Upper row  
			{
			if ((x>=2) && (x<=238))                                  // �����
				{
					waitForIt(2, 278, 238, 318);
					return;
				}
			}
		}
	}			
}

void XBee_alarm()
{
	 word val;
	 word i = 0;
		payload[0] = 0x01;
		//payload[1] = 0x00;
		//payload[2] = 0x0A;
		//payload[3] = 0x00;
		//payload[4] = 0x1F;
	 //funcType = 9;
	 //clock_read();
	 //payload[0] = funcType;
	 //payload[1] = 0;//i2c_eeprom_read_byte( deviceaddress,adr_level_war_gaz_max+1);
	 //payload[2] = 0;//i2c_eeprom_read_byte( deviceaddress,adr_level_war_gaz_max);

	 //for (int i_xbee = 0;i_xbee<20;i_xbee++)
	 //{
  //  	 payload[3+i_xbee] = i2c_eeprom_read_byte( deviceaddress,adr_n_user+i_xbee);
	 //}

	 //payload[23] = date;
	 //payload[24] = mon;
	 //byte *x = (byte *)&year;     //��������� ������  �������� ��� ������ � ������
	 //payload[25] = x[0];
	 //payload[26] = x[1];
	 //payload[27] = hour;
	 //payload[28] = min;
	 //stCurrentLen_telef = i2c_eeprom_read_byte( deviceaddress,adr_n_telef-2);// ������ ������ ������������
		//			
		//	for (int z=0; z<stCurrentLen_telef; z++)
		//		{
		//			payload[29+z] = i2c_eeprom_read_byte( deviceaddress,adr_n_telef+z);
		//		} 
	 XBeeWrite();

} 

byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress )
{

	byte rdata = 0xFF;
	Wire.beginTransmission(deviceaddress);
	Wire.write((int)(eeaddress >> 8)); // MSB
	Wire.write((int)(eeaddress & 0xFF)); // LSB
	Wire.endTransmission();
	Wire.requestFrom(deviceaddress,1);
	if (Wire.available()) rdata = Wire.read();
	//delay(10);
	return rdata;
	
}
void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data )
{
	int rdata = data;
	Wire.beginTransmission(deviceaddress);
	Wire.write((int)(eeaddress >> 8)); // MSB
	Wire.write((int)(eeaddress & 0xFF)); // LSB
	Wire.write(rdata);
	Wire.endTransmission();
	delay(20);
}
void format_memory()
{
	   if (int x = i2c_eeprom_read_byte(deviceaddress,510) != 5)

		  {	// write a 0 to all 500 bytes of the EEPROM
			myGLCD.setColor(255, 255, 255);
			myGLCD.print("Format!",CENTER, 80);// "Format!"
			//delay (500);
			//myGLCD.clrScr();
			for (int i = 0; i < 4095; i++)
				{
				  i2c_eeprom_write_byte(deviceaddress,i, 0);
				}
			i2c_eeprom_write_byte(deviceaddress,510, 5); 
			myGLCD.clrScr();
			myGLCD.setColor(255, 255, 255);
			myGLCD.print("Format OK!",CENTER, 80);// "Format Ok!"
			delay (500);
			myGLCD.clrScr();
		  }
}

void format_memory1()
{
	int a = 1000;
	int xp = 0;
	long int li1 = 0;   
	int adr_xbee_h = 1000;
	for (int ip = 0; ip < 256; ip++)
		{
		  li1 = ip;                                     // ������������� ������ ����� ������ � �������� HEX	
						
		byte *m = (byte *)&li1;                                                       //��������� ������ �������� ������ ������������ �������� ��� ������ � ������
		for (int i=0; i<4; i++)
			{
				i2c_eeprom_write_byte(deviceaddress, i+adr_xbee_h+2, m[i]); // �������� � ������ ������ �������� ������ ������������
				i2c_eeprom_write_byte(deviceaddress, i+adr_xbee_h+6, m[i]); // �������� � ������ ������ �������� ������ ������������
			}

			//i2c_eeprom_write_byte(deviceaddress,a, i);
				Serial.println(adr_xbee_h);
				adr_xbee_h += 10;
		}
}

void read_memory1()
{
	int a = 1000;
	int xp = 0;

	for (int i = 0; i < 256; i++)
		{
			Serial.print(a);
			Serial.print("  ");
			xp = i2c_eeprom_read_byte(deviceaddress,a);
			Serial.println(xp);
			a += 10;
		}

}

void FileOpen()
{
  Serial.println("FileOpen");
  int temp_file_name = 0;
  preob_num_str();
  while (sd.exists(fileName)) 
  {
	if (fileName[BASE_NAME_SIZE + 1] != '9') 
	{
	  fileName[BASE_NAME_SIZE + 1]++;
	}
	else if (fileName[BASE_NAME_SIZE] != '9') 
	{
	  fileName[BASE_NAME_SIZE + 1] = '0';
	  fileName[BASE_NAME_SIZE]++;
	}
	else 
	{
		//regBank.set(122,1);                              // ���� ������  �������� �����
	}
  }

 
  temp_file_name = ((fileName[BASE_NAME_SIZE]-48)*10) + (fileName[BASE_NAME_SIZE + 1]-48); // �������������� ����������� ������ ����� � �����
 // regBank.set(adr_reg_file_name,temp_file_name);      
//  i2c_eeprom_write_byte(0x50, adr_file_name_count,temp_file_name);                 // ��� ����� ���� ������� ������ ����� �������� � "0"

  if (!myFile.open(fileName, O_CREAT | O_WRITE | O_EXCL)) //sdError("file.open");
  {
	//regBank.set(122,1);                              // ���� ������  �������� �����
  }
  else
  {
	Serial.print(fileName);
	Serial.println(F("  Open Ok!"));

	DateTime now = RTC.now();

	//regBank.set(adr_Mic_Start_day , now.day());           // ����� ������ �����
	//regBank.set(adr_Mic_Start_month, now.month());
	//regBank.set(adr_Mic_Start_year, now.year());
	//regBank.set(adr_Mic_Start_hour, now.hour());
	//regBank.set(adr_Mic_Start_minute, now.minute());
	//regBank.set(adr_Mic_Start_second, now.second());
	//// �������� 			
	//regBank.set(adr_Time_Test_day, 0); 
	//regBank.set(adr_Time_Test_hour, 0); 
	//regBank.set(adr_Time_Test_minute, 0); 
	//regBank.set(adr_Time_Test_second, 0); 
	myFile.println ("");
	myFile.print ("Report of test module Audio-1 N ");
	// �������� ������ int �� ���������
	//int val_3 = regBank.get(40010);
	//int val_2 = regBank.get(40011);
	//int val_1 = regBank.get(40012);
	//int val_0 = regBank.get(40013);
	 
	// ����������� ��� �������������� ��������� ������
	 //byte *x3 = (byte *)&val_3;  
	 //byte *x2 = (byte *)&val_2;
	 //byte *x1 = (byte *)&val_1;
	 //byte *x0 = (byte *)&val_0;

	 // �������� ����� � ���� �������� byte  � ������
	//byte y[4];  
	//	y[3]= x3[0];
	//	y[2]= x2[0];
	//	y[1]= x1[0];
	//	y[0]= x0[0];

 // unsigned long *yx = (unsigned long *)&y;

 // number_audio = *yx;

 // Serial.println(number_audio);

	myFile.println ("");
	myFile.println ("");
	myFile.println ("");
	myFile.print ("Start test   ");
	file_print_date();
	myFile.println ("");
	myFile.println ("");
                                 
//	Serial.println(fileName);
   }
}
void FileClose()
{
	//Serial.println(fileName);
	myFile.println ("");
	myFile.print ("Stop test   ");
	file_print_date();
	myFile.println ("");
	myFile.close();

	if (sd.exists(fileName))
		{ 
			Serial.println();
			Serial.print(fileName);
			Serial.println("  Close  OK!.");
		}
	else 
		{
			Serial.println();
			Serial.print(fileName);
			Serial.println(" doesn't exist.");  
		}
}
void list_file()
{
 while (file.openNext(sd.vwd(), O_READ))
  {
	file.printName(&Serial);
	Serial.write(' ');
	file.printModifyDateTime(&Serial);
	Serial.write(' ');
	file.printFileSize(&Serial);
	if (file.isDir()) {
	  // Indicate a directory.
	  Serial.write('/');
	}
	Serial.println();
	file.close();
  }
}
void load_list_files()
{

	if (!sd.begin(chipSelect)) 
		{
			Serial.println("initialization SD failed!");
		}
	else
		{
	
		while (file.openNext(sd.vwd(), O_READ))
		  {
			file.printName(&Serial2);
			Serial2.println();
			file.printName(&Serial);
			Serial.println();

			file.close();
		  } 
		   Serial2.flush();
		 }
		delay(100);
	//	Serial2.println("Files end");
	//	Serial.println("Files end");
// regBank.set(adr_control_command,0);
}
void file_name()
{

   preob_num_str();

  while (sd.exists(fileName)) 
  {
	if (fileName[BASE_NAME_SIZE + 1] != '9') 
	{
	  fileName[BASE_NAME_SIZE + 1]++;
	}
	else if (fileName[BASE_NAME_SIZE] != '9') 
	{
	  fileName[BASE_NAME_SIZE + 1] = '0';
	  fileName[BASE_NAME_SIZE]++;
	}
	else 
	{
		Serial.println("Can't create file name");
//	  sdError("Can't create file name");
	}
  }
  if (!myFile.open(fileName, O_CREAT | O_WRITE | O_EXCL)) //sdError("file.open");
  {
  }
  Serial.print(F("Logging to: "));
  Serial.println(fileName);
  myFile.close();
  Serial.println("done.");
 } 
void file_print_date()  //���������  ������ ���� � ����
	{
	  DateTime now = RTC.now();
	  myFile.print(now.day(), DEC);
	  myFile.print('/');
	  myFile.print(now.month(), DEC);
	  myFile.print('/');
	  myFile.print(now.year(), DEC);//Serial display time
	  myFile.print(' ');
	  myFile.print(now.hour(), DEC);
	  myFile.print(':');
	  myFile.print(now.minute(), DEC);
	  myFile.print(':');
	  myFile.print(now.second(), DEC);
  }
void file_del_SD()
{
	if (!sd.begin(chipSelect)) 
		{
			//Serial.println("initialization SD failed!");
			//regBank.set(125,false); 
		}
	else
		{
			  myFile = sd.open(fileName_F);
				//myFile = sd.open("example.txt", FILE_WRITE);
				//myFile.close();

			  // Check to see if the file exists:
			  if (sd.exists(fileName_F)) 
			  {
				 // regBank.set(125,true); 
				  sd.remove(fileName_F);
			   // Serial.println("example.txt exists.");
			  }
			  else 
			  {
			   // Serial.println("example.txt doesn't exist.");
				//regBank.set(125,false); 
			  }
			}
	delay(100);
}
void set_SD()
{
		if (!sd.begin(chipSelect)) 
		{
			//Serial.println("initialization SD failed!");
		}
	else
		{
			  myFile = sd.open("example.txt", FILE_WRITE);
			  myFile.close();

			  // Check to see if the file exists:
			  if (sd.exists("example.txt")) 
			  {
				  sd.remove("example.txt");
			   // Serial.println("example.txt exists.");
			  }
			  else 
			  {
			   // Serial.println("example.txt doesn't exist.");
			  }
			}

	delay(100);
}
void preob_num_str() // ��������� ������������ ����� �����, ���������� �� ������� ���� � �������� ������
{
	DateTime now = RTC.now();
	day   = now.day();
	month = now.month();
	year  = now.year();
	int year_temp = year-2000;

	itoa (year_temp,str_year_file, 10);                                        // �������������� ���� ��� � ������ ( 10 - ���������� ������) 

	if (month <10)
		{
		   itoa (0,str_mon_file0, 10);                                         //  �������������� ���� �����  � ������ ( 10 - ���������� ������) 
		   itoa (month,str_mon_file10, 10);                                    //  �������������� ����� � ������ ( 10 - ���������� ������) 
		   sprintf(str_mon_file, "%s%s", str_mon_file0, str_mon_file10);       // �������� 2 �����
		}
	else
		{
		   itoa (month,str_mon_file, 10);                                      // �������������� ����� � ������ ( 10 - ���������� ������) 
		}
	if (day <10)
		{
		   itoa (0,str_day_file0, 10);                                         // �������������� ����� � ������ ( 10 - ���������� ������) 
		   itoa (day,str_day_file10, 10);                                      // �������������� ����� � ������ ( 10 - ���������� ������) 
		   sprintf(str_day_file, "%s%s", str_day_file0, str_day_file10);       // �������� 2 �����
		}
	else
		{
		itoa (day,str_day_file, 10);                                           // �������������� ����� � ������ ( 10 - ���������� ������) 
		}
		 
	sprintf(str1_1, "%s%s",str_year_file, str_mon_file);                         // �������� 2 �����
	sprintf(str2_1, "%s%s",str1_1, str_day_file);                                // �������� 2 �����
	sprintf(fileName, "%s%s", str2_1, "00.KAM");                                 // ��������� ����� ����� � file_name
	//Serial.println(fileName);
	//regBank.set(adr_reg_temp_day, day);  
	//regBank.set(adr_reg_temp_mon, month); 
	//regBank.set(adr_reg_temp_year, year-2000); 
	//char* strcpy(char* fileName_p, const char* fileName);
	//Serial.println(fileName_p);
}


void setup_pin()
{
	pinMode(led_13, OUTPUT);                             //
	digitalWrite(led_13, HIGH);                          //
	pinMode(KN1, INPUT); 
	pinMode(KN2, INPUT); 
	pinMode(KN3, INPUT); 
	pinMode(KN4, INPUT); 
	pinMode(KN5, INPUT); 
	pinMode(KN6, INPUT); 
	pinMode(KN7, INPUT); 
	pinMode(KN8, INPUT); 

	digitalWrite(KN1, HIGH); 
	digitalWrite(KN2, HIGH); 
	digitalWrite(KN3, HIGH); 
	digitalWrite(KN4, HIGH); 
	digitalWrite(KN5, HIGH); 
	digitalWrite(KN6, HIGH); 
	digitalWrite(KN7, HIGH); 
	digitalWrite(KN8, HIGH); 
}
void setup()
{
	Serial.begin(9600);                                    // ����������� � USB ��
//	Serial1.begin(115200);                                 // ����������� �
	Serial2.begin(9600);                                 // ����������� �
	xbee.setSerial(Serial2);
	//Serial3.begin(115200);                                 // ����������� �
	Serial.println(" ");
	Serial.println(" ***** Start system  *****");
	Serial.println(" ");
	myGLCD.InitLCD(0);
	myGLCD.clrScr();
	myGLCD.setFont(BigFont);
	myTouch.InitTouch(0);
	delay(1000);
	//myTouch.setPrecision(PREC_MEDIUM);
	myTouch.setPrecision(PREC_HI);
	//myTouch.setPrecision(PREC_EXTREME);
	myButtons.setTextFont(BigFont);
	myButtons.setSymbolFont(Dingbats1_XL);
	Wire.begin();
	if (!RTC.begin())                                      // ��������� �����
	{
		Serial.println("RTC failed");
		while (1);
	}
	 SdFile::dateTimeCallback(dateTime); 
	pinMode(53, OUTPUT);                                          // ��������� ������ SD
	if (!sd.begin(chipSelect)) 
		{
			Serial.println("initialization SD failed!");
		}
	else
		{
			Serial.println("initialization SD successfully.");
		}

	SdFile::dateTimeCallback(dateTime);                          // ��������� ������� ������ �����

	serial_print_date();                                   // ������ ���� � �������
	setup_pin();
	Serial.print(F("FreeRam: "));
	Serial.println(FreeRam());
	restore_default_device();

	//format_memory1();
	//read_memory1();
	//format_memory();
	Serial.println(" ");                                   //
	Serial.println("System initialization OK!.");          // ���������� � ���������� ���������
	//pass_start();                                        // ������ �� �����
}
void loop()
{
	klav_Glav_Menu();
}