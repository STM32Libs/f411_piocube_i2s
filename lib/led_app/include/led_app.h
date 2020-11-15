#include "stm32f4xx_hal.h"

class LedApp{
    public:
        bool init(GPIO_TypeDef  *port_v, uint16_t pin_v);
        void on();
        void off();
        void toggle();
    private:
        GPIO_TypeDef  *port;
        uint16_t pin;
};
