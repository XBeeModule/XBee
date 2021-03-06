#pragma once
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <UTFT.h>
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  uint8_t R, G,B;
  
} RGBClolor;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace Drawing
{
  void DrawGrid(int startX, int startY, int columnsCount, int rowsCount, int columnWidth, int rowHeight, RGBClolor gridColor);
};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

