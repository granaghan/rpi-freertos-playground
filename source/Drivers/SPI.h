#include <codegen/spi.h>
#include <FreeRTOSConfig.h>
#include <stdint>


void* SPI0BaseAddress = 0x7E204000;

typedef enum Polarity {polarityLow, polarityHigh};

void setClockSpeed(uint32_t frequenct)
{
   //writeA
}

void setChannelChipSelectPolarity(uint32_t channel, Polarity polarity)
{
   switch(channel)
   {
      case 0:
         writeCS_CSPOL0(polarity);
         break;
      case 1:
         writeCS_CSPOL1(polarity);
         break;
      case 2:
         writeCS_CSPOL2(polarity);
         break;
   }
}

void setChipSelectPolarity(Polarity polarity)
{
   writeCS_CSPOL(polarity);
}