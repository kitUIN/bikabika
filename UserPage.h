#pragma once

#include "UserPage.g.h"
#include "Utils/API/BikaHttp.h"
#include "Utils/Blocks/UserViewModel.h"
namespace winrt::bikabika::implementation
{
    struct UserPage : UserPageT<UserPage>
    {
        UserPage();
        bikabika::UserViewModel MainUserViewModel();
        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
    private:
        bikabika::UserViewModel m_userViewModel;
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct UserPage : UserPageT<UserPage, implementation::UserPage>
    {
    };
}
