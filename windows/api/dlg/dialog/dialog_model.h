#if !defined DIALOG_MODEL_H
#define DIALOG_MODEL_H

#include <windows.h>

class DialogModel
{
	typedef INT_PTR (CALLBACK* Proc)(HWND, UINT, WPARAM, LPARAM);
public:
	DialogModel();
	void AddProc(const Proc proc){
		proc_ = proc;
	}
	bool Generate(); // if return true you can get a hwnd ,using GetHwnd
	HWND GetHwnd() const {
		return hwnd_;
	}
protected:
	Proc proc_;
private:
	HWND hwnd_;
};

#endif