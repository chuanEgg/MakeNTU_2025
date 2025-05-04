#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
//#include "main.h"
#include "global_val.h"

extern uint8_t GraphData[LCD_NUM_POINT];
extern uint8_t* dataHead, *dataTail, *graphHead;
extern uint8_t bUpdate;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if (bUpdate)
	{
		modelListener->UpdateGraph(dataHead, dataTail, graphHead);
		bUpdate = 0;
	}
	modelListener->tick();
}
