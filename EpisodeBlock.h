#pragma once
#include "EpisodeBlock.g.h"


namespace winrt::bikabika::implementation
{
    struct EpisodeBlock : EpisodeBlockT<EpisodeBlock>
    {
        EpisodeBlock() = default;

        EpisodeBlock(hstring const& _id, hstring const& title, int32_t order, hstring const& updatedAt);
        hstring ID();
        hstring UpdatedAt();
        int32_t Order();
        hstring Title();
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring m_id;
        hstring m_title;
        int32_t m_order;
        hstring m_updatedAt;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

    };
}
namespace winrt::bikabika::factory_implementation
{
    struct EpisodeBlock : EpisodeBlockT<EpisodeBlock, implementation::EpisodeBlock>
    {
    };
}
