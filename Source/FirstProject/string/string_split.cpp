#include "stdafx.h"
#include "string_split.h"


namespace String
{
#define WHITESPACE_UNICODE \
  0x0009, /* CHARACTER TABULATION */      \
  0x000A, /* LINE FEED (LF) */            \
  0x000B, /* LINE TABULATION */           \
  0x000C, /* FORM FEED (FF) */            \
  0x000D, /* CARRIAGE RETURN (CR) */      \
  0x0020, /* SPACE */                     \
  0x0085, /* NEXT LINE (NEL) */           \
  0x00A0, /* NO-BREAK SPACE */            \
  0x1680, /* OGHAM SPACE MARK */          \
  0x2000, /* EN QUAD */                   \
  0x2001, /* EM QUAD */                   \
  0x2002, /* EN SPACE */                  \
  0x2003, /* EM SPACE */                  \
  0x2004, /* THREE-PER-EM SPACE */        \
  0x2005, /* FOUR-PER-EM SPACE */         \
  0x2006, /* SIX-PER-EM SPACE */          \
  0x2007, /* FIGURE SPACE */              \
  0x2008, /* PUNCTUATION SPACE */         \
  0x2009, /* THIN SPACE */                \
  0x200A, /* HAIR SPACE */                \
  0x2028, /* LINE SEPARATOR */            \
  0x2029, /* PARAGRAPH SEPARATOR */       \
  0x202F, /* NARROW NO-BREAK SPACE */     \
  0x205F, /* MEDIUM MATHEMATICAL SPACE */ \
  0x3000, /* IDEOGRAPHIC SPACE */         \
  0

const wchar_t kWhitespaceUTF16[] = {
     WHITESPACE_UNICODE
};

const char kWhitespaceASCII[] = {
    0x09,    // CHARACTER TABULATION
    0x0A,    // LINE FEED (LF)
    0x0B,    // LINE TABULATION
    0x0C,    // FORM FEED (FF)
    0x0D,    // CARRIAGE RETURN (CR)
    0x20,    // SPACE
    0
};

namespace
{
template <typename STR>
void SplitStringT(const STR& str, const typename STR::value_type s,
                  bool trim_whitespace, vector<STR>* r)
{
    r->clear();
    size_t last = 0;
    size_t c = str.size();
    for (size_t i = 0; i <= c; ++i)
    {
        if (i == c || str[i] == s)
        {
            STR tmp(str, last, i - last);
            if (trim_whitespace)
                TrimWhitespace(tmp, TRIM_ALL, &tmp);

            if (i != c || !r->empty() || !tmp.empty())
                r->push_back(tmp);

            last = i + 1;
        }
    }
}

template<typename STR>
TrimPositions TrimStringT(const STR& input, const STR& trim_chars,
                          TrimPositions positions, STR* output)
{
    const size_t last_char = input.length() - 1;
    const size_t first_good_char = (positions & TRIM_LEADING) ?
        input.find_first_not_of(trim_chars) : 0;
    const size_t last_good_char = (positions & TRIM_TRAILING) ?
        input.find_last_not_of(trim_chars) : last_char;

    if (input.empty() ||
        (first_good_char == STR::npos) || (last_good_char == STR::npos))
    {
        bool input_was_empty = input.empty();  // in case output == &input
        output->clear();
        return input_was_empty ? TRIM_NONE : positions;
    }

    *output =
        input.substr(first_good_char, last_good_char - first_good_char + 1);

    return static_cast<TrimPositions>(
        ((first_good_char == 0) ? TRIM_NONE : TRIM_LEADING) |
        ((last_good_char == last_char) ? TRIM_NONE : TRIM_TRAILING));
}
}

void SplitString(const wstring& str, wchar_t c, vector<wstring>* r)
{
    SplitStringT(str, c, true, r);
}

void SplitString(const string& str, char c, vector<string>* r)
{
    SplitStringT(str, c, true, r);
}

TrimPositions TrimWhitespace(const string& input, 
                                     TrimPositions positions, 
                                     std::string* output)
{
    return TrimStringT(input, std::string(kWhitespaceASCII), positions, output);    
}

TrimPositions TrimWhitespace(const wstring& input,
                                     TrimPositions positions,
                                     std::wstring* output)
{
    return TrimStringT(input, wstring(kWhitespaceUTF16), positions, output);
}

}