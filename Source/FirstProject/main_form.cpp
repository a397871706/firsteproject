#include "stdafx.h"
#include "main_form.h"
#include "medal/pop_win_medal.h"


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
    , llkWnd_()
    , rc_()
    , posX_()
    , posY_()
{

}

void MainForm::InitWindow()
{
    __super::InitWindow();

    logo_ = reinterpret_cast<CLabelUI*>(m_PaintManager.FindControl(L"logotitle"));
    assert(logo_);    
    logo_->SetText(L"连连看外怪");
    posX_ = reinterpret_cast<CTextUI*>(m_PaintManager.FindControl(L"txt_pos_x"));
    posY_ = reinterpret_cast<CTextUI*>(m_PaintManager.FindControl(L"txt_pos_y"));
}

void MainForm::Notify(TNotifyUI& msg)
{
    __super::Notify(msg);
}

void MainForm::OnClick(TNotifyUI& msg)
{
    __super::OnClick(msg);
    if (msg.pSender->GetName() == L"btn_start")
    {
        llkWnd_ = ::FindWindow(L"", L"QQ游戏 - 连连看角色版");
        ::GetWindowRect(llkWnd_, &rc_);
        //::ScreenToClient()
    }
}

void MainForm::OnFinalMessage(HWND hWnd)
{
    delete this;
}

MainForm* MainForm::mainform_ = nullptr;
