#pragma once
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <SdFat.h>
#include <Arduino.h>
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
extern SdFat SD;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class SDInit
{
  public:
    static bool sdInitFlag;
    static bool sdInitResult;
    static bool InitSD();
};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class FileUtils
{
  public:

    static int CountFiles(const String& dirName);
  
};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
