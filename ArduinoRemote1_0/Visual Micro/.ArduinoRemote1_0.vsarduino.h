/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino/Genuino Mega w/ ATmega2560 (Mega 2560), Platform=avr, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __AVR_ATmega2560__
#define F_CPU 16000000L
#define ARDUINO 165
#define ARDUINO_AVR_MEGA2560
#define ARDUINO_ARCH_AVR
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
//#define __ATTR_PURE__
//#define __ATTR_CONST__
#define __inline__
//#define __asm__ 
#define __volatile__
#define GCC_VERSION 40801
#define volatile(va_arg) 
#define _CONST
typedef void *__builtin_va_list;
#define __builtin_va_start
#define __builtin_va_end
//#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
#ifndef __builtin_constant_p
#define __builtin_constant_p __attribute__((__const__))
#endif
#ifndef __builtin_strlen
#define __builtin_strlen  __attribute__((__const__))
#endif
#define NEW_H
/*
#ifndef __ATTR_CONST__
#define __ATTR_CONST__ __attribute__((__const__))
#endif

#ifndef __ATTR_MALLOC__
#define __ATTR_MALLOC__ __attribute__((__malloc__))
#endif

#ifndef __ATTR_NORETURN__
#define __ATTR_NORETURN__ __attribute__((__noreturn__))
#endif

#ifndef __ATTR_PURE__
#define __ATTR_PURE__ __attribute__((__pure__))
#endif            
*/
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}



#include <arduino.h>
#include <pins_arduino.h> 
#undef F
#define F(string_literal) ((const PROGMEM char *)(string_literal))
#undef PSTR
#define PSTR(string_literal) ((const PROGMEM char *)(string_literal))
#undef cli
#define cli()
#define pgm_read_byte(address_short)
#define pgm_read_word(address_short)
#define pgm_read_word2(address_short)
#define digitalPinToPort(P)
#define digitalPinToBitMask(P) 
#define digitalPinToTimer(P)
#define analogInPinToBit(P)
#define portOutputRegister(P)
#define portInputRegister(P)
#define portModeRegister(P)

void sdError_F(const __FlashStringHelper* str);
void debugPrint();
uint8_t writeCache(uint32_t lbn);
void initSizes();
void clearCache(uint8_t addSig);
void clearFatDir(uint32_t bgn, uint32_t count);
uint16_t lbnToCylinder(uint32_t lbn);
uint8_t lbnToHead(uint32_t lbn);
uint8_t lbnToSector(uint32_t lbn);
void writeMbr();
uint32_t volSerialNumber();
void makeFat16();
void makeFat32();
void formatCard();
void formatSD();
void print_up();
void draw_menu4();
void draw_menu5();
void draw_menu6();
void draw_menu7();
void draw_menu8();
void klav_menu4();
void klav_menu5();
void klav_menu6();
void klav_menu7();
void klav_menu8();
void set_n_user_start();
void set_pass_user_start();
void interval_start();
void set_interval(int adr_interval);
void set_pass_admin_start();
void pass_off();
void view_on_off();
void set_power();
void view_set_power(int powert, int power);
void search_XBee();
void drawMenuReset();
void klav_Menu_Reset();
void drawMenuBlockKN();
void klav_MenuBlockKN();
void waitForIt(int x1, int y1, int x2, int y2);
void waitForIt_inv();
void waitForIt_page(int x1, int y1, int x2, int y2);
void waitForStart(int x1, int y1, int x2, int y2);
void waitForEnd(int x1, int y1, int x2, int y2);
void waitForStartR(int x1, int y1, int x2, int y2);
void waitForEndR(int x1, int y1, int x2, int y2);
void updateStr(int val);
void XBeeRead();
void info_module();
void XBeeWrite();
void XBee_Setup();
void XBee_status();
void time_flag_start();
void updateStrXBee(int val);
void XBee_SetH(int adr_xbee_h);
void XBee_SetL(int adr_xbee_h);
void XBee_Set_Network();
void sendAtCommand();
void sendAtCommand_ar();
void sendRemoteAtCommand();
void testRemoteAtCommand();
void test_arRequestMod();
void read_HL_mem_XBee(int N_device );
void draw_view_adr_device();
void view_adr_device();
void view_page(int block_n);
void draw_view_adr_user();
void view_adr_user();
void view_page_user(int block_n);
void set_number_user(int adr_user);
void restore_default_device();
void read_adr_device(int N_device);
void set_adr_device();
byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress );
void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data );
void format_memory();
void read_memory1();
void FileOpen();
void FileClose();
void list_file();
void load_list_files();
void file_name();
void file_print_date();
void file_del_SD();
void set_SD();
void preob_num_str();
void vibroM();
void sdErrorMsg_F(const __FlashStringHelper* str);
uint8_t cidDmp();
uint8_t csdDmp();
uint8_t partDmp();
void volDmp();
void SD_info();
void setup_pin();
//
//
void drawUpButton(int x, int y);
void drawDownButton(int x, int y);
void showDOW(byte dow);
int bin_to_bcd(int temp);
byte validateDate(byte d, byte m, word y);
byte validateDateForMonth(byte d, byte m, word y);
void setClock();
char uCase(char c);
void buttonWait(int x, int y);
byte calcDOW(byte d, byte m, int y);
void waitForTouchRelease();

#include <ArduinoRemote1_0.ino>
#include <setTimeDate.ino>
#include <utils.ino>
#endif
