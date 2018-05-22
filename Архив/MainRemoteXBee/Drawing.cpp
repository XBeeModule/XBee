//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "Drawing.h"
#include "UTFTMenu.h"
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace Drawing
{
  void DrawGrid(int startX, int startY, int columnsCount, int rowsCount, int columnWidth, int rowHeight, RGBClolor gridColor)
  {
    UTFT* dc = Screen.getDC();
    word color = dc->getColor();  
  
    dc->setColor(gridColor.R, gridColor.G, gridColor.B);
      
    for (int col = 0; col <= columnsCount; col++)
    {
        int colX = startX + col*columnWidth;
        dc->drawLine(colX , startY, colX , startY + rowHeight*rowsCount);
    }
    for (int row = 0; row <= rowsCount; row++)
    {
        int rowY = startY + row*rowHeight;
        dc->drawLine(startX, rowY,  startX + columnWidth*columnsCount, rowY);
    }
    
      dc->setColor(color);    
  }
};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

