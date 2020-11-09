#include "cube_main.h"
#include "i2s_app.h"
#include "stm32f4xx_hal.h"

void LED_Init();

I2sApp mic;

uint16_t data_tx[10];
uint16_t data_rx[10];

void setup(void) {

  LED_Init();

  mic.init();

  for(int i=0;i<10;i++){
    data_tx[i] = i;
  }
  data_tx[0] = 0xEE55;
  data_tx[1] = 0x1025;
  data_tx[8] = 0x1025;
  data_tx[9] = 0x55EE;
}

void loop(){
    mic.receive(data_rx,10,100);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	  HAL_Delay(1);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	  HAL_Delay(1999);
}


void LED_Init() {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();


  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}
