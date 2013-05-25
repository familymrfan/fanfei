#include "controller.h"
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

Controller::Controller(){
	model_.AddProc([](
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam)->LRESULT{
			switch(uMsg){
			case WM_PAINT:
				mv->view->Paint(*mv->model);
				break;
			case WM_DESTROY:
				::PostQuitMessage(0);
				break;
			}
			return ::DefWindowProc (hwnd, uMsg, wParam, lParam);
	});
	model_.Generate();
	view_.Generate(model_.GetHwnd(),50,50,500,500);
	mv = std::make_shared<MV>(&model_,&view_);
	::ShowWindow(model_.GetHwnd(),SW_SHOW);
	::UpdateWindow(model_.GetHwnd());
}