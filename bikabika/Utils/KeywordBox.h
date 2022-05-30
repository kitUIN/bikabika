#pragma once
#include "KeywordBox.g.h"


namespace winrt::bikabika::implementation
{
    struct KeywordBox : KeywordBoxT<KeywordBox>
    {
        KeywordBox() = default;

        KeywordBox(hstring const& keyword, hstring const& keywordType, hstring const& icon);
        hstring Keyword();
        hstring KeywordType();
        hstring Icon();
    private:
        hstring m_keywords=L"";
        hstring m_icon = L"";
        hstring m_type = L"";
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct KeywordBox : KeywordBoxT<KeywordBox, implementation::KeywordBox>
    {
    };
}
