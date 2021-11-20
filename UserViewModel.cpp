#include "pch.h"
#include "UserViewModel.h"
#include "UserViewModel.g.cpp"


namespace winrt::bikabika::implementation
{
    UserViewModel::UserViewModel()
    {
        m_user = winrt::make<bikabika::implementation::User>(L"", L"");
    }
    winrt::bikabika::User UserViewModel::User()
    {
        return m_user;
    }
}
