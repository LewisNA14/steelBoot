# Includes all the linkers and files required to build the object
# As well as the Toolchains required for compilation

# Variables
CC 		= arm-none-eabi-gcc		# ARM Toolchain Compiler
CCOPY   = arm-none-eabi-objcopy	# Toolchain for copying / converting
CFLAGS 	= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 	# Hardware peripheral / Compiler flags
OBJ 	= startup.o led2.o main.o ringbuff.o tim2.o usart2.o
TARGET 	= firmware

# Include Libraries
CMSIS_DEVICE_INC = /home/lewisnicholson/STM32_base_CMSIS_package/CMSIS/STM32F3xx/inc
CMSIS_DEVICE_SRC = /home/lewisnicholson/STM32_base_CMSIS_package/CMSIS/STM32F3xx/src
CMSIS_CORE_INC   = /home/lewisnicholson/STM32_base_CMSIS_package/CMSIS/ARM/inc

INCLUDE_DIRS = -I./inc -I$(CMSIS_DEVICE_INC) -I$(CMSIS_DEVICE_SRC) -I$(CMSIS_CORE_INC)

# Linker Script Flags
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
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

check-sections:
	arm-none-eabi-readelf -S $(TARGET).elf

check-program:
	arm-none-eabi-readelf -l $(TARGET).elf

clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).hex

