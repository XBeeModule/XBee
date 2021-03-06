#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include "CONFIG.h"
#include "TinyVector.h"
//--------------------------------------------------------------------------------------------------------------------------------------
typedef Vector<uint32_t> InterruptTimeList;
//--------------------------------------------------------------------------------------------------------------------------------------
// структура-подписчик обработчика прерываний. Имея такой интерфейс - всегда можно переназначить вывод результатов серий измерений
// от одного обработчика прерываний в разных подписчиков, например: в обычном режиме показывается график при срабатывании прерываний,
// в режиме записи эталона - показывается другой экран, который регистрирует себя в качестве временного обработчика результатов
// серий прерываний, и что-то там с ними делает; по выходу с экрана обработчиком результатов прерываний опять назначается экран с 
// графиками. Т.е. имеем гибкий инструмент, кмк.
//--------------------------------------------------------------------------------------------------------------------------------------
struct InterruptEventSubscriber
{
  // вызывается, когда прерывания на нужном номере завершены, и накоплена статистика
  virtual void OnInterruptRaised(const InterruptTimeList& list, uint8_t interruptNumber) = 0;

  // вызывается, когда есть хотя бы один список с прерываниями - закончен
  virtual void OnHaveInterruptData() = 0;
};
//--------------------------------------------------------------------------------------------------------------------------------------
class InterruptHandlerClass
{
 public:
  InterruptHandlerClass();

   void begin();
   void update();

   void setSubscriber(InterruptEventSubscriber* h);

   void handleInterrupt(uint8_t interruptNumber);

private:

  // списки времён срабатываний прерываний на наших портах
  InterruptTimeList list1;
  InterruptTimeList list2;
  InterruptTimeList list3;

  uint32_t list1LastDataAt;
  uint32_t list2LastDataAt;
  uint32_t list3LastDataAt;

  InterruptEventSubscriber* subscriber;

  void normalizeList(InterruptTimeList& list);

  void writeToLog(const InterruptTimeList& lst1, const InterruptTimeList& lst2, const InterruptTimeList& lst3);

};
//--------------------------------------------------------------------------------------------------------------------------------------
extern InterruptHandlerClass InterruptHandler;
//--------------------------------------------------------------------------------------------------------------------------------------

