#include <gui/screen1_screen/Screen1View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <algorithm>

float maxValue = 0.0;
float minValue = 100.0; // arbitrary initial value
Unicode::UnicodeChar TempBuffer[6];

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::UpdateGraph(float* value)
{
//	displayGraph.clear();
	for (int i=0; i<100; i++)
	{
		displayGraph.addDataPoint(value[i]);
		maxValue = std::max(maxValue, value[i]);
		minValue = std::min(minValue, value[i]);
	}
	Unicode::snprintfFloat(TempBuffer, sizeof(TempBuffer), "%.2f", maxValue - minValue);
	vppText.setWildcard(TempBuffer);
}
