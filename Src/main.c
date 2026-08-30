#include "main.h"

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
  init_tim();
  init_uart();
  init_dma();
  init_adc();
  printf("hello world\r\n");
  while (1) {
    ;;
  }
}
