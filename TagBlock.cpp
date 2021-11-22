#include "pch.h"
#include "TagBlock.h"
#include "TagBlock.g.cpp"


namespace winrt::bikabika::implementation
{
    TagBlock::TagBlock(hstring const& tag)
    {
        if (m_tag != tag) m_tag = tag;
    }
    hstring TagBlock::Tag()
    {
        return m_tag;
    }
    winrt::event_token TagBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void TagBlock::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
