#ifndef DRIVERS_GPIO_H_
#define DRIVERS_GPIO_H_

#include <codegen/GPIO.h>
#include <FreeRTOSConfig.h>
#include <stdint.h>

class GPIO
{
   public:
      static GPIO& getSingleton();

      typedef enum
      {
         polarityLow,
         polarityHigh
      } Polarity;

      ~GPIO(){}

   private:
      GPIO(){}
      GPIO(uint8_t* baseAddress);
      GPIO(GPIO const&);
      void operator=(GPIO const&);

      uint8_t* baseAddress;
};

#endif
