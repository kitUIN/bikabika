#pragma once
#include "PageNumBox.g.h"


namespace winrt::bikabika::implementation
{
    struct PageNumBox : PageNumBoxT<PageNumBox>
    {
        PageNumBox(int32_t pageIndex, int32_t pages, hstring title);
        int32_t PageIndex();
        void PageIndex(int32_t value);
        int32_t Pages();
        void Pages(int32_t value); 
        hstring Title();
        void Title(hstring value);
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        int32_t m_pageIndex;
        int32_t m_pages;
        hstring m_title;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct PageNumBox : PageNumBoxT<PageNumBox, implementation::PageNumBox>
    {
    };
}
