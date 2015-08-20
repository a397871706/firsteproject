#ifndef _MAIN_FORM_H_
#define _MAIN_FORM_H_

#include "../DuiLib/UIlib.h"

#include <memory>

using namespace DuiLib;
class PopWinMedal;


class MainForm : public DuiLib::WindowImplBase
{
public:
    virtual ~MainForm();

    static MainForm* GetInstance();
    DUI_DECLARE_MESSAGE_MAP()
protected:
    virtual CDuiString GetSkinFolder() override;
    virtual CDuiString GetSkinFile() override;
    virtual LPCTSTR GetWindowClassName() const override;
    virtual void InitWindow() override;
    virtual void OnClick(TNotifyUI& msg) override;
    virtual void OnFinalMessage(HWND hWnd) override;

    virtual void Notify(TNotifyUI& msg) override;    

private:
    MainForm();
    void OnStartclick();

    CLabelUI* logo_;
    CButtonUI* start_;
    POINT currentPoint_;
    CTextUI* posX_;
    CTextUI* posY_;
    HWND llkWnd_;
    RECT rc_;
    std::unique_ptr<PopWinMedal> pop_medal_;
    static MainForm* mainform_;
};

#endif