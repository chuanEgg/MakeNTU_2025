#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void displayOptionScrollUpdateItem(displayOption& item, int16_t itemIndex);
    virtual void measureOptionScrollUpdateItem(measureOption& item, int16_t itemIndex);

    void UpdateGraph(uint8_t* value);
protected:
};

#endif // SCREEN1VIEW_HPP
