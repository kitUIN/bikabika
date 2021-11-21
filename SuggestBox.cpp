#include "pch.h"
#include "SuggestBox.h"
#include "SuggestBox.g.cpp"


namespace winrt::bikabika::implementation
{

    SuggestBox::SuggestBox(hstring const& keyword, hstring const& message, hstring const& keywordType)
    {
        m_keyword = keyword;
        m_message = message;
        m_keywordType = keywordType;

    }
    hstring SuggestBox::Keywords()
    {
        throw m_keyword;
    }
    hstring SuggestBox::Messages()
    {
        throw m_message;
    }
    hstring SuggestBox::KeywordType()
    {
        return m_keywordType;
    }

}
