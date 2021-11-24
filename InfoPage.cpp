#include "pch.h"
#include "InfoPage.h"
#if __has_include("InfoPage.g.cpp")
#include "InfoPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    InfoPage::InfoPage()
    {
        InitializeComponent();
    }

    int32_t InfoPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void InfoPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void InfoPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
