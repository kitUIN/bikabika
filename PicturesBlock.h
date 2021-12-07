#pragma once
#include "PicturesBlock.g.h"


namespace winrt::bikabika::implementation
{
    struct PicturesBlock : PicturesBlockT<PicturesBlock>
    {
        PicturesBlock() = default;

        PicturesBlock(hstring const& path);
        hstring Order();
        void Order(hstring const& value);
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Path();
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_path;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
        hstring m_order;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct PicturesBlock : PicturesBlockT<PicturesBlock, implementation::PicturesBlock>
    {
    };
}
