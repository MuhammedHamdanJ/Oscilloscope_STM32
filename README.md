# STM32 Oscilloscope

## Introduction
This is a basic oscilloscope I built to learn to program the STM32 without using an abstracted GUI like, It is derived from my basic STM32 project structure repo which in turn uses code generated from ST's CUBEMX along with some of my opinionated additions

## Stuff I used from other people
- All the HAL/LL drivers, Linker Script and Startup Assembly Code from ST
- The SSD1306 drivers from this [cool github repo](https://github.com/afiskon/stm32-ssd1306/tree/master). (I modified the offset to make it work on my SH1106)

## Architecture
 
```
              input signal to display, using TIM3 PWM for demo
                                    ↓
              TIM2 (10kHz TRGO) →  ADC1 
                                    ↓
                    DMA2 (circular, 256-sample buffer)
                                    ↓
                    half/full-complete callback flags
                                    ↓
                    render_waveform() on SH1106 over IIC

```
 
## Hardware Used
- STM32F446RE Nucleo-64
- SH1106 128x64 I2C OLED display

## Build,Flash and monitor
 
Requires the `arm-none-eabi-gcc` toolchain. Flash via STM32CubeProgrammerCLI:
```bash
$ make
$ STM32_Programmer_CLI -c port=SWD -w build/oscilloscope.elf -v -rst
$ picocom -b 115200 /dev/ttyACM0 #or whichever port you're using
```
## Debugging

Change port or path as needed.
```bash
ST-LINK_gdbserver -d -p 3333 -cp /opt/stm32cubeclt/STM32CubeProgrammer/bin
#On a different terminal
arm-none-eabi-gdb build/oscilloscope.elf
(gdb) target remote localhost:3333
#debug as needed
```

## What I learned
 
This project was built to learn STM32 peripheral programming from the ground up. Stuff like ADC configuration and sampling theory, DMA circular/double-buffering patterns, timer trigger outputs (TRGO) and interrupt-driven timing, the IIC protocol , and ST's HAL's weak-callback conventions. Coming from ESP-IDF (FreeRTOS-based), this was also a deliberate exercise in bare metal-ish development (`volatile` flags instead of semaphores, manual Makefile/linker management instead of a GUI-driven toolchain).
