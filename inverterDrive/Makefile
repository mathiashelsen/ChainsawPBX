# Makefile, for AVR Programming
 
 
# Target name:
TARGET = output
 
# Target type
MCU=attiny85
PROGRAMMER=stk500
F_CPU=8000000UL
 
 
SRC = main.c
OBJ = $(SRC:.c=.o)
 
 
# Compiler / Linker flags:
CFLAGS = -mmcu=$(MCU) -Wall -Os -std=gnu99 -D F_CPU=$(F_CPU) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
LDFLAGS = -mmcu=$(MCU) -Wl,-Map=$(TARGET).map
 
 
 
###################################
# Makerules:
 
 
.PHONY: compile flash clean
 
compile: $(TARGET).hex $(TARGET).eep $(TARGET).lss
 
flash: compile
	avrdude -c $(PROGRAMMER) -P /dev/ttyACM0 -p $(MCU) -U flash:w:$(TARGET).hex
	# sleep 2
	# avrdude -c $(PROGRAMMER) -P usb -p $(MCU) -U eeprom:w:$(TARGET).eep
 
clean:
	rm -f $(OBJ) $(TARGET).{elf,hex,lss,map,eep}
 
 
 
###################################
# Psudorules:
 
%.eep: %.hex
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex $< $@
 
%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@
 
%.lss: %.elf
	avr-objdump -h -S $< > $@
 
%.elf: $(OBJ)
	avr-gcc $^ $(LDFLAGS) -o $@
 
%.o : %.c
	avr-gcc $(CFLAGS) -c $< -o $@
