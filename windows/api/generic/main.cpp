#include <windows.h>
#include "controller.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	Controller controller1;
	MSG  msg;
	int status;
	while ((status = ::GetMessage (&msg, 0, 0, 0)) != 0)
	{
		if (status == -1)
			return false;
		::TranslateMessage (&msg);
		::DispatchMessage (&msg);
	}
	return msg.wParam;
}
