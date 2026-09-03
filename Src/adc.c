#include "adc.h"

volatile uint16_t adc_buf[256] = {0};
volatile uint8_t buf_state = 0;

ADC_HandleTypeDef adc_handle = {
    .Instance = ADC1,
    .Init = {
        .ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4,
        .Resolution = ADC_RESOLUTION_12B,
        .ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING,
        .ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_TRGO,
        .DataAlign = ADC_DATAALIGN_RIGHT,
        .NbrOfConversion = 1,
        .DMAContinuousRequests = ENABLE,
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
  HAL_ADC_Start_DMA(&adc_handle, (uint32_t *)adc_buf, 256); //weird typecast cuz api only accepts full word but i use half word
}

// buf_state: 0 = empty, 1 = half, 2 = full
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* adc_handle) {
  buf_state = 1;
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* adc_handle) {
  buf_state = 2; // rtos wud be nice here but :(
}
