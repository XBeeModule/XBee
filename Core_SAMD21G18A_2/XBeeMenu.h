#ifndef _XBEEMENU_H
#define _XBEEMENU_H

#include <XBee.h>
#include <Arduino.h>
//################################### Настройки XBee ########################################################################################

//
//XBee xbee = XBee();                                   //создаем XBee библиотеку
//
//// ++++++++++  настройки для приема и передачи пакета +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//XBeeResponse response = XBeeResponse();               //Это создает экземпляр объекта "response" "ответ" обрабатывать пакеты Xbee
//ZBRxResponse rx = ZBRxResponse();                     //Это создает экземпляр объекта "rx" на процесс Xbee Series 2 API пакеты
//ModemStatusResponse msr = ModemStatusResponse();      //Это создает экземпляр объекта "msr" процесс associate/disassociate packets (PAN membership)
//ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();

/*
//Строка с данными
uint8_t payload[64] = { 0 };

int XBee_Addr16;                            //16-разрядный адрес
int Len_XBee = 0;
unsigned char info_XBee_data[96];
unsigned char info_XBee_data1[96];
char* simbol_ascii[2];
char   cmd;

uint8_t shCmd[] = { 'S','H' };                // serial high Старший байт адреса куда отправляется пакет
uint8_t slCmd[] = { 'S','L' };                // serial low Младший байт адреса куда отправляется пакет
uint8_t assocCmd[] = { 'A','I' };             // association status Индикация присоединения 
											  
											  //Считывает информацию о последнем запросе узла на присоединение:
											  //0x00 – Завершено успешно - Координатор стартовал илиМаршрутизатор/Конечное устройство
											  //обнаружило и присоединилось родительскому устройству.
											  //0x21 – Сканирование не обнаружило сети
											  //0x22 – Сканирование не обнаружило работающей сети с текущими установками SC и ID
											  //0x23 – Работающий Координатор или Маршрутизаторы найдены, но они не дали разрешение на
											  //присоединение к сети (истекло время NJ)
											  //0x27 – Попытка присоединения не удалась
											  //0x2A – Запуск Координатора не удался
											  //0xFF – Идет поиск родительского устройства
											  
uint8_t irCmd[] = { 'I','R' };             // 
uint8_t opCmd[] = { 'O','P' };             // Номер сети (PAN ID)
uint8_t IDCmd[] = { 'I','D' };             // Номер сети (ID)
uint8_t OICmd[] = { 'O','I' };             // Operating 16-bit PAN ID(OI)
uint8_t MYCmd[] = { 'M','Y' };             // Номер сети (16-bit Network Adress
uint8_t CHCmd[] = { 'C','H' };             // Номер Радиоканала
uint8_t SCCmd[] = { 'S','C' };             // Scan Channel
uint8_t BDCmd[] = { 'B','D' };             // Скорость канала (Baud Rate )
uint8_t VoltCmd[] = { '%','V' };             // Напряжение питания Считывает напряжение на выводе Vcc. Для преобразования значения
											 // в мВ, поделите значение на 1023 и умножьте на 1200. Значение %V равное 0x8FE (или 2302 в
											 // десятичном виде) соответствует 2700мВ или 2.70В
uint8_t TPCmd[] = { 'T','P' };             // Температура
uint8_t dhCmd[] = { 'D','H' };             // Старший байт адреса
uint8_t dlCmd[] = { 'D','L' };             // Младший байт адреса
uint8_t d0Cmd[] = { 'D','0' };             //
uint8_t WRCmd[] = { 'W','R' };             // Запись в модуль параметров
										   // Примечание: Если введена команда WR, до получения ответа "OK\r" не должно вводится
										   // дополнительных символов
uint8_t FRCmd[] = { 'F','R' };             // Перезапуск программного обеспечения
uint8_t NRCmd[] = { 'N','R' };             // Перезапуск сети 
										   // Если NR = 0: Переустанавливает параметры сети на узле, вызвавшем команду. 
										   // Если NR = 1:Отправляетшироковещательную передачу для перезапуска параметров на всех узлах сети.
uint8_t PLCmd[] = { 'P','L' };             // TX Power level mW
uint8_t NDCmd[] = { 'N','D' };             // Обнаружение узла (Node Discover). Обнаруживает и сообщает обо всех
										   // найденных модулях. Следующая информация будет сообщена для каждого
										   // обнаруженного модуля:
										   // MY<CR>      16-разрядный адрес источника
										   // SH<CR>      Старшие байты серийного номера
										   // SL<CR>      Младшие байты серийного номера
										   // DB<CR>      Сила принимаемого сигнала (Received Signal Strength)
										   // NI<CR><CR>  Идентификатор узла (Node Identifier). Имя модуля

uint8_t NTCmd[] = { 'N','T' };             // Node Discovery Timeout. Set/Read the node discovery timeout. When the network
										   // discovery (ND) command is issued, the NT value is included in the transmission to
										   // provide all remote devices with a response timeout. Remote devices wait a random
										   //  time, less than NT, before sending their response.  0x3C (60d)


uint8_t d0Value[] = { 0x2 };
uint8_t irValue[] = { 0xff, 0xff };
uint8_t IDValue[] = { 0x02, 0x34 };


uint8_t command[] = { 'I','D' };             // Номер сети (ID)
uint8_t commandValue[] = { 0x02, 0x35 };
uint8_t commandValueLength = 0x2;




//Два 32-битных половинки th4 64-разрядный адрес
long XBee_Addr64_MS = 0x0013a200;
long XBee_Addr64_LS = 0; //0x40672567;

						 //Два 32-битных половинки th4 64-разрядный адрес
long XBee_Addr64_MS_tmp = 0;                    //
long XBee_Addr64_LS_tmp = 0;                    //

XBeeAddress64 addr64 = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);                                     // SH + SL Address of receiving XBee
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));                                         // Формирует пакет  zbTx с адресом отправителя и данными
ZBTxStatusResponse txStatus = ZBTxStatusResponse();                                                       // Это создает экземпляр объекта "txStatus" процесс благодарности прислал Xbee Series 2 API пакеты
AtCommandRequest atRequest = AtCommandRequest(shCmd);                                                     // XBeeAddress64 remoteAddress = XBeeAddress64(XBee_Addr64_MS, XBee_Addr64_LS);
AtCommandRequest arRequestMod = AtCommandRequest(command, commandValue, commandValueLength);
AtCommandResponse atResponse = AtCommandResponse();
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(addr64, irCmd, irValue, sizeof(irValue)); // Create a remote AT request with the IR command
RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();                                     // Create a Remote AT response object


																										  //********************************
byte funcType;                      // Номер функции, переданной по каналу  XBee
word field1;                        // Данные,  переданные по каналу  XBee
word field2;                        // Данные,  переданные по каналу  XBee
byte *_msg, _len;                   // Длина строки
word _baud, _crc;                   // Скорость обмена и контрольная сумма блока  
*/

//class XBeeActive
//{
//
//public:
//	//XBeeActive();
//
//
//
//
//
//private:
//
//
//
//};
//--------------------------------------------------------------------------------------------------------------------------------------
//extern XBeeActive RealXBeeMenu;
//--------------------------------------------------------------------------------------------------------------------------------------
#endif
