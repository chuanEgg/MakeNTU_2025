#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "main.h"

extern uint8_t GraphData[NUM_DATA_POINT];
extern uint8_t bUpdate;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if (bUpdate)
	{
		modelListener->UpdateGraph(GraphData);
		bUpdate = 0;
	}
	modelListener->tick();
}
