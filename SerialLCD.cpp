/** @file	SerialLCD.cpp
 *  @author	Eddie Roosenmaallen, eddie@page.ca
 *  @date	January 2015
 */

#include <SerialLCD.h>

SerialLCD::SerialLCD(int pin) : SoftwareSerial(pin, pin)
{
  pinMode(pin, OUTPUT);
  
  _pin	 = pin;
  _lines = 2;
  _cols	 = 16;
}

void SerialLCD::begin(byte cols, byte rows, unsigned int baud)
{
  SoftwareSerial::begin(baud);
  
  _lines = rows;
  _cols	 = cols;
}

size_t SerialLCD::command(byte cmd)
{
  size_t bytes = 0;
  bytes += write(LCD_COMMAND);
  bytes += write(cmd);
  delay(3);
  return bytes;
}

size_t SerialLCD::specialCommand(byte cmd)
{
  size_t bytes = 0;
  bytes += write(LCD_CONFIG);
  bytes += write(cmd);
  delay(3);
  return bytes;
}

void SerialLCD::clear()
{
  command(LCD_CMD_CLEAR);
}

void SerialLCD::home()
{
  setCursor(0, 0);
}

void SerialLCD::setCursor(byte col, byte row)
{
  byte cmd = LCD_CMD_GOTO;
  
  switch(row)
  {
    case 0:
      cmd += LCD_GOTO_LINE1;
      break;
    case 1:
      cmd += LCD_GOTO_LINE2;
      break;
    case 2:
      if (_cols == 20)
        cmd += LCD_GOTO_LINE3_20;
      else
        cmd += LCD_GOTO_LINE3_16;
      break;
    case 3:
      if (_cols == 20)
        cmd += LCD_GOTO_LINE4_20;
      else
        cmd += LCD_GOTO_LINE4_16;
      break;
  }
  
  cmd += col;
  
  command(cmd);
}

void SerialLCD::left()
{
  command(LCD_CMD_LEFT);
}

void SerialLCD::right()
{
  command(LCD_CMD_RIGHT);
}

void SerialLCD::scrollDisplayLeft()
{
  command(LCD_CMD_SCROLL_L);
}

void SerialLCD::scrollDisplayRight()
{
  command(LCD_CMD_SCROLL_R);
}

void SerialLCD::display()
{
  command(LCD_CMD_DISP_ON);
}

void SerialLCD::noDisplay()
{
  command(LCD_CMD_DISP_OFF);
}

void SerialLCD::cursor()
{
  command(LCD_CMD_CURSOR_ON);
}

void SerialLCD::noCursor()
{
  command(LCD_CMD_CURSOR_OFF);
}

void SerialLCD::blink()
{
  command(LCD_CMD_BLINK_ON);
}

void SerialLCD::noBlink()
{
  command(LCD_CMD_BLINK_OFF);
}

void SerialLCD::configLight(byte percent)
{
  byte level;
  level = map(percent, 0, 100, 0, 30);
  specialCommand(LCD_CONF_LIGHT + level);
}
