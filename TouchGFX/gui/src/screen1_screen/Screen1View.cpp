#include <gui/screen1_screen/Screen1View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/containers/SlideMenu.hpp>
#include <algorithm>

#define SCREEN_HEIGHT 260
#define SCREEN_WIDTH 200
#define MAX_X_SCALE_INDEX 12
#define MAX_Y_SCALE_INDEX 12
#define MAX_OFFSET 130
#define MIN_OFFSET -130
#define MAX_LEVEL 270
#define MIN_LEVEL 25
#define MAX_CURSOR_1X 435
#define MIN_CURSOR_1X 20
#define MAX_CURSOR_1Y 250
#define MIN_CURSOR_1Y 25

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
	singleToggle[4] = &cursor1XToggle;
	singleToggle[5] = &cursor1YToggle;
	singleToggle[6] = &cursor2XToggle;
	singleToggle[7] = &cursor2YToggle;

	menuList[0] = &mainMenu;
	menuList[1] = &displayMenu;
	menuList[2] = &measureMenu;
	menuList[3] = &triggerMenu;
	menuList[4] = &cursorMenu;

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
	for (int i = 1; i < 5; i ++)
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

void Screen1View::onCursorMenuClicked()
{
    mainMenu.setVisible(false);
    cursorMenu.setVisible(true);
    backButton.setVisible(true);

    mainMenu.invalidate();
	cursorMenu.invalidate();
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
	for (int i = 0; i < 8; i ++)
	{
		if (singleToggle[i] != targetToggle)
		{
			singleToggle[i]->forceState(false);
			singleToggle[i]->invalidate();
		}
	}
	horizontalLine0.setVisible(false);
	horizontalLine0.invalidate();
	horizontalLine1.setVisible(false);
	horizontalLine1.invalidate();
	verticalLine1.setVisible(false);
	verticalLine1.invalidate();
	horizontalLine2.setVisible(false);
	horizontalLine2.invalidate();
	verticalLine2.setVisible(false);
	verticalLine2.invalidate();
	lastXScaleIndex = curXScale;
	lastYScaleIndex = curYScale;
	lastOffset = curOffset;
	lastLevel = triggerLevel;
	lastCursor1X = curCursor1X;
	lastCursor1Y = curCursor1Y;
	lastCursor2X = curCursor2X;
	lastCursor2Y = curCursor2Y;
}

void Screen1View::onXScaleToggled()
{
	encoderTarget = (XScaleToggle.getState()) ? 1 : 0;
	if(XScaleToggle.getState() == false) {
			lastXScaleIndex = curXScale;
		}
		else {
			curXScale = lastXScaleIndex;
		}
	onSingleToggle(&XScaleToggle);
}

void Screen1View::onYScaleToggled()
{
	encoderTarget = (YScaleToggle.getState()) ? 2 : 0;
	if(YScaleToggle.getState() == false) {
		lastYScaleIndex = curYScale;
	}
	else {
		curYScale = lastYScaleIndex;
	}
	onSingleToggle(&YScaleToggle);
}

void Screen1View::onOffsetToggled()
{
	encoderTarget = (offsetToggle.getState()) ? 3 : 0;
	if(offsetToggle.getState() == false) {
		lastOffset = curOffset;
	}
	else {
		curOffset = lastOffset;
	}
	onSingleToggle(&offsetToggle);
}

void Screen1View::onLevelToggled()
{
	encoderTarget = (levelToggle.getState()) ? 4 : 0;
	onSingleToggle(&levelToggle);
	if (levelToggle.getState())
	{
		triggerLevel = lastLevel;
		horizontalLine0.setVisible(true);
		horizontalLine0.invalidate();
	}
	else {
		lastLevel = triggerLevel;
	}
}

void Screen1View::onCursor1XToggled()
{
	encoderTarget = (cursor1XToggle.getState()) ? 5 : 0;
	onSingleToggle(&cursor1XToggle);
	if(cursor1XToggle.getState() == false) {
		lastCursor1X = curCursor1X;
	}
	else {
		curCursor1X = lastCursor1X;
		horizontalLine1.setVisible(true);
		horizontalLine1.invalidate();
		verticalLine1.setVisible(true);
		verticalLine1.invalidate();
	}
}

void Screen1View::onCursor2XToggled()
{
	encoderTarget = (cursor2XToggle.getState()) ? 7 : 0;
	onSingleToggle(&cursor2XToggle);
	if (cursor2XToggle.getState() == false)
	{
		lastCursor2X = curCursor2X;
	}
	else
	{
		curCursor2X = lastCursor2X;
		horizontalLine2.setVisible(true);
		horizontalLine2.invalidate();
		verticalLine2.setVisible(true);
		verticalLine2.invalidate();
	}
}
void Screen1View::onCursor1YToggled()
{
	encoderTarget = (cursor1YToggle.getState()) ? 6 : 0;
	onSingleToggle(&cursor1YToggle);
	if(cursor1YToggle.getState() == false) {
		lastCursor1Y = curCursor1Y;
	}
	else {
		curCursor1Y = lastCursor1Y;
		horizontalLine1.setVisible(true);
		horizontalLine1.invalidate();
		verticalLine1.setVisible(true);
		verticalLine1.invalidate();
	}
}

void Screen1View::onCursor2YToggled()
{
	encoderTarget = (cursor2YToggle.getState()) ? 8 : 0;
	onSingleToggle(&cursor2YToggle);
	if (cursor2YToggle.getState() == false)
	{
		lastCursor2Y = curCursor2Y;
	}
	else
	{
		curCursor2Y = lastCursor2Y;
		horizontalLine2.setVisible(true);
		horizontalLine2.invalidate();
		verticalLine2.setVisible(true);
		verticalLine2.invalidate();
	}

}

void Screen1View::tick()
{
	switch(encoderTarget) {
		case 0:
			break;
		case 1: // XScale
			curXScale = lastXScaleIndex + encoderValue - encoderZero;
			if(curXScale > MAX_X_SCALE_INDEX) {
				curXScale = MAX_X_SCALE_INDEX;
				encoderZero = lastXScaleIndex + encoderValue - curXScale;
			}
			if(curXScale < 0) {
				curXScale = 0;
				encoderZero = lastXScaleIndex + encoderValue - curXScale;
			}
			break;
		case 2: // YScale
			curYScale = lastYScaleIndex + encoderValue - encoderZero;
			if(curYScale > MAX_Y_SCALE_INDEX) {
				curYScale = MAX_Y_SCALE_INDEX;
				encoderZero = lastYScaleIndex + encoderValue - curYScale;
			}
			if(curYScale < 0) {
				curYScale = 0;
				encoderZero = lastYScaleIndex + encoderValue - curYScale;
			}
			break;
		case 3: // offset
			curOffset = lastOffset + (encoderValue - encoderZero) * 5;
			if(curOffset > MAX_OFFSET) {
				curOffset = MAX_OFFSET;
				encoderZero = encoderValue - (curOffset - lastOffset) / 5;
			}
			if(curOffset < MIN_OFFSET) {
				curOffset = MIN_OFFSET;
				encoderZero = encoderValue - (curOffset - lastOffset) / 5;
			}
			break;
		case 4: // level
			triggerLevel = lastLevel + (encoderValue - encoderZero) * 5;
			if(triggerLevel >= MAX_CURSOR_1Y) {
				triggerLevel = MAX_CURSOR_1Y;
				encoderZero = encoderValue - (triggerLevel - lastLevel) / 5;
			}
			if(triggerLevel <= MIN_CURSOR_1Y) {
				triggerLevel = MIN_CURSOR_1Y;
				encoderZero = encoderValue - (triggerLevel - lastLevel) / 5;
			}
			horizontalLine0.setPosition(15, (int16_t)(MAX_LEVEL - triggerLevel), slideMenu1.getState() == SlideMenu::COLLAPSED ? 430 : 297, 15);
			horizontalLine0.invalidate();
			break;
		case 5: // cursor1X
			curCursor1X = lastCursor1X + (encoderValue - encoderZero) * 5;
			if(curCursor1X >= MAX_CURSOR_1X) {
				curCursor1X = MAX_CURSOR_1X;
				encoderZero = encoderValue - (curCursor1X - lastCursor1X) / 5;
			}
			if(curCursor1X <= MIN_CURSOR_1X) {
				curCursor1X = MIN_CURSOR_1X;
				encoderZero = encoderValue - (curCursor1X - lastCursor1X) / 5;
			}
			verticalLine1.setPosition(slideMenu1.getState() == SlideMenu::COLLAPSED ? (int16_t)curCursor1X : (int16_t)curCursor1X * 297 / 450, 20, 15, 230);
			verticalLine1.invalidate();
			break;
		case 6: // cursor1Y
			curCursor1Y = lastCursor1Y + (encoderValue - encoderZero) * 5;
			if(curCursor1Y >= MAX_CURSOR_1Y) {
				curCursor1Y = MAX_CURSOR_1Y;
				encoderZero = encoderValue - (curCursor1Y - lastCursor1Y) / 5;
			}
			if(curCursor1Y <= MIN_CURSOR_1Y) {
				curCursor1Y = MIN_CURSOR_1Y;
				encoderZero = encoderValue - (curCursor1Y - lastCursor1Y) / 5;
			}
			horizontalLine1.setPosition(15, (int16_t)(MAX_LEVEL - curCursor1Y), slideMenu1.getState() == SlideMenu::COLLAPSED ? 435 : 297, 15);
			horizontalLine1.invalidate();
			break;
		case 7:
			curCursor2X = lastCursor2X + (encoderValue - encoderZero) * 5;
			if(curCursor2X >= MAX_CURSOR_1X) {
				curCursor2X = MAX_CURSOR_1X;
				encoderZero = encoderValue - (curCursor2X - lastCursor2X) / 5;
			}
			if(curCursor2X <= MIN_CURSOR_1X) {
				curCursor2X = MIN_CURSOR_1X;
				encoderZero = encoderValue - (curCursor2X - lastCursor2X) / 5;
			}
			verticalLine2.setPosition(slideMenu1.getState() == SlideMenu::COLLAPSED ? (int16_t)curCursor2X : (int16_t)curCursor2X * 297 / 450, 20, 15, 230);
			verticalLine2.invalidate();
			break;
		case 8:
			curCursor2Y = lastCursor2Y + (encoderValue - encoderZero) * 5;
			if(curCursor2Y >= MAX_CURSOR_1Y) {
				curCursor2Y = MAX_CURSOR_1Y;
				encoderZero = encoderValue - (curCursor2Y - lastCursor2Y) / 5;
			}
			if(curCursor2Y <= MIN_CURSOR_1Y) {
				curCursor2Y = MIN_CURSOR_1Y;
				encoderZero = encoderValue - (curCursor2Y - lastCursor2Y) / 5;
			}
			horizontalLine2.setPosition(15, (int16_t)(MAX_LEVEL - curCursor2Y), slideMenu1.getState() == SlideMenu::COLLAPSED ? 435 : 297, 15);
			horizontalLine2.invalidate();
			break;
		default:
			break;
	}
	Unicode::snprintfFloat(cursor1DataTextBuffer1, 10, "%.3f\0", curCursor1X);
	Unicode::snprintfFloat(cursor1DataTextBuffer2, 10, "%.3f\0", curCursor1Y);
	Unicode::snprintfFloat(cursor2DataTextBuffer1, 10, "%.3f\0", curCursor2X);
	Unicode::snprintfFloat(cursor2DataTextBuffer2, 10, "%.3f\0", curCursor2Y);
	cursor1DataText.invalidate();
	cursor2DataText.invalidate();
}

void Screen1View::onSlideMenuUpdated()
{
	if (slideMenu1.getState() == SlideMenu::COLLAPSED)
	{
//		slideMenu.setPisition()
		backButton.setVisible(false);
		for (int i = 1; i < 5; i ++)
		{
			menuList[i]->setVisible(false);
		}
		mainMenu.setVisible(true);
		displayGraph.setPosition(15, 20, 435, 230);
		displayGraph.invalidate();
//		slideMenu1.setXY(486, 0);
//		slideMenu1.invalidate();
		horizontalLine0.setPosition(15, (int16_t)(250 - triggerLevel), 435, 15);
		horizontalLine0.invalidate();
		horizontalLine1.setPosition(15, (int16_t)(250 - curCursor1Y), 435, 15);
		horizontalLine1.invalidate();
		verticalLine1.setPosition((int16_t)curCursor1X, 20, 15, 230);
		verticalLine1.invalidate();
	}
	else
	{
		displayGraph.setPosition(15, 20, 297, 230);
		displayGraph.invalidate();
		horizontalLine0.setPosition(15, (int16_t)(250 - triggerLevel), 297, 15);
		horizontalLine0.invalidate();
		horizontalLine1.setPosition(15, (int16_t)(250 - curCursor1Y), 297, 15);
		horizontalLine1.invalidate();
		verticalLine1.setPosition((int16_t)curCursor1X * 297 / 435, 20, 15, 230);
		verticalLine1.invalidate();
	}
}

void Screen1View::UpdateGraph(uint8_t* value)
{
	displayGraph.clear();
	for (int i = 0; i < NUM_DATA_POINT; i ++)
	{
		displayGraph.addDataPoint((value[i] - (SCREEN_HEIGHT / 2)) * YScaleTable[curYScale] + (SCREEN_HEIGHT / 2) + curOffset);
	}
	displayGraph.invalidateContent();
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
