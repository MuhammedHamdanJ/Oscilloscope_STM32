#include "dma.h"

DMA_HandleTypeDef dma_handle = {
  .Instance = DMA2_Stream0,
  .Init = {
    .Channel = DMA_CHANNEL_0,
    .Direction = DMA_PERIPH_TO_MEMORY,
    .PeriphInc = DMA_PINC_DISABLE, //read periph from same addr, write to mem in arr
    .MemInc = DMA_MINC_ENABLE,
    .PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD, //12-bit data in 16-bit reg. 16bit is halfword
    .MemDataAlignment = DMA_MDATAALIGN_HALFWORD,
    .Mode = DMA_CIRCULAR,
    .Priority = DMA_PRIORITY_HIGH
  }
};

void init_dma() {
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_LINKDMA(&adc_handle, DMA_Handle, dma_handle);
  HAL_DMA_Init(&dma_handle);
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

void DMA2_Stream0_IRQHandler(void) {
  HAL_DMA_IRQHandler(&dma_handle);
}
