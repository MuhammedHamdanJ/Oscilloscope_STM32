#include "uart.h"

UART_HandleTypeDef huart2 = {
    .Instance = USART2,
    .Init = {
        .BaudRate = 115200,
        .WordLength = UART_WORDLENGTH_8B,
        .StopBits = UART_STOPBITS_1,
        .Parity = UART_PARITY_NONE,
        .Mode = UART_MODE_TX_RX,
        .HwFlowCtl = UART_HWCONTROL_NONE,
        .OverSampling = UART_OVERSAMPLING_16,
    },
};

void init_uart(void) {
  setvbuf(stdout, NULL, _IONBF, 0);
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_USART2_CLK_ENABLE();

  GPIO_InitTypeDef gpio = {
      .Pin = GPIO_PIN_2 | GPIO_PIN_3,
      .Mode = GPIO_MODE_AF_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
      .Alternate = GPIO_AF7_USART2,
  };
  HAL_GPIO_Init(GPIOA, &gpio);

  HAL_UART_Init(&huart2);
}

int _write(int file, char *ptr, int len) {
  HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
  return len;
}
