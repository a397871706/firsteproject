#ifndef _POP_WIN_MEDAL_H_
#define _POP_WIN_MEDAL_H_

#include "UIlib.h"

#include "../thread/win_thread.h"

using namespace DuiLib;


class PopWinMedal : public DuiLib::WindowImplBase
{
public:
    PopWinMedal();
    ~PopWinMedal();

protected:
    virtual DuiLib::CDuiString GetSkinFolder() override;
    virtual DuiLib::CDuiString GetSkinFile() override;
    virtual LPCTSTR GetWindowClassName() const override;
    virtual void InitWindow() override;


    virtual void Notify(DuiLib::TNotifyUI& msg) override;


private:
    void DownLoad();

    WinThread thread;
};

#endif