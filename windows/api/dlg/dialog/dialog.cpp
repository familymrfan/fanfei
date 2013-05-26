#include "dialog.h"
#include <memory>

void Dialog::Generate(){
	model_.AddProc([](
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam)->INT_PTR{
			return FALSE;
	});
	if(!model_.Generate())
		return ;
	::ShowWindow(model_.GetHwnd(),SW_SHOW);
	::UpdateWindow(model_.GetHwnd());
}