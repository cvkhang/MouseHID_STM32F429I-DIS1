#ifndef MOUSE_HID_H
#define MOUSE_HID_H

#include "usbd_hid.h"
#include "usb_device.h"

#ifdef __cplusplus
extern "C" {
#endif

void Mouse_SendReport(uint8_t buttons, int8_t x, int8_t y, int8_t wheel);

#ifdef __cplusplus
}
#endif

#endif // MOUSE_HID_H
