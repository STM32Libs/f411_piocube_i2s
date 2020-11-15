#include <stdint.h>

class I2sApp{
    public:
        enum Mode_e : uint8_t
        {
            Blocking = 0,
            Interrupt = 1,
            DMA = 2
        };    
        I2sApp();
        bool init(Mode_e mode=Blocking );
        bool receive(uint32_t *pData, uint16_t Size);
        bool pause();
        bool receive_direct(uint16_t *pData, uint16_t Size, uint32_t Timeout);
    
};
