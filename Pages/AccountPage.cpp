#include "pch.h"
#include "AccountPage.h"
#if __has_include("AccountPage.g.cpp")
#include "AccountPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    AccountPage::AccountPage()
    {
        InitializeComponent();
    }

    int32_t AccountPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AccountPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AccountPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
