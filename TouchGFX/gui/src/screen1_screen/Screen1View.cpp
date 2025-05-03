#include <gui/screen1_screen/Screen1View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/containers/SlideMenu.hpp>
#include <algorithm>

#define SCREEN_HEIGHT 260
#define SCREEN_WIDTH 200

extern "C"
{
	extern int16_t encoderValue;
}
// map [0, 255] to [-5, 5] (float) for display purpose
float UnMap(uint8_t value)
{
	return ((float)value / 25.5) - 5;
}

Screen1View::Screen1View()
{
	singleToggle[0] = &XScaleToggle;
	singleToggle[1] = &YScaleToggle;
	singleToggle[2] = &offsetToggle;
	singleToggle[3] = &levelToggle;

	menuList[0] = &mainMenu;
	menuList[1] = &displayMenu;
	menuList[2] = &measureMenu;
	menuList[3] = &triggerMenu;
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
	for (int i = 1; i < 4; i ++)
	{
		menuList[i]->setVisible(false);
		menuList[i]->invalidate();
	}

	// hide back button itself
	backButton.setVisible(false);
	backButton.invalidate();

	// show main menu back on
	mainMenu.setVisible(true);
	mainMenu.invalidate();
}

void Screen1View::onDisplayMenuClicked()
{
	// hide main menu first
	mainMenu.setVisible(false);

	// show display menu and back button
	displayMenu.setVisible(true);
	backButton.setVisible(true);

	mainMenu.invalidate();
	displayMenu.invalidate();
	backButton.invalidate();
}

void Screen1View::onMeasureMenuClicked()
{
	mainMenu.setVisible(false);
	measureMenu.setVisible(true);
	backButton.setVisible(true);

	mainMenu.invalidate();
	measureMenu.invalidate();
	backButton.invalidate();
}

void Screen1View::onTriggerMenuClicked()
{
	mainMenu.setVisible(false);
	triggerMenu.setVisible(true);
	backButton.setVisible(true);

	mainMenu.invalidate();
	triggerMenu.invalidate();
	backButton.invalidate();
}
// TODO: naive implementation for toggling measure
// should rearrange text position

void Screen1View::onMeasureToggled(
		const touchgfx::ToggleButton* targetButton,
		touchgfx::TextArea* targetText)
{
	targetText->setVisible(!(targetButton->getState()));
	targetText->invalidate();
}
void Screen1View::onVppToggled()
{
	Screen1View::onMeasureToggled(&VppToggle, &VppText);
}
void Screen1View::onFreqToggled()
{
	Screen1View::onMeasureToggled(&freqToggle, &freqText);
}
void Screen1View::onPeriodToggled()
{
	Screen1View::onMeasureToggled(&periodToggle, &periodText);
}

void Screen1View::onSingleToggle(const touchgfx::ToggleButton* targetToggle)
{
	encoderZero = encoderValue;
	for (int i = 0; i < 4; i ++)
	{
		if (singleToggle[i] != targetToggle)
		{
			singleToggle[i]->forceState(false);
			singleToggle[i]->invalidate();
		}
	}
	horizontalLine0.setVisible(false);
	horizontalLine0.invalidate();
}

void Screen1View::onXScaleToggled()
{
	encoderTarget = (XScaleToggle.getState()) ? 1 : 0;
	onSingleToggle(&XScaleToggle);
}

void Screen1View::onYScaleToggled()
{
	encoderTarget = (YScaleToggle.getState()) ? 2 : 0;
	if(YScaleToggle.getState() == false) {
		curYScale = lastYScaleIndex;
	}
	else {
		lastYScaleIndex = curYScale;
	}
	onSingleToggle(&YScaleToggle);
}

void Screen1View::onOffsetToggled()
{
	encoderTarget = (offsetToggle.getState()) ? 3 : 0;
	onSingleToggle(&offsetToggle);
}

void Screen1View::onLevelToggled()
{
	encoderTarget = (levelToggle.getState()) ? 4 : 0;
	onSingleToggle(&levelToggle);
	if (levelToggle.getState())
	{
		horizontalLine0.setVisible(true);
		horizontalLine0.invalidate();
	}
}

void Screen1View::tick()
{
	switch(encoderTarget) {
		case 0:
			break;
		case 1: // XScale
			break;
		case 2: // YScale
			curYScale = lastYScaleIndex + encoderValue - encoderZero;
			if(curYScale > maxYScaleIndex) {
				curYScale = maxYScaleIndex;
				encoderZero = lastYScaleIndex + encoderValue - curYScale;
			}
			if(curYScale < 0) {
				curYScale = 0;
				encoderZero = lastYScaleIndex + encoderValue - curYScale;
			}
			break;
		case 3: // offset
			break;
		case 4: // level
			break;
	}
}

void Screen1View::onSlideMenuUpdated()
{
	if (slideMenu1.getState() == SlideMenu::COLLAPSED)
	{
		backButton.setVisible(false);
		for (int i = 1; i < 4; i ++)
		{
			menuList[i]->setVisible(false);
		}
		mainMenu.setVisible(true);
	}
}

void Screen1View::UpdateGraph(uint8_t* value)
{
	displayGraph.clear();
	for (int i = 0; i < NUM_DATA_POINT; i ++)
	{
		displayGraph.addDataPoint((value[i] - (SCREEN_HEIGHT / 2)) * YScaleTable[curYScale] + (SCREEN_HEIGHT / 2));
	}
	displayGraph.invalidate();
}

void Screen1View::onTriggerTypeClicked()
{
	triggerType = !triggerType;
	if (triggerType)
	{
		Unicode::strncpy(triggerTypeTextBuffer, "falling", TRIGGERTYPETEXT_SIZE);
	}
	else
	{
		Unicode::strncpy(triggerTypeTextBuffer, "rising", TRIGGERTYPETEXT_SIZE);
	}
	triggerTypeText.invalidate();
}
// trigger menu
// detection type
// level
