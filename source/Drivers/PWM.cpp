#include "Drivers/PWM.h"

uint8_t* const PWM::PWM0BaseAddress = (uint8_t* const)  0x2020C000;

PWM::PWM(uint8_t* baseAddress):
   baseAddress(baseAddress)
{
   writeRNG1(baseAddress, 100);
   writeRNG2(baseAddress, 100);
}

PWM::~PWM(){}

void PWM::enableChannel(uint8_t channel)
{
   switch(channel)
   {
      case 0:
         writeCTL_PWEN1(baseAddress, 1);
      case 1:
         writeCTL_PWEN2(baseAddress, 1);
   }
}

void PWM::disableChannel(uint8_t channel)
{
   switch(channel)
   {
      case 0:
         writeCTL_PWEN1(baseAddress, 0);
      case 1:
         writeCTL_PWEN2(baseAddress, 0);
   }
}

void PWM::setDutyCycle(uint8_t channel, uint8_t dutyCycle)
{
   switch(channel)
   {
      case 0:
         writeDAT1(baseAddress, dutyCycle);
      case 1:
         writeDAT2(baseAddress, dutyCycle);
   }
}


