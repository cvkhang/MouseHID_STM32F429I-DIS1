
#ifndef MOUSE_MACRO_H
#define MOUSE_MACRO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Recording
void     Macro_StartRecording(void);
void     Macro_StopRecording(void);
void     Macro_ToggleRecording(void);
uint8_t  Macro_IsRecording(void);

// Playback
void     Macro_TogglePlay(void);
uint8_t  Macro_IsPlaying(void);
void     Macro_Service(void);

void     macroRecord(void); // wrapper cho nút Record
void     macroPlay(void);   // wrapper cho nút Play

void     Macro_RecordEvent(uint8_t buttons,
                           int8_t   x,
                           int8_t   y,
                           int8_t   wheel);

#ifdef __cplusplus
}
#endif

#endif /* MOUSE_MACRO_H */
