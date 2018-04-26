/***************************************************
This is our GFX example for the Adafruit ILI9341 Breakout and Shield
----> http://www.adafruit.com/products/1651

Check out the links above for our tutorials and wiring diagrams
These displays use SPI to communicate, 4 or 5 pins are required to
interface (RST is optional)
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
MIT license, all text above must be included in any redistribution
****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "UTFT.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 8
#define TFT_CS 9
#define TFT_RST 7
#define TFT_MOSI MOSI
#define TFT_MISO MISO
#define TFT_CLK SCK
const int ledPin = 11;


UTFT tft = UTFT(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define Serial SERIAL_PORT_USBVIRTUAL


void setup() {
	Serial.begin(9600);
	Serial.println("ILI9341 Test!");
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
	tft.begin();

	tft.setRotation(1);

	// read diagnostics (optional but can help debug problems)
	uint8_t x = tft.readcommand8(ILI9341_RDMODE);
	Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
	x = tft.readcommand8(ILI9341_RDMADCTL);
	Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
	x = tft.readcommand8(ILI9341_RDPIXFMT);
	Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
	x = tft.readcommand8(ILI9341_RDIMGFMT);
	Serial.print("Image Format: 0x"); Serial.println(x, HEX);
	x = tft.readcommand8(ILI9341_RDSELFDIAG);
	Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);

	/*Serial.println(F("Benchmark                Time (microseconds)"));

	Serial.print(F("Screen fill              "));
	Serial.println(testFillScreen());
	delay(500);

	Serial.print(F("Text                     "));
	Serial.println(testText());
	delay(3000);

	Serial.print(F("Lines                    "));
	Serial.println(testLines(VGA_CYAN));
	delay(500);

	Serial.print(F("Horiz/Vert Lines         "));
	Serial.println(testFastLines(VGA_RED, VGA_BLUE));
	delay(500);

	Serial.print(F("Rectangles (outline)     "));
	Serial.println(testRects(VGA_GREEN));
	delay(500);

	Serial.print(F("Rectangles (filled)      "));
	Serial.println(testFilledRects(VGA_YELLOW, VGA_MAGENTA));
	delay(500);

	Serial.print(F("Circles (filled)         "));
	Serial.println(testFilledCircles(10, VGA_MAGENTA));

	Serial.print(F("Circles (outline)        "));
	Serial.println(testCircles(10, VGA_WHITE));
	delay(500);

	Serial.print(F("Triangles (outline)      "));
	Serial.println(testTriangles());
	delay(500);

	Serial.print(F("Triangles (filled)       "));
	Serial.println(testFilledTriangles());
	delay(500);

	Serial.print(F("Rounded rects (outline)  "));
	Serial.println(testRoundRects());
	delay(500);

	Serial.print(F("Rounded rects (filled)   "));
	Serial.println(testFilledRoundRects());
	delay(500);
*/
	Serial.println(F("Done!"));

}


void loop(void) 
{
	int buf[318];
	int x, x2;
	int y, y2;
	int r;


	tft.setRotation(0);

	//tft.invertDisplay(1);
	// Clear the screen and draw the frame
	//tft.clrScr();
	//tft.fillScreen(VGA_BLACK);

	//tft.setColor(255, 0, 0);
	//tft.fillRect(0, 0, 319, 13, VGA_YELLOW);
	//tft.setColor(64, 64, 64);
	//tft.fillRect(0, 226, 319, 239, VGA_GREEN);
	//tft.setColor(255, 255, 255);
//	tft.fillScreen(VGA_RED);



	tft.setTextColor(VGA_YELLOW); tft.setTextSize(2);
	//tft.setBackColor(255, 0, 0);
	tft.println("* Universal Color tft Display Library *");
//	tft.print("* Universal Color tft Display Library *", CENTER, 1);
	//tft.fillScreen(VGA_BLUE);
//	tft.setBackColor(64, 64, 64);
	tft.setColor(255, 255, 0);
//	tft.print("<http://electronics.henningkarlsen.com>", CENTER, 227);
	delay(4000);
	tft.setColor(0, 0, 255);
//tft.drawRect(0, 14, 319, 225);

	// Draw crosshairs
	tft.setColor(0, 0, 255);
	tft.fillScreen(VGA_BLACK);
	//tft.setBackColor(0, 0, 0);
	tft.drawLine(159, 15, 159, 224, VGA_LIME);
	tft.drawLine(1, 119, 318, 119, VGA_LIME);
	for (int i = 9; i < 310; i += 10)
		tft.drawLine(i, 117, i, 121, VGA_PINK);
	for (int i = 19; i < 220; i += 10)
		tft.drawLine(157, i, 161, i, VGA_PINK);

	//// Draw sin-, cos- and tan-lines
	//tft.setColor(0, 255, 255);
	//tft.print("Sin", 5, 15);
	//for (int i = 1; i < 318; i++)
	//{
	//	tft.drawPixel(i, 119 + (sin(((i * 1.13) * 3.14) / 180) * 95));
	//}

	//tft.setColor(255, 0, 0);
	//tft.print("Cos", 5, 27);
	//for (int i = 1; i < 318; i++)
	//{
	//	tft.drawPixel(i, 119 + (cos(((i * 1.13) * 3.14) / 180) * 95));
	//}

	//tft.setColor(255, 255, 0);
	//tft.print("Tan", 5, 39);
	//for (int i = 1; i < 318; i++)
	//{
	//	tft.drawPixel(i, 119 + (tan(((i * 1.13) * 3.14) / 180)));
	//}

	//delay(2000);
//
//	tft.setColor(0, 0, 0);
////tft.fillRect(1, 15, 318, 224);
//	tft.setColor(0, 0, 255);
//	tft.fillScreen(VGA_BLACK);
//	//tft.setBackColor(0, 0, 0);
//	tft.drawLine(159, 15, 159, 224);
//	tft.drawLine(1, 119, 318, 119);

	// Draw a moving sinewave
	x = 1;
	for (int i = 1; i < (318 * 20); i++)
	{
		x++;
		if (x == 319)
			x = 1;
		if (i > 319)
		{
			if ((x == 159) || (buf[x - 1] == 119))
				tft.setColor(0, 0, 255);
			else
				tft.setColor(0, 0, 0);
			tft.drawPixel(x, buf[x - 1], VGA_PINK);
		}
		tft.setColor(0, 255, 255);
		y = 119 + (sin(((i * 1.1) * 3.14) / 180) * (90 - (i / 100)));
		tft.drawPixel(x, y, VGA_PINK);
		buf[x - 1] = y;
	}

	//delay(2000);

	tft.setColor(0, 0, 0);
	tft.fillRect(1, 15, 318, 224, VGA_BLACK);

	// Draw some filled rectangles
	for (int i = 1; i < 6; i++)
	{
		switch (i)
		{
		case 1:
			tft.setColor(255, 0, 255);
			break;
		case 2:
			tft.setColor(255, 0, 0);
			break;
		case 3:
			tft.setColor(0, 255, 0);
			break;
		case 4:
			tft.setColor(0, 0, 255);
			break;
		case 5:
			tft.setColor(255, 255, 0);
			break;
		}
		tft.fillRect(70 + (i * 20), 30 + (i * 20), 130 + (i * 20), 90 + (i * 20), VGA_YELLOW);
	}

	//delay(2000);

	tft.setColor(0, 0, 0);
//tft.fillRect(1, 15, 318, 224);

	// Draw some filled, rounded rectangles
	for (int i = 1; i < 6; i++)
	{
		switch (i)
		{
		case 1:
			tft.setColor(255, 0, 255);
			break;
		case 2:
			tft.setColor(255, 0, 0);
			break;
		case 3:
			tft.setColor(0, 255, 0);
			break;
		case 4:
			tft.setColor(0, 0, 255);
			break;
		case 5:
			tft.setColor(255, 255, 0);
			break;
		}
		//tft.fillRoundRect(190 - (i * 20), 30 + (i * 20), 250 - (i * 20), 90 + (i * 20), VGA_LIME);
	}

	//delay(2000);

	tft.setColor(0, 0, 0);
	//tft.fillRect(1, 15, 318, 224);

	// Draw some filled circles
	for (int i = 1; i < 6; i++)
	{
		switch (i)
		{
		case 1:
			tft.setColor(255, 0, 255);
			break;
		case 2:
			tft.setColor(255, 0, 0);
			break;
		case 3:
			tft.setColor(0, 255, 0);
			break;
		case 4:
			tft.setColor(0, 0, 255);
			break;
		case 5:
			tft.setColor(255, 255, 0);
			break;
		}
		tft.fillCircle(100 + (i * 20), 60 + (i * 20), 30, VGA_LIME);
	}

	//delay(2000);

	//tft.setColor(0, 0, 0);
	//tft.fillRect(1, 15, 318, 224);

	//// Draw some lines in a pattern
	//tft.setColor(255, 0, 0);
	//for (int i = 15; i < 224; i += 5)
	//{
	//	tft.drawLine(1, i, (i * 1.44) - 10, 224);
	//}
	//tft.setColor(255, 0, 0);
	//for (int i = 224; i > 15; i -= 5)
	//{
	//	tft.drawLine(318, i, (i * 1.44) - 11, 15);
	//}
	//tft.setColor(0, 255, 255);
	//for (int i = 224; i > 15; i -= 5)
	//{
	//	tft.drawLine(1, i, 331 - (i * 1.44), 15);
	//}
	//tft.setColor(0, 255, 255);
	//for (int i = 15; i < 224; i += 5)
	//{
	//	tft.drawLine(318, i, 330 - (i * 1.44), 224);
	//}

	////delay(2000);

	//tft.setColor(0, 0, 0);
	//tft.fillRect(1, 15, 318, 224);

	// Draw some random circles
	for (int i = 0; i < 100; i++)
	{
		tft.setColor(random(255), random(255), random(255));
		x = 32 + random(256);
		y = 45 + random(146);
		r = random(30);
		tft.drawCircle(x, y, r, VGA_LIME);
	}

	//delay(2000);

	tft.setColor(0, 0, 0);
	tft.fillRect(1, 15, 318, 224, VGA_LIME);

	// Draw some random rectangles
	for (int i = 0; i < 100; i++)
	{
		tft.setColor(random(255), random(255), random(255));
		x = 2 + random(316);
		y = 16 + random(207);
		x2 = 2 + random(316);
		y2 = 16 + random(207);
		tft.drawRect(x, y, x2, y2, VGA_GREEN);
	}

	//delay(2000);

	tft.setColor(0, 0, 0);
//tft.fillRect(1, 15, 318, 224);

	// Draw some random rounded rectangles
	for (int i = 0; i < 100; i++)
	{
		tft.setColor(random(255), random(255), random(255));
		x = 2 + random(316);
		y = 16 + random(207);
		x2 = 2 + random(316);
		y2 = 16 + random(207);
		tft.drawRoundRect(x, y, x2, y2, 180, tft.setColor(255, 0, 0));
	}

	//delay(2000);

	//tft.setColor(0, 0, 0);
	//tft.fillRect(1, 15, 318, 224);

	//for (int i = 0; i < 100; i++)
	//{
	//	tft.setColor(random(255), random(255), random(255));
	//	x = 2 + random(316);
	//	y = 16 + random(209);
	//	x2 = 2 + random(316);
	//	y2 = 16 + random(209);
	//	tft.drawLine(x, y, x2, y2);
	//}

	////delay(2000);

	//tft.setColor(0, 0, 0);
	//tft.fillRect(1, 15, 318, 224);

	//for (int i = 0; i < 10000; i++)
	//{
	//	tft.setColor(random(255), random(255), random(255));
	//	tft.drawPixel(2 + random(316), 16 + random(209));
	//}

	//delay(2000);

	//tft.fillScr(0, 0, 255);

	//tft.setColor(255, 0, 0);
	//tft.fillRoundRect(80, 70, 239, 169);

	//tft.setColor(255, 255, 255);
	//tft.setBackColor(255, 0, 0);
	//tft.print("That's it!", CENTER, 93);
	//tft.print("Restarting in a", CENTER, 119);
	//tft.print("few seconds...", CENTER, 132);

	//tft.setColor(0, 255, 0);
	//tft.setBackColor(0, 0, 255);
	//tft.print("Runtime: (msecs)", CENTER, 210);
	//tft.printNumI(millis(), CENTER, 225);

	delay(5000);




	//for (uint8_t rotation = 0; rotation < 4; rotation++) {
	//	tft.setRotation(rotation);
	//	testText();
	//	delay(1000);
	//}
}



unsigned long testFillScreen() {
	unsigned long start = micros();
	tft.fillScreen(VGA_BLACK);
	tft.fillScreen(VGA_RED);
	tft.fillScreen(VGA_GREEN);
	tft.fillScreen(VGA_BLUE);

	tft.fillScreen(VGA_GRAY);
	tft.fillScreen(VGA_LIME);
	tft.fillScreen(VGA_AQUA);


	tft.fillScreen(VGA_BLACK);


	return micros() - start;
}

unsigned long testText() {
	tft.fillScreen(VGA_BLACK);
	unsigned long start = micros();
	tft.setCursor(0, 0);
	tft.setTextColor(VGA_WHITE);  tft.setTextSize(1);
	tft.println("Hello World!");
	tft.setTextColor(VGA_YELLOW); tft.setTextSize(2);
	tft.println(1234.56);
	tft.setTextColor(VGA_RED);    tft.setTextSize(3);
	tft.println(0xDEADBEEF, HEX);
	tft.println();
	tft.setTextColor(VGA_GREEN);
	tft.setTextSize(5);
	tft.println("Groop");
	tft.setTextSize(2);
	tft.println("I implore thee,");
	tft.setTextSize(1);
	tft.println("my foonting turlingdromes.");
	tft.println("And hooptiously drangle me");
	tft.println("with crinkly bindlewurdles,");
	tft.println("Or I will rend thee");
	tft.println("in the gobberwarts");
	tft.println("with my blurglecruncheon,");
	tft.println("see if I don't!");
	return micros() - start;
}

unsigned long testLines(uint16_t color) {
	unsigned long start, t;
	int           x1, y1, x2, y2,
		w = tft.width(),
		h = tft.height();

	tft.fillScreen(VGA_BLACK);

	x1 = y1 = 0;
	y2 = h - 1;
	start = micros();
	for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = w - 1;
	for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	t = micros() - start; // fillScreen doesn't count against timing

	tft.fillScreen(VGA_BLACK);

	x1 = w - 1;
	y1 = 0;
	y2 = h - 1;
	start = micros();
	for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = 0;
	for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	t += micros() - start;

	tft.fillScreen(VGA_BLACK);

	x1 = 0;
	y1 = h - 1;
	y2 = 0;
	start = micros();
	for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = w - 1;
	for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	t += micros() - start;

	tft.fillScreen(VGA_BLACK);

	x1 = w - 1;
	y1 = h - 1;
	y2 = 0;
	start = micros();
	for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = 0;
	for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

	return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
	unsigned long start;
	int           x, y, w = tft.width(), h = tft.height();

	tft.fillScreen(VGA_BLACK);
	start = micros();
	for (y = 0; y < h; y += 5) tft.drawFastHLine(0, y, w, color1);
	for (x = 0; x < w; x += 5) tft.drawFastVLine(x, 0, h, color2);

	return micros() - start;
}

unsigned long testRects(uint16_t color) {
	unsigned long start;
	int           n, i, i2,
		cx = tft.width() / 2,
		cy = tft.height() / 2;

	tft.fillScreen(VGA_BLACK);
	n = min(tft.width(), tft.height());
	start = micros();
	for (i = 2; i < n; i += 6) {
		i2 = i / 2;
		tft.drawRect(cx - i2, cy - i2, i, i, color);
	}

	return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
	unsigned long start, t = 0;
	int           n, i, i2,
		cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(VGA_BLACK);
	n = min(tft.width(), tft.height());
	for (i = n; i > 0; i -= 6) {
		i2 = i / 2;
		start = micros();
		tft.fillRect(cx - i2, cy - i2, i, i, color1);
		t += micros() - start;
		// Outlines are not included in timing results
		tft.drawRect(cx - i2, cy - i2, i, i, color2);
	}

	return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
	unsigned long start;
	int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

	tft.fillScreen(VGA_BLACK);
	start = micros();
	for (x = radius; x < w; x += r2) {
		for (y = radius; y < h; y += r2) {
			tft.fillCircle(x, y, radius, color);
		}
	}

	return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
	unsigned long start;
	int           x, y, r2 = radius * 2,
		w = tft.width() + radius,
		h = tft.height() + radius;

	// Screen is not cleared for this one -- this is
	// intentional and does not affect the reported time.
	start = micros();
	for (x = 0; x < w; x += r2) {
		for (y = 0; y < h; y += r2) {
			tft.drawCircle(x, y, radius, color);
		}
	}

	return micros() - start;
}

unsigned long testTriangles() {
	unsigned long start;
	int           n, i, cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(VGA_BLACK);
	n = min(cx, cy);
	start = micros();
	for (i = 0; i < n; i += 5) {
		tft.drawTriangle(
			cx, cy - i, // peak
			cx - i, cy + i, // bottom left
			cx + i, cy + i, // bottom right
			tft.setColor(0, 0, i));
	}

	return micros() - start;
}

unsigned long testFilledTriangles() {
	unsigned long start, t = 0;
	int           i, cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(VGA_BLACK);
	start = micros();
	for (i = min(cx, cy); i > 10; i -= 5) {
		start = micros();
		tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
			tft.setColor(0, i, i));
		t += micros() - start;
		tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
			tft.setColor(i, i, 0));
	}

	return t;
}

unsigned long testRoundRects() {
	unsigned long start;
	int           w, i, i2,
		cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(VGA_BLACK);
	w = min(tft.width(), tft.height());
	start = micros();
	for (i = 0; i < w; i += 6) {
		i2 = i / 2;
		tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.setColor(i, 0, 0));
	}

	return micros() - start;
}

unsigned long testFilledRoundRects() {
	unsigned long start;
	int           i, i2,
		cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(VGA_BLACK);
	start = micros();
	for (i = min(tft.width(), tft.height()); i > 20; i -= 6) {
		i2 = i / 2;
		tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.setColor(0, i, 0));
	}

	return micros() - start;
}