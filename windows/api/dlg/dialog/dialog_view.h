#if !defined DIALOG_VIEW
#define  DIALOG_VIEW

#include "dialog_model.h"

class DialogView
{
public:
	DialogView();
	// chaneg wnd position and size
	bool Generate(HWND hwnd,int x,int y,int cx,int cy);
	void Paint(const DialogModel& model);
private:
	int x_,y_;
	int cx_,cy_;
};

#endif