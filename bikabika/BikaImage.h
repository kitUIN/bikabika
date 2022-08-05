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
        Windows::UI::Xaml::Media::ImageSource ImgSource();
        static Windows::UI::Xaml::DependencyProperty ImageProperty() { return m_imageProperty; }
        void ImageLoaded(bool const& value);
        bool ImageLoaded();
    private:
        static Windows::UI::Xaml::DependencyProperty m_imageProperty;
        bool m_loaded = false;

    public:
        void BikaImg_ImageFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::ExceptionRoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction BikaImg_ImageOpened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void RefreshIcon_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct BikaImage : BikaImageT<BikaImage, implementation::BikaImage>
    {
    };
}
