#include <gui/containers/measureOption.hpp>

measureOption::measureOption()
{

}

void measureOption::initialize()
{
    measureOptionBase::initialize();
}

void measureOption::setText(int id)
{
	// maybe we shouldn't use switch case here
	// probably use a string array to store options, like seen in the function generator button
	switch (id % 3)
	{
	case 0:
		Unicode::strncpy(optionText2Buffer, "Vpp", OPTIONTEXT2_SIZE);
		break;
	case 1:
		Unicode::strncpy(optionText2Buffer, "freq", OPTIONTEXT2_SIZE);
		break;
	case 2:
		Unicode::strncpy(optionText2Buffer, "period", OPTIONTEXT2_SIZE);
		break;
	}
}
