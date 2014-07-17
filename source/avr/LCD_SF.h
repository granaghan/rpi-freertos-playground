#ifndef __LCD_SF_H__
#define __LCD_SF_H__
#include <avr/io.h>
#include <stdio.h>

//Backlight Brightnes Settings
//=====================================================================
#define BL_OFF      0
#define BL_40      12
#define BL_73      22
#define BL_ON      29
#define LCD_SETBACKLIGHT(x) do                                \
                            {                                 \
                               while(!(UCSR0A & 0b00100000)); \
                               UDR0 = 0x7C;                   \
                               while(!(UCSR0A & 0b00100000)); \
                               UDR0 = x + 128;                \
                            } while(0);                       \

//=====================================================================

//Set Display Type
//=====================================================================
#define LCD_20WIDE       3
#define LCD_16WIDE       4
#define LCD_4LINE      5
#define LCD_2LINE      6
#define LCD_SETSIZE(x) do                                \
                       {                                 \
                          while(!(UCSR0A & 0b00100000)); \
                          UDR0 = 0x7C;                   \
                          while(!(UCSR0A & 0b00100000)); \
                          UDR0 = x;                      \
                       } while(0);                       \

//=====================================================================

//LCD Commands
//=====================================================================
#define LCD_CLEAR          0x01
#define LCD_MOVERIGHT      0x14
#define LCD_MOVELEFT       0x10
#define LCD_SCROLLRIGHT    0x1C
#define LCD_SCROLLLEFT     0x18
#define LCD_DISPLAYON      0x0C
#define LCD_DISPLAYOFF     0x08
#define LCD_UNDERLINEON    0x0E
#define LCD_UNDERLINEOFF   0x0C
#define LCD_BLINKINGBOXON  0x0D
#define LCD_BLINKINGBOXOFF 0x0C
#define LCD_SETSPLASH        10
#define LCD_BAUD2400         11
#define LCD_BAUD4800         12
#define LCD_BAUD9600         13
#define LCD_BAUD14400        14
#define LCD_BAUD19200        15
#define LCD_BAUD38400        16
#define LCD_BAUDRESET        18
#define LCD_SENDCOMMAND(x) do                                \
                           {                                 \
                              while(!(UCSR0A & 0b00100000)); \
                              UDR0 = 0xFE;                   \
                              while(!(UCSR0A & 0b00100000)); \
                              UDR0 = x;                      \
                           } while(0);                       \

#define LCD_SETCURSORPOS(x) do                                \
                            {                                 \
                               while(!(UCSR0A & 0b00100000)); \
                               UDR0 = 0xFE;                   \
                               while(!(UCSR0A & 0b00100000)); \
                               UDR0 = 0x80 + x;               \
                            } while(0);                       \

#define LCD_TOGGLESPLASH() do                                \
                           {                                 \
                              while(!(UCSR0A & 0b00100000)); \
                              UDR0 = 0x7C;                   \
                              while(!(UCSR0A & 0b00100000)); \
                              UDR0 = 0x09;                   \
                           } while(0);                       \

#define LCD_SETBAUD(x) do                                  \
                       {                                   \
                           while(!(UCSR0A & 0b00100000));  \
                           UDR0 = 0x7C;                    \
                           while(!(UCSR0A & 0b00100000));  \
                           UDR0 = x;                       \
                       } while(0);                         \

//=====================================================================

//Define Program Settings
//=====================================================================
#ifndef F_CPU
#error "F_CPU is not defined. Define F_CPU before including LCD_SF.h."
#endif
#define BAUD_LCD (9600)
#define UBRR_LCD (F_CPU/16/BAUD_LCD-1)
//=====================================================================

//Variables
//=====================================================================
extern FILE LCDout;
//=====================================================================

//Prototypes
//=====================================================================
void init_LCD(void);
int sendChar_LCD(char send, FILE* stream);
//=====================================================================

#endif
