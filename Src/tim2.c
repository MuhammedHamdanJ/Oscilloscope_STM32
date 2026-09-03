#include "tim2.h"

/* i2c cant handle very high freq,
* to save cycles, set at lower freq
*/

TIM_HandleTypeDef tim2_handle = {
  .Instance = TIM2,
  .Init = {
      .Prescaler = 83,                     // 84MHz / (Prescaler+1) = 1MHz timer clock (base clk is 84Mhz)
      .CounterMode = TIM_COUNTERMODE_UP,   // counts from 0 to period (100)
      .Period = 199,                        // 1MHz / (199+1)Khz = 5kHz trigger rate
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
