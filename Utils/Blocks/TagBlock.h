#pragma once
#include "TagBlock.g.h"


namespace winrt::bikabika::implementation
{
    struct TagBlock : TagBlockT<TagBlock>
    {
        TagBlock() = default;
        TagBlock(hstring const& tag);
        hstring Tag();
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring m_tag;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

    };
}
namespace winrt::bikabika::factory_implementation
{
    struct TagBlock : TagBlockT<TagBlock, implementation::TagBlock>
    {
    };
}
