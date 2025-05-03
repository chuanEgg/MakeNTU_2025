#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>



Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::UpdateGraph(uint8_t* dataHead, uint8_t* dataTail, uint8_t* graphHead)
{
	view.UpdateGraph(dataHead, dataTail, graphHead);
}

void Screen1Presenter::tick()
{
	view.tick();
}
