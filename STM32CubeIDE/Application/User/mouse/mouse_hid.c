#include "mouse_hid.h"
#include "mouse_macro.h"

extern USBD_HandleTypeDef hUsbDeviceHS;

void Mouse_SendReport(uint8_t buttons, int8_t x, int8_t y, int8_t wheel)
{
    Macro_RecordEvent(buttons, x, y, wheel);

    uint8_t report[4] = {buttons, x, y, wheel};
    USBD_HID_SendReport(&hUsbDeviceHS, report, sizeof(report));
}
