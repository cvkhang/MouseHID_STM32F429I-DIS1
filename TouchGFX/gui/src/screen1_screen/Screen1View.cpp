#include <gui/screen1_screen/Screen1View.hpp>
#include "mouse_hid.h"
#include "mouse_config.h"
#include <algorithm>
#include "mouse_click.h"
#include "mouse_macro.h"
#include "touchpad.h"
using namespace touchgfx;



Screen1View::Screen1View()
    : lastX(-1)
    , lastY(-1)
{
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();

    Rect r = touchArea.getAbsoluteRect();
    Touchpad_Init(r.x, r.y, r.width, r.height);

}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

bool Screen1View::isInsideTouchpad(int16_t x, int16_t y) const
{
    Rect r = touchArea.getAbsoluteRect();
    return r.intersect(Rect(x, y, 1, 1));
}



void Screen1View::handleClickEvent(const ClickEvent& evt)
{
	Screen1ViewBase::handleClickEvent(evt);

	switch (evt.getType())
	{
	case ClickEvent::PRESSED:   Touchpad_Press  (evt.getX(), evt.getY()); break;
	case ClickEvent::RELEASED:
	case ClickEvent::CANCEL:    Touchpad_Release();                      break;
	default: break;
	}
}

void Screen1View::handleDragEvent(const DragEvent& evt)
{
    Touchpad_Drag(evt.getNewX(), evt.getNewY());
}

void Screen1View::btnUpSenClicked()      { Touchpad_SetMouseGain (gMouseGain  < 8 ? ++gMouseGain  : 8); }
void Screen1View::btnDownSenClicked()    { Touchpad_SetMouseGain (gMouseGain  > 1 ? --gMouseGain  : 1); }
void Screen1View::btnUpScrollClicked()   { Touchpad_SetScrollGain(gScrollGain < 8 ? ++gScrollGain : 8); }
void Screen1View::btnDownScrollClicked() { Touchpad_SetScrollGain(gScrollGain > 1 ? --gScrollGain : 1); }

void Screen1View::recMacroClicked()
{
    macroRecord();

}

void Screen1View::playMacroClicked()
{
    if (!Macro_IsRecording())
        macroPlay();
}


void Screen1View::handleTickEvent()
{
    Screen1ViewBase::handleTickEvent();
    Macro_Service();
}
