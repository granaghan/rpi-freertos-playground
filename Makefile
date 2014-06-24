# Force deault target
default: kernel.img

# Define toolchain variables
TOOLCHAIN=C:\\yagarto-20121222\\bin\\arm-none-eabi-
CC=$(TOOLCHAIN)gcc
CXX=$(TOOLCHAIN)g++
AS=$(TOOLCHAIN)as
LD=$(TOOLCHAIN)ld
OBJCOPY=$(TOOLCHAIN)objcopy
ARCH=$(TOOLCHAIN)
PYTHON=python

CODEGEN_DIR:=$(CURDIR)/codegen
MK_DIRS:= $(CODEGEN_DIR)

define addRegmap
ARM_SRC+=$(CODEGEN_DIR)/$(basename $(notdir $1)).c
codegen:$(CODEGEN_DIR)/$(basename $(notdir $1)).c $(CODEGEN_DIR)/$(basename $(notdir $1)).h
$(CODEGEN_DIR)/$(basename $(notdir $1)).c:$1
	@echo $(notdir $$@) \<-- $(notdir $$<)
	@$(PYTHON) source/regmaps/RegMapParse.py $$< | python source/regmaps/GenerateRegisterMap.py --include "io.h" --read_func "read32" --write_func "write32"> $$@
$(CODEGEN_DIR)/$(basename $(notdir $1)).h:$1
	@echo $(notdir $$@) \<-- $(notdir $$<)
	@$(PYTHON) source/regmaps/RegMapParse.py $$< | python source/regmaps/GenerateRegisterMap.py --header > $$@
endef

#
# CFLAGS common to both the THUMB and ARM mode builds
#
CFLAGS=-Wall -Wextra -Isource/FreeRTOS/Source/include -Isource/FreeRTOS/Source/portable/GCC/RaspberryPi \
		-Isource -I. $(DEBUG) -march=armv6z -T$(LDSCRIPT) \
		-fomit-frame-pointer -fno-strict-aliasing \
		-fno-dwarf2-cfi-asm -O0

      #-Wcast-align $(OPTIM)

ifeq ($(USE_THUMB_MODE),YES)
	CFLAGS += -mthumb-interwork -D THUMB_INTERWORK
	THUMB_FLAGS=-mthumb
endif

LDSCRIPT=raspberrypi.ld
LINKER_FLAGS=-Xlinker -ortosdemo.elf -Xlinker -M -Xlinker -Map=rtosdemo.map

#
# Source files that can be built to THUMB mode.
#
THUMB_SRC = \
   source/main.c \
   source/FreeRTOS/Source/tasks.c \
   source/FreeRTOS/Source/queue.c \
   source/FreeRTOS/Source/list.c \
   source/FreeRTOS/Source/croutine.c \
   source/FreeRTOS/Source/timers.c \
   source/FreeRTOS/Source/portable/MemMang/heap_2.c \
   source/FreeRTOS/Source/portable/GCC/RaspberryPi/port.c

#
# Source files that must be built to ARM mode.
#
ARM_CPP_SRC :=\
   source/Drivers/UART.cpp \
   source/Drivers/GPIO.cpp \
   source/Drivers/SPI.cpp \
   source/Peripherals/SparkfunLCD.cpp \
   source/tasks.cpp \
   source/cppSupport.cpp \

ARM_SRC := \
   source/Drivers/interrupts.c \
   source/FreeRTOS/Source/portable/GCC/RaspberryPi/portisr.c \
   source/io.c \
   source/syscalls.c \

#   source/syscalls.c \

STARTUP_SRC := \
   source/startup.s \

# Define regmap source and call generation rule
REGMAPS := \
   source/regmaps/SPI.rm \
   source/regmaps/UART.rm \
   source/regmaps/GPIO.rm \

$(foreach regmap,$(REGMAPS),$(eval $(call addRegmap,$(regmap))))

#
# Define all object files.
#
ARM_OBJ := $(ARM_SRC:.c=.o)
ARM_CPP_OBJ := $(ARM_CPP_SRC:.cpp=.o)
THUMB_OBJ := $(THUMB_SRC:.c=.o)
STARTUP_OBJ := $(STARTUP_SRC:.s=.o)

kernel.img: rtosdemo.elf
	@echo $(notdir $@)
	@$(OBJCOPY) rtosdemo.elf -O binary $@

rtosdemo.hex : rtosdemo.elf
	@echo $(notdir $@)
	@$(OBJCOPY) rtosdemo.elf -O ihex rtosdemo.hex

rtosdemo.elf : $(ARM_OBJ) $(ARM_CPP_OBJ) $(THUMB_OBJ) $(STARTUP_OBJ) $(CRT0) codegen dirs
	@echo $(notdir $@)
	@$(CC) $(CFLAGS) $(ARM_OBJ) $(ARM_CPP_OBJ) $(THUMB_OBJ) $(STARTUP_OBJ) -nostartfiles $(CRT0) $(LINKER_FLAGS)
	@echo

   #$(LD) $(ARM_OBJ) $(THUMB_OBJ) -nostartfiles $(CRT0) $(LINKER_FLAGS)  raspberrypi.ld

$(THUMB_OBJ) : %.o : %.c $(LDSCRIPT) codegen
	@echo $(notdir $@) \<-- $(notdir $<)
	@$(CC) -c $(THUMB_FLAGS) $(CFLAGS) $< -o $@
	@echo

$(ARM_OBJ) : %.o : %.c $(LDSCRIPT) codegen
	@echo $(notdir $@) \<-- $(notdir $<)
	$(CC) -c $(CFLAGS) $< -o $@
	@echo

$(ARM_CPP_OBJ) : %.o : %.cpp $(LDSCRIPT) codegen
	@echo $(notdir $@) \<-- $(notdir $<)
	@$(CXX) -c $(CFLAGS) -fno-rtti -fno-exceptions $< -o $@
	@echo

$(STARTUP_OBJ) : %.o : %.s $(LDSCRIPT) codegen
	@echo $(notdir $@) \<-- $(notdir $<)
	@$(CC) -c $(CFLAGS) $< -o $@
	@echo

codegen: dirs

dirs:
	@mkdir -p $(MK_DIRS)

clean :
	rm -f $(ARM_CPP_OBJ)
	rm -f $(ARM_OBJ)
	rm -f $(THUMB_OBJ)
	rm -f $(STARTUP_OBJ)
