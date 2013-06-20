### Error Show ###
----

	int WINAPI _tWinMain(HINSTANCE hinstExe, HINSTANCE, PTSTR pszCmdLine, int) {

	   	HWND hwnd = FindWindow(TEXT("#32770"), TEXT("Error Show"));
	   	if (IsWindow(hwnd)) {
	      // An instance is already running, activate it and send it the new #
	      SendMessage(hwnd, ESM_POKECODEANDLOOKUP, _ttoi(pszCmdLine), 0);
	   	} else {
	      DialogBoxParam(hinstExe, MAKEINTRESOURCE(IDD_ERRORSHOW), 
	         NULL, Dlg_Proc, _ttoi(pszCmdLine));
	   	}
	   	return(0);
	}

**FindWindow**
	
	HWND FindWindow(LPCTSTR lpClassName,
    LPCTSTR lpWindowName);

查找窗口并返回窗口句柄，不会查找子窗口只查找最外层窗口，查找条件是类名（lpClassName）和窗口名（lpWindowName）匹配




