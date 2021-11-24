#pragma once

#include "InfoPage.g.h"

namespace winrt::bikabika::implementation
{
    struct InfoPage : InfoPageT<InfoPage>
    {
        InfoPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct InfoPage : InfoPageT<InfoPage, implementation::InfoPage>
    {
    };
}
