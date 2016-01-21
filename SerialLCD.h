/** @file    SerialLCD.h
 *  @author  Eddie Roosenmaallen, eddie@page.ca
 *  @date    January 2015
 *
 *  This is a helper library for the SparkFun SerLCD 2.5. The API is modelled after 
 *  LiquidCrystal, with additions to support the SerLCD's additional functionality.
 */

#ifndef SerialLCD_h
#define SerialLCD_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#define LCD_COMMAND           0xFE
#define LCD_CONFIG            0x7C

#define LCD_CMD_CLEAR         0x01
#define LCD_CMD_RIGHT         0x14
#define LCD_CMD_LEFT          0x10
#define LCD_CMD_SCROLL_L      0x18
#define LCD_CMD_SCROLL_R      0x1C
#define LCD_CMD_DISP_ON       0x0C
#define LCD_CMD_DISP_OFF      0x08
#define LCD_CMD_CURSOR_ON     0x0E
#define LCD_CMD_CURSOR_OFF    0x0C
#define LCD_CMD_BLINK_ON      0x0D
#define LCD_CMD_BLINK_OFF     0x0C

#define LCD_CMD_GOTO          0x80
#define LCD_GOTO_LINE1        0
#define LCD_GOTO_LINE2        64
#define LCD_GOTO_LINE3_16     16
#define LCD_GOTO_LINE4_16     80
#define LCD_GOTO_LINE3_20     20
#define LCD_GOTO_LINE4_20     84

#define LCD_CONF_SPLASH_ONOFF 0x09      // Toggle the splash screen
#define LCD_CONF_SAVE_SPLASH  0x0A      // ^j == Save a new splash screen
#define LCD_CONF_LIGHT        0x80      // 0x80 + [0..30] to set brightness 0..100%
#define LCD_CONF_LIGHT_OFF    127       // 127 == 0% brightness
#define LCD_CONF_LIGHT_50     143       // 127 + 15 == 50% brightness
#define LCD_CONF_LIGHT_ON     157       // 127 + 30 == 100% brightness
#define LCD_CONF_20C          0x03      // 20-character display
#define LCD_CONF_16C          0x04      // 16-cahracter display
#define LCD_CONF_4L           0x05      // 4-line display
#define LCD_CONF_2L           0x06      // 2-line display
#define LCD_CONF_2400         0x0B
#define LCD_CONF_4800         0x0C
#define LCD_CONF_9600         0x0D
#define LCD_CONF_14400        0x0E
#define LCD_CONF_19200        0x0F
#define LCD_CONF_38400        0x10

#define LCD_CONF_RESET        0x12      // MUST be sent while splash is displayed

class SerialLCD : public SoftwareSerial
{
  public:
    SerialLCD(int pin);
    
    void begin(byte cols, byte rows, unsigned int baud);
    void clear();
    void home();

    void left();
    void right();
    void scrollDisplayLeft();
    void scrollDisplayRight();
  
    void display();
    void noDisplay();
    void cursor();
    void noCursor();
    void blink();
    void noBlink();

    void setCursor(byte col, byte row);
    
//     void configGeometry(byte lines, byte cols);
    void configToggleSplash();
    void configSaveSplash();
    void configLight(byte percent);
    void configBaud(byte newBaud);
    
    size_t command(byte);
    size_t specialCommand(byte);
        
  private:
    byte _lines;
    byte _cols;
    byte _pin;
};

#endif
