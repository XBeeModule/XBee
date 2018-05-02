#pragma once
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "UTFTMenu.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// экран номер 1_0
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Screen1_0 : public AbstractTFTScreen
{
  public:

  static AbstractTFTScreen* create()
  {
    return new Screen1_0();
  }
    
protected:

    virtual void doSetup(TFTMenu* menu);
    virtual void doUpdate(TFTMenu* menu);
    virtual void doDraw(TFTMenu* menu);
    virtual void onButtonPressed(TFTMenu* menu, int pressedButton);

private:
      Screen1_0();
  
  
};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
