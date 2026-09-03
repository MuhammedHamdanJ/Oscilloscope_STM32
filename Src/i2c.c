#include "i2c.h"

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

/* 
  Procedure to interface with SSD1306:-
    Start:
      pull SDA to low while SCL stays high
*/
/*
1) The master device initiates the data communication by a start condition. The definition of the start
condition is shown in Figure 8-8. The start condition is established by pulling the SDA from HIGH to
LOW while the SCL stays HIGH.
2) The slave address is following the start condition for recognition use. For the SSD1306, the slave
address is either “b0111100” or “b0111101” by changing the SA0 to LOW or HIGH (D/C pin acts as
SA0).
3) The write mode is established by setting the R/W# bit to logic “0”.
4) An acknowledgement signal will be generated after receiving one byte of data, including the slave
address and the R/W# bit. Please refer to the Figure 8-9 for the graphical representation of the
acknowledge signal. The acknowledge bit is defined as the SDA line is pulled down during the HIGH
period of the acknowledgement related clock pulse.
5) After the transmission of the slave address, either the control byte or the data byte may be sent across
the SDA. A control byte mainly consists of Co and D/C# bits following by six “0” ‘s.
a. If the Co bit is set as logic “0”, the transmission of the following information will contain
data bytes only.
b. The D/C# bit determines the next data byte is acted as a command or a data. If the D/C# bit is
set to logic “0”, it defines the following data byte as a command. If the D/C# bit is set to
logic “1”, it defines the following data byte as a data which will be stored at the GDDRAM.
The GDDRAM column address pointer will be increased by one automatically after each
data write.
6) Acknowledge bit will be generated after receiving each control byte or data byte.
7) The write mode will be finished when a stop condition is applied. The stop condition is also defined
in Figure 8-8. The stop condition is established by pulling the “SDA in” from LOW to HIGH while
the “SCL” stays HIGH.
*/
