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
		int32_t MyProperty();
		void MyProperty(int32_t value);
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
	
	private:
		//bikabika::LoginBlockViewModel m_mainViewModel{ nullptr };
		// Vector of std::pair holding the Navigation Tag and the relative Navigation Page.
		std::vector<std::pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>> m_pages;
	};

}

namespace winrt::bikabika::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{

	};
}
