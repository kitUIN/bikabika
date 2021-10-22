#pragma once

#include "Home.g.h"

namespace winrt::bikabika::implementation
{
    struct Home : HomeT<Home>
    {
        Home();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct Home : HomeT<Home, implementation::Home>
    {
    };
}
