#include "UTFTMenu.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TFTMenu* tftMenuManager;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
AbstractTFTScreen::AbstractTFTScreen(const char* name)
{
  screenName = name;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
AbstractTFTScreen::~AbstractTFTScreen()
{
  delete screenButtons;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AbstractTFTScreen::setup(TFTMenu* menu)
{
  screenButtons = new UTFT_Buttons_Rus(menu->getDC(), menu->getTouch(),menu->getRusPrinter());
  screenButtons->setTextFont(TFT_FONT);
  screenButtons->setButtonColors(TFT_BUTTON_COLORS);

  doSetup(menu);
  
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AbstractTFTScreen::update(TFTMenu* menu)
{
  int pressedButton = screenButtons->checkButtons();
  
  if(pressedButton != -1)
    onButtonPressed(menu, pressedButton);

  doUpdate(menu);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AbstractTFTScreen::draw(TFTMenu* menu)
{
  doDraw(menu);
  screenButtons->drawButtons(); 
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// TFTMenu
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TFTMenu::TFTMenu()
{
  currentScreenIndex = -1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TFTMenu::addScreen(AbstractTFTScreen* screen)
{
  screen->setup(this);
  screens.push_back(screen);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TFTMenu::setup()
{
  tftMenuManager = this;
  
  tftDC = new UTFT;
  tftTouch = new URTouch(TFT_TOUCH_CLK_PIN,TFT_TOUCH_CS_PIN,TFT_TOUCH_DIN_PIN,TFT_TOUCH_DOUT_PIN,TFT_TOUCH_IRQ_PIN);

  #if TFT_INIT_DELAY > 0
  delay(TFT_INIT_DELAY);
  #endif
  
  tftDC->InitLCD(TFT_ORIENTATION);
  tftDC->setBackColor(TFT_BACK_COLOR);
  tftDC->fillScr(TFT_BACK_COLOR);
  tftDC->setFont(TFT_FONT);

  tftTouch->InitTouch(TFT_ORIENTATION);
  tftTouch->setPrecision(TOUCH_PRECISION);
  
  rusPrint.init(tftDC);

  
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int TFTMenu::print(const char* str,int x, int y, int deg, bool computeStringLengthOnly)
{
  return rusPrint.print(str,x,y,deg,computeStringLengthOnly);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TFTMenu::update()
{

  if(currentScreenIndex == -1) // ни разу не рисовали ещё ничего, исправляемся
  {
    if(screens.size())
     switchToScreen((unsigned int)0); // переключаемся на первый экран, если ещё ни разу не показали ничего     
  }

  if(currentScreenIndex == -1)
    return;

  // обновляем текущий экран
  AbstractTFTScreen* currentScreen = screens[currentScreenIndex];
  currentScreen->update(this);
  
  
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TFTMenu::switchToScreen(AbstractTFTScreen* screen)
{
  if(currentScreenIndex > -1 && screens.size())
  {
     AbstractTFTScreen* si = screens[currentScreenIndex];
     si->setActive(false);
  }
  
  for(size_t i=0;i<screens.size();i++)
  {
    if(screens[i] == screen)
    {
      screen->setActive(true);
      currentScreenIndex = i;
      tftDC->setBackColor(TFT_BACK_COLOR);
      tftDC->fillScr(TFT_BACK_COLOR); // clear screen first
      screen->update(this);
      screen->draw(this);
      break;
    }
  }  
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TFTMenu::switchToScreen(unsigned int screenIndex)
{
  if(screenIndex < screens.size())
      switchToScreen(screens[screenIndex]);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TFTMenu::switchToScreen(const char* screenName)
{
  
  // переключаемся на запрошенный экран
  for(size_t i=0;i<screens.size();i++)
  {
    AbstractTFTScreen* si = screens[i];
    if(!strcmp(si->getName(),screenName))
    {
      switchToScreen(si);
      break;
    }
  }

}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TFTMenu Screen;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

