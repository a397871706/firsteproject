#include "stdafx.h"
#include "main_form.h"
#include "medal/pop_win_medal.h"

#include "dialog/dialogs.h"

#include <sstream>


DUI_BEGIN_MESSAGE_MAP(MainForm, WindowImplBase)

DUI_END_MESSAGE_MAP()
MainForm::~MainForm()
{
    if (mainform_)
        mainform_ = nullptr;
}

MainForm* MainForm::GetInstance()
{
    if (mainform_ == nullptr)
        mainform_ = new MainForm();

    return mainform_;
}

DuiLib::CDuiString MainForm::GetSkinFolder()
{
    return L"resource";
}

DuiLib::CDuiString MainForm::GetSkinFile()
{
    return L"main_form.xml";
}

LPCTSTR MainForm::GetWindowClassName() const
{
    return L"MainForm";
}

MainForm::MainForm()
    : WindowImplBase()
    , logo_()
    , pop_medal_()
    , rc_()
    , posX_()
    , posY_()
    , start_()
    , currentPoint_()
{

}

void MainForm::InitWindow()
{
    __super::InitWindow();

    logo_ = reinterpret_cast<CLabelUI*>(m_PaintManager.FindControl(L"logotitle"));
    posX_ = reinterpret_cast<CTextUI*>(m_PaintManager.FindControl(L"txt_pos_x"));
    posY_ = reinterpret_cast<CTextUI*>(m_PaintManager.FindControl(L"txt_pos_y"));
    start_ = reinterpret_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_start"));    
}

void MainForm::Notify(TNotifyUI& msg)
{
    __super::Notify(msg);
}

void MainForm::OnClick(TNotifyUI& msg)
{
    __super::OnClick(msg);
    if (start_ != nullptr && msg.pSender == start_)
    {
        OnStartclick();
    }
}

void MainForm::OnFinalMessage(HWND hWnd)
{
    delete this;
}

void MainForm::OnStartclick()
{
    OnStartGame();
}

void MainForm::OnStartGame()
{
    HWND h = ::FindWindow(L"Shell_TrayWnd", NULL);
    ::ShowWindow(h, SW_SHOW);
    return;

    HWND hWnd = ::FindWindow(NULL, L"QQ游戏 - 连连看角色版");
    if (NULL == hWnd)
#ifdef _DEBUG
        ::MessageBox(NULL, L"请运行游戏!", L"错误", MB_OK);
        return;
#else
        return;
#endif

    ::GetWindowRect(hWnd, &rc_);
    std::wostringstream s;
    s << rc_.left;
    posX_->SetText(s.str().c_str());
    s.clear();
    s << rc_.top;
    posY_->SetText(s.str().c_str());
    ::GetCursorPos(&currentPoint_);
    ::SetCursorPos(rc_.left + 646, rc_.top + 561);
    mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
    mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
    ::SetCursorPos(currentPoint_.x, currentPoint_.y);

    DWORD processid;
    ::GetWindowThreadProcessId(hWnd, &processid);
    if (processid == 0)
        return;

    HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
    if (NULL != hProcess)
    {
        //::ReadProcessMemory(hProcess,)
    }
}


MainForm* MainForm::mainform_ = nullptr;
