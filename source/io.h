#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif

void write32(volatile uint32_t* ptr, uint32_t value);

uint32_t read32(volatile uint32_t* ptr);

#ifdef __cplusplus
}
#endif