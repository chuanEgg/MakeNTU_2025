#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>


extern float NewData;
extern float GraphData[100];

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	modelListener->UpdateGraph(GraphData);
}
