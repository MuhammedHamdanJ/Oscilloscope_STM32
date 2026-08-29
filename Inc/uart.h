#pragma once
#include "main.h"

void init_uart(void);

int _write(int file, char *ptr, int len);
extern UART_HandleTypeDef huart2;
