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

		void NavView_Loaded(
			Windows::Foundation::IInspectable const& /* sender */,
			Windows::UI::Xaml::RoutedEventArgs const& /* args */);

		void NavView_ItemInvoked(
			Windows::Foundation::IInspectable const& /* sender */,
			muxc::NavigationViewItemInvokedEventArgs const& args);
		// NavView_SelectionChanged is not used in this example, but is shown for completeness.
		// You'll typically handle either ItemInvoked or SelectionChanged to perform navigation,
		// but not both.
		void NavView_Navigate(
			std::wstring navItemTag,
			Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo);
		void NavView_BackRequested(muxc::NavigationView const&, muxc::NavigationViewBackRequestedEventArgs const&);
		void CoreDispatcher_AcceleratorKeyActivated(Windows::UI::Core::CoreDispatcher const&, Windows::UI::Core::AcceleratorKeyEventArgs const& args);
		void CoreWindow_PointerPressed(Windows::UI::Core::CoreWindow const&, Windows::UI::Core::PointerEventArgs const& args);
		void System_BackRequested(Windows::Foundation::IInspectable const&, Windows::UI::Core::BackRequestedEventArgs const& args);
		void ContentFrame_NavigationFailed(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& args);
		bool TryGoBack();
		void On_Navigated(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);
		void ContentFrame_Navigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
		bikabika::UserViewModel MainUserViewModel();
		Windows::Foundation::IAsyncAction UpdateToken();
		Windows::Foundation::IAsyncAction UpdateSuggestion();
		void CatSearch_TextChanged(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
		void CatSearch_QuerySubmitted(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args);
		void CatSearch_SuggestionChosen(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args);
		
	private:

		std::vector<std::pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>> m_pages;
		bikabika::UserViewModel m_userViewModel;
		bool m_suggestIsChosen = false;
		bikabika::FileCheckTool m_fileCheckTool;
		winrt::Windows::Foundation::Collections::IObservableVector<bikabika::KeywordsBox> m_suggestions = winrt::single_threaded_observable_vector<bikabika::KeywordsBox>();
		Windows::Storage::ApplicationDataContainer serversSettings = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Servers", Windows::Storage::ApplicationDataCreateDisposition::Always);
		Windows::Storage::ApplicationDataContainer userData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"User", Windows::Storage::ApplicationDataCreateDisposition::Always);
		Windows::Storage::ApplicationDataContainer localSettings = Windows::Storage::ApplicationData::Current().LocalSettings();
		
	};

}

namespace winrt::bikabika::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{

	};
}
