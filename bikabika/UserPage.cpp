#include "pch.h"
#include "UserPage.h"
#if __has_include("UserPage.g.cpp")
#include "UserPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    UserPage::UserPage()
    {
        InitializeComponent();
    }

    int32_t UserPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void UserPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void UserPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
