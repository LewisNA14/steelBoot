# Includes all the linkers and files required to build the object
# As well as the Toolchains required for compilation

# Assigning Aliases
CC 		= arm-none-eabi-gcc		# ARM Toolchain Compiler
CFLAGS 	= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
OBJ 	= main.o startup.o
TARGET 	= firmware.hex
SRC 	= src/


# Default Rule:
all : $(TARGET)

# Linker Script Rule
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -T STM32F334R8TX_FLASH.ld -o $@

# Compile rule (using pattern rule)
%.o: %.c 
	$(CC) -c $< -o $@ (CFLAGS)

clean:
	rm - main

