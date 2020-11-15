#include "i2s_app.h"
#include "stm32f4xx_hal.h"
#include "i2s_it.h"

void Error_Handler(void);

I2S_HandleTypeDef hi2s2;
DMA_HandleTypeDef hdma_spi2_rx;
DMA_HandleTypeDef *hdmarx;      /*!< I2S Rx DMA handle parameters */
I2sApp::Mode_e mode = I2sApp::Blocking;
PacketCallback packet_callback = nullptr;

static void MX_I2S2_Init(void);
static void MX_DMA_Init(void);
void HAL_I2S_MspInit_no_cb(I2S_HandleTypeDef* hi2s);


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

bool I2sApp::init(Mode_e mode_v)
{
  mode = mode_v;

  SystemClock_Config_I2S();

  __HAL_RCC_SPI2_CLK_ENABLE();

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();


  if(mode == I2sApp::DMA){
      MX_DMA_Init();
  }
  MX_I2S2_Init();

  return true;
}

void I2sApp::onPacket(PacketCallback cb){
  packet_callback = cb;
}

bool I2sApp::receive(int32_t *pData, uint16_t size){
  uint16_t *pu16 = reinterpret_cast<uint16_t*>(pData);
  if (HAL_I2S_Receive_DMA(&hi2s2,pu16,size) != HAL_OK)
  {
    return false;
  }
  else{
    return true;
  }
}

bool I2sApp::pause(){
  if (HAL_I2S_DMAPause(&hi2s2) != HAL_OK)
  {
    return false;
  }
  else{
    return true;
  }
}

bool I2sApp::resume(){
  if (HAL_I2S_DMAResume(&hi2s2) != HAL_OK)
  {
    return false;
  }
  else{
    return true;
  }
}

bool I2sApp::stop(){
  if (HAL_I2S_DMAStop(&hi2s2) != HAL_OK)
  {
    return false;
  }
  else{
    return true;
  }
}

//defined in startup '.s' as EXPORT  DMA1_Stream3_IRQHandler           [WEAK]
//redirect needed, direct instantiation here of 'DMA1_Stream3_IRQHandler' does not trigger
void I2sApp_DMA1_Stream3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream3_IRQn 0 */

  /* USER CODE END DMA1_Stream3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi2_rx);
  /* USER CODE BEGIN DMA1_Stream3_IRQn 1 */

  /* USER CODE END DMA1_Stream3_IRQn 1 */
}

void Error_Handler(){
  while(1){

  }
}

static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

}

static void MX_I2S2_Init(void)
{
  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_RX;
  hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_32K;
  hi2s2.Init.CPOL = I2S_CPOL_LOW;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;

  //user direct call as the __weak override does not work from a '.a' library
  HAL_I2S_MspInit_no_cb(&hi2s2);

  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }
}

//packing HAL_I2S_MspInit in a lib does not override the __weak version
//so renamed to _no_cb to avoid ambiguities and using a direct call
void HAL_I2S_MspInit_no_cb(I2S_HandleTypeDef* hi2s)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hi2s->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2S2 GPIO Configuration
    PB10     ------> I2S2_CK
    PB12     ------> I2S2_WS
    PB15     ------> I2S2_SD
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
  }


  if(mode == I2sApp::DMA){
    /* I2S2 DMA Init */
    /* SPI2_RX Init */
    hdma_spi2_rx.Instance       = DMA1_Stream3;
    hdma_spi2_rx.Init.Channel   = DMA_CHANNEL_0;
    hdma_spi2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_rx.Init.MemInc    = DMA_MINC_ENABLE;
    hdma_spi2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_spi2_rx.Init.MemDataAlignment    = DMA_PDATAALIGN_HALFWORD;
    hdma_spi2_rx.Init.Mode                = DMA_CIRCULAR;
    hdma_spi2_rx.Init.Priority            = DMA_PRIORITY_HIGH;
    hdma_spi2_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    hdma_spi2_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    hdma_spi2_rx.Init.MemBurst            = DMA_MBURST_SINGLE;
    hdma_spi2_rx.Init.PeriphBurst         = DMA_PBURST_SINGLE;
    if (HAL_DMA_Init(&hdma_spi2_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hi2s,hdmarx,hdma_spi2_rx);
  }
}

void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s){
}
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s){
    packet_callback();
}

void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s){
}

