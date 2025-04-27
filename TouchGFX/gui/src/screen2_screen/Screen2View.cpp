#include <gui/screen2_screen/Screen2View.hpp>
#include <initializer_list>
#include <texts/TextKeysAndLanguages.hpp>

extern uint8_t funcType;
Unicode::UnicodeChar TempBuffer2[6];
const char* funcName[3] = {"sin", "square", "tri"};


/*
	virtual void onFuncButtonClicked();
    virtual void onFreqConfirmed();
    virtual void onAmpConfirmed();
    virtual void freqValueUpdate();
    virtual void ampValueUpdate();
 */

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::onFuncButtonClicked()
{
	funcType = (funcType + 1) % 3;
	Unicode::strncpy(TempBuffer2, funcName[funcType], sizeof(TempBuffer2));
	funcText.setWildcard(TempBuffer2);
	funcText.invalidate();
}

void Screen2View::onFreqConfirmed(int value)
{
	// TODO call freq changing function
}

void Screen2View::onAmpConfirmed(int value)
{
	// TODO call amp changing function
}

void Screen2View::freqValueUpdate(int value)
{
	Unicode::snprintf(freqValueTextBuffer, FREQVALUETEXT_SIZE, "%d", value);
	freqValueText.invalidate();
}

void Screen2View::ampValueUpdate(int value)
{
	//
	Unicode::snprintfFloat(ampValueTextBuffer, AMPVALUETEXT_SIZE, "%.1f", (float)value/10);
	ampValueText.invalidate();
}
