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
    , medal_()
    , pop_medal_()
{

}

void MainForm::InitWindow()
{
    __super::InitWindow();

    logo_ = reinterpret_cast<CLabelUI*>(m_PaintManager.FindControl(L"logotitle"));
    assert(logo_);    
    logo_->SetText(L"J Z");
    medal_ = reinterpret_cast<CButtonUI*>(m_PaintManager.FindControl(L"medal"));
    assert(medal_);
    medal_->SetToolTip(L"未领取勋章的、领取后更安全。");
}

void MainForm::Notify(TNotifyUI& msg)
{
    __super::Notify(msg);
}

void MainForm::OnClick(TNotifyUI& msg)
{
    __super::OnClick(msg);
    if (msg.pSender->GetName() == L"medal")
    {
        if (!pop_medal_)
            pop_medal_.reset(new PopWinMedal());

        pop_medal_->ShowWindow();
        pop_medal_->CenterWindow();
    }
}

void MainForm::OnFinalMessage(HWND hWnd)
{
    delete this;
}

MainForm* MainForm::mainform_ = nullptr;
