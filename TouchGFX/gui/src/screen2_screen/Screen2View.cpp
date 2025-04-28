#include <gui/screen2_screen/Screen2View.hpp>
#include <initializer_list>
#include <texts/TextKeysAndLanguages.hpp>
#include <math.h>

#define MAX_FREQ 1000
#define MAX_AMP 31

extern uint8_t funcType;
extern uint32_t funcFreq;
extern uint32_t funcAmp;
Unicode::UnicodeChar TempBuffer2[6];
const char* funcName[4] = {"sin", "sqr", "tri", "pwm"};


/*
	virtual void onFuncButtonClicked();
    virtual void onFreqConfirmed();
    virtual void onAmpConfirmed();
    virtual void freqValueUpdate();
    virtual void ampValueUpdate();
 */

float logMap(int value, int maxVal)
{
	const float k = std::log(maxVal + 1.0) / 2000;
	float y = (std::exp(k * value) - 1.0) / (std::exp(k * 2000.0) - 1.0) * maxVal;
	return y;
}

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
	funcType = (funcType + 1) % 4;
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
	float temp = logMap(value, MAX_FREQ);
	Unicode::snprintfFloat(freqValueTextBuffer, FREQVALUETEXT_SIZE, "%.3f", temp);
	freqValueText.invalidate();
}

void Screen2View::ampValueUpdate(int value)
{
	//
	float temp = logMap(value, MAX_AMP);
	Unicode::snprintfFloat(ampValueTextBuffer, AMPVALUETEXT_SIZE, "%.3f", temp/10);
	ampValueText.invalidate();
}
