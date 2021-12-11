#pragma once

#include "Generated Files/AccountPage.g.h"
#include "Utils/API/BikaHttp.h"
#include "Utils/Blocks/UserViewModel.h"
namespace winrt::bikabika::implementation
{
    struct AccountPage : AccountPageT<AccountPage>
    {
        AccountPage();
        bikabika::UserViewModel MainUserViewModel();
	private:
		bikabika::UserViewModel m_userViewModel;
	};
}

namespace winrt::bikabika::factory_implementation
{
    struct AccountPage : AccountPageT<AccountPage, implementation::AccountPage>
    {
    };
}
