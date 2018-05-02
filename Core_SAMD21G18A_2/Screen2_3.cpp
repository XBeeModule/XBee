//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Screen2_3.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Screen2_3::Screen2_3() : AbstractTFTScreen("SCREEN2_3")
{
  
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen2_3::doSetup(TFTMenu* menu)
{
  // тут настраиваемся, например, можем добавлять кнопки
  screenButtons->addButton( 10 , 30, 200,  50, "ВОЗВРАТ");
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen2_3::doUpdate(TFTMenu* menu)
{
    // тут обновляем внутреннее состояние
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen2_3::doDraw(TFTMenu* menu)
{
  UTFT* dc = menu->getDC();
  dc->setColor(VGA_WHITE);
  dc->setBackColor(VGA_BLACK);
  dc->setFont(TFT_FONT);
  
  // тут рисуем, что надо именно нам, кнопки прорисуются сами после того, как мы тут всё отрисуем
  menu->print("Меню файлов", 25, 0);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Screen2_3::onButtonPressed(TFTMenu* menu, int pressedButton)
{
  // обработчик нажатия на кнопку. Номера кнопок начинаются с 0 и идут в том порядке, в котором мы их добавляли
  if(pressedButton == 0)
    menu->switchToScreen("SCREEN1_1"); // переключаемся на первый экран
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
