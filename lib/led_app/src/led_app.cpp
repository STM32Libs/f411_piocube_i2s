#include "led_app.h"
#include "stm32f4xx_hal.h"

bool LedApp::init(GPIO_TypeDef  *port_v, uint16_t pin_v)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();

  port = port_v;
  pin = pin_v;

  GPIO_InitStruct.Pin = pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(port, &GPIO_InitStruct);

  return true;
}

void LedApp::on(){
  HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

void LedApp::off(){
  HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}

void LedApp::toggle(){
  HAL_GPIO_TogglePin(port, pin);
}
