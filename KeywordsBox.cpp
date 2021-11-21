#include "pch.h"
#include "KeywordsBox.h"
#include "KeywordsBox.g.cpp"


namespace winrt::bikabika::implementation
{
    KeywordsBox::KeywordsBox(hstring const& keywords, hstring const& messages, hstring const& keywordType, winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& keywordIcon)
    {
        m_keywords = keywords;
        m_message = messages;
        m_type = keywordType;
        m_icon = keywordIcon;
    }
    hstring KeywordsBox::GetKeywords()
    {
        return m_keywords;
    }
    hstring KeywordsBox::GetMessages()
    {
        return m_message;
    }
    hstring KeywordsBox::GetKeywordType()
    {
        return m_type;
    }
    winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage KeywordsBox::GetKeywordIcon()
    {
        return m_icon;
    }
}
