#include "cube_main.h"
#include "i2s_app.h"
#include "led_app.h"
#include "stm32f4xx_hal.h"

I2sApp mic;
LedApp led;

uint16_t data_tx[10];
uint16_t data_rx[10];

void setup(void) {

  led.init(GPIOC,GPIO_PIN_13);

  mic.init();

  for(int i=0;i<10;i++){
    data_tx[i] = i;
  }
}

void loop(){
    mic.receive(data_rx,10,100);
	  led.on();
	  HAL_Delay(1);
	  led.off();
	  HAL_Delay(1999);
}

