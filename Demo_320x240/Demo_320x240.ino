// UTFT_Demo_320x240 (C)2012 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels.
//
// This program requires the UTFT library.
//
//#define ARDUINO_SAMD_ZERO
//#define __SAMD21G18A__
#include <TFT9341.h>
#include <SPI.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];


#define TFT_RST 7
#define TFT_DC 8
#define TFT_CS 9
#define TFT_MOSI MOSI
#define TFT_MISO MISO
#define TFT_CLK SCK
const int ledPin = 11;

TFT9341 tft(ILI9341_SP, TFT_RST, TFT_CS, TFT_DC);

extern "C" char *sbrk(int i);

#define Serial SERIAL_PORT_USBVIRTUAL

int FreeRam() {
	char stack_dummy = 0;
	return &stack_dummy - sbrk(0);
}


void setup()
{
	Serial.begin(9600);
	delay(1000);
	Serial.println("ILI9341 Test!");
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
	Serial.print("FreeRam");
	Serial.println(FreeRam());
	delay(300);
//	randomSeed(analogRead(0));
  
	// Setup the LCD
	//delay(1000);
	tft.InitLCD(3);
	tft.setFont(SmallFont);
}

void loop()
{
  int buf[318];
  int x, x2;
  int y, y2;
  int r;

// Clear the screen and draw the frame
  tft.clrScr();

  tft.setColor(255, 0, 0);
  tft.fillRect(0, 0, 319, 13);
  tft.setColor(64, 64, 64);
  tft.fillRect(0, 226, 319, 239);
  tft.setColor(255, 255, 255);
  tft.setBackColor(255, 0, 0);
  tft.print("* Universal Color tft Display Library *", CENTER, 1);
  tft.setBackColor(64, 64, 64);
  tft.setColor(255,255,0);
  tft.print("<http://electronics.henningkarlsen.com>", CENTER, 227);

  tft.setColor(0, 0, 255);
  tft.drawRect(0, 14, 319, 225);

// Draw crosshairs
  tft.setColor(0, 0, 255);
  tft.setBackColor(0, 0, 0);
  tft.drawLine(159, 15, 159, 224);
  tft.drawLine(1, 119, 318, 119);
  for (int i=9; i<310; i+=10)
    tft.drawLine(i, 117, i, 121);
  for (int i=19; i<220; i+=10)
    tft.drawLine(157, i, 161, i);

// Draw sin-, cos- and tan-lines  
  tft.setColor(0,255,255);
  tft.print("Sin", 5, 15);
  for (int i=1; i<318; i++)
  {
    tft.drawPixel(i,119+(sin(((i*1.13)*3.14)/180)*95));
  }
  
  tft.setColor(255,0,0);
  tft.print("Cos", 5, 27);
  for (int i=1; i<318; i++)
  {
    tft.drawPixel(i,119+(cos(((i*1.13)*3.14)/180)*95));
  }

  tft.setColor(255,255,0);
  tft.print("Tan", 5, 39);
  for (int i=1; i<318; i++)
  {
	  tft.drawPixel(i, 119 + (cos(((i*1.13)*3.14) / 180) * 95));
    tft.drawPixel(i,119+(tan(((i*1.13)*3.14)/180)));
	
  }

  delay(200);

  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);
  tft.setColor(0, 0, 255);
  tft.setBackColor(0, 0, 0);
  tft.drawLine(159, 15, 159, 224);
  tft.drawLine(1, 119, 318, 119);

// Draw a moving sinewave
  x=1;
  for (int i=1; i<(318*20); i++) 
  {
    x++;
    if (x==319)
      x=1;
    if (i>319)
    {
      if ((x==159)||(buf[x-1]==119))
        tft.setColor(0,0,255);
      else
        tft.setColor(0,0,0);
      tft.drawPixel(x,buf[x-1]);
    }
    tft.setColor(0,255,255);
    y=119+(sin(((i*1.1)*3.14)/180)*(90-(i / 100)));
    tft.drawPixel(x,y);
    buf[x-1]=y;
  }

  delay(200);
  
  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);

// Draw some filled rectangles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        tft.setColor(255,0,255);
        break;
      case 2:
        tft.setColor(255,0,0);
        break;
      case 3:
        tft.setColor(0,255,0);
        break;
      case 4:
        tft.setColor(0,0,255);
        break;
      case 5:
        tft.setColor(255,255,0);
        break;
    }
    tft.fillRect(70+(i*20), 30+(i*20), 130+(i*20), 90+(i*20));
  }

  delay(200);
  
  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);

// Draw some filled, rounded rectangles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        tft.setColor(255,0,255);
        break;
      case 2:
        tft.setColor(255,0,0);
        break;
      case 3:
        tft.setColor(0,255,0);
        break;
      case 4:
        tft.setColor(0,0,255);
        break;
      case 5:
        tft.setColor(255,255,0);
        break;
    }
   // tft.fillRoundRect(190-(i*20), 30+(i*20), 250-(i*20), 90+(i*20));
  }
  
  delay(1000);
  
  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);

// Draw some filled circles
  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        tft.setColor(255,0,255);
        break;
      case 2:
        tft.setColor(255,0,0);
        break;
      case 3:
        tft.setColor(0,255,0);
        break;
      case 4:
        tft.setColor(0,0,255);
        break;
      case 5:
        tft.setColor(255,255,0);
        break;
    }
    tft.fillCircle(100+(i*20),60+(i*20), 30);
  }
  
  delay(100);
  
  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);

// Draw some lines in a pattern
  tft.setColor (255,0,0);
  for (int i=15; i<224; i+=5)
  {
    tft.drawLine(1, i, (i*1.44)-10, 224);
  }
  tft.setColor (255,0,0);
  for (int i=224; i>15; i-=5)
  {
    tft.drawLine(318, i, (i*1.44)-11, 15);
  }
  tft.setColor (0,255,255);
  for (int i=224; i>15; i-=5)
  {
    tft.drawLine(1, i, 331-(i*1.44), 15);
  }
  tft.setColor (0,255,255);
  for (int i=15; i<224; i+=5)
  {
    tft.drawLine(318, i, 330-(i*1.44), 224);
  }
  
  delay(200);
  
  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);

// Draw some random circles
  for (int i=0; i<100; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    x=32+random(256);
    y=45+random(146);
    r=random(30);
    //tft.drawCircle(x, y, r);
  }

  delay(200);
  
  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);

// Draw some random rectangles
  for (int i=0; i<100; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    x=2+random(316);
    y=16+random(207);
    x2=2+random(316);
    y2=16+random(207);
    tft.drawRect(x, y, x2, y2);
  }

  delay(200);
  
  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);

// Draw some random rounded rectangles
  for (int i=0; i<100; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    x=2+random(316);
    y=16+random(207);
    x2=2+random(316);
    y2=16+random(207);
   // tft.drawRoundRect(x, y, x2, y2);
  }

  delay(200);
  
  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);

  for (int i=0; i<100; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    x=2+random(316);
    y=16+random(209);
    x2=2+random(316);
    y2=16+random(209);
    tft.drawLine(x, y, x2, y2);
  }

  delay(200);
  
  tft.setColor(0,0,0);
  tft.fillRect(1,15,318,224);

  for (int i=0; i<10000; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    tft.drawPixel(2+random(316), 16+random(209));
  }

  delay(200);

  tft.fillScr(0, 0, 255);
  
  tft.setColor(255, 0, 0);
  tft.fillRoundRect(80, 70, 239, 169);
  
  tft.setColor(255, 255, 255);
  tft.setBackColor(255, 0, 0);
  tft.print("That's it!", CENTER, 93);
  tft.print("Restarting in a", CENTER, 119);
  tft.print("few seconds...", CENTER, 132);
  
  tft.setColor(0, 255, 0);
  tft.setBackColor(0, 0, 255);
  tft.print("Runtime: (msecs)", CENTER, 210);
  tft.printNumI(millis(), CENTER, 225);
  
 // Serial.println(FreeRam());
  delay (1000);
}


