//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Settings.h"
#include "CONFIG.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SettingsClass Settings;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SettingsClass::SettingsClass()
{
  eeprom = NULL;
  dsTemp.Value = NO_TEMPERATURE_DATA;
  analogSensorValue = 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void SettingsClass::begin()
{
//  eeprom = new AT24C64();
  dsTemp.Value = NO_TEMPERATURE_DATA;
  analogSensorValue = 0;

  dsSensor.begin(DS18B20_PIN);
  dsSensor.setResolution(temp12bit);

  sensorsUpdateTimer = millis() + SENSORS_UPDATE_FREQUENCY;
  
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void SettingsClass::update()
{
  if(millis() - sensorsUpdateTimer > SENSORS_UPDATE_FREQUENCY)
  {
    sensorsUpdateTimer = millis();
    dsSensor.readTemperature(dsTemp,DS18B20_SENSOR);

    analogSensorValue = analogRead(ANALOG_SENSOR_PIN);
  }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
uint16_t SettingsClass::getChannelPulses(uint8_t channelNum)
{
  uint16_t addr = 0;
  switch(channelNum)
  {
    case 0:
    addr = COUNT_PULSES_STORE_ADDRESS1;
    break;
    
    case 1:
    addr = COUNT_PULSES_STORE_ADDRESS2;
    break;
    
    case 2:
    addr = COUNT_PULSES_STORE_ADDRESS3;
    break;
  }

  uint16_t result = 0;
  uint8_t* writePtr = (uint8_t*)&result;
  eeprom->read(addr,writePtr,sizeof(uint16_t));

  if(result == 0xFFFF)
  {
    result = 0;
    setChannelPulses(channelNum,result);
  }

  return result;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void SettingsClass::setChannelPulses(uint8_t channelNum, uint16_t val)
{
  uint16_t addr = 0;
  switch(channelNum)
  {
    case 0:
    addr = COUNT_PULSES_STORE_ADDRESS1;
    break;
    
    case 1:
    addr = COUNT_PULSES_STORE_ADDRESS2;
    break;
    
    case 2:
    addr = COUNT_PULSES_STORE_ADDRESS3;
    break;
  }

    uint8_t* writePtr = (uint8_t*)&val;
    eeprom->write(addr,writePtr,sizeof(uint16_t));
}
*/
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

