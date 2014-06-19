#include <codegen/UART.h>
#include <FreeRTOSConfig.h>
#include <stdint.h>

class UART
{
   public:
      typedef enum {parityNone, parityEven, parityOdd} Parity;

      typedef enum
      {
         polarityLow,
         polarityHigh
      } Polarity;

      UART(uint8_t* baseAddress);
      ~UART();
      void setBaudRate(uint32_t baudRate);
      void setWordSize(uint32_t sizeInBits);
      void setParity(Parity parity);
      void setStopBitCount(uint32_t stopBitCount);
      void enableTransmit(uint8_t enable);
      void enableReceive(uint8_t enable);
      void sendByte(uint8_t data);
      bool txFIFOFull();
      bool txFIFOEmpty();

      static uint8_t* UART0BaseAddress;

   private:
      uint8_t* baseAddress;
};