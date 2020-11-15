#include <stdint.h>

typedef void (*PacketCallback)();
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
        void onPacket(PacketCallback cb);
        bool receive(int32_t *pData, uint16_t Size);
        bool pause();
        bool resume();
        bool stop();
    
};
