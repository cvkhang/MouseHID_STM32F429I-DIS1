#include "touchpad.h"
#include "mouse_hid.h"
#include "mouse_click.h"

#include <stdlib.h>

#define LIMIT_127(v)  ( (v) > 127 ? 127 : ( (v) < -127 ? -127 : (v) ) )

// Internal state
static int16_t areaX0, areaY0, areaW, areaH;
static int16_t lastX = -1, lastY = -1;
static uint8_t mouseGain  = 2;
static uint8_t scrollGain = 2;

// API implementation
void Touchpad_Init(int16_t x0, int16_t y0, int16_t w, int16_t h)
{
    areaX0 = x0; areaY0 = y0; areaW = w; areaH = h;
    lastX = lastY = -1;
}

static bool inside(int16_t x, int16_t y)
{
    return (x >= areaX0) && (y >= areaY0) &&
           (x <  areaX0 + areaW) && (y <  areaY0 + areaH);
}

void Touchpad_Press(int16_t x, int16_t y)
{
    if (inside(x, y)) {
        lastX = x;
        lastY = y;
    }
}

void Touchpad_Drag(int16_t x, int16_t y)
{
    if (!inside(x, y) || lastX < 0) return;

    int32_t dx = (x - lastX) * mouseGain;
    int32_t dy = (y - lastY) * mouseGain;

    dx = LIMIT_127(dx);
    dy = LIMIT_127(dy);

    Mouse_SendReport(Mouse_GetButtons(), dx, dy, 0);

    lastX = x;
    lastY = y;
}

void Touchpad_Release(void)
{
    lastX = lastY = -1;
}

// gain
void Touchpad_SetMouseGain(uint8_t g)  { mouseGain  = (g < 1) ? 1 : (g > 8) ? 8 : g; }
void Touchpad_SetScrollGain(uint8_t g) { scrollGain = (g < 1) ? 1 : (g > 8) ? 8 : g; }
