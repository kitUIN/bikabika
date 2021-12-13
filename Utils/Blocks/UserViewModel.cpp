#include "pch.h"
#include "UserViewModel.h"
#include "UserViewModel.g.cpp"


namespace winrt::bikabika::implementation
{
    UserViewModel::UserViewModel()
    {
        m_user = winrt::make<bikabika::implementation::User>(L"Picacg", L"Lv.?");
    }
    winrt::bikabika::User UserViewModel::User()
    {
        return m_user;
    }
}
