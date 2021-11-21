#pragma once
#include "SuggestBlock.g.h"


namespace winrt::bikabika::implementation
{
    struct SuggestBlock : SuggestBlockT<SuggestBlock>
    {
        SuggestBlock() = default;

        SuggestBlock(hstring const& keyword, hstring const& message, hstring const& keywordType, winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource const& icon);
        hstring Keyword();
        hstring Message();
        hstring KeywordType();
        winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource Icon();
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring m_keyword;
        hstring m_message;
        hstring m_keywordType;
        winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource m_icon;
        
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;


    };
}
namespace winrt::bikabika::factory_implementation
{
    struct SuggestBlock : SuggestBlockT<SuggestBlock, implementation::SuggestBlock>
    {
    };
}
