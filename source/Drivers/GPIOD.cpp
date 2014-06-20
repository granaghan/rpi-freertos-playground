#include <Drivers/GPIOD.h>

GPIO& GPIO::getSingleton()
{
   static GPIO gpio(reinterpret_cast<uint8_t*>(0x20200000));

   return gpio;
}

GPIO::GPIO(uint8_t* baseAddress):
   baseAddress(baseAddress)
{}

