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
    OpenFileDialog(const wchar_t* filter, 
                   const wchar_t* title = NULL);
    ~OpenFileDialog();
#ifndef _XDEBUG
    virtual std::vector<std::wstring> DoModel() override;
#else
    std::vector<std::wstring> DoModel(HWND parert);
#endif

private:
    const wchar_t* filter_;
    const wchar_t* title_;

};

class SaveFileDialog
{
public:
    SaveFileDialog(const wchar_t* filter, 
                   const std::wstring& fileTitle, 
                   const std::wstring& dialogTile,
                   const std::wstring& defaultFileExt);

    ~SaveFileDialog();

    std::wstring DoModel(HWND parerts);

private:
    const wchar_t* filter_;
    std::wstring fileTitle_;
    std::wstring dialogTile_;
    std::wstring defaultFileExt_;
};

#endif