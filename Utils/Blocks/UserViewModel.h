#pragma once
#include "UserViewModel.g.h"
#include "User.h"

namespace winrt::bikabika::implementation
{
    struct UserViewModel : UserViewModelT<UserViewModel>
    {
        UserViewModel();

        winrt::bikabika::User User();
        void Clear();
    private:
        winrt::bikabika::User m_user{ nullptr };
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct UserViewModel : UserViewModelT<UserViewModel, implementation::UserViewModel>
    {
    };
}
