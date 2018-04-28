#ifndef __TFT_LCD_H
#define __TFT_LCD_H

#include "spi1.h"

/*
spi1 miso pa6
spi1 mosi pa7
spi1 sck pa5    
spi1 nss pa4
reset pa2
d/c pa3
*/






#define TFT_RESET_PIN 7
#define TFT_DC_PIN    8
#define TFT_CS_PIN    9

#define TFT_DC_SET    digitalWrite(TFT_DC_PIN,HIGH) 
#define TFT_DC_RESET  digitalWrite(TFT_DC_PIN,LOW);

#define TFT_RST_SET   digitalWrite(TFT_RESET_PIN, HIGH);
#define TFT_RST_RESET digitalWrite(TFT_RESET_PIN, LOW);

#define TFT_CS_SET    digitalWrite(TFT_CS_PIN, HIGH);
#define TFT_CS_RESET  digitalWrite(TFT_CS_PIN, LOW);





//#define TFT_RESET_PIN GPIO_Pin_2
//#define TFT_DC_PIN    GPIO_Pin_3
//#define TFT_CS_PIN    GPIO_Pin_4
//
//#define TFT_DC_SET    GPIO_SetBits(GPIOA, TFT_DC_PIN);
//#define TFT_DC_RESET  GPIO_ResetBits(GPIOA, TFT_DC_PIN);
//
//#define TFT_RST_SET   GPIO_SetBits(GPIOA, TFT_RESET_PIN);
//#define TFT_RST_RESET GPIO_ResetBits(GPIOA, TFT_RESET_PIN);
//
//#define TFT_CS_SET    GPIO_SetBits(GPIOA, TFT_CS_PIN);
//#define TFT_CS_RESET   GPIO_ResetBits(GPIOA, TFT_CS_PIN);

#define LCD_WIDTH       240
#define LCD_HEIGHT      320
#define LCD_PIXEL_COUNT	LCD_WIDTH * LCD_HEIGHT

/// TODO: list of defines of commands
/// FIRST: test reading from display

void LCD_SendCommand(uint8_t com);
void LCD_SendData(uint8_t data);
uint8_t LCD_Receve();

void LCD_Init();
void LCD_InitGPIO();
void LCD_Fill(uint16_t color);
void LCD_Image(unsigned char const *img);

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
uint32_t LCD_Putchar(uint32_t x, uint32_t y, char c);
void LCD_DrawString(uint32_t x, uint32_t y,char *str);


//void Delay(__IO uint32_t nTime);

//Commands
#define ILI9341_RESET				0x01
#define ILI9341_SLEEP_OUT			0x11
#define ILI9341_GAMMA				0x26
#define ILI9341_DISPLAY_OFF			0x28
#define ILI9341_DISPLAY_ON			0x29
#define ILI9341_COLUMN_ADDR			0x2A
#define ILI9341_PAGE_ADDR			0x2B
#define ILI9341_GRAM				0x2C
#define ILI9341_MAC			        0x36
#define ILI9341_PIXEL_FORMAT        0x3A
#define ILI9341_WDB			    	0x51
#define ILI9341_WCD				    0x53
#define ILI9341_RGB_INTERFACE       0xB0
#define ILI9341_FRC				    0xB1
#define ILI9341_BPC				    0xB5
#define ILI9341_DFC				    0xB6
#define ILI9341_POWER1				0xC0
#define ILI9341_POWER2				0xC1
#define ILI9341_VCOM1				0xC5
#define ILI9341_VCOM2				0xC7
#define ILI9341_POWERA				0xCB
#define ILI9341_POWERB				0xCF
#define ILI9341_PGAMMA				0xE0
#define ILI9341_NGAMMA				0xE1
#define ILI9341_DTCA				0xE8
#define ILI9341_DTCB				0xEA
#define ILI9341_POWER_SEQ			0xED
#define ILI9341_3GAMMA_EN			0xF2
#define ILI9341_INTERFACE			0xF6
#define ILI9341_PRC				    0xF7


#endif /* __TFT_LCD_H */
