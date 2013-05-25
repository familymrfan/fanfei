#include <windows.h>
#include "controller.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	Controller controller;
	return controller.RunLoop();
}
