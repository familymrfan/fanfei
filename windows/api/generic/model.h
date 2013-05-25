#if !defined MODEL_H
#define MODEL_H

#include <windows.h>
#include <string>
#include <functional>

class Model
{
	typedef LRESULT (CALLBACK* Proc)(HWND, UINT, WPARAM, LPARAM);
public:
	Model();
	void AddProc(const Proc proc){
		proc_ = proc;
	}
	bool Generate(); // if return true you can get a hwnd ,using GetHwnd
	HWND GetHwnd() const {
		return hwnd_;
	}
protected:
	DWORD dwStyle_;
	Proc proc_;
private:
	HWND hwnd_;
};


#endif // define MODEL_H