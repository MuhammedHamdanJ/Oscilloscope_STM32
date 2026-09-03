#include "main.h"

/* Oscilloscope:
* get adc + dma with debug message
* interface spi monitor
* later:
* voltage regulation (hardware)
* trigger
* measuring function
*/
void display_logic(void);


int main(void) {
  HAL_Init();
  SystemClock_Config();
  init_tim();
  init_uart();
  init_dma();
  init_adc();
  init_i2c();
  printf("hello world\r\n");
  display_logic();
  while (1) {
    ;;
  }
}

void display_logic() {
  ssd1306_Init();
  ssd1306_Fill(Black);
  ssd1306_SetCursor(0, 0);
  ssd1306_WriteString("Hello", Font_7x10, White);
  ssd1306_UpdateScreen();
}
