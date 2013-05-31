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

	void DrawPie(int x,int y,int width,int height,int x1,int y1,int x2,int y2,COLORREF color = RGB(0,0,0)){
		auto brush = ::CreateSolidBrush(color);
		auto old_brush = ::SelectObject(hdc_,brush);
		::Pie(hdc_,x,y,x + width,y + height,x1,y1,x2,y2);
		::SelectObject(hdc_,old_brush);
	}

	void DrawRound(int x,int y,int width,int height,COLORREF color = RGB(0,0,0)){
		auto brush = ::CreateSolidBrush(color);
		auto old_brush = ::SelectObject(hdc_,brush);
		::Ellipse(hdc_,x, y, x + width, y + height);
		::SelectObject(hdc_,old_brush);
	}

	void DrawRect(int x,int y,int width,int height,COLORREF color = RGB(0,0,0)){
		auto brush = ::CreateSolidBrush(color);
		auto old_brush = ::SelectObject(hdc_,brush);
		::Rectangle (hdc_, x, y, x + width, y + height);
		::SelectObject(hdc_,old_brush);
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