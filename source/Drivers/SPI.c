#include <codegen/SPI.h>
#include <FreeRTOSConfig.h>
#include <stdint.h>


uint8_t* SPI0BaseAddress = (uint8_t*)0x7E20400;

typedef enum
{
   polarityLow,
   polarityHigh
} Polarity;

void setClockSpeed(uint32_t frequenct)
{
   //writeA
}

void setChannelChipSelectPolarity(uint32_t channel, Polarity polarity)
{
   switch(channel)
   {
      case 0:
         writeCS_CSPOL0(SPI0BaseAddress, polarity);
         break;
      case 1:
         writeCS_CSPOL1(SPI0BaseAddress, polarity);
         break;
      case 2:
         writeCS_CSPOL2(SPI0BaseAddress, polarity);
         break;
   }
}

void setChipSelectPolarity(Polarity polarity)
{
   writeCS_CSPOL(SPI0BaseAddress, polarity);
}