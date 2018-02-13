#ifndef _XBEEMENU_H
#define _XBEEMENU_H
#include "XBee.h"

#define DEBAG SERIAL_PORT_USBVIRTUAL  

class XBeeActive
{

public:
	void setup();
	void sendAtCommand();
	void sendAtCommand_ar();
	void sendRemoteAtCommand();
	void testRemoteAtCommand();
	void test_arRequestMod();
	void search_XBee();
	void XBee_status();


	byte funcType;                      // Номер функции, переданной по каналу  XBee
	word field1;                        // Данные,  переданные по каналу  XBee
	word field2;                        // Данные,  переданные по каналу  XBee
	byte *_msg, _len;                   // Длина строки
	word _baud, _crc;                   // Скорость обмена и контрольная сумма блока  

private:
	unsigned long UARTSpeed=9600;          // скорость работы с SIM800 (1 - 9600, 2 - 19200, 4 - 38400, 6 - 57600, 12 - 115200)
	////uint8_t SerialNumber;       // номер Serial, который используется для работы с SIM800 (1 - Serial1, 2 - Serial2, 3 - Serial 3)

	////Serial = &SERIAL_PORT_USBVIRTUAL;
	Stream* workStream;
	//Stream* workStream0;
};
//--------------------------------------------------------------------------------------------------------------------------------------
extern XBeeActive RealXBeeMenu;
//--------------------------------------------------------------------------------------------------------------------------------------
#endif
