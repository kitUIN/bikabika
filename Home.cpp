#include "pch.h"
#include "Home.h"
#if __has_include("Home.g.cpp")
#include "Home.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    Home::Home()
    {
        InitializeComponent();
    }

    int32_t Home::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Home::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Home::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
