#pragma once

#include "HomePage.g.h"

namespace winrt::bikabika::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        Windows::Foundation::IAsyncAction ContentDialogShow(hstring const& mode, hstring const& message);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
