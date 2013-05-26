#if !defined CANVAS_H
#define  CANVAS_H

#include <windows.h>
#include <string>

class Canvas
{
public:
	operator HDC () const {
		return hdc_;
	}

	void DrawText(std::wstring text,int x,int y){
		::TextOut(hdc_,x,y,text.c_str(),text.size());
	}
protected:
	Canvas(HDC hdc):hdc_(hdc){}
private:
	HDC hdc_;
};

class PaintCanvas :public Canvas
{
public:
	PaintCanvas(HWND hwnd)
		: Canvas(::BeginPaint(hwnd,&ps_)){

	}

	~PaintCanvas(){
		::EndPaint(hwnd_,&ps_);
	}
protected:
	PAINTSTRUCT ps_;
	HWND hwnd_;
};

#endif // define CANVAS_H