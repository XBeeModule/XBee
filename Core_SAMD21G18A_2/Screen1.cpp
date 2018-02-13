//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Screen1.h"
#include "DS3231.h"
#include "XBeeMenu.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Screen1::Screen1() : AbstractTFTScreen("SCREEN1")
{
  
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen1::doSetup(TFTMenu* menu)
{
  // тут настраиваемся, например, можем добавлять кнопки
  screenButtons->addButton( 5 ,  260, 105,  40, "МЕНЮ 1");
  screenButtons->addButton( 120 ,  260, 105,  40, "МЕНЮ 2");
 }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen1::doUpdate(TFTMenu* menu)
{
    // тут обновляем внутреннее состояние
	if (isActive())
	{
		DS3231Time tm = RealtimeClock.getTime();
		if (oldsecond != tm.second)
		{
			oldsecond = tm.second;
			UTFT* dc = menu->getDC();
			dc->setColor(VGA_WHITE);
			dc->setBackColor(VGA_BLACK);
			// получаем компоненты даты в виде строк
			String strDate = RealtimeClock.getDateStr(tm);
			String strTime = RealtimeClock.getTimeStr(tm);
			dc->setFont(SmallRusFont);
			// печатаем их
			dc->print(strDate, 5, 305);
			dc->print(strTime, 160, 305);
															//dc->printNumF(setupPin.power3V3, 1, 195, 1);    //
															//dc->printNumF(setupPin.power5V0, 1, 195, 15);   //
															//dc->printNumI(setupPin.power200, 195, 30);      //
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen1::doDraw(TFTMenu* menu)
{
  UTFT* dc = menu->getDC();
  dc->setColor(VGA_WHITE);
  dc->setBackColor(VGA_BLACK);
  dc->setFont(TFT_FONT);
  // тут рисуем, что надо именно нам, кнопки прорисуются сами после того, как мы тут всё отрисуем
  menu->print("Главный экран", 15, 0);
  
  //// выводим число
  //dc->setColor(VGA_BLUE);
  //int number = 12345;
  //dc->printNumI(number, 20,200);

  //dc->setFont(SmallSymbolFont);
  //// выводим спецсимвол
  //dc->printChar(47,20,250);

  // возвращает шрифт по умолчанию
  dc->setFont(TFT_FONT); 
  /*RealXBeeMenu.XBee_status();
  delay(300);*/
  }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen1::onButtonPressed(TFTMenu* menu, int pressedButton)
{
  // обработчик нажатия на кнопку. Номера кнопок начинаются с 0 и идут в том порядке, в котором мы их добавляли
  if(pressedButton == 0)
    menu->switchToScreen("SCREEN1_0"); // переключаемся на SCREEN1_1 экран
  else if(pressedButton == 1)
    menu->switchToScreen("SCREEN2_0"); // переключаемся на третий экран
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

