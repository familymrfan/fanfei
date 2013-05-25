#include "model.h"

Model::Model(){
	class_name_		= L"generic";
	window_caption_ = L"generic";
	hwnd_			= 0;
	dwStyle_		= WS_OVERLAPPEDWINDOW;
	proc_			= nullptr;
}

bool Model::Generate(){
	WNDCLASSEX wndclass;
	// Provide reasonable default values
	wndclass.cbSize = sizeof (WNDCLASSEX);
	wndclass.style = 0;
	wndclass.lpszClassName = class_name_.c_str();
	wndclass.hInstance = ::GetModuleHandle(NULL);
	wndclass.lpfnWndProc = proc_;
	wndclass.hIcon = 0;
	wndclass.hIconSm = 0;
	wndclass.lpszMenuName = 0;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = reinterpret_cast<HBRUSH> (COLOR_WINDOW + 1);
	wndclass.hCursor = ::LoadCursor (0, IDC_ARROW);

	if (::RegisterClassEx (&wndclass) == 0)
		return false;

	hwnd_ = ::CreateWindowEx(0,wndclass.lpszClassName,window_caption_.c_str(),
		dwStyle_,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,0,wndclass.hInstance,0);

	if(hwnd_ == NULL)
		return false;
	return true;
}