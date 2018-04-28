#include <usb_ch9.h>
#include <usbhub.h>
#include <UsbCore.h>
#include <Usb.h>
#include <sink_parser.h>
#include <printhex.h>
#include <parsetools.h>
#include <MouseController.h>
#include <message.h>
#include <macros.h>
#include <KeyboardController.h>
#include <hidusagestr.h>
#include <hiduniversal.h>
#include <hidescriptorparser.h>
#include <hidboot.h>
#include <hid.h>
#include <hexdump.h>
#include <confdescparser.h>
#include <adk.h>
#include <address.h>
#include <SAMD_AnalogCorrection.h>
#include <TFT.h>
#include <Arduino.h>
#include <pins_arduino.h>
#include <SPI.h>
#include "tft_lcd.h"



#define ledPin 11




#define Serial SERIAL_PORT_USBVIRTUAL


void setup()
{
	Serial.begin(9600);
	Serial.println("ILI9341 Test!");
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

}
