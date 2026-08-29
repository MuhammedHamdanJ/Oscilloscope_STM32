#include <stdio.h>
#include "main.h"
#include "sys_clk.h"
#include "stm32f4xx_hal.h"

/* Oscilloscope:
* get adc + dma with debug message
* interface spi monitor
* later:
* voltage regulation (hardware)
* trigger
* measuring function
*/



int main(void) {
  HAL_Init();
  SystemClock_Config();
  init_uart();
  while (1) {
    printf("hello world\r\n");
    HAL_Delay(1000);
  }
}
