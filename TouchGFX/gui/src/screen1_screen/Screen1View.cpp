#include <gui/screen1_screen/Screen1View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/containers/SlideMenu.hpp>
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

void Screen1View::onBackButtonClicked()
{
	// hide every menu container
	measureMenu.setVisible(false);
	displayMenu.setVisible(false);

	// hide back button itself
	backButton.setVisible(false);

	measureMenu.invalidate();
	displayMenu.invalidate();
	backButton.invalidate();
}

void Screen1View::onDisplayMenuClicked()
{
	// collapse main menu first
	slideMenu1.animateToState(SlideMenu::COLLAPSED);

	// show display menu and back button
	displayMenu.setVisible(true);
	backButton.setVisible(true);

	displayMenu.invalidate();
	backButton.invalidate();
}

// TODO: naive implementation for toggling measure
// should rearrange text position
void Screen1View::onVppToggled()
{
	if (VppToggle.getState())
	{
		VppText.setVisible(false);
	}
	else
	{
		VppText.setVisible(true);
	}
	VppText.invalidate();
}

void Screen1View::onFreqToggled()
{
	if (freqToggle.getState())
	{
		freqText.setVisible(false);
	}
	else
	{
		freqText.setVisible(true);
	}
	freqText.invalidate();
}

void Screen1View::onPeriodToggled()
{
	if (periodToggle.getState())
	{
		periodText.setVisible(false);
	}
	else
	{
		periodText.setVisible(true);
	}
	periodText.invalidate();
}

void Screen1View::UpdateGraph(uint8_t* value)
{
	displayGraph.clear();
	for (int i = 0; i < NUM_DATA_POINT; i ++)
	{
		displayGraph.addDataPoint(value[i]);
	}
	displayGraph.invalidate();
}

