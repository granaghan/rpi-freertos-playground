#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned int targetTemperature = 100;
unsigned char encoderState = 0;
unsigned char incrementTransition[] = {1, 3, 2, 0};
unsigned char decrementTransition[] = {0, 2, 3, 1};

int main()
{
   //DDRB |=1<<PB5;  /* PA0 will now be the output pin */
   DDRB |= 1<<PB5;
   DDRB &= ~(1<<PB2);
   DDRB &= ~(1<<PB1);
   PORTB |= (1<<PB2) | (1<<PB1);

   PCICR |= (1<<PCIE0);
   PCMSK0 |= (1<<PCINT2) | (1<<PCINT1);

   TWCR = (1<<TWEA) | (1<<TWEN);
   TWAR = 1<<1;
   TWBR = 32;//72; //100kHz

   encoderState = (PINB >> 1) & 3;
   sei();

   init_LCD();

   // Enable interrupts now.
   while(1)
   {
      //_delay_ms(1000);
      //PORTB |= (1<<PB5);
      //_delay_ms(1000);
      //PORTB &= ~(1<<PB5);
      if(TWCR & (1<<TWINT))
      {
         if((TWSR & 0xF8) == 0xA8)
         {
            TWDR = targetTemperature;
            TWCR |= (1<<TWINT);
            TWCR &= ~(1<<TWEA);
         }

         while(!(TWCR & (1<<TWINT)));

         if((TWSR & 0xF8) == 0xC0)
         {
            TWCR |= (1<<TWINT);
            TWCR |= (1<<TWEA);
         }
      }

      //LCD_SENDCOMMAND(LCD_CLEAR);
      //printf("%d", targetTemperature);
   }
   return 0;
}

ISR(PCINT0_vect)
{
   {
      _delay_ms(1);
   }
   unsigned char newEncoderState = (PINB >> 1) & 3;
   if(newEncoderState == incrementTransition[encoderState])
   {
      targetTemperature++;
   }
   else if(newEncoderState == decrementTransition[encoderState])
   {
      targetTemperature--;
   }
   encoderState = newEncoderState;
}
