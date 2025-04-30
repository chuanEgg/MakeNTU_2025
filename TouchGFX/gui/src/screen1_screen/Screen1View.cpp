#include <gui/screen1_screen/Screen1View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <algorithm>

uint8_t maxValue = 0;
uint8_t minValue = 255; // arbitrary initial value
Unicode::UnicodeChar MeasureBuffer[6];

// Vpp, freq, period
uint8_t measureTarget = 0;

// map [0, 255] to [-5, 5] (float) for display purpose
float UnMap(uint8_t value)
{
	return ((float)value / 25.5) - 5;
}


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

void Screen1View::displayOptionScrollUpdateItem(displayOption& item, int16_t itemIndex)
{
	item.setText(itemIndex);
}

void Screen1View::measureOptionScrollUpdateItem(measureOption& item, int16_t itemIndex)
{
	item.setText(itemIndex);
	measureTarget = itemIndex;
}

void Screen1View::UpdateGraph(uint8_t* value)
{
	displayGraph.clear();
	for (int i = 0; i < NUM_DATA_POINT; i ++)
	{
		displayGraph.addDataPoint(value[i]);
	}
	displayGraph.invalidate();
	UpdateMeasureText(value);
}

void Screen1View::UpdateMeasureText(uint8_t* value)
{
	switch (measureTarget % NUM_MEASURE_OPTION)
	{
	case 0:
		for()
	}
}
