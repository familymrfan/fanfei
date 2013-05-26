#if !defined VIEW_MODEL
#define VIEW_MODEL

#include <windows.h>
#include "model.h"

class View
{
public:
	View();
	// chaneg wnd position and size
	bool Generate(HWND hwnd,int x,int y,int cx,int cy);
	void Paint(const Model& model);
private:
	int x_,y_;
	int cx_,cy_;
};

#endif // define VIEW_MODEL