#include "adc.h"

ADC_HandleTypeDef adc_handle = {
    .Instance = ADC1,
    .Init = {
        .ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4,
        .Resolution = ADC_RESOLUTION_12B,
        .ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE,
        .DataAlign = ADC_DATAALIGN_RIGHT,
        .NbrOfConversion = 1,
        .DMAContinuousRequests = DISABLE,
        .EOCSelection = ADC_EOC_SINGLE_CONV,
    },
};

void init_adc(void) {
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_ADC1_CLK_ENABLE();

  GPIO_InitTypeDef gpio = {
    .Pin = GPIO_PIN_0,
    .Mode = GPIO_MODE_ANALOG,
    .Pull = GPIO_NOPULL
  };
  HAL_GPIO_Init(GPIOA, &gpio);
  HAL_ADC_Init(&adc_handle);
  ADC_ChannelConfTypeDef adc_channel = {
    .Channel = ADC_CHANNEL_0,
    .SamplingTime = ADC_SAMPLETIME_144CYCLES,
    .Rank = 1
  };
  HAL_ADC_ConfigChannel(&adc_handle, &adc_channel);
}

uint16_t read_adc(void) {
  HAL_ADC_Start(&adc_handle);
  HAL_ADC_PollForConversion(&adc_handle, 10000);
  uint16_t value = HAL_ADC_GetValue(&adc_handle);
  return value;
}
