//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Logger.h"
#include "FileUtils.h"
#include "DS3231.h"
#include "CONFIG.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
LoggerClass Logger;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
LoggerClass::LoggerClass()
{
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void LoggerClass::writeLine(const String& line)
{
 // пишем в лог-файл дату/время срабатывания системы
  SD.mkdir(LOGS_DIRECTORY);

  DS3231Time tm = RealtimeClock.getTime();

  // формируем имя файла ггггммдд.log. (год,месяц,день)
  String logFileName;
  
  logFileName = LOGS_DIRECTORY;
  if(!logFileName.endsWith("/"))
    logFileName += "/";
  
  logFileName += tm.year;
  if(tm.month < 10)
    logFileName += '0';
  logFileName += tm.month;

 if(tm.dayOfMonth < 10)
  logFileName += '0';
 logFileName += tm.dayOfMonth;

  logFileName += F(".LOG");

  //DBG(F("WRITE INFO TO: "));
  //DBGLN(logFileName);

  SdFile file;
  file.open(logFileName.c_str(),FILE_WRITE);
  
  if(file.isOpen())
  {

    DBG(F("LOG >> "));
    DBGLN(line);
    
    file.println(line);
    file.close();
  }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

