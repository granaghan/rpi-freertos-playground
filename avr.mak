TOOLCHAINPATH := C:\build\avr\WinAVR-20100110\bin
DEVICE:=atmega168
default:
	$(TOOLCHAINPATH)\avr-gcc -mmcu=$(DEVICE) -Wall -Isource -Os -o blink.elf source\avr\avrmain.c
	$(TOOLCHAINPATH)\avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex

flash: default
	avrdude -p $(DEVICE) -c avrispmkii -P usb -U lfuse:w:0xe2:m -U hfuse:w:0xda:m -U efuse:w:0x05:m
	avrdude -p $(DEVICE) -c avrispmkii -P usb -U flash:w:blink.hex

#	avrdude -p atmega168 -c avrispmkii -P usb -U lfuse:w:0xff:m -U hfuse:w:0xda:m -U efuse:w:0x05:m