#ifndef _STRING_SPLIT_H_
#define _STRING_SPLIT_H_

#include <string>
#include <vector>

using std::wstring;
using std::string;
using std::vector;

namespace String
{
enum TrimPositions
{
    TRIM_NONE = 0,
    TRIM_LEADING = 1 << 0,
    TRIM_TRAILING = 1 << 1,
    TRIM_ALL = TRIM_LEADING | TRIM_TRAILING,
};
    
TrimPositions TrimWhitespace(const string& input, TrimPositions positions,
                             std::string* output);

TrimPositions TrimWhitespace(const wstring& input, TrimPositions positions,
                             std::wstring* output);

void SplitString(const wstring& str, wchar_t c, vector<wstring>* r);

void SplitString(const string& str, char c, vector<string>* r);
}

#endif