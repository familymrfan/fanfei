#include "dialog_model.h"
#include "resource.h"
#include "res.h"

DialogModel::DialogModel()
	:proc_(nullptr),hwnd_(NULL){

}

bool DialogModel::Generate(){
	HINSTANCE hint = ::GetModuleHandle(NULL);
	hwnd_ = ::CreateDialog(hint,MAKEINTRESOURCE(IDD_DIALOG),NULL,proc_);
	if(hwnd_ == NULL){
		int e = ::GetLastError ();
		return false;
	}
	return true;
}