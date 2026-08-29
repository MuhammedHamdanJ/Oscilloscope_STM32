/**
  ******************************************************************************
  * @file    sys_clk.h
  * @brief   Header file for system clock configuration and error handling.
  ******************************************************************************
  */

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "main.h"  /* Or your target MCU HAL header, e.g., "stm32f4xx_hal.h" */

/* Exported Functions Prototypes ---------------------------------------------*/

/**
  * @brief  Configures the system clock source, PLL, AHB, and APB bus dividers.
  * @retval None
  */
void SystemClock_Config(void);

/**
  * @brief  Handles system execution errors by disabling interrupts and looping infinitely.
  * @retval None
  */
void Error_Handler(void);


