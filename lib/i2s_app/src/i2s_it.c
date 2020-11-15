#include "i2s_it.h"

//this instantiation does not work as it's a separate library for the startup '.s'
//only an instantiation on the lib containing main.c file works so far
void DMA1_Stream3_IRQHandler(void)
{
  I2sApp_DMA1_Stream3_IRQHandler();
}


