#include "LCD_SF.h"

//Define Program Vars
//==================================
FILE LCDout = FDEV_SETUP_STREAM(sendChar_LCD, NULL, _FDEV_SETUP_WRITE);

void init_LCD(void)
{
   //PIND &= 0b11111101;
   UCSR0A = 0b00000000;
   UCSR0B = 0b00001100; //Enable Tx; UCSZ01:0 sets char size
   UCSR0C = 0b00000110; //char size is one byte
   UBRR0 = UBRR_LCD; //Set Baud
   stdout = &LCDout;
   //PIND |= 0b00010000;
   //LCD_SENDCOMMAND(LCD_CLEAR);
   PORTD &= ~(1 << 4);
   //PORTD |= 1 << 4;

}

int sendChar_LCD(char send, FILE* stream)
{
   while (!(UCSR0A & 0b00100000));
   UDR0 = send;
   return 0;
}
