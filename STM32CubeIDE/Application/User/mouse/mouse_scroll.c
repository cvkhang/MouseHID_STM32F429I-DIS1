#include "mouse_scroll.h"
#include "mouse_hid.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "mouse_config.h"
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;

#define UPPER 2300
#define LOWER 1800

void Mouse_HandleScroll(void)
{
    // 1. Lấy trung bình ADC
    uint32_t total = 0;
    for (int i = 0; i < 10; i++)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        total += HAL_ADC_GetValue(&hadc1);
        osDelay(1);
    }
    uint16_t adc_val = total / 10;

    // 2. Chuyển thành scroll (-1, 0, +1)
    int8_t scrollStep = 0;
    if (adc_val > UPPER)
        scrollStep = -1;               // cuộn xuống
    else if (adc_val < LOWER)
        scrollStep = +1;               // cuộn lên

    // 3. Áp dụng độ nhạy (gain) & clamp về ±127
    if (scrollStep != 0)
    {
        int32_t scroll = scrollStep * gScrollGain;  // gScrollGain = 1-8

        if (scroll >  127) scroll =  127;
        if (scroll < -127) scroll = -127;

        Mouse_SendReport(0, 0, 0, (int8_t)scroll);

        // Log
        char msg[40];
        snprintf(msg, sizeof(msg), "ADC:%u  Scroll:%ld  Gain:%d\r\n",
                 adc_val, scroll, gScrollGain);
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 10);

        osDelay(100);
    }
}
