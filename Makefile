# Includes all the linkers and files required to build the object
# As well as the Toolchains required for compilation

# Variables
CC 		= arm-none-eabi-gcc												# ARM Toolchain Compiler
CCOPY   = arm-none-eabi-objcopy											# Toolchain for copying / converting
CFLAGS 	= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 	# Hardware peripheral / Compiler flags
OUT_DIR = output
OBJ_NAMES = startup.o led2.o main.o ringbuff.o tim2.o usart2.o
OBJ 	= $(addprefix $(OUT_DIR)/, $(OBJ_NAMES))
TARGET 	= $(OUT_DIR)/firmware

# Include Libraries
CMSIS_DEVICE_INC = /home/lewisnicholson/STM32_base_CMSIS_package/CMSIS/STM32F3xx/inc
CMSIS_DEVICE_SRC = /home/lewisnicholson/STM32_base_CMSIS_package/CMSIS/STM32F3xx/src
CMSIS_CORE_INC   = /home/lewisnicholson/STM32_base_CMSIS_package/CMSIS/ARM/inc

INCLUDE_DIRS = -I./inc -I$(CMSIS_DEVICE_INC) -I$(CMSIS_DEVICE_SRC) -I$(CMSIS_CORE_INC)


# Linker Script Flags
LDFLAGS = -T STM32F334R8TX_FLASH.ld -Wl,--gc-sections -nostartfiles

# Default Rule:
all : $(TARGET).hex

# Create the output directory
$(OUT_DIR):
	@mkdir -p $@

# Linker Script Rule for creating ELF
$(TARGET).elf: $(OBJ)
	@echo "  LINK    $@"
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

# Convert ELF to HEX
$(TARGET).hex: $(TARGET).elf
	@echo "  OBJCOPY $@"
	@$(CCOPY) -O ihex $< $@


vpath %.c src .

# Compiler rule (using pattern rule)
$(OUT_DIR)/%.o: %.c | $(OUT_DIR)
	@echo "  CC      $<"
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

check-sections:
	arm-none-eabi-readelf -S $(TARGET).elf

check-program:
	arm-none-eabi-readelf -l $(TARGET).elf

clean:
	rm -rf $(OUT_DIR)

flash: $(TARGET).hex
	st-flash --connect-under-reset --format ihex write $<
