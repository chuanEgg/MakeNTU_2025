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

    void tick();

    // measure
    void onMeasureToggled(const touchgfx::ToggleButton* targetButton, touchgfx::TextArea* targetText);
    virtual void onVppToggled();
    virtual void onFreqToggled();
    virtual void onPeriodToggled();

    // display
    virtual void onXScaleToggled();
    virtual void onYScaleToggled();
    virtual void onOffsetToggled();

    // menu
    virtual void onSlideMenuUpdated();
    virtual void onBackButtonClicked(); // close every menu container
    virtual void onDisplayMenuClicked(); // show display menu
    virtual void onMeasureMenuClicked(); // show measure menu
    virtual void onTriggerMenuClicked(); // show trigger menu

    // trigger
    virtual void onLevelToggled();
    virtual void onTriggerTypeClicked();

    // helpers
    virtual void onSingleToggle(const touchgfx::ToggleButton* targetToggle);

    // graph
    void UpdateGraph(uint8_t* value); // update dynamicGraph

    // 0: nothing, 1: XScale, 2: YScale, 3: offset, 4: level
    uint8_t encoderTarget;
    int16_t encoderZero = 0;

    int maxYScaleIndex = 12, startYScaleIndex = 6, lastYScaleIndex = 6;
	float YScaleTable[13] = {0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10, 20, 50, 100};
	// int16_t tempEncoderValue;
	int curXScale = 0;
	int curYScale = 6;

    // 0: rising edge, 1: falling edge
    uint8_t triggerType;
    uint8_t triggerLevel;

    // ToggleButtons that should be only one being toggled
    touchgfx::ToggleButton* singleToggle[4];

    // list to maintain menu items
    touchgfx::Container* menuList[4];
protected:
};

#endif // SCREEN1VIEW_HPP
