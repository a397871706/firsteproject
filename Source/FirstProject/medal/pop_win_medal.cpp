#include "stdafx.h"
#include "pop_win_medal.h"

#include "StdoutLog.h"
#include "SocketHandler.h"
#include "HttpGetSocket.h"



PopWinMedal::PopWinMedal()
    : WindowImplBase()
    , thread("Medal")
{
    thread.Start();
    //auto fun = std::bind(&PopWinMedal::DownLoad, this);
    //thread.AddTask(fun);
}

PopWinMedal::~PopWinMedal()
{
    thread.Stop();
}

DuiLib::CDuiString PopWinMedal::GetSkinFolder()
{
    return L"";
}

DuiLib::CDuiString PopWinMedal::GetSkinFile()
{
    return L"";
}

LPCTSTR PopWinMedal::GetWindowClassName() const
{
    return L"";
}

void PopWinMedal::InitWindow()
{
    __super::InitWindow();
}

void PopWinMedal::Notify(DuiLib::TNotifyUI& msg)
{
    __super::Notify(msg);
}

void PopWinMedal::DownLoad()
{
    StdoutLog log;    
    SocketHandler s(&log);
    HttpGetSocket get(s, "http://www.baidu.com");
    get.DoConnect();

    auto f = std::bind(&PopWinMedal::DownLoad, this);
    thread.AddTask(f);
}
