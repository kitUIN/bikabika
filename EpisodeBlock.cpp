#include "pch.h"
#include "EpisodeBlock.h"
#include "EpisodeBlock.g.cpp"


namespace winrt::bikabika::implementation
{
    EpisodeBlock::EpisodeBlock(hstring const& _id, hstring const& title, int32_t order, hstring const& updatedAt)
    {
        m_id = _id;
        m_updatedAt = updatedAt;
        m_order = order;
        m_title = title;

    }
    hstring EpisodeBlock::ID()
    {
        return m_id;
    }
    hstring EpisodeBlock::UpdatedAt()
    {
        return m_updatedAt;
    }
    int32_t EpisodeBlock::Order()
    {
        return m_order;
    }
    hstring EpisodeBlock::Title()
    {
        return m_title;
    }
    winrt::event_token EpisodeBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void EpisodeBlock::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
