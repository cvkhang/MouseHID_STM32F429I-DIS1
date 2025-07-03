#ifndef MOUSE_CLICK_H
#define MOUSE_CLICK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void Mouse_SendReport(uint8_t buttons, int8_t x, int8_t y, int8_t wheel);
void Mouse_EXTI_Callback(uint16_t GPIO_Pin);
void Mouse_HandleClick(void);

// Query current button state
uint8_t Mouse_GetButtons(void);

// Access these if necessary elsewhere
extern volatile uint8_t gMultitaskMode;
extern volatile uint8_t hold_left;

#ifdef __cplusplus
}
#endif

#endif /* MOUSE_CLICK_H */
