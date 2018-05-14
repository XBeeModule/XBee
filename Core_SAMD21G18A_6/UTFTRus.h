#ifndef _UTFTRUS_H
#define _UTFTRUS_H
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <UTFT.h>
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// класс поддержки русских шрифтов для UTFT
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class UTFTRus
{
  public:
    UTFTRus();
    void init(UTFT* uTft);

    int print(const char* str,int x, int y, int deg=0, bool computeStringLengthOnly=false);
    
  private:
    UTFT* pDisplay;


  
};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------