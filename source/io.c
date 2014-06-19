#include <stdint.h>

inline void write32(volatile uint32_t* ptr, uint32_t value)
{
   *ptr = value;
}

inline uint32_t read32(volatile uint32_t* ptr)
{
   return *ptr;
}