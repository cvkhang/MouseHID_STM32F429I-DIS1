#ifndef MOUSE_CONFIG_H
#define MOUSE_CONFIG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern volatile int8_t gMouseGain;   // 1 - 8
extern volatile int8_t gScrollGain;  // 1 - 8
#ifdef __cplusplus
}
#endif
#endif
