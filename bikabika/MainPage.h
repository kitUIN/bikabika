#pragma once

#include "MainPage.g.h"
namespace muxc
{
	using namespace winrt::Microsoft::UI::Xaml::Controls;
};

namespace wuxc
{
	using namespace winrt::Windows::UI::Xaml::Controls;
};

namespace winrt::bikabika::implementation
{
	struct MainPage : MainPageT<MainPage>
	{
		MainPage();


		void CreateNewTab(Windows::UI::Xaml::Controls::Frame const& frame, hstring const& title, Microsoft::UI::Xaml::Controls::SymbolIconSource const& symbol);
		void ContentDialogShow(hstring const& mode, hstring const& message);
		Windows::Foundation::IAsyncAction Login();
		Windows::Foundation::IAsyncAction  PunchIn();
		int32_t GetEXP(int32_t const& level);
		Windows::Foundation::IAsyncAction SetPerson();
		Windows::Foundation::IAsyncAction GetKeywords();
		Windows::Foundation::IAsyncAction AutoLogin();
		void ChangeSignature();
		void ChangePassword();
		void LogOut();
		hstring PicPath();
		void LoginClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
		void ContentFrame_NavigationFailed(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& args);
		void NavView_ItemInvoked(
			Windows::Foundation::IInspectable const& /* sender */,
			muxc::NavigationViewItemInvokedEventArgs const& args);
		void NavView_Navigate(
			std::wstring navItemTag,
			Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo);
		void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
		void UsersPic_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void AutoCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void RememberCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ClearCatSearchHistory_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ContentTabView_TabCloseRequested(winrt::Microsoft::UI::Xaml::Controls::TabView const& sender, winrt::Microsoft::UI::Xaml::Controls::TabViewTabCloseRequestedEventArgs const& args);
		void Grid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);
		void NavView_PaneClosed(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args);
		void NavView_PaneOpened(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args);
		void Flyout_Opened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);
		void LogOut_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ChangeSignature_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		Windows::Foundation::IAsyncAction Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ChangePassword_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void LoginButton_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
		void SubmitButton_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
		void CatSearch_TextChanged(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
		void CatSearch_QuerySubmitted(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args);
		void CatSearch_SuggestionChosen(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args);
		void Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		static bikabika::MainPage Current() { return current; }
	private:
		static bikabika::MainPage current;
		BikaClient::BikaHttpClient m_bikaClient;
		Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		bool _suggestIsChosen = false;
		bool m_login = false;
		bool _firstArrive = true;
		int32_t _suggestionSize = 0;
		hstring _picPath = L"ms-appx:///Assets//Picacgs//icon_unknown_error.png";
	};

}

namespace winrt::bikabika::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{
	};
}
