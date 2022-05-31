#pragma once

#include "DownloadPage.g.h"

namespace winrt::bikabika::implementation
{
    struct DownloadPage : DownloadPageT<DownloadPage>
    {
        DownloadPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct DownloadPage : DownloadPageT<DownloadPage, implementation::DownloadPage>
    {
    };
}
