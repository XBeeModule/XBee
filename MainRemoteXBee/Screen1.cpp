//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Screen1.h"
#include "DS3231.h"
#include "XBeeMenu.h"



//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Screen1::Screen1() : AbstractTFTScreen("Main")
{
	oldsecond = 0;
	mainScreen = this;
	//points1 = NULL;
	//points2 = NULL;
	//points3 = NULL;
	//canDrawChart = false;
	//inDrawingChart = false;
	last3V3Voltage = last5Vvoltage = last200Vvoltage = -1;

	//inductiveSensorState1 = inductiveSensorState2 = inductiveSensorState3 = 0xFF;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen1::drawVoltage(TFTMenu* menu)
{
	if (!isActive())
		return;

	word color = VGA_RED;
	UTFT* dc = menu->getDC();

	word oldColor = dc->getColor();
	dc->setBackColor(VGA_BLACK);
	dc->setFont(SmallRusFont);
	uint8_t fontHeight = dc->getFontYsize();

	uint16_t curX = 190;
	uint16_t curY = 20;

	//VoltageData vData = Settings.get3V3Voltage();// Контроль источника питания +3.3в

	//if (last3V3Voltage != vData.raw)
	//{
	//	last3V3Voltage = vData.raw;

	//	float threshold = (3.3 / 100)*VOLTAGE_THRESHOLD;
	//	float lowBorder = 3.3 - threshold;
	//	float highBorder = 3.3 + threshold;

	//	if (vData.voltage >= lowBorder && vData.voltage <= highBorder)
	//		color = VGA_LIME;

	//	String data = String(vData.voltage, 1) + "V";
	//	while (data.length() < 4)
	//		data += ' ';

	//	dc->setColor(color);
	//	dc->print(data.c_str(), curX, curY);
	//}

	//curY += fontHeight + 2;


	//vData = Settings.get5Vvoltage();        // Контроль источника питания +5.0в

	//if (last5Vvoltage != vData.raw)
	//{
	//	last5Vvoltage = vData.raw;

	//	float threshold = (5.0 / 100)*VOLTAGE_THRESHOLD;
	//	float lowBorder = 5.0 - threshold;
	//	float highBorder = 5.0 + threshold;

	//	color = VGA_RED;

	//	if (vData.voltage >= lowBorder && vData.voltage <= highBorder)
	//		color = VGA_LIME;

	//	String data = String(vData.voltage, 1) + "V";
	//	while (data.length() < 4)
	//		data += ' ';

	//	dc->setColor(color);
	//	dc->print(data.c_str(), curX, curY);
	//}



	dc->setColor(oldColor);


}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen1::onDeactivate()
{
	last3V3Voltage = last5Vvoltage = last200Vvoltage = -1;

	//inductiveSensorState1 = inductiveSensorState2 = inductiveSensorState3 = 0xFF;

	// прекращаем отрисовку графика
	//chart.stopDraw();

	// станем неактивными, надо выключить подписчика результатов прерываний
	//InterruptHandler.setSubscriber(NULL);
}

void Screen1::onActivate()
{
	// мы активизируемся, назначаем подписчика результатов прерываний
	//InterruptHandler.setSubscriber(ScreenInterrupt);

}

void Screen1::doSetup(TFTMenu* menu)
{
 
  screenButtons->setSymbolFont(Various_Symbols_32x32);
  // тут настраиваемся, например, можем добавлять кнопки
  screenButtons->addButton(5, 260, 185, 40, "НАСТРОЙКИ");
  screenButtons->addButton(200, 260, 35, 40, "z", BUTTON_SYMBOL); // кнопка Часы 



 }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen1::drawTime(TFTMenu* menu)
{
	DS3231Time tm = RealtimeClock.getTime();
	if (oldsecond != tm.second)
	{
		oldsecond = tm.second;
		// получаем компоненты даты в виде строк
		UTFT* dc = menu->getDC();
		dc->setColor(VGA_WHITE);
		dc->setBackColor(VGA_BLACK);
		dc->setFont(SmallRusFont);
		String strDate = RealtimeClock.getDateStr(tm);
		String strTime = RealtimeClock.getTimeStr(tm);

		// печатаем их
		dc->print(strDate, 5, 1);
		dc->print(strTime, 90, 1);

		String str = "RAM: ";
	/*	str += getFreeMemory();
		Screen.print(str.c_str(), 10, 123);*/

	}
}


void Screen1::doUpdate(TFTMenu* menu)
{

	drawTime(menu);
	drawVoltage(menu);



 //   // тут обновляем внутреннее состояние
	//if (isActive())
	//{
	//	DS3231Time tm = RealtimeClock.getTime();
	//	if (oldsecond != tm.second)
	//	{
	//		oldsecond = tm.second;
	//		UTFT* dc = menu->getDC();
	//		dc->setColor(VGA_WHITE);
	//		dc->setBackColor(VGA_BLACK);
	//		// получаем компоненты даты в виде строк
	//		String strDate = RealtimeClock.getDateStr(tm);
	//		String strTime = RealtimeClock.getTimeStr(tm);
	//		dc->setFont(SmallRusFont);
	//		// печатаем их
	//		dc->print(strDate, 5, 305);
	//		dc->print(strTime, 160, 305);
	//														//dc->printNumF(setupPin.power3V3, 1, 195, 1);    //
	//														//dc->printNumF(setupPin.power5V0, 1, 195, 15);   //
	//														//dc->printNumI(setupPin.power200, 195, 30);      //
	//	}
	//}
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
	//if (pressedButton == 0)
	//{
	//	menu->switchToScreen("Settings"); // переключаемся на экран работы с SD
	//}
	//else if (pressedButton == 1)
	//{
	//	menu->switchToScreen("SCREEN4"); // переключаемся на третий экран
	//}





  // обработчик нажатия на кнопку. Номера кнопок начинаются с 0 и идут в том порядке, в котором мы их добавляли
  if(pressedButton == 0)
    menu->switchToScreen("SCREEN1_0"); // переключаемся на SCREEN1_1 экран
  else if(pressedButton == 1)
    menu->switchToScreen("SCREEN2_0"); // переключаемся на третий экран



}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int Screen1::getFreeMemory()
{
	//struct mallinfo mi = mallinfo();
	//char* heapend = _sbrk(0);
	//register char* stack_ptr asm("sp");

	//return (stack_ptr - heapend + mi.fordblks);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
