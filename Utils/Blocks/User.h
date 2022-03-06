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
        hstring CreatedAt();
        void CreatedAt(hstring const& value);
        hstring Birthday();
        void Birthday(hstring const& value);
        hstring Email();
        void Email(hstring const& value);
        hstring Level();
        void Level(hstring const& value);
        bool IsPunched();
        void IsPunched(bool const& value);
        bool Verified();
        void Verified(bool const& value);
        hstring IsPunchedString();
        void IsPunchedString(hstring const& value);
        hstring VerifiedString();
        void VerifiedString(hstring const& value);
        hstring ID();
        void ID(hstring const& value);
        hstring Gender();
        void Gender(hstring const& value);
        hstring LevelString();
        void LevelString(hstring const& value);
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Img();
        void Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);
        hstring ImageSource();
        void ImageSource(hstring const& value);
        hstring Slogan();
        void Slogan(hstring const& value);
        int32_t Exp();
        void Exp(int32_t const& value);
        int32_t Percent();
        void Percent(int32_t const& value);
        hstring LevelExp();
        void LevelExp(hstring const& value);
        hstring Title();
        void Title(hstring const& value);
        void Clear();
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };

        winrt::hstring m_title = L"";
        winrt::hstring m_gender = L"";
        winrt::hstring m_id = L"";
        bool m_verified = false;
        winrt::hstring m_verifiedString = L"";
        bool m_isPunched = false;
        winrt::hstring m_isPunchedString = L"";
        winrt::hstring m_createAt = L"";
        winrt::hstring m_birthday = L"";
        winrt::hstring m_slogan = L"";
        winrt::hstring m_levelExp = L"(? / ?)";
        int32_t m_exp = 0;
        int32_t m_percent = 100;
        winrt::hstring m_name=L"Gentleman";
        winrt::hstring m_email=L"";
        winrt::hstring m_levelString= L"Lv.0";
        hstring  m_level=L"";
        winrt::hstring m_imageSource= L"https://storage1.picacomic.com/static/0788a77a-81e4-46a5-9206-c424226bed07.jpg";
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_img{ Windows::Foundation::Uri{ L"ms-appx:///Assets//Picacgs//placeholder_avatar_2.png" } };
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

    };
}
namespace winrt::bikabika::factory_implementation
{
    struct User : UserT<User, implementation::User>
    {
    };
}
