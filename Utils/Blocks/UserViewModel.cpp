#include "pch.h"
#include "UserViewModel.h"
#include "UserViewModel.g.cpp"


namespace winrt::bikabika::implementation
{
    UserViewModel::UserViewModel()
    {
        m_user = winrt::make<bikabika::implementation::User>(L"Picacg", L"Lv.?");
        m_user.Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ L"ms-appx:///Assets//Picacgs//placeholder_avatar_2.png"} });
    }
    winrt::bikabika::User UserViewModel::User()
    {
        return m_user;
    }
    void UserViewModel::Clear()
    {
     }
}
