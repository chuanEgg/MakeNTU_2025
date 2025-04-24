#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>


extern float NewData;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	modelListener->UpdateGraph(NewData);
}
