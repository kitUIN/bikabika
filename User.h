#pragma once
#include "User.g.h"


namespace winrt::bikabika::implementation
{
    struct User : UserT<User>
    {
        User() = delete;

        User(hstring const& name, hstring const& level);
        hstring Name();
        void Name(hstring const& value);
        hstring Level();
        void Level(hstring const& value);
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Img();
        void Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);
        hstring ImageSource();
        void ImageSource(hstring const& value);
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        winrt::hstring m_name;
        winrt::hstring m_level;
        winrt::hstring m_imageSource= L"https://storage1.picacomic.com/static/0788a77a-81e4-46a5-9206-c424226bed07.jpg";
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_img{ Windows::Foundation::Uri{ L"ms-appx:///gray.png" } };
        
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct User : UserT<User, implementation::User>
    {
    };
}
