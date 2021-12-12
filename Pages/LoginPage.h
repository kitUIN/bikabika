#pragma once

#include "LoginPage.g.h"


namespace winrt::bikabika::implementation
{
    struct LoginPage : LoginPageT<LoginPage>
    {
        LoginPage();
        Windows::Foundation::IAsyncAction ReadAccountJson();
        Windows::Foundation::IAsyncAction WriteAccountJson(hstring email, hstring password, hstring token, boolean isCheck);
        void ContentDialogShow(hstring const& mode, hstring const& message);
        Windows::Foundation::IAsyncAction LoginAccount();
        Windows::Foundation::IAsyncAction SetPerson();
        void LoginClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction AutoLogin();
    public:
        bikabika::BikaHttp m_bikaHttp;
        bikabika::FileCheckTool m_fileCheckTool;
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
}

