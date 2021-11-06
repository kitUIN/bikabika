#pragma once

#include "Login.g.h"

namespace winrt::bikabika::implementation
{
    struct Login : LoginT<Login>
    {
        Login();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        Windows::Foundation::IAsyncAction ReadAccountJson();

        Windows::Foundation::IAsyncAction CreateAccountJson(hstring email, hstring password, boolean isCheck);

        //Windows::Foundation::IAsyncOperation<winrt::hstring>  ReadAccountJson();

      
        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct Login : LoginT<Login, implementation::Login>
    {
    };
}
