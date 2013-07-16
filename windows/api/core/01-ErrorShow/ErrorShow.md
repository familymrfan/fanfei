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

查找窗口并返回窗口句柄，不会查找子窗口只查找最外层窗口，查找条件是类名（lpClassName）和窗口名（lpWindowName）匹配,EnumWindows可以枚举所有的最外层窗口

**SendMessage 和 PostMessage**

	LRESULT SendMessage(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);

PostMessage 是异步的，SendMessage 是同步的。
PostMessage 只把消息放入队列，不管消息是否被处理就返回，消息可能不被处理；
而 SendMessage则是直接调用winproc，等待消息被处理完了之后才返回，如果消息不被处理，发送消息的线程将一直被阻塞

如果在不同线程内，SendMessage 发送消息到目标窗口所属线程的消息队列，然后发送消息的线程在 USER32.DLL 模块内监视和等待消息处理，直到目标窗口处理完返回。SendMessage 在返回前还做了很多工作，比如，响应别的线程向它 SendMessage。Post 到别的线程时，最好用 PostThreadMessage 代替 PostMessage，PostMessage 的 hWnd 参数可以是 NULL，等效于 PostThreadMessage + GetCurrentThreadId。Post WM_QUIT 时，应使用 PostQuitMessage 代替。

**DialogBoxParam**

	INT_PTR DialogBoxParam(
	HINSTANCE hInstance,
    LPCTSTR lpTemplateName,
    HWND hWndParent,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam
	);

从资源里创建模态对话框，hInstance就是含有资源的那个exe，lpTemplateName资源的名称，可以使用例如上面的MAKEINTRESOURCE(IDD_ERRORSHOW)

DialogBoxParam函数用CreateWindowEx函数创建对话框，然后把一个WM\_INITDIALOG消息传递到对话框窗口过程函数，如果资源指定DS\_SETFONT类型，DialogBoxParam函数把一个WM_SETFONT消息传递到对话框过程。(不管模板是否指定WS\_VISIBLE类型）,对话框显示，父窗口窗口失效。对话框启动它本身的消息循环。当对话框应用程序调用EndDialog函数时，DialogBoxParam函数清除对话框中止消息循环；使拥有窗口生效（如果以前有效），且返回函数EndDialog的调用中的nReSUlt参数。

和DialogBox是一个东西

	INT_PTR WINAPI Dlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

   	switch (uMsg) {
      chHANDLE_DLGMSG(hwnd, WM_INITDIALOG, Dlg_OnInitDialog);
      chHANDLE_DLGMSG(hwnd, WM_COMMAND,    Dlg_OnCommand);

   	case ESM_POKECODEANDLOOKUP:
      SetDlgItemInt(hwnd, IDC_ERRORCODE, (UINT) wParam, FALSE);
      FORWARD_WM_COMMAND(hwnd, IDOK, GetDlgItem(hwnd, IDOK), BN_CLICKED, 
         PostMessage);
      SetForegroundWindow(hwnd);
      break;
   	}

   	return(FALSE);
	}

**chHANDLE_DLGMSG消息分流器**
	
   	#define chHANDLE_DLGMSG(hWnd, message, fn)                 \
   	case (message): return (SetDlgMsgResult(hWnd, uMsg,     \
      HANDLE_##message((hWnd), (wParam), (lParam), (fn))))

参见 

[http://blog.csdn.net/jasonm2008/article/details/3869296](http://blog.csdn.net/jasonm2008/article/details/3869296)

[http://blog.pfan.cn/lym51/29232.html](http://blog.pfan.cn/lym51/29232.html)

[http://blog.csdn.net/xujiezhige/article/details/6329545](http://blog.csdn.net/xujiezhige/article/details/6329545)





