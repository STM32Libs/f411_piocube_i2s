# f411_piocube_i2s
Example using the black pill STM32F411 with platformio for an i2s example

# issues with callbacks
the `__weak void HAL_I2S_MspInit(I2S_HandleTypeDef *hi2s)` does not get replaced when the built override is packed on a library