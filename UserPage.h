#pragma once

#include "UserPage.g.h"
#include "MainPage.h"
#include "Utils/API/BikaHttp.h"
#include "Utils/Blocks/FileCheckTool.h"
#include "Utils/Blocks/UserViewModel.h"
#include "Utils/Blocks/ComicBlock.h"
namespace winrt::bikabika::implementation
{
    struct UserPage : UserPageT<UserPage>
    {
        UserPage();
        bikabika::UserViewModel MainUserViewModel();
        void CheckPunchIn();
        Windows::Foundation::IAsyncAction  OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        Windows::Foundation::IAsyncAction GetHistory();
        Windows::Foundation::IAsyncAction ContentDialogShow(hstring const& mode, hstring const& message);
        Windows::Foundation::IAsyncAction GetFavourite(hstring const& sort, int32_t const& page);
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> FavComicBlocks();
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> LookComicBlocks();


    private:
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };

        bikabika::MainPage rootPage{ MainPage::Current() };
        bikabika::UserViewModel m_userViewModel;
        bikabika::FileCheckTool m_fileCheckTool;
        bikabika::BikaHttp m_bikaHttp;
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> m_favComicBlocks = winrt::single_threaded_observable_vector<bikabika::ComicBlock>();
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> m_lookComicBlocks = winrt::single_threaded_observable_vector<bikabika::ComicBlock>();
        int32_t m_total;
        int32_t m_limit;
        winrt::Windows::UI::Xaml::Controls::Image m_img;
        bool m_firstArrive = false;
    public:
        void GotoLook_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void GotoFav_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Grid_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void AutoPunch_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Punch_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void UserLogOut_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void UserSettings_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Flyout_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);
        void FlyoutPasswordButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void FlyoutSloganButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
    
}

namespace winrt::bikabika::factory_implementation
{
    struct UserPage : UserPageT<UserPage, implementation::UserPage>
    {
    };
}
