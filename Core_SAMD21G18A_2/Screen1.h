#pragma once
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "UTFTMenu.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// экран номер 1
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Screen1 : public AbstractTFTScreen
{
  public:

  static AbstractTFTScreen* create()
  {
    return new Screen1();
  }
    
protected:

    virtual void doSetup(TFTMenu* menu);
    virtual void doUpdate(TFTMenu* menu);
    virtual void doDraw(TFTMenu* menu);
    virtual void onButtonPressed(TFTMenu* menu, int pressedButton);

private:
      Screen1();
	  int oldsecond = 0;
  
};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
