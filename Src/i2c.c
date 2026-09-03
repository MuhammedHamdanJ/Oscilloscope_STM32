#include "i2c.h"
// TODO: Make ts use dma
I2C_HandleTypeDef i2c_handle = {
  .Instance = I2C1, // B8,B9 = SCLK, SDA respectfully
  .Init = {
    .ClockSpeed = 400000, //400khz
    .DutyCycle = I2C_DUTYCYCLE_2, //low:high::2:1 timing ratio 
    .NoStretchMode = I2C_NOSTRETCH_DISABLE, //incase slave too slow, good to have
    .DualAddressMode = I2C_DUALADDRESS_DISABLE, // dual address also ownaddr1,2 and general call all do not matter in usecase of 1 slave and 1 master
    .GeneralCallMode = I2C_GENERALCALL_DISABLE 
  }
};

void init_i2c() {
  __HAL_RCC_I2C1_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef gpio = {
    .Pin = GPIO_PIN_8 | GPIO_PIN_9,
    .Mode = GPIO_MODE_AF_OD,
    .Pull = GPIO_PULLUP,
    .Alternate = GPIO_AF4_I2C1,
    .Speed = GPIO_SPEED_FREQ_HIGH
  };
  HAL_GPIO_Init(GPIOB, &gpio);
  HAL_I2C_Init(&i2c_handle);

  if (HAL_I2C_IsDeviceReady(&i2c_handle, 0x3c, 3, 300)){
    printf("slave ready");
  }
}

