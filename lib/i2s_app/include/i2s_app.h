#include <stdint.h>

class I2sApp{
    public:
        I2sApp();
        bool init();
        bool receive(uint16_t *pData, uint16_t Size, uint32_t Timeout);
    
};
