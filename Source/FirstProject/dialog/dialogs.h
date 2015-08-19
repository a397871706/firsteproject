#ifndef _DIALOGS_H_
#define _DIALOGS_H_

#include <vector>
#include <string>

#ifndef _XDEBUG
class FileDialogBase;

class FileDialogHook
{
public:
    FileDialogHook();
    ~FileDialogHook();
};


class FileDialogBase
{
public:
    virtual std::vector<std::wstring> DoModel() = 0;
protected:
    friend class FileDialogHook;
};
#endif

class OpenFileDialog 
#ifndef _XDEBUG 
    : public FileDialogBase 
#endif
{
public:
    OpenFileDialog(HWND hWnd, const wchar_t* filter, 
                   const wchar_t* title = NULL);
    ~OpenFileDialog();
#ifndef _XDEBUG
    virtual std::vector<std::wstring> DoModel() override;
#else
    std::vector<std::wstring> DoModel();
#endif

private:
    HWND hWnd_;
    const wchar_t* filter_;
    const wchar_t* title_;

};

/*class SaveFileDialog
{
public:
    SaveFileDialog(HWND hWnd, const wchar_t* filter, 
                   const wchar_t* title = NULL);
    ~SaveFileDialog();

    std::wstring DoModel();


};*/

#endif