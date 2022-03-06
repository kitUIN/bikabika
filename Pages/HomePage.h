#pragma once

#include "HomePage.g.h"
#include "MainPage.h"
namespace winrt::bikabika::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    private:
        bikabika::MainPage rootPage{ MainPage::Current() };
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
