#include "mouse_click.h"
#include <string.h>
#include "main.h"
#include "mouse_config.h"

extern UART_HandleTypeDef huart1;

// Flags
volatile uint8_t flag_left_click  = 0;
volatile uint8_t flag_right_click = 0;
static   volatile uint8_t flag_multi_toggle = 0;

// Mode & state
volatile uint8_t gMultitaskMode = 0;  // 0 = normal; 1 = multitask hold mode
volatile uint8_t hold_left      = 0;  // 1 = left button is being held

// Internal: track the *current* button mask so other code can query it
static volatile uint8_t current_buttons = 0x00;

#define DEBOUNCE_MS 200U
static uint32_t last_left_tick  = 0;
static uint32_t last_right_tick = 0;
static uint32_t last_multi_tick = 0;

static inline void send_report(uint8_t buttons, int8_t x, int8_t y, int8_t wheel)
{
    current_buttons = buttons;
    Mouse_SendReport(buttons, x, y, wheel);
}

uint8_t Mouse_GetButtons(void)
{
    return current_buttons;
}

void Mouse_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    if (GPIO_Pin == GPIO_PIN_7 && (now - last_left_tick) > DEBOUNCE_MS) // LEFT – PA7
    {
        last_left_tick = now;
        flag_left_click = 1;
#ifdef DEBUG_UART_CLICK
        const char *msg = "\nleft click";
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 10);
#endif
    }
    else if (GPIO_Pin == GPIO_PIN_5 && (now - last_right_tick) > DEBOUNCE_MS) // RIGHT – PC5
    {
        last_right_tick = now;
        flag_right_click = 1;
#ifdef DEBUG_UART_CLICK
        const char *msg = "\nright click";
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 10);
#endif
    }
    else if (GPIO_Pin == GPIO_PIN_6 && (now - last_multi_tick) > DEBOUNCE_MS) // MULTI – PF6
    {
        last_multi_tick = now;
        flag_multi_toggle = 1;
#ifdef DEBUG_UART_CLICK
        const char *msg = "\nmulti click";
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 10);
#endif
    }
}

// Main loop – call often from scheduler

void Mouse_HandleClick(void)
{
    // 1. Toggle Multitask (drag lock) mode
    if (flag_multi_toggle)
    {
        flag_multi_toggle = 0;
        gMultitaskMode ^= 1;   // flip

        if (!gMultitaskMode && hold_left)
        {
            // Exiting – release left button
            send_report(0x00, 0, 0, 0);
            hold_left = 0;
        }
    }

    // Handle LEFT button event
    if (flag_left_click)
    {
        flag_left_click = 0;

        if (gMultitaskMode)
        {
            // Press & HOLD (drag lock)
            send_report(0x01, 0, 0, 0);
            hold_left = 1;
        }
        else
        {
            // Normal click
            send_report(0x01, 0, 0, 0);   // press
            HAL_Delay(20);
            send_report(0x00, 0, 0, 0);   // release
        }
    }

    // Handle RIGHT button event
    if (flag_right_click)
    {
        flag_right_click = 0;

        send_report(0x02, 0, 0, 0);   // press
        HAL_Delay(20);
        send_report(0x00, 0, 0, 0);   // release
    }
}
