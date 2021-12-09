#include "pch.h"
#include "PageNumBox.h"
#include "PageNumBox.g.cpp"


namespace winrt::bikabika::implementation
{

    PageNumBox::PageNumBox(int32_t pageIndex, int32_t pages, hstring title)
    {
        m_pageIndex = pageIndex;
        m_pages = pages;
        m_title = title;
    }
    int32_t PageNumBox::PageIndex()
    {
        return m_pageIndex;
    }
    void PageNumBox::PageIndex(int32_t value)
    {
        if (m_pageIndex != value) { 
            m_pageIndex = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"PageIndex" });
        }
    }
    int32_t PageNumBox::Pages()
    {
        return m_pages;
    }
    void PageNumBox::Pages(int32_t value)
    {
        if (m_pages != value) {
            m_pages = value;
        
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Pages" });
        }
    }
    hstring PageNumBox::Title()
    {
        return m_title;
    }
    void PageNumBox::Title(hstring value)
    {
        if (m_title != value) {
            m_title = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Title" });
        }
    }
    winrt::event_token PageNumBox::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void PageNumBox::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
