#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "main.h"

extern uint8_t GraphData[NUM_DATA_POINT];

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	modelListener->UpdateGraph(GraphData);
}
