#pragma once
#include "SuggestBox.g.h"


namespace winrt::bikabika::implementation
{
    struct SuggestBox : SuggestBoxT<SuggestBox>
    {

        SuggestBox(hstring const& keyword, hstring const& message, hstring const& keywordType);
        hstring Keywords();
        hstring Messages();
        hstring KeywordType();
    private:
        hstring m_message;
        hstring m_keyword;
        hstring m_keywordType;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct SuggestBox : SuggestBoxT<SuggestBox, implementation::SuggestBox>
    {
    };
}
