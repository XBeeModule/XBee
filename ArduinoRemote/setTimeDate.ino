

void drawUpButton(int x, int y)
{
  myGLCD.setColor(64, 64, 128);
  myGLCD.fillRoundRect(x, y, x+32, y+25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(x, y, x+32, y+25);
  myGLCD.setColor(128, 128, 255);
  for (int i=0; i<15; i++)
  myGLCD.drawLine(x+6+(i/1.5), y+20-i, x+27-(i/1.5), y+20-i);
}

void drawDownButton(int x, int y)
{
  myGLCD.setColor(64, 64, 128);
  myGLCD.fillRoundRect(x, y, x+32, y+25);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(x, y, x+32, y+25);
  myGLCD.setColor(128, 128, 255);
  for (int i=0; i<15; i++)
  myGLCD.drawLine(x+6+(i/1.5), y+5+i, x+27-(i/1.5), y+5+i);
}

void showDOW(byte dow)
{
  char* str[] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};
  myGLCD.setColor(128, 128, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print(str[dow-1], 16, 167);
}

int bin_to_bcd(int temp)//decimal to BCD
{
	int a,b,c;
	a=temp;
	b=0;
	if(a>=10)
	{
		while(a>=10)
		{
			a=a-10;
			b=b+16;
			c=a+b;
			temp=c;
		}
	}
	return temp;
}

byte validateDate(byte d, byte m, word y)
{
  byte mArr[12] = {31,0,31,30,31,30,31,31,30,31,30,31};
  byte od;
  
  if (m==2)
  {
    if ((y % 4)==0)
    {
      if (d==30)
        od=1;
      else if (d==0)
        od=29;
      else
        od=d;
    }
    else
    {
      if (d==29)
        od=1;
      else if (d==0)
        od=28;
      else
        od=d;
    }
  }
  else
  {
    if (d==0)
      od=mArr[m-1];
    else if (d==(mArr[m-1]+1))
      od=1;
    else
      od=d;
  }
  
  return od;
}

byte validateDateForMonth(byte d, byte m, word y)
{
  byte mArr[12] = {31,0,31,30,31,30,31,31,30,31,30,31};
  byte od;
  boolean dc=false;
  
  if (m==2)
  {
    if ((y % 4)==0)
    {
      if (d>29)
      {
        d=29;
        dc=true;
      }
    }
    else
    {  
      if (d>28)
      {
        d=28;
        dc=true;
      }
    }
  }
  else
  {
    if (d>mArr[m-1])
    {
      d=mArr[m-1];
      dc=true;
    }
  }
  
  if (dc)
  {
    if (d<10)
    {
      myGLCD.printNumI(0, 82, 140);
      myGLCD.printNumI(d, 98, 140);
    }
    else
    {
      myGLCD.printNumI(d, 82, 140);
    }
  }
  
  return d;
}

void setClock()
{

  int t_temp_sec, t_temp_min, t_temp_hour, t_temp_dow, t_temp_date, t_temp_mon, t_temp_year;
 
  int x, y;
  int res = 0;
  boolean ct=false;
  boolean cd=false;
  
  waitForTouchRelease();    
  
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);

  myGLCD.setColor(64, 64, 128);
  myGLCD.fillRoundRect(121, 200, 234, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(121, 200, 234, 239);
  myGLCD.setBackColor(64, 64, 128);
  myGLCD.print("Save", 140, 212);
  myGLCD.setBackColor(0, 0, 0);
  // Draw Cancel button
  myGLCD.setColor(64, 64, 128);
  myGLCD.fillRoundRect(5, 200, 118, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(5, 200, 118, 239);
  myGLCD.setBackColor(64, 64, 128);
  myGLCD.print("Cancel", 15, 212);
  myGLCD.setBackColor(0, 0, 0);
  
  // Draw frames
  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRoundRect(0, 0, 239, 96);
  myGLCD.drawRoundRect(0, 100, 239, 196);
  myGLCD.print("Time:", 5, 40);
  myGLCD.print(":", 114, 40);
  myGLCD.print(":", 162, 40);
  myGLCD.print("Date:", 5, 140);
  myGLCD.print(".", 114, 140);
  myGLCD.print(".", 159, 140);
  
 // Draw Buttons
  drawUpButton(82, 10);
  drawUpButton(130, 10);
  drawUpButton(178, 10);
  drawDownButton(82, 61);
  drawDownButton(130, 61);
  drawDownButton(178, 61);
  drawUpButton(82, 110);
  drawUpButton(130, 110);
  drawUpButton(184, 110);
  drawDownButton(82, 161);
  drawDownButton(130, 161);
  drawDownButton(184, 161);
  
  // Print current time and date
  myGLCD.setColor(255, 255, 255);
  clock_read();

    t_temp_date=day;
    t_temp_mon=month;
    t_temp_year=year;
    t_temp_dow=dow;
    t_temp_hour=hour;
    t_temp_min=minute;
    t_temp_sec=second;

  if (t_temp_date==0)
  {
    t_temp_date=1;
    t_temp_mon=1;
    t_temp_year=2016;
    t_temp_dow=5;
    t_temp_hour=0;
    t_temp_min=0;
    t_temp_sec=0;
    ct=true;
    cd=true;
  }
  
  if (t_temp_hour<10)
  {
    myGLCD.printNumI(0, 82, 40);
    myGLCD.printNumI(t_temp_hour, 98, 40);
  }
  else
  {
    myGLCD.printNumI(t_temp_hour, 82, 40);
  }
  if (t_temp_min<10)
  {
    myGLCD.printNumI(0, 130, 40);
    myGLCD.printNumI(t_temp_min, 146, 40);
  }
  else
  {
    myGLCD.printNumI(t_temp_min, 130, 40);
  }
  if (t_temp_sec<10)
  {
    myGLCD.printNumI(0, 178, 40);
    myGLCD.printNumI(t_temp_sec, 194, 40);
  }
  else
  {
    myGLCD.printNumI(t_temp_sec, 178, 40);
  }
  if (t_temp_date<10)
  {
    myGLCD.printNumI(0, 82, 140);
    myGLCD.printNumI(t_temp_date, 98, 140);
  }
  else
  {
    myGLCD.printNumI(t_temp_date, 82, 140);
  }
  if (t_temp_mon<10)
  {
    myGLCD.printNumI(0, 130, 140);
    myGLCD.printNumI(t_temp_mon, 146, 140);
  }
  else
  {
    myGLCD.printNumI(t_temp_mon, 130, 140);
  }
  myGLCD.printNumI(t_temp_year, 168, 140);
 // showDOW(t_temp_dow);
  
  while (res==0)
  {

    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
	 
      if ((y>=20) && (y<=45)) // Buttons: Time UP
      {


        if ((x>=82+x_delta+6) && (x<=114+x_delta+6))
        {
          buttonWait(82, 10);
          t_temp_hour+=1;
          if (t_temp_hour==24)
            t_temp_hour=0;
          if (t_temp_hour<10)
          {
            myGLCD.printNumI(0, 82, 40);
            myGLCD.printNumI(t_temp_hour, 98, 40);
          }
          else
          {
            myGLCD.printNumI(t_temp_hour, 82, 40);
          }
          if (ct==false)
          {
            ct=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 10);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        else if ((x>=130+x_delta+3) && (x<=162+x_delta+3))
        {
          buttonWait(130, 10);
          t_temp_min+=1;
          if (t_temp_min==60)
            t_temp_min=0;
          if (t_temp_min<10)
          {
            myGLCD.printNumI(0, 130, 40);
            myGLCD.printNumI(t_temp_min, 146, 40);
          }
          else
          {
            myGLCD.printNumI(t_temp_min, 130, 40);
          }
          if (ct==false)
          {
            ct=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 10);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        else if ((x>=178+x_delta) && (x<=210+x_delta))
        {
          buttonWait(178, 10);
          t_temp_sec+=1;
          if (t_temp_sec==60)
            t_temp_sec=0;
          if (t_temp_sec<10)
          {
            myGLCD.printNumI(0, 178, 40);
            myGLCD.printNumI(t_temp_sec, 194, 40);
          }
          else
          {
            myGLCD.printNumI(t_temp_sec, 178, 40);
          }
          if (ct==false)
          {
            ct=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 10);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
      }
	
      else if ((y>=61+10) && (y<=86+10)) // Buttons: Time DOWN
      {
        if ((x>=82+x_delta+6) && (x<=114+x_delta+6))
        {
          buttonWait(82, 61);
          t_temp_hour-=1;
          if (t_temp_hour==-1)
            t_temp_hour=23;
          if (t_temp_hour<10)
          {
            myGLCD.printNumI(0, 82, 40);
            myGLCD.printNumI(t_temp_hour, 98, 40);
          }
          else
          {
            myGLCD.printNumI(t_temp_hour, 82, 40);
          }
          if (ct==false)
          {
            ct=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 10);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        else if ((x>=130+x_delta+3) && (x<=162+x_delta+3))
        {
          buttonWait(130, 61);
          t_temp_min-=1;
          if (t_temp_min==-1)
            t_temp_min=59;
          if (t_temp_min<10)
          {
            myGLCD.printNumI(0, 130, 40);
            myGLCD.printNumI(t_temp_min, 146, 40);
          }
          else
          {
            myGLCD.printNumI(t_temp_min, 130, 40);
          }
          if (ct==false)
          {
            ct=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 10);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        else if ((x>=178+x_delta) && (x<=210+x_delta))
        {
          buttonWait(178, 61);
          t_temp_sec-=1;
          if (t_temp_sec==-1)
            t_temp_sec=59;
          if (t_temp_sec<10)
          {
            myGLCD.printNumI(0, 178, 40);
            myGLCD.printNumI(t_temp_sec, 194, 40);
          }
          else
          {
            myGLCD.printNumI(t_temp_sec, 178, 40);
          }
          if (ct==false)
          {
            ct=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 10);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
      }

	  
      if ((y>=120) && (y<=145)) // Buttons: Date UP
      {
        if ((x>=82+x_delta+6) && (x<=114+x_delta+6))
        {
          buttonWait(82, 110);
          t_temp_date+=1;
          t_temp_date=validateDate(t_temp_date, t_temp_mon, t_temp_year);
          if (t_temp_date<10)
          {
            myGLCD.printNumI(0, 82, 140);
            myGLCD.printNumI(t_temp_date, 98, 140);
          }
          else
          {
            myGLCD.printNumI(t_temp_date, 82, 140);
          }
          if (cd==false)
          {
            cd=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 110);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        else if ((x>=130+x_delta+3) && (x<=162+x_delta+3))
        {
          buttonWait(130, 110);
          t_temp_mon+=1;
          if (t_temp_mon==13)
		  {
            t_temp_mon=1;
		  }
          if (t_temp_mon<10)
          {
            myGLCD.printNumI(0, 130, 140);
            myGLCD.printNumI(t_temp_mon, 146, 140);
          }
          else
          {
            myGLCD.printNumI(t_temp_mon, 130, 140);
          }
          t_temp_date=validateDateForMonth(t_temp_date, t_temp_mon, t_temp_year);
          if (cd==false)
          {
            cd=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 110);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        else if ((x>=184+x_delta) && (x<=220+x_delta))// исправить
        {
          buttonWait(184, 110);
          t_temp_year+=1;
          if (t_temp_year==2100)
            t_temp_year=2000;
          myGLCD.printNumI(t_temp_year, 168, 140);
          t_temp_date=validateDateForMonth(t_temp_date, t_temp_mon, t_temp_year);
          if (cd==false)
          {
            cd=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 110);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        t_temp_dow=calcDOW(t_temp_date, t_temp_mon, t_temp_year);
        showDOW(t_temp_dow);
      }
      else if ((y>=171) && (y<=196)) // Buttons: Date DOWN
      {
        if ((x>=82+x_delta+6) && (x<=114+x_delta+6))
        {
          buttonWait(82, 161);
          t_temp_date-=1;
          t_temp_date=validateDate(t_temp_date, t_temp_mon, t_temp_year);
          if (t_temp_date<10)
          {
            myGLCD.printNumI(0, 82, 140);
            myGLCD.printNumI(t_temp_date, 98, 140);
          }
          else
          {
            myGLCD.printNumI(t_temp_date, 82, 140);
          }
          if (cd==false)
          {
            cd=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 110);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        else if ((x>=130+x_delta+3) && (x<=162+x_delta+3))
        {
          buttonWait(130, 161);
          t_temp_mon-=1;
          if (t_temp_mon==0)
            t_temp_mon=12;
          if (t_temp_mon<10)
          {
            myGLCD.printNumI(0, 130, 140);
            myGLCD.printNumI(t_temp_mon, 146, 140);
          }
          else
          {
            myGLCD.printNumI(t_temp_mon, 130, 140);
          }
          t_temp_date=validateDateForMonth(t_temp_date, t_temp_mon, t_temp_year);
          if (cd==false)
          {
            cd=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 110);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        else if ((x>=184+x_delta) && (x<=216+x_delta))// исправить
        {
          buttonWait(184, 161);
          t_temp_year-=1;
          if (t_temp_year==1999)
            t_temp_year=2099;
          myGLCD.printNumI(t_temp_year, 168, 140);
          t_temp_date=validateDateForMonth(t_temp_date, t_temp_mon, t_temp_year);
          if (cd==false)
          {
            cd=true;
            myGLCD.setColor(64, 64, 128);
            myGLCD.setFont(SmallFont);
            myGLCD.print("Changed!", 5, 110);
            myGLCD.setColor(255, 255, 255);
            myGLCD.setFont(BigFont);
          }
        }
        t_temp_dow=calcDOW(t_temp_date, t_temp_mon, t_temp_year);
        showDOW(t_temp_dow);
      }
	  

      else if ((y>=200) && (y<=239)) // Buttons: CANCEL / SAVE
      {
        if ((x>=121) && (x<=234))
        {
          res=1;
          myGLCD.setColor (255, 0, 0);
          myGLCD.drawRoundRect(121, 200, 234, 239);
        }
        else if ((x>=5) && (x<=118))
        {
          res=2;
          myGLCD.setColor (255, 0, 0);
          myGLCD.drawRoundRect(5, 200, 118, 239);
        }
      }
	}
  }
  
  waitForTouchRelease();

  if (res==1)
  {
    if (ct|cd)
	{
	  t_temp_year = t_temp_year-2000;
	  Wire.beginTransmission(0x68);//DS1307 write the initial time
	  Wire.write(0);
	  Wire.requestFrom(0x68, 7);
	  Wire.write(bin_to_bcd(t_temp_sec));
	  Wire.write(bin_to_bcd(t_temp_min));
	  Wire.write(bin_to_bcd(t_temp_hour));
	  Wire.write(bin_to_bcd(t_temp_dow));
	  Wire.write(bin_to_bcd(t_temp_date));
	  Wire.write(bin_to_bcd(t_temp_mon));
	  Wire.write(bin_to_bcd(t_temp_year));	
	  Wire.endTransmission();
	}
   
  }
}


