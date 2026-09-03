#include "main.h"

/*
* TODO:
* measuring of -ve Vge using offset DC
* voltage regulation (hardware)
* trigger
* measuring function
*/
void test_display(void);
void render_waveform(uint8_t buf_state);

int main(void) {
  HAL_Init();
  SystemClock_Config();
  init_tim();
  init_uart();
  init_dma();
  init_adc();
  init_i2c();
  test_display();
  HAL_Delay(1000);
  while (1) {
    if (buf_state) {
      render_waveform(buf_state);
      buf_state = 0;
    }
  }
}
// adc_buffer[256]: state=1;0-127;;state=2;128-255
// map 4096v=>0y; 0v=>63y
void render_waveform(uint8_t buf_state) {
  ssd1306_Fill(Black);
  uint8_t start_idx = (buf_state-1)<<7; // 0 if 1, 128 if 2; No IF statement RAAAAAAAH
  // data to write: adc_buffer[start_idx - start_idx + 128];
  uint8_t y[128] =  {0};
  y[0] = 63 - adc_buf[start_idx] / 64;
  for (int  i = 1; i < 128; i++) {
    y[i] = 63 - adc_buf[start_idx + i] / 64;
    ssd1306_Line(i-1, y[i-1], i, y[i], White);
  }
  ssd1306_UpdateScreen();
}

void test_display() {
  ssd1306_Init();
  ssd1306_Fill(Black);
  ssd1306_SetCursor(0, 0);
  ssd1306_WriteString("Hello World", Font_7x10, White);
  ssd1306_UpdateScreen();
}
