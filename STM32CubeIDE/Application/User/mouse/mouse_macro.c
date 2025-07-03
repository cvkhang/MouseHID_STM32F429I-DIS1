#include "mouse_macro.h"
#include "mouse_hid.h"
#include "main.h"


#define MAX_MACRO_EVENTS  128u          // max elements in circular buffer

typedef struct {
    uint8_t  buttons;
    int8_t   x;
    int8_t   y;
    int8_t   wheel;
    uint32_t delay_ms;
} MacroEvent;


static MacroEvent macro_buffer[MAX_MACRO_EVENTS];
static uint16_t   macro_count      = 0; // filled entries
static uint8_t    recording        = 0; // 1 = currently recording
static uint32_t   last_tick        = 0; // tick when previous event saved

// Playback state machine
static uint8_t    playing          = 0; // 1 = currently playing
static uint16_t   play_index       = 0; // next event to send
static uint32_t   play_last_tick   = 0; // tick when previous event sent

// Recording
void Macro_StartRecording(void)
{
    macro_count = 0;
    recording   = 1;
    playing     = 0;               // cannot play while recording
    last_tick   = HAL_GetTick();
}

void Macro_StopRecording(void)
{
    recording = 0;
}

void Macro_ToggleRecording(void)
{
    if (recording)
        Macro_StopRecording();
    else
        Macro_StartRecording();
}

uint8_t Macro_IsRecording(void)
{
    return recording;
}

// Called by Mouse_SendReport() each time an HID report is emitted
void Macro_RecordEvent(uint8_t buttons, int8_t x, int8_t y, int8_t wheel)
{
    if (!recording || playing)                 // ignore when not recording or while playing
        return;

    if (macro_count >= MAX_MACRO_EVENTS)
        return;                                // buffer full – ignore additional events

    uint32_t now = HAL_GetTick();
    uint32_t delay = now - last_tick;
    last_tick = now;

    macro_buffer[macro_count].buttons   = buttons;
    macro_buffer[macro_count].x         = x;
    macro_buffer[macro_count].y         = y;
    macro_buffer[macro_count].wheel     = wheel;
    macro_buffer[macro_count].delay_ms  = delay;

    macro_count++;
}

// Playback
void Macro_TogglePlay(void)
{
    // Never start playback while recording, and need at least 1 event
    if (recording || (macro_count == 0))
        return;

    if (!playing) {
        // Start playback
        playing         = 1;
        play_index      = 0;
        play_last_tick  = HAL_GetTick();
    } else {
        // Stop playback
        playing = 0;
    }
}

uint8_t Macro_IsPlaying(void)
{
    return playing;
}

// To be called regularly from TouchGFX handleTickEvent()
void Macro_Service(void)
{
    if (!playing || (macro_count == 0))
        return;

    uint32_t now = HAL_GetTick();

    if ((now - play_last_tick) >= macro_buffer[play_index].delay_ms) {
        // Time to send next event
        Mouse_SendReport(macro_buffer[play_index].buttons,
                         macro_buffer[play_index].x,
                         macro_buffer[play_index].y,
                         macro_buffer[play_index].wheel);

        play_last_tick = now;
        play_index++;

        if (play_index >= macro_count)        // loop endlessly – change to stop if desired
            play_index = 0;
    }
}

// wrappers for TouchGFX buttons
void macroRecord(void)
{
    Macro_ToggleRecording();
}

void macroPlay(void)
{
    Macro_TogglePlay();
}
