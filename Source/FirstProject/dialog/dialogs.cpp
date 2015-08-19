#include "stdafx.h"
#include "dialogs.h"
#include "../string/string_split.h"

#include <commdlg.h>
#include <assert.h>

OpenFileDialog::OpenFileDialog(HWND hWnd, const wchar_t* filter,
                               const wchar_t* title)
#ifndef _XDEBUG  
    : FileDialogBase()
    , hWnd_(hWnd)
    , filter_(filter)
#else
    : hWnd_(hWnd)
    , filter_(filter)
    , title_(title)
#endif

{
}

OpenFileDialog::~OpenFileDialog()
{

}

std::vector<std::wstring> OpenFileDialog::DoModel()
{
    std::wstring fileNamesBuffer;
    const int fileNameBufferSize = 2 * 1024 * 1024;
    fileNamesBuffer.resize(fileNameBufferSize);

    OPENFILENAMEW openfilename = { 0 };
    openfilename.lStructSize = sizeof(openfilename);
    openfilename.hwndOwner = hWnd_;
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
