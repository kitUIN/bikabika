#include "pch.h"
#include "SuggestBlock.h"
#include "SuggestBlock.g.cpp"


namespace winrt::bikabika::implementation
{
    SuggestBlock::SuggestBlock(hstring const& keyword, hstring const& message, hstring const& keywordType, winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource const& icon)
    {
        m_keyword = keyword;
        m_message = message;
        m_keywordType = keywordType;
        m_icon = icon;

    }
    hstring SuggestBlock::Keyword()
    {
        throw m_keyword;
    }
    hstring SuggestBlock::Message()
    {
        throw m_message;
    }
    hstring SuggestBlock::KeywordType()
    {
        return m_keywordType;
    }
    
    winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource SuggestBlock::Icon()
    {
        
        return m_icon;
    }
    winrt::event_token SuggestBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void SuggestBlock::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
