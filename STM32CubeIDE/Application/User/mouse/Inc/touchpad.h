#ifndef TOUCHPAD_H
#define TOUCHPAD_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Gọi một lần khi khởi tạo màn hình
void Touchpad_Init(int16_t x0, int16_t y0, int16_t w, int16_t h);

// Sự kiện từ GUI
void Touchpad_Press (int16_t x, int16_t y);          // PRESSED
void Touchpad_Drag  (int16_t x, int16_t y);          // DRAGGED
void Touchpad_Release(void);                         // RELEASED

// Thay đổi độ nhạy
void Touchpad_SetMouseGain (uint8_t gain);           // 1 – 8
void Touchpad_SetScrollGain(uint8_t gain);           // 1 – 8

#ifdef __cplusplus
}
#endif
#endif /* TOUCHPAD_H */
