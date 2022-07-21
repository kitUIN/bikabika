#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "BikaImage.g.h"

namespace winrt::bikabika::implementation
{
    struct BikaImage : BikaImageT<BikaImage>
    {
        BikaImage();

        winrt::BikaClient::Blocks::ImageBlock ImgBlock();
        void ImgBlock(winrt::BikaClient::Blocks::ImageBlock const& value);

        static Windows::UI::Xaml::DependencyProperty ImageProperty() { return m_imageProperty; }
        static void OnBlockChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&);
        Windows::Foundation::IAsyncAction ImgLoad();
        bool ImageLoaded();
        void ImageLoaded(bool const& value);
    private:
        bikabika::MainPage rootPage{ MainPage::Current() };
        static Windows::UI::Xaml::DependencyProperty m_imageProperty;
        bool m_loaded = false;
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct BikaImage : BikaImageT<BikaImage, implementation::BikaImage>
    {
    };
}
