#include "model.h"
#include "res.h"
#include "resource.h"

Model::Model(){
	hwnd_			= 0;
	dwStyle_		= WS_OVERLAPPEDWINDOW;
	proc_			= nullptr;
}

bool Model::Generate(){
	WNDCLASSEX wndclass;
	// Provide reasonable default values
	wndclass.cbSize = sizeof (WNDCLASSEX);
	wndclass.style = 0;
	wndclass.hInstance = ::GetModuleHandle(NULL);
	wndclass.lpszClassName = ResString(wndclass.hInstance,IDS_CLASS);
	wndclass.lpfnWndProc = proc_;
	wndclass.hIcon = ResIcon(wndclass.hInstance,IDI_ICON);
	wndclass.hIconSm = ResIcon(wndclass.hInstance,IDI_ICON);
	wndclass.lpszMenuName = MAKEINTRESOURCE (IDR_MENU);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = reinterpret_cast<HBRUSH> (COLOR_WINDOW + 1);
	wndclass.hCursor = ::LoadCursor (0, IDC_ARROW);

	if (::RegisterClassEx (&wndclass) == 0)
		return false;

	hwnd_ = ::CreateWindowEx(0,wndclass.lpszClassName,ResString(wndclass.hInstance,IDS_CAPTION),
		dwStyle_,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,0,wndclass.hInstance,0);

	if(hwnd_ == NULL)
		return false;
	return true;
}