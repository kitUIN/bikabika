#pragma once

#include "UserPage.g.h"

namespace winrt::bikabika::implementation
{
    struct UserPage : UserPageT<UserPage>
    {
        UserPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct UserPage : UserPageT<UserPage, implementation::UserPage>
    {
    };
}
