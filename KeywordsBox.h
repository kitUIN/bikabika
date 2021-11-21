#pragma once
#include "KeywordsBox.g.h"


namespace winrt::bikabika::implementation
{
    struct KeywordsBox : KeywordsBoxT<KeywordsBox>
    {
        KeywordsBox() = default;

        KeywordsBox(hstring const& keywords, hstring const& messages, hstring const& keywordType, winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& keywordIcon);
        hstring GetKeywords();
        hstring GetMessages();
        hstring GetKeywordType();
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage GetKeywordIcon();
    private:
        hstring m_keywords;
        hstring m_message;
        hstring m_type;
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_icon;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct KeywordsBox : KeywordsBoxT<KeywordsBox, implementation::KeywordsBox>
    {
    };
}
