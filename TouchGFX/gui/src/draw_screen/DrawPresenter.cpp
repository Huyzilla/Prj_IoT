#include <gui/draw_screen/DrawView.hpp>
#include <gui/draw_screen/DrawPresenter.hpp>

DrawPresenter::DrawPresenter(DrawView& v)
    : view(v)
{

}

void DrawPresenter::activate()
{

}

void DrawPresenter::deactivate()
{

}

void DrawPresenter::onRequestRegisterMode()
{
    view.enterRegisterMode();
}
