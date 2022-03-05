#pragma once

#include "MainPage.g.h"
#include "Utils/Blocks/UserViewModel.h"
#include "Utils/Blocks/KeywordsBox.h"
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

		void NavView_ItemInvoked(
			Windows::Foundation::IInspectable const& /* sender */,
			muxc::NavigationViewItemInvokedEventArgs const& args);
		void NavView_Navigate(
			std::wstring navItemTag,
			Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo);
		// 新建标签页
		void CreateNewTab(Windows::UI::Xaml::Controls::Frame const& frame, hstring const& title, Microsoft::UI::Xaml::Controls::SymbolIconSource const& symbol);
		
		void ContentFrame_NavigationFailed(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& args);
		void On_Navigated(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);
		void ContentFrame_Navigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
		bikabika::UserViewModel MainUserViewModel();
		
		void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
		Windows::Foundation::IAsyncAction ContentDialogShow(hstring const& mode, hstring const& message);
		Windows::Foundation::IAsyncAction Login();
		Windows::Foundation::IAsyncAction SetPerson();
		void LoginClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
		Windows::Foundation::IAsyncAction GetKeywords();
		Windows::Foundation::IAsyncAction AutoLogin();
		void CatSearch_TextChanged(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
		void CatSearch_QuerySubmitted(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args);
		void CatSearch_SuggestionChosen(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args);
		void Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		hstring PicPath();
	private:
		static bikabika::MainPage current;
		Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		std::vector<std::pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>> m_pages;
		bikabika::UserViewModel m_userViewModel;
		bool m_suggestIsChosen = false;
		bool m_firstArrive = true;
		int32_t m_suggestionSize = 0;
		hstring m_picPath = L"ms-appx:///Assets//Picacgs//icon_unknown_error.png";
		bikabika::BikaHttp m_bikaHttp;
		bikabika::FileCheckTool m_fileCheckTool;
		winrt::Windows::Foundation::Collections::IObservableVector<bikabika::KeywordsBox> m_suggestions = winrt::single_threaded_observable_vector<bikabika::KeywordsBox>();
	public:
		static bikabika::MainPage Current() { return current; }
		
		void UsersPic_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void AutoCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void RememberCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void CatSearch_GettingFocus(winrt::Windows::UI::Xaml::UIElement const& sender, winrt::Windows::UI::Xaml::Input::GettingFocusEventArgs const& args);
		void ClearCatSearchHistory_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ContentTabView_TabCloseRequested(winrt::Microsoft::UI::Xaml::Controls::TabView const& sender, winrt::Microsoft::UI::Xaml::Controls::TabViewTabCloseRequestedEventArgs const& args);
		void Frame_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);
		void Grid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);
		void NavView_PaneClosed(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args);
		void NavView_PaneOpened(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args);
		void Flyout_Opened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);
	};

}

namespace winrt::bikabika::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{

	};
}
