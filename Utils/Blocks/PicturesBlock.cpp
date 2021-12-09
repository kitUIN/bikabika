#include "pch.h"
#include "PicturesBlock.h"
#include "PicturesBlock.g.cpp"


namespace winrt::bikabika::implementation
{
    PicturesBlock::PicturesBlock(hstring const& path)
    {
        m_path = winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{path} };
    }
    hstring PicturesBlock::Order()
    {
        return m_order;
    }
    void PicturesBlock::Order(hstring const& value)
    {
        if (m_order != value)m_order = value;
    }
    winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage PicturesBlock::Path()
    {
        return m_path;
    }
    winrt::event_token PicturesBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void PicturesBlock::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
