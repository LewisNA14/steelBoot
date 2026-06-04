# steelBoot — Baremetal STM32 Nucleo-F334R8 Project

## Overview

This project implements a baremetal firmware stack for the STM32 Nucleo-F334R8 development board without using STM32CubeIDE or any Hardware Abstraction Layer (HAL). Every peripheral is configured by writing directly to hardware registers, with all supporting infrastructure: linker script, startup file, and Makefile — written from scratch.

The goal is to develop a genuine understanding of how a microcontroller works at the lowest level, rather than relying on generated or abstracted code. AI-generated code has been kept to a minimum for the same reason.

---

## Hardware

- **Board:** STM32 Nucleo-F334R8
- **Core:** ARM Cortex-M4 (32-bit)
- **Flash:** 64KB @ `0x08000000`
- **SRAM:** 12KB @ `0x20000000`
- **Default Clock:** HSI 8MHz

---

## Software Architecture

```
steelBoot/
├── STM32F334R8TX_FLASH.ld   # Linker script
├── src/
│   ├── startup.c            # Vector table and reset handler
│   └── main.c               # Main application logic
├── include/
│   └── stm32f334x8.h        # STM32 vendor CMSIS headers
└── Makefile
```

---

## 1. Linker Script — `STM32F334R8TX_FLASH.ld`

The linker script tells the linker where to place code and data in the device's memory. Without it the linker has no knowledge of the memory map and cannot produce a valid binary.

### Memory Layout

Embedded systems are typically made up of three core memory areas:

| Area | Purpose |
|------|---------|
| Flash (ROM) | Stores code, constants, and the initial values of initialised variables. Non-volatile. |
| SRAM (RAM) | Contains variables, stack, and heap at runtime. Volatile. |
| Peripheral Registers | Memory-mapped hardware control registers (GPIO, UART, TIM, etc.) |

### Sections

The linker script defines sections that control how the linker allocates memory:

- `.isr_vector` — The vector table. Must sit at the very start of Flash (`0x08000000`) so the CPU can find it on reset.
- `.text` — Executable machine code. All compiled C functions including `main()` live here.
- `.rodata` — Read-only constants. Stored in Flash and never modified at runtime.
- `.data` — Initialised global and static variables. Stored in Flash at build time and copied to SRAM by the startup code on reset.
- `.bss` — Uninitialised global and static variables. Zeroed in SRAM by the startup code on reset. Nothing is copied from Flash.

### Key Design Decisions

- All data is aligned to 4-byte boundaries to match the 32-bit ARM architecture.
- `_DATA_LOAD`, `_DATA_START`, and `_DATA_END` symbols are exported so the startup code knows where to copy initialised data from Flash into SRAM.
- `_BSS_START` and `_BSS_END` symbols are exported for the startup zeroing loop.
- `_stack_ptr` is placed at the top of SRAM (`ORIGIN(SRAM) + LENGTH(SRAM)`).
- A heap/stack guard section ensures the linker errors at build time if SRAM is exhausted, rather than silently overflowing at runtime.

---

## 2. Startup File — `startup.c`

The startup file is the first code executed after a reset. It runs before `main()` and is responsible for putting the system into a known state.

### Responsibilities

1. Providing the vector table in the `.isr_vector` section
2. Copying initialised `.data` values from Flash to SRAM
3. Zeroing the `.bss` section in SRAM
4. Calling `main()`

### Vector Table

The vector table is an array of function pointers placed at the start of Flash. On reset, the CPU hardware reads the first entry as the initial stack pointer and the second as the address of the reset handler. Every subsequent entry corresponds to an exception or interrupt handler.

The table follows the exception layout defined in the PM0214 Cortex-M4 Programming Manual, with 255 entries covering both the 16 core Cortex-M4 exceptions and the STM32F334-specific interrupt requests (IRQs).

Unused handlers are aliased to `Default_Handler` using GCC's `__attribute__((weak, alias(...)))`. This means:
- Any handler not explicitly defined will safely fall through to `Default_Handler` (an infinite loop)
- A real handler defined elsewhere in the project will automatically override the weak alias at link time

### Reset Handler

The reset handler performs the memory initialisation before jumping to `main()`:

1. Copies the `.data` section from its load address in Flash to its runtime address in SRAM
2. Zeroes the entire `.bss` section in SRAM
3. Calls `main()`

---

## 3. CMSIS Vendor Headers

The STM32 vendor CMSIS package is included for register mapping and naming standardisation. No HAL functions are used, the headers are used solely for their struct definitions and bitmask macros.

### Files Used

- `stm32f334x8.h` — The primary device header. Contains `typedef struct` definitions for every peripheral (e.g. `TIM_TypeDef`, `GPIO_TypeDef`), which are mapped to their base addresses as pointers (e.g. `TIM2`, `GPIOA`). Also contains the `IRQn_Type` enum mapping interrupt names to their vector table positions, and bitmask macros for every register field.
- `core_cm4.h` and supporting CMSIS files provide the underlying Cortex-M4 core peripheral definitions (NVIC, SysTick) that `stm32f334x8.h` builds on.

### Rationale

Using the vendor CMSIS headers is standard industry practice in baremetal development. They provide a well-tested, chip-specific register map and eliminate the risk of subtle addressing errors from manually typing base addresses. The decision to use them does not compromise the baremetal nature of the project every register write is still explicit and deliberate. It also means if supported is needed from fellow developers it's easy to pick up on the peripherals used.

---

## 4. Main Application — `main.c`

### GPIO — LED2 (PA5)

LED2 on the Nucleo-F334R8 is connected to PA5 (Port A, Pin 5).

**Relevant registers:**

| Register | Address | Purpose |
|----------|---------|---------|
| `GPIOA_MODER` | `0x40020000` | Pin mode configuration |
| `GPIOA_ODR` | `0x40020014` | Output data register |
| `GPIOA_BSRR` | `0x40020018` | Bit set/reset register |

**Initialisation sequence:**
1. Enable the GPIOA clock via `RCC->AHBENR` (bit `IOPAEN`). GPIO sits on the AHB bus on STM32F3. Without the clock enabled, register writes have no effect, the peripheral is frozen.
2. Clear the MODER bits for pin 5 (`MODER5[1:0] = 00`) to ensure a clean state.
3. Set `MODER5[1:0] = 01` for general purpose output mode.

**BSRR vs ODR:**

`BSRR` is used instead of `ODR` for toggling the LED. `ODR` requires a read-modify-write cycle, which is non-atomic - an interrupt firing between the read and write could corrupt the register state. `BSRR` is a write-only register where writing a `1` to the lower 16 bits sets the corresponding pin and writing a `1` to the upper 16 bits resets it. Writing `0` to any bit has no effect, making every write inherently atomic and safe.

**LED state machine:**

The LED state is managed using an enum:

```c
typedef enum led_status_e {
    ON,
    OFF,
    LED_ENUM_END
} led_status_t;
```

`LED_ENUM_END` acts as a bounds marker, enabling automatic state rollover via modulo arithmetic:

```c
led_status = (led_status + 1) % LED_ENUM_END;
```

The BSRR bit position is calculated directly from the state value, eliminating explicit if/else branching:

```c
uint8_t bsrr_pos = 5 + (16 * led_status);
GPIOA->BSRR = (1U << bsrr_pos);
```

When `led_status` is `ON` (0), bit 5 is set (pin high). When `led_status` is `OFF` (1), bit 21 (5+16) is set (pin low).

---

## 5. Timer — TIM2

### Overview

Rather than using a software delay loop for LED timing, TIM2 is used to generate a periodic interrupt. This is more accurate, CPU-efficient, and representative of real embedded practice.

### Configuration

TIM2 is a general-purpose timer on the APB1 bus. Configuration steps:

1. Enable the TIM2 clock via `RCC->APB1ENR`
2. Set the prescaler (`TIM2->PSC = 7999`) — divides the 8MHz clock by 8000, giving a 1kHz tick (1ms per tick)
3. Set the auto-reload value (`TIM2->ARR = 999`) — the counter resets every 1000 ticks, giving a 1 second period
4. Enable the update interrupt (`TIM2->DIER |= TIM_DIER_UIE`)
5. Enable the TIM2 IRQ in the NVIC (`NVIC_EnableIRQ(TIM2_IRQn)`)
6. Start the counter (`TIM2->CR1 |= TIM_CR1_CEN`)

### Interrupt Handler

`TIM2_IRQHandler` is defined in `main.c` and overrides the weak alias in `startup.c` at link time.

The handler checks the Update Interrupt Flag (`UIF`) in `TIM2->SR`, calls `LED_update()`, then clears the flag by writing 0 to it. The flag must be cleared before exiting the handler, if left set, the CPU would immediately re-enter the handler on return.

The `UIF` flag is `rc_w0` (read, clear by writing 0), which is why `&= ~(TIM_SR_UIF)` is used rather than a set operation.

---

## Makefile

| Variable | Purpose |
|----------|---------|
| `CC` | ARM GCC cross-compiler toolchain |
| `OBJCOPY` | Converts `.elf` to `.hex` |
| `CFLAGS` | Compiler flags including target CPU and FPU |
| `OBJECTS` | `main.o`, `startup.o` |
| `TARGET` | Output firmware filename |
| `LDFLAGS` | Linker script path, removes unused sections, excludes `.init`/`.fini` |

**Build pipeline:**
1. Compile `.c` files to `.o` object files
2. Link object files into a `.elf` file using the linker script
3. Convert `.elf` to `.hex` firmware file

**To flash:**
```bash
st-flash --format ihex write firmware.hex
```

---

## References

1. [RM0364 — STM32F334xx Reference Manual](https://www.st.com/resource/en/reference_manual/rm0364-stm32f334xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
2. [PM0214 — STM32 Cortex-M4 Programming Manual](https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)
3. [Git Merge Documentation](https://git-scm.com/docs/git-merge)
4. [Introduction to Linker Scripts — mcyoung.xyz](https://mcyoung.xyz/2021/06/01/linker-script/)