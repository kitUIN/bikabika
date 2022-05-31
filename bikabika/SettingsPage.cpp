#include "pch.h"
#include "SettingsPage.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    SettingsPage::SettingsPage()
    {
        InitializeComponent();
    }

    int32_t SettingsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SettingsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void SettingsPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
