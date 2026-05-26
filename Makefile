# Includes all the linkers and files required to build the object
# As well as the Toolchains required for compilation

# Variables
CC 		= arm-none-eabi-gcc		# ARM Toolchain Compiler
CCOPY   = arm-none-eabi-objcopy	# Toolchain for copying / converting
CFLAGS 	= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 	# Hardware peripheral / Compiler flags
OBJ 	= main.o startup.o
TARGET 	= firmware

LDFLAGS = -T STM32F334R8TX_FLASH.ld -Wl,--gc-sections -nostartfiles


# Default Rule:
all : $(TARGET).hex

# Linker Script Rule for creating ELF
$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

# Convert ELF to HEX
$(TARGET).hex: $(TARGET).elf
	$(CCOPY) -O ihex $< $@

# Compiler rule (using pattern rule)
%.o: src/%.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

check-sections:
	arm-none-eabi-readelf -S $(TARGET).elf

check-program:
	arm-none-eabi-readelf -l $(TARGET).elf

clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).hex

