CC 			= gcc						# Compiler
CFLAGS 		= -Wall	-Wextra -g -O0		# Compiler Flags
TARGET = Testing

# CMock and Unity - Unit Testing Tools / Frameworks
UNITY_DIR := $(HOME)/testing_tools/unity
CMOCK_DIR := $(HOME)/testing_tools/cmock

TEST_SRCS
TEST_OBJS

# Include Directories
INCLUDE_DIRS = 	-I./inc \
				-I$(UNITY_DIR)/src \
				-I./test/mocks \
				-I/home/lewisnicholson/STM32_base_CMSIS_package/CMSIS/ARM/inc

# Default Rule
all: $(TARGET)
		@echo "--------------------------====="
		@echo " RUNNING UNIT TESTS"
		@echo "--------------------------====="
		@./$(TARGET)

# Link the test runner executable
$(TARGET): $(TEST_OBJS)
		@echo " LINKING TEST RUNNER"
		@$(CC)	$(CFLAGS) $(TEST_OBJS) -o $@

# Compile rule for PC object files
# Pattern rule
%.o: %.c
	@echo " CC (HOST) $<"
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@ 

clean:
		rm -f $(TARGET) src/*.o $(UNITY_DIR)/src/*.o test/*.o	