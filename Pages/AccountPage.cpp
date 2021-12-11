#include "pch.h"
#include "Pages/AccountPage.h"
#if __has_include("Generated Files/AccountPage.g.cpp")
#include "Generated Files/AccountPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    AccountPage::AccountPage()
    {
        InitializeComponent();
        auto localSettings = Windows::Storage::ApplicationData::Current().LocalSettings();
        winrt::Windows::Data::Json::JsonObject personInfo = unbox_value<winrt::Windows::Data::Json::JsonObject>(localSettings.Values().Lookup(L"personInfo"));
        
    }

    bikabika::UserViewModel AccountPage::MainUserViewModel()
    {
        return m_userViewModel;
    }

}
