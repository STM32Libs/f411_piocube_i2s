#include "cube_main.h"
#include "i2s_app.h"
#include "led_app.h"
#include "stm32f4xx_hal.h"

I2sApp mic;
LedApp led;

uint16_t data_rx[1000*2];//32bit samples

void setup(void) {

  led.init(GPIOC,GPIO_PIN_13);
  mic.init();
  led.on();
  mic.receive(data_rx,200,100);
  led.off();
}

void loop(){
    led.on();
    HAL_Delay(10);
    led.off();
    HAL_Delay(1990);
}

