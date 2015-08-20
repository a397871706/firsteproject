#include "stdafx.h"
#include "dialogs.h"
#include "../string/string_split.h"

#include <commdlg.h>
#include <assert.h>

OpenFileDialog::OpenFileDialog(const wchar_t* filter,
                               const wchar_t* title)
#ifndef _XDEBUG  
    : FileDialogBase()
    , hWnd_(hWnd)
    , filter_(filter)
#else
    : filter_(filter)
    , title_(title)
#endif

{
}

OpenFileDialog::~OpenFileDialog()
{

}

std::vector<std::wstring> OpenFileDialog::DoModel(HWND parert)
{
    std::wstring fileNamesBuffer;
    const int fileNameBufferSize = 2 * 1024 * 1024;
    fileNamesBuffer.resize(fileNameBufferSize);

    OPENFILENAMEW openfilename = { 0 };
    openfilename.lStructSize = sizeof(openfilename);
    openfilename.hwndOwner = parert;
    openfilename.lpstrFilter = filter_;
    openfilename.lpstrCustomFilter = NULL;
    openfilename.nFilterIndex = 1;
    openfilename.lpstrFile = &fileNamesBuffer[0];
    openfilename.nMaxFile = fileNamesBuffer.length();
    openfilename.lpstrTitle = title_;
    openfilename.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_FILEMUSTEXIST |
        OFN_PATHMUSTEXIST;
    std::vector<std::wstring> result;
    if (GetOpenFileNameW(&openfilename))
    {
        auto parserFileName = [](wchar_t* source,
                                 std::vector<std::wstring>* result)
        {
            wchar_t* data = source;
            do
            {
                if (!*(data++))
                {
                    *(data - 1) = '*';
                    if (!*data)
                        break;
                }
            } while (true);
            wstring split(source);
            split.erase(split.length() - 1);
            vector<wstring> splitv;
            String::SplitString(split, L'*', &splitv);
            assert(!splitv.empty());
            wstring filepath = *(splitv.begin()) + L'\\';
            for (auto i = splitv.begin() + 1; i != splitv.end(); ++i)
            {
                result->push_back(filepath + *i);
            }
        };

        fileNamesBuffer[fileNameBufferSize - 1] = '\0';
        fileNamesBuffer[fileNameBufferSize - 2] = '\0';
        parserFileName(&fileNamesBuffer[0], &result);
    }

    return std::move(result);
}

SaveFileDialog::SaveFileDialog(const wchar_t* filter, 
                               const std::wstring& fileTitle, 
                               const std::wstring& dialogTile, 
                               const std::wstring& defaultFileExt)
    : fileTitle_(fileTitle)
    , filter_(filter)
    , dialogTile_(dialogTile)
    , defaultFileExt_(defaultFileExt)
{

}

SaveFileDialog::~SaveFileDialog()
{

}

std::wstring SaveFileDialog::DoModel(HWND parert)
{
    wstring fileName = fileTitle_;
    fileName.resize(MAX_PATH);

    OPENFILENAME params = { 0 };
    params.lStructSize = sizeof(params);
    params.hwndOwner = parert;
    params.lpstrFilter = filter_;
    params.lpstrCustomFilter = NULL;
    params.nFilterIndex = 0;
    params.lpstrFile = &fileName[0];
    params.nMaxFile = fileName.length();
    params.lpstrTitle = NULL;
    params.Flags = OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;
    params.lpstrDefExt = defaultFileExt_.c_str();

    wstring result;
    if (GetSaveFileNameW(&params))
        result = params.lpstrFile;

    return std::move(result);
}
