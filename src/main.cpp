#include "cube_main.h"
#include "i2s_app.h"
#include "led_app.h"
#include "stm32f4xx_hal.h"

I2sApp mic;
LedApp led;

uint16_t data_rx[128];//32bit samples
int32_t frac_rx[32];

//0x0B05 C000 => 0xB05C0 => 722368
void PacketReceived(){
    mic.stop();
    led.toggle();
    uint16_t *p_data = data_rx;
    for(int i=0;i<32;i++){
      uint32_t val = static_cast<uint32_t>(*p_data++);
      int32_t frac = (val<<16) + static_cast<uint32_t>(*p_data++);
      frac_rx[i] = frac>>8;
    }
    led.toggle();
}

void setup(void) {

  led.init(GPIOC,GPIO_PIN_13);
  mic.init(I2sApp::DMA);
  mic.onPacket(PacketReceived);
  led.off();
  HAL_Delay(1);
  led.on();
  mic.start(data_rx,32);
  //mic.pause();
  //led.off();
}

void loop(){
    //led.on();
    HAL_Delay(10);
    //led.off();
    HAL_Delay(1990);
}

