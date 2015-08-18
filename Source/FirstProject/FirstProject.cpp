// FirstProject.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "FirstProject.h"
#include "main_form.h"

#include "UIlib.h"
#include <assert.h>

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    HRESULT Hr = ::CoInitialize(NULL);
    if (FAILED(Hr)) return 0;

    DuiLib::CPaintManagerUI::SetInstance(hInstance);
    MainForm* mainform = MainForm::GetInstance();
    assert(mainform);
    if (!mainform)
        return 0;

    mainform->Create(NULL, L"", UI_WNDSTYLE_FRAME, WS_EX_LTRREADING);
    mainform->CenterWindow();
    mainform->ShowWindow();
    CPaintManagerUI::MessageLoop();
    ::CoUninitialize();
    return 0;
}