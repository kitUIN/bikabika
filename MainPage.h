#pragma once

#include "MainPage.g.h"

namespace winrt::bikabika::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
        int32_t MyProperty();
        void MyProperty(int32_t value);
    private:
        Windows::UI::Composition::ContainerVisual GetVisual(Windows::UI::Xaml::UIElement element);
    };

}

namespace winrt::bikabika::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {

    };
}
