#include "cube_main.h"
#include "i2s_app.h"
#include "led_app.h"
#include "stm32f4xx_hal.h"

I2sApp mic;
LedApp led;

uint16_t data_rx[10*2];//32bit samples

void setup(void) {

  led.init(GPIOC,GPIO_PIN_13);
  mic.init();
  mic.receive(data_rx,10,100);
}

void loop(){
    led.on();
    HAL_Delay(10);
    led.off();
    HAL_Delay(1990);
}

