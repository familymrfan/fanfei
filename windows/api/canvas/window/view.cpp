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
	PaintCanvas cv(model.GetHwnd());
	
	cv.DrawRect(10,10,400,400,RGB(100,30,200));
	cv.DrawRound(20,20,200,200,RGB(200,130,100));
	cv.DrawRound(30,30,100,100,RGB(100,130,100));
	cv.DrawPie(30,30,100,100,
		0,0,
		30,0,RGB(130,200,100));
	cv.DrawText(L"123",0,0);
}