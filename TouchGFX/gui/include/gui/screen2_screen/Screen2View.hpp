#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void onFuncButtonClicked();
    virtual void onFreqConfirmed(int value);
    virtual void onAmpConfirmed(int value);
    virtual void freqValueUpdate(int value);
    virtual void ampValueUpdate(int value);
protected:
};

#endif // SCREEN2VIEW_HPP
