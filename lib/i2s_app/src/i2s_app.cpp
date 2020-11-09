#include "i2s_app.h"
#include "stm32f4xx_hal.h"

void Error_Handler(void);

I2S_HandleTypeDef hi2s2;

void SystemClock_Config_I2S(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 164;
  PeriphClkInitStruct.PLLI2S.PLLI2SM = 25;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

I2sApp::I2sApp(){
  
}

bool I2sApp::init(void)
{

  SystemClock_Config_I2S();

  __HAL_RCC_SPI2_CLK_ENABLE();

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_RX;
  hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_32K;
  hi2s2.Init.CPOL = I2S_CPOL_LOW;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }
  return true;
}

bool I2sApp::receive(uint16_t *pData, uint16_t size, uint32_t Timeout){
  if (HAL_I2S_Receive(&hi2s2,pData,size,Timeout) != HAL_OK)
  {
    Error_Handler();
  }
  return true;
}

void Error_Handler(){
  while(1){

  }
}
