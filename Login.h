#pragma once

#include "Login.g.h"
#include "MainPage.h"
namespace winrt::bikabika::implementation
{
    struct Login : LoginT<Login>
    {
        Login();
        Windows::Foundation::IAsyncAction ReadAccountJson();

        Windows::Foundation::IAsyncAction WriteAccountJson(hstring email, hstring password, hstring token, boolean isCheck);


        bikabika::BikaHttp BikaHttpAPI();
        //Windows::Foundation::IAsyncOperation<winrt::hstring>  ReadAccountJson();

      
        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    private:
        bikabika::BikaHttp m_bikaHttp;
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct Login : LoginT<Login, implementation::Login>
    {
    };
}
