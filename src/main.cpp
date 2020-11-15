#include "cube_main.h"
#include "i2s_app.h"
#include "led_app.h"
#include "stm32f4xx_hal.h"

I2sApp mic;
LedApp led;

int32_t data_rx[64];//32bit samples

void PacketReceived(){
    volatile uint8_t debug = 0;
    debug++;
    led.toggle();
}

void setup(void) {
  led.init(GPIOC,GPIO_PIN_13);
  mic.init(I2sApp::DMA);
  mic.onPacket(PacketReceived);
  led.off();
  HAL_Delay(1);
  led.on();
  mic.receive(data_rx,32);
  //mic.pause();
  //led.off();
}

void loop(){
    //led.on();
    HAL_Delay(10);
    //led.off();
    HAL_Delay(1990);
}

