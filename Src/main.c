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
  init_uart();
  init_adc();
  while (1) {
    printf("hello world\r\n");
    printf("%d", read_adc());
    HAL_Delay(1000);
  }
}
