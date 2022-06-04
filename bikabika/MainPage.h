#pragma once

#include "MainPage.g.h"
#include "Utils/KeywordBox.h"
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

		void LoginViewShow(bool const& isOpen);

		void CreateNewTab(Windows::UI::Xaml::Controls::Frame const& frame, hstring const& title, Microsoft::UI::Xaml::Controls::SymbolIconSource const& symbol);
		void ContentDialogShow(bikabika::BikaHttpStatus const& mode, hstring const& message);
		void LayoutMessageShow(hstring const& message,bool const& isOpen);
		void LayoutMessageShow(bool const& isOpen);
		Windows::Foundation::IAsyncAction Login();
		Windows::Foundation::IAsyncAction PunchIn();
		void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

		hstring Omit(hstring const& str, uint32_t const& length);

		void StartInfoBar();
		void ChangePassword(bool const& isOpen);
		void ChangeSignature(bool const& isOpen);
		Windows::Foundation::IAsyncAction SetPerson();
		Windows::Foundation::IAsyncAction GetKeywords();
		BikaClient::BikaHttpClient HttpClient();
		void OnTick(Windows::Foundation::IInspectable const&, Windows::Foundation::IInspectable const&);
		void InfoBarMessageShow(hstring const& title, hstring const& message, winrt::Microsoft::UI::Xaml::Controls::InfoBarSeverity const& severity);
		void LogOut();
		BikaClient::Blocks::UserBlock User();
		void User(BikaClient::Blocks::UserBlock const& value);
		winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
		void PropertyChanged(winrt::event_token const& token) noexcept;
		bool IsLogin();
		void IsLogin(bool const& value);
		static bikabika::MainPage Current() { return current; }
	private:
		static bikabika::MainPage current;
		winrt::Windows::Foundation::Collections::IObservableVector<bikabika::KeywordBox> m_suggestions = winrt::single_threaded_observable_vector<bikabika::KeywordBox>();
		winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
		BikaClient::BikaHttpClient m_bikaClient;
		BikaClient::Blocks::UserBlock m_user{nullptr};
		Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		bool m_login = false;
		bool m_suggestIsChosen = false;
		bool m_firstArrive = true;
		Windows::UI::Xaml::DispatcherTimer timer;

	public:
		void KeywordClose_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void LoginClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
		void ContentFrame_NavigationFailed(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& args);
		void NavView_ItemInvoked(Windows::Foundation::IInspectable const& /* sender */,muxc::NavigationViewItemInvokedEventArgs const& args);
		void NavView_Navigate(std::wstring navItemTag,Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo);
		Windows::Foundation::IAsyncAction SetPassword_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ChangePassword_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void LoginButton_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
		void ChangePasswordButton_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
		void CatSearch_TextChanged(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
		void CatSearch_QuerySubmitted(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args);
		void CatSearch_SuggestionChosen(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args);
		void Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void Omit_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void UsersPic_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
		void AutoCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void RememberCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ContentTabView_TabCloseRequested(winrt::Microsoft::UI::Xaml::Controls::TabView const& sender, winrt::Microsoft::UI::Xaml::Controls::TabViewTabCloseRequestedEventArgs const& args);
		void Grid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);
		void NavView_PaneClosed(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args);
		void NavView_PaneOpened(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args);
		void Flyout_Opened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);
		void LogOut_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ChangeSignature_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ChangeSignatureBox_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
		Windows::Foundation::IAsyncAction ChangePasswordButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		Windows::Foundation::IAsyncAction ChangeSignatureButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void ButtonRegister_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
		void LoginUserSlogan_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
	};

}

namespace winrt::bikabika::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{
	};
}
