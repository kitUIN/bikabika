#include "pch.h"
#include "BikaImage.h"
#if __has_include("BikaImage.g.cpp")
#include "BikaImage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    BikaImage::BikaImage()
    {
        DefaultStyleKey(winrt::box_value(L"bikabika.BikaImage"));
        InitializeComponent();
    }

    Windows::UI::Xaml::DependencyProperty BikaImage::m_imageProperty =
        Windows::UI::Xaml::DependencyProperty::Register(
            L"ImgBlock",
            winrt::xaml_typename<winrt::BikaClient::Blocks::ImageBlock>(),
            winrt::xaml_typename<bikabika::BikaImage>(),
            Windows::UI::Xaml::PropertyMetadata{ nullptr }
    );
    winrt::BikaClient::Blocks::ImageBlock BikaImage::ImgBlock()
    {
        return winrt::unbox_value<winrt::BikaClient::Blocks::ImageBlock>(GetValue(m_imageProperty));
    }

    void BikaImage::ImgBlock(winrt::BikaClient::Blocks::ImageBlock const& value)
    {
        SetValue(m_imageProperty, winrt::box_value(value));
    }
    void BikaImage::OnBlockChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&)
    {
        if (bikabika::BikaImage theControl{ d.try_as<bikabika::BikaImage>() })
        {

        }
    }
    Windows::Foundation::IAsyncAction BikaImage::ImgLoad()
    {
        
    }
    bool BikaImage::ImageLoaded()
    {
        return m_loaded;
    }
    void BikaImage::ImageLoaded(bool const& value)
    {
        m_loaded = value;
    }
}
