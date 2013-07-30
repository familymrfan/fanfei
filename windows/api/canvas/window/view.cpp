#include "view.h"
#include "canvas.h"

View::View(){
	x_  = 0;
	y_  = 0;
	cx_ = 0;
	cy_ = 0;
}

bool View::Generate(HWND hwnd,int x,int y,int cx,int cy){
	if (::IsWindow (hwnd) == 0)
		return false;
	x_ = x;
	y_ = y;
	cx_ = cx;
	cy_ = cy;
	if(::MoveWindow(hwnd,x_,y_,cx_,cy_,true) == 0)
		return false;
	return true;
}

void View::Paint(const Model& model){
	D2DCanvas cv(model.GetHwnd());
	cv.DrawRect(10,10,400,400,RGB(100,30,200));
}