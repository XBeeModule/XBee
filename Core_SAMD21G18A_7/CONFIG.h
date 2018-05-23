#pragma once
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define _DEBUG // закомментировать для выключения отладочной информации
#define IGNORE_ROD_POSITION // ЗАКОММЕНТИРОВАТЬ, ЕСЛИ НЕ НАДО ИГНОРИРОВАТЬ ПОЗИЦИЮ ШТАНГИ ПРИ СРАВНЕНИИ ЭТАЛОНОВ !!!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define SERIAL_SPEED 115200 // скорость работы с Serial
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// настройки пинов прерываний
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// настройка логов
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define LOGS_DIRECTORY "/LOG" // папка, в которой лежат логи
#define ETHALONS_DIRECTORY "/ETL" // папка, где лежат эталоны
#define ETHALON_NAME_PREFIX "/et" // префикс имени файла эталона
#define ETHALON_UP_POSTFIX "up" // постфикс для имени файла эталона, поднятие штанги
#define ETHALON_DOWN_POSTFIX "dwn" // постфикс для имени файла эталона, опускание штанги
#define ETHALON_FILE_EXT ".etl" // расширение файла эталона
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define DATA_MEASURE_THRESHOLD 2000 // через сколько миллисекунд обновлять показания с линий вольтажа и температуру с часов
#define VOLTAGE_THRESHOLD 10 // порог изменений, в процентах, для принятия решения о том, хороший вольтаж или нет
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// настройки EEPROM
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// заголовки записей, которым нужны префиксы
#define RECORD_HEADER1 0xD0
#define RECORD_HEADER2 0xEF
#define RECORD_HEADER3 0x18

// импульсы по каналам
#define COUNT_PULSES_STORE_ADDRESS1 10 // по какому адресу храним переменную для кол-ва импульсов канала 1 (2 байта)
#define COUNT_PULSES_STORE_ADDRESS2 12 // по какому адресу храним переменную для кол-ва импульсов канала 2 (2 байта)
#define COUNT_PULSES_STORE_ADDRESS3 14 // по какому адресу храним переменную для кол-ва импульсов канала 3 (2 байта)

// дельты импульсов по каналам
#define CHANNEL_PULSES_DELTA_ADDRESS1 16 // адрес хранения дельты импульсов канала 1 (1 байт)
#define CHANNEL_PULSES_DELTA_ADDRESS2 17 // адрес хранения дельты импульсов канала 1 (1 байт)
#define CHANNEL_PULSES_DELTA_ADDRESS3 18 // адрес хранения дельты импульсов канала 1 (1 байт)

// моторесурс по каналам
#define MOTORESOURCE_STORE_ADDRESS1  100 // адрес хранения кол-ва срабатываний защиты канала 1 (4 байта)
#define MOTORESOURCE_STORE_ADDRESS2  104 // адрес хранения кол-ва срабатываний защиты канала 2 (4 байта)
#define MOTORESOURCE_STORE_ADDRESS3  108 // адрес хранения кол-ва срабатываний защиты канала 3 (4 байта)

#define MOTORESOURCE_MAX_STORE_ADDRESS1  112 // адрес хранения макс. кол-ва срабатываний защиты канала 1 (4 байта)
#define MOTORESOURCE_MAX_STORE_ADDRESS2  116 // адрес хранения макс. кол-ва срабатываний защиты канала 2 (4 байта)
#define MOTORESOURCE_MAX_STORE_ADDRESS3  120 // адрес хранения макс. кол-ва срабатываний защиты канала 3 (4 байта)

#define UUID_STORE_ADDRESS  130 // адрес хранения уникального идентификатора контроллера (32 байта идентификатор + 3 байта - префикс = 35 байт)

#define TRANSFORMER_LOW_BORDER_STORE_ADDRESS 170 // адрес хранения нижнего порога токового трансформатора (4 байта)
#define TRANSFORMER_HIGH_BORDER_STORE_ADDRESS 174 // адрес хранения верхнего порога токового трансформатора (4 байта)

#define RELAY_DELAY_STORE_ADDRESS 178 // адрес хранения задержки после срабатывания защиты и до начала импульсов (4 байта)
#define ACS_DELAY_STORE_ADDRESS 182 // адрес хранения задержки после срабатывания защиты и до начала выдачи сигнала АСУ ТП (2 байта)
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// настройки обновления состояния исправности индуктивных датчиков
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define INDUCTIVE_SENSORS_UPDATE_INTERVAL 1000 // интервал обновления, в миллисекундах
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// версия ПО
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define SOFTWARE_VERSION "v.0.1a"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//// время в миллисекундах, после которого идёт переключение на главный экран, если какой-то экран висит долгое время
#define RESET_TO_MAIN_SCREEN_DELAY 60000
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//// частота мигания надписью моторесурса, если он исчерпан, миллисекунд
//#define MOTORESOURCE_BLINK_DURATION 800
//
//// через сколько процентов до максимального мигать надписью моторесурса (например, если уканано 10, то будет мигать после 90% выработки)
//#define MOTORESOURCE_BLINK_PERCENTS 10
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//// кол-во кадров в секунду для отображения синусоид
//#define CHART_FPS 30
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//// дельта времени импульсов (микросекунд) при сравнении эталона с пачкой пойманных импульсов
//#define ETHALON_COMPARE_DELTA 500
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//// настройки порогов токового трансформатора по умолчанию
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//#define TRANSFORMER_HIGH_DEFAULT_BORDER 3500 // верхний порог
//#define TRANSFORMER_LOW_DEFAULT_BORDER 2500 // нижний порог
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------




#define NVIC_PriorityGroup_0   ((uint32_t)0x700)
#define NVIC_PriorityGroup_1   ((uint32_t)0x600)
#define NVIC_PriorityGroup_2   ((uint32_t)0x500)
#define NVIC_PriorityGroup_3   ((uint32_t)0x400)
#define NVIC_PriorityGroup_4   ((uint32_t)0x300)



#ifdef _DEBUG
  #define DBG(s) { Serial << (s); }
  #define DBGLN(s) { Serial << (s) << ENDL; }
#else
  #define DBG(s) (void) 0
  #define DBGLN(s) (void) 0
#endif
#define ENDL '\n'
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename T> inline Stream& operator << (Stream &s, T n) { s.print(n); return s; }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define CORE_COMMAND_GET F("GET=") // префикс для команды получения данных из ядра
#define CORE_COMMAND_SET F("SET=") // префикс для команды сохранения данных в ядро
#define CORE_COMMAND_ANSWER_OK F("OK=") // какой префикс будет посылаться в ответ на команду получения данных и её успешной отработке
#define CORE_COMMAND_ANSWER_ERROR F("ER=") // какой префикс будет посылаться в ответ на команду получения данных и её неуспешной отработке
#define CORE_COMMAND_PARAM_DELIMITER '|' // разделитель параметров
#define CORE_END_OF_DATA F("[END]")
#define CORE_COMMAND_DONE F("DONE")
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

