#include "pwm.h"

TIM_HandleTypeDef tim3_handle = {
  .Instance = TIM3,
  .Init = {
      .Prescaler = 830,                     // 84MHz / (Prescaler+1) = 0.1MHz timer clock (base clk is 84Mhz)
      .CounterMode = TIM_COUNTERMODE_UP,   // counts from 0 to period (100)
      .Period = 999,                        // 0.1MHz / 1000Khz = 100Hz trigger rate
      .ClockDivision = TIM_CLOCKDIVISION_DIV1, // Irrelevant here, DIV1 for no division
      .AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,
  }
};

void init_test_signal(void) {
  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  GPIO_InitTypeDef gpio = {
  .Pin = GPIO_PIN_4,
  .Mode = GPIO_MODE_AF_PP,
  .Pull = GPIO_NOPULL,
  .Speed = GPIO_SPEED_FREQ_HIGH,
  .Alternate = GPIO_AF2_TIM3
  };
  HAL_GPIO_Init(GPIOB, &gpio);
  HAL_TIM_Base_Init(&tim3_handle);
  TIM_OC_InitTypeDef sConf = {
    .OCMode = TIM_OCMODE_PWM1,
    .Pulse = 200,
    .OCPolarity = TIM_OCPOLARITY_HIGH
  };
  HAL_TIM_PWM_Init(&tim3_handle);
  HAL_TIM_PWM_ConfigChannel(&tim3_handle, &sConf, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&tim3_handle, TIM_CHANNEL_1);
}
