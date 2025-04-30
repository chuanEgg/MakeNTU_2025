#include <gui/containers/displayOption.hpp>

displayOption::displayOption()
{

}

void displayOption::initialize()
{
    displayOptionBase::initialize();
}

void displayOption::setText(int id)
{
	switch (id % 3)
	{
	case 0: // X scale
		Unicode::strncpy(optionText1Buffer, "H scale", OPTIONTEXT1_SIZE);
		break;
	case 1: // Y scale
		Unicode::strncpy(optionText1Buffer, "V scale", OPTIONTEXT1_SIZE);
		break;
	case 2: // offset
		Unicode::strncpy(optionText1Buffer, "offset", OPTIONTEXT1_SIZE);
		break;
	}
}
