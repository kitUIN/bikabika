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
        NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled);
    }

    

}
