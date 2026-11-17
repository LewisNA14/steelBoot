CC          = gcc                       		 # Compiler
CFLAGS      = -Wall -Wextra -g -O0 -MMD -MP      # Compiler Flags
TARGET      = Testing
BUILD_DIR   = build

# CMock and Unity - Unit Testing Tools / Frameworks
UNITY_DIR   := $(HOME)/testing_tools/Unity
CMOCK_DIR   := $(HOME)/testing_tools/cmock

TEST_SRCS   = test_ringbuff.c \
              ../src/ringbuff.c \
              $(UNITY_DIR)/unity.c

# Flatten paths so objects all land in build/
TEST_OBJS   = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRCS:.c=.o)))

VPATH       = . ../src $(UNITY_DIR)

# Include Directories
INCLUDE_DIRS = -I../inc \
               -I$(UNITY_DIR) \
               -Imocks \
               -I/home/lewisnicholson/STM32_base_CMSIS_package/CMSIS/ARM/inc

# Default Rule
all: $(BUILD_DIR)/$(TARGET)
	@echo "--------------------------====="
	@echo " RUNNING UNIT TESTS"
	@echo "--------------------------====="
	@./$(BUILD_DIR)/$(TARGET)

# Link the test runner executable
$(BUILD_DIR)/$(TARGET): $(TEST_OBJS)
	@echo " LINKING TEST RUNNER"
	@$(CC) $(CFLAGS) $(TEST_OBJS) -o $@

# Compile rule for PC object files
# Pattern rule
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo " CC (HOST) $<"
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

-include $(TEST_OBJS:.o=.d)