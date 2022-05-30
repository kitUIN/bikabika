#include "pch.h"
#include "KeywordBox.h"
#include "KeywordBox.g.cpp"

using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;

namespace winrt::bikabika::implementation
{
    KeywordBox::KeywordBox(hstring const& keyword, hstring const& keywordType, hstring const& icon)
    {
        m_keywords = keyword;
        m_type = keywordType;
        m_icon = icon;
    }
    hstring KeywordBox::Keyword()
    {
        return m_keywords;
    }
    hstring KeywordBox::KeywordType()
    {
        return m_type;
    }
    hstring KeywordBox::Icon()
    {
        return m_icon;
    }
}
