#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/events/ClickEvent.hpp>
#include <touchgfx/events/DragEvent.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    virtual void handleClickEvent(const touchgfx::ClickEvent& evt) override;
    virtual void handleDragEvent(const touchgfx::DragEvent& evt) override;
    virtual void btnUpSenClicked();
    virtual void btnDownSenClicked();
    virtual void btnUpScrollClicked();
    virtual void btnDownScrollClicked();
    void recMacroClicked();
    void playMacroClicked();

private:
    int16_t lastX = -1;
    int16_t lastY = -1;
    bool isInsideTouchpad(int16_t x, int16_t y) const;

};

#endif // SCREEN1VIEW_HPP
