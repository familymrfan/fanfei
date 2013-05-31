#include "window.h"
#include <memory>

namespace
{
struct MV{
	MV(Model *_model,View *_view){
		model = _model;
		view  = _view;
	}
	Model *model;
	View *view;
};

std::shared_ptr<MV> mv = nullptr;
} // namespace

void Window::Generate(){
	model_.AddProc([](
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam)->LRESULT{
			switch(uMsg){
			case WM_COMMAND:

				break;
			case WM_PAINT:
				mv->view->Paint(*mv->model);
				break;
			case WM_DESTROY:
				::PostQuitMessage(0);
				break;
			}
			return ::DefWindowProc (hwnd, uMsg, wParam, lParam);
	});
	if(!model_.Generate())
		return ;
	if(!view_.Generate(model_.GetHwnd(),50,50,500,500))
		return ;
	mv = std::make_shared<MV>(&model_,&view_);
	::ShowWindow(model_.GetHwnd(),SW_SHOW);
	::UpdateWindow(model_.GetHwnd());
}