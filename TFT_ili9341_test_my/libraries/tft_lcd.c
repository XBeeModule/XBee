#include "tft_lcd.h"
#include "font.h"

extern const font_type TimesNewRoman;

void LCD_SendCommand(uint8_t com) {
  TFT_DC_RESET;
  TFT_CS_RESET;
  spi1_send(com);
  TFT_CS_SET;
}

void LCD_SendData(uint8_t data) {
  TFT_DC_SET;
  TFT_CS_RESET;
  spi1_send(data);
  TFT_CS_SET;
}

uint8_t LCD_Receve() {
  return 0;
}

void LCD_Init(){
  LCD_InitGPIO();
  
  TFT_CS_SET;
  spi1_init();
  
  // сброс дисплея
  TFT_RST_SET;
  LCD_SendCommand(ILI9341_RESET);
  delay(100);
  
  /// commands here
  LCD_SendCommand(ILI9341_POWERA);
  LCD_SendData(0x39);
  LCD_SendData(0x2C);
  LCD_SendData(0x00);
  LCD_SendData(0x34);
  LCD_SendData(0x02);
  LCD_SendCommand(ILI9341_POWERB);
  LCD_SendData(0x00);
  LCD_SendData(0xC1);
  LCD_SendData(0x30);
  LCD_SendCommand(ILI9341_DTCA);
  LCD_SendData(0x85);
  LCD_SendData(0x00);
  LCD_SendData(0x78);
  LCD_SendCommand(ILI9341_DTCB);
  LCD_SendData(0x00);
  LCD_SendData(0x00);
  LCD_SendCommand(ILI9341_POWER_SEQ);
  LCD_SendData(0x64);
  LCD_SendData(0x03);
  LCD_SendData(0x12);
  LCD_SendData(0x81);
  LCD_SendCommand(ILI9341_PRC);
  LCD_SendData(0x20);
  LCD_SendCommand(ILI9341_POWER1);
  LCD_SendData(0x23);
  LCD_SendCommand(ILI9341_POWER2);
  LCD_SendData(0x10);
  LCD_SendCommand(ILI9341_VCOM1);
  LCD_SendData(0x3E);
  LCD_SendData(0x28);
  LCD_SendCommand(ILI9341_VCOM2);
  LCD_SendData(0x86);
  LCD_SendCommand(ILI9341_MAC);
  LCD_SendData(0x48);
  LCD_SendCommand(ILI9341_PIXEL_FORMAT);
  LCD_SendData(0x55);
  LCD_SendCommand(ILI9341_FRC);
  LCD_SendData(0x00);
  LCD_SendData(0x18);
  LCD_SendCommand(ILI9341_DFC);
  LCD_SendData(0x08);
  LCD_SendData(0x82);
  LCD_SendData(0x27);
  LCD_SendCommand(ILI9341_3GAMMA_EN);
  LCD_SendData(0x00);
  LCD_SendCommand(ILI9341_COLUMN_ADDR);
  LCD_SendData(0x00);
  LCD_SendData(0x00);
  LCD_SendData(0x00);
  LCD_SendData(0xEF);
  LCD_SendCommand(ILI9341_PAGE_ADDR);
  LCD_SendData(0x00);
  LCD_SendData(0x00);
  LCD_SendData(0x01);
  LCD_SendData(0x3F);
  LCD_SendCommand(ILI9341_GAMMA);
  LCD_SendData(0x01);
  LCD_SendCommand(ILI9341_PGAMMA);
  LCD_SendData(0x0F);
  LCD_SendData(0x31);
  LCD_SendData(0x2B);
  LCD_SendData(0x0C);
  LCD_SendData(0x0E);
  LCD_SendData(0x08);
  LCD_SendData(0x4E);
  LCD_SendData(0xF1);
  LCD_SendData(0x37);
  LCD_SendData(0x07);
  LCD_SendData(0x10);
  LCD_SendData(0x03);
  LCD_SendData(0x0E);
  LCD_SendData(0x09);
  LCD_SendData(0x00);
  LCD_SendCommand(ILI9341_NGAMMA);
  LCD_SendData(0x00);
  LCD_SendData(0x0E);
  LCD_SendData(0x14);
  LCD_SendData(0x03);
  LCD_SendData(0x11);
  LCD_SendData(0x07);
  LCD_SendData(0x31);
  LCD_SendData(0xC1);
  LCD_SendData(0x48);
  LCD_SendData(0x08);
  LCD_SendData(0x0F);
  LCD_SendData(0x0C);
  LCD_SendData(0x31);
  LCD_SendData(0x36);
  LCD_SendData(0x0F);
  LCD_SendCommand(ILI9341_SLEEP_OUT);
  
  delay(100);
  LCD_SendCommand(ILI9341_DISPLAY_ON);
  LCD_SendCommand(ILI9341_GRAM);
}

void LCD_InitGPIO() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);  // тактирование порта
    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
 
    gpio.GPIO_Pin = TFT_DC_PIN | TFT_RESET_PIN | TFT_CS_PIN;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOA,&gpio);
}

void LCD_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	LCD_SendCommand(ILI9341_COLUMN_ADDR);
	LCD_SendData(x1 >> 8);
	LCD_SendData(x1 & 0xFF);
	LCD_SendData(x2 >> 8);
	LCD_SendData(x2 & 0xFF);

	LCD_SendCommand(ILI9341_PAGE_ADDR);
	LCD_SendData(y1 >> 8);
	LCD_SendData(y1 & 0xFF);
	LCD_SendData(y2 >> 8);
	LCD_SendData(y2 & 0xFF);
}

void LCD_Fill(uint16_t color) {
	unsigned int n, i, j;
	i = color >> 8;
	j = color & 0xFF;
	LCD_SetCursorPosition(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

	LCD_SendCommand(ILI9341_GRAM);

	for (n = 0; n < LCD_PIXEL_COUNT; n++) {
		LCD_SendData(i);
		LCD_SendData(j);
	}
}


void LCD_Image(unsigned char const *img) {
        uint32_t n;
        
	LCD_SetCursorPosition(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

	LCD_SendCommand(ILI9341_GRAM);

	for (n = 0; n < LCD_PIXEL_COUNT; n++) {
		uint8_t color = *img;
                img++;
		LCD_SendData(*img);
		LCD_SendData(color);
                img++;
	}
}

#define FONT_HEIGHT 25
#define FONT_WIDTH 20

uint32_t LCD_Putchar(uint32_t x, uint32_t y, char c) {
        uint32_t i, j;
        unsigned short Data;
        
        uint32_t offset = (c-32)*TimesNewRoman.height;
        uint16_t width = TimesNewRoman.width;
        
    	for (i = 0; i < TimesNewRoman.height; i++) {

            Data = TimesNewRoman.data_table[offset+i];    
            
            
            for (j = 0; j < width; j++) {
                if ((Data << j) & 0x8000) {
                    LCD_DrawPixel(x + j, (y + i), 0xFFFF);  //white
                } else {
                    LCD_DrawPixel(x + j, (y + i), 0x0000);  //black
                }
            }
        }
        
        return x+width;
}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    LCD_SetCursorPosition(x, y, x, y);
    LCD_SendCommand(ILI9341_GRAM);
    LCD_SendData(color >> 8);
    LCD_SendData(color & 0xFF);
}

void LCD_DrawString(uint32_t x, uint32_t y, char *str)
{
    while(*str) {
        x = LCD_Putchar(x,y,*str++);
    }
}