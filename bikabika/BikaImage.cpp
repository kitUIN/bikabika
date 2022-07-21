#include "pch.h"
#include "BikaImage.h"
#if __has_include("BikaImage.g.cpp")
#include "BikaImage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
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
        BikaImg().Source(value.Img());
    }

    Windows::UI::Xaml::Media::ImageSource BikaImage::ImgSource()
    {
        return BikaImg().Source();
    }
    void BikaImage::ImageLoaded(bool const& value)
    {
        m_loaded = value;
    }
    bool BikaImage::ImageLoaded()
    {
        return m_loaded;
    }
}
void winrt::bikabika::implementation::BikaImage::BikaImg_ImageFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::ExceptionRoutedEventArgs const& e)
{
    ImageLoaded(false);
    RefreshIcon().Visibility(Visibility::Visible);
}


Windows::Foundation::IAsyncAction winrt::bikabika::implementation::BikaImage::BikaImg_ImageOpened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    ImageLoaded(true);
    RefreshIcon().Visibility(Visibility::Collapsed);
    // 通过Xaml界面获取位图的大小不对
    //winrt::BikaClient::Blocks::ImageBlock imgBlock = ImgBlock();
    //winrt::Windows::UI::Xaml::Media::Imaging::RenderTargetBitmap bitmap;
    //co_await bitmap.RenderAsync(sender.as<UIElement>());
    //IBuffer pixels = co_await bitmap.GetPixelsAsync();

    //Windows::Storage::ApplicationDataContainer settings = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Settings", Windows::Storage::ApplicationDataCreateDisposition::Always);
    //if (!settings.Values().HasKey(L"CacheFolder"))
    //{
    //    Windows::Storage::StorageFolder storageFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
    //    Windows::Storage::StorageFolder downloadFolder = co_await storageFolder.CreateFolderAsync(L"Cache");
    //    settings.Values().Insert(L"CacheFolder", box_value(downloadFolder.Path()));
    //}
    //Windows::Storage::StorageFolder storageFolder = co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(settings.Values().Lookup(L"CacheFolder").as<hstring>());
    //Windows::Storage::StorageFile imgFile = co_await storageFolder.CreateFileAsync(imgBlock.OriginalName(), Windows::Storage::CreationCollisionOption::ReplaceExisting);
    //Windows::Storage::Streams::IRandomAccessStream stream{ co_await imgFile.OpenAsync(Windows::Storage::FileAccessMode::ReadWrite) };
    //auto softwareBitmap = winrt::Windows::Graphics::Imaging::SoftwareBitmap::CreateCopyFromBuffer(pixels, winrt::Windows::Graphics::Imaging::BitmapPixelFormat::Bgra8, (uint32_t)200, (uint32_t)200, winrt::Windows::Graphics::Imaging::BitmapAlphaMode::Ignore);
    //auto propertySet = winrt::Windows::Graphics::Imaging::BitmapPropertySet();
    //winrt::Windows::Graphics::Imaging::BitmapTypedValue qualityValue(box_value(1.0), Windows::Foundation::PropertyType::Single);
    //propertySet.Insert(L"ImageQuality", qualityValue);
    //winrt::Windows::Graphics::Imaging::BitmapEncoder encoder = co_await winrt::Windows::Graphics::Imaging::BitmapEncoder::CreateAsync(winrt::Windows::Graphics::Imaging::BitmapEncoder::JpegEncoderId(), stream, propertySet);
    //encoder.SetSoftwareBitmap(softwareBitmap);
    ///*auto dataReader = DataReader::FromBuffer(pixels);
    //winrt::array_view<byte> b;
    //dataReader.ReadBytes(b);
    //encoder.SetPixelData(winrt::Windows::Graphics::Imaging::BitmapPixelFormat::Bgra8,
    //    winrt::Windows::Graphics::Imaging::BitmapAlphaMode::Ignore,
    //    (uint32_t)bitmap.PixelWidth(),(uint32_t)bitmap.PixelHeight(),
    //    96, 96,b);*/
    //co_await encoder.FlushAsync();

}


void winrt::bikabika::implementation::BikaImage::RefreshIcon_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    winrt::BikaClient::Blocks::ImageBlock imgBlock = ImgBlock();
    BikaImg().Source(imgBlock.Img());
}
