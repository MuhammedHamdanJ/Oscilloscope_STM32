#include "tim2.h"

TIM_HandleTypeDef tim2_handle = {
  .Instance = TIM2,
  .Init = {
      .Prescaler = 83,                     // 84MHz / (Prescaler+1) = 1MHz timer clock (base clk is 84Mhz)
      .CounterMode = TIM_COUNTERMODE_UP,   // counts from 0 to period (100)
      .Period = 99,                        // 1MHz / (99+1)Khz = 10kHz trigger rate
      .ClockDivision = TIM_CLOCKDIVISION_DIV1, // Irrelevant here, DIV1 for no division
      .AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,
  }
};

void init_tim(void) {
  __HAL_RCC_TIM2_CLK_ENABLE();
  HAL_TIM_Base_Init(&tim2_handle);
  TIM_MasterConfigTypeDef master_conf= {
    .MasterOutputTrigger = TIM_TRGO_UPDATE,
    .MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE // only one tim; not needed
  };
  HAL_TIMEx_MasterConfigSynchronization(&tim2_handle, &master_conf);
  HAL_TIM_Base_Start(&tim2_handle);
}
