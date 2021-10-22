#pragma once

#include "Login.g.h"

namespace winrt::bikabika::implementation
{
    struct Login : LoginT<Login>
    {
        Login();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct Login : LoginT<Login, implementation::Login>
    {
    };
}
