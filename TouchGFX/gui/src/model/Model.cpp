#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
//#include "main.h"
#include "global_val.h"

extern uint8_t GraphData[LCD_NUM_POINT];
extern uint8_t *screen_buff_head, *screen_buff_tail, *screen_buff_start;
extern uint8_t start_plot;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if (start_plot)
	{
		modelListener->UpdateGraph(screen_buff_head, screen_buff_tail, screen_buff_start);
		start_plot = 0;
	}
	modelListener->tick();
}
