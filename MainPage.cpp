#include "pch.h"
#include "MainPage.h"

#include "MainPage.g.cpp"
#include "Login.h"


using namespace std;
using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Numerics;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;

namespace winrt::bikabika::implementation
{
	;
	MainPage::MainPage()
	{
		InitializeComponent();
		m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
			(L"home", winrt::xaml_typename<bikabika::HomePage>()));
		m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
			(L"classification", winrt::xaml_typename<bikabika::ClassificationPage>()));
		m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
			(L"account", winrt::xaml_typename<bikabika::AccountPage>()));
		m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
			(L"settings", winrt::xaml_typename<bikabika::SettingsPage>()));
		m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
			(L"login", winrt::xaml_typename<bikabika::Login>()));

		Window::Current().SetTitleBar(AppTitleBar());
	}

	int32_t MainPage::MyProperty()
	{
		throw hresult_not_implemented();
	}

	void MainPage::MyProperty(int32_t /* value */)
	{
		throw hresult_not_implemented();
	}
	

	// List of ValueTuple holding the Navigation Tag and the relative Navigation Page
	std::vector<std::pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>> m_pages;

	void MainPage::NavView_Loaded(
		Windows::Foundation::IInspectable const& /* sender */,
		Windows::UI::Xaml::RoutedEventArgs const& /* args */)
	{
		//NavView().MenuItems().Append(muxc::NavigationViewItemSeparator());
		//muxc::NavigationViewItem navigationViewItem;
		//navigationViewItem.Content(winrt::box_value(L"My content"));
		//navigationViewItem.Icon(wuxc::SymbolIcon(static_cast<wuxc::Symbol>(0xF1AD)));
		// navigationViewItem.Tag(winrt::box_value(L"content"));
		//NavView().MenuItems().Append(navigationViewItem);
		
		NavView_Navigate(L"login",
			Windows::UI::Xaml::Media::Animation::EntranceNavigationTransitionInfo());
		//NavView().SelectedItem(NavView().MenuItems().GetAt(1));
	}

	void MainPage::NavView_ItemInvoked(
		Windows::Foundation::IInspectable const& /* sender */,
		muxc::NavigationViewItemInvokedEventArgs const& args)
	{
		if (args.IsSettingsInvoked())
		{
			NavView_Navigate(L"settings", args.RecommendedNavigationTransitionInfo());
		}
		else if (args.InvokedItemContainer())
		{
			NavView_Navigate(
				winrt::unbox_value_or<winrt::hstring>(
					args.InvokedItemContainer().Tag(), L"").c_str(),
				args.RecommendedNavigationTransitionInfo());
		}
	}



	void MainPage::NavView_Navigate(
		std::wstring navItemTag,
		Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo)
	{
		Windows::UI::Xaml::Interop::TypeName pageTypeName;
		if (navItemTag == L"settings")
		{
			pageTypeName = winrt::xaml_typename<bikabika::SettingsPage>();
		}
		else
		{
			for (auto&& eachPage : m_pages)
			{
				if (eachPage.first == navItemTag)
				{
					pageTypeName = eachPage.second;
					break;
				}
			}
		}
		// Get the page type before navigation so you can prevent duplicate
		// entries in the backstack.
		Windows::UI::Xaml::Interop::TypeName preNavPageType =
			ContentFrame().CurrentSourcePageType();

		// Navigate only if the selected page isn't currently loaded.
		if (pageTypeName.Name != L"" && preNavPageType.Name != pageTypeName.Name)
		{
			ContentFrame().Navigate(pageTypeName, nullptr, transitionInfo);
		}
	}

	void MainPage::NavView_BackRequested(
		muxc::NavigationView const& /* sender */,
		muxc::NavigationViewBackRequestedEventArgs const& /* args */)
	{
		TryGoBack();
	}

	void MainPage::CoreDispatcher_AcceleratorKeyActivated(
		Windows::UI::Core::CoreDispatcher const& /* sender */,
		Windows::UI::Core::AcceleratorKeyEventArgs const& args)
	{
		// When Alt+Left are pressed navigate back
		if (args.EventType() == Windows::UI::Core::CoreAcceleratorKeyEventType::SystemKeyDown
			&& args.VirtualKey() == Windows::System::VirtualKey::Left
			&& args.KeyStatus().IsMenuKeyDown
			&& !args.Handled())
		{
			args.Handled(TryGoBack());
		}
	}

	void MainPage::CoreWindow_PointerPressed(
		Windows::UI::Core::CoreWindow const& /* sender */,
		Windows::UI::Core::PointerEventArgs const& args)
	{
		// Handle mouse back button.
		if (args.CurrentPoint().Properties().IsXButton1Pressed())
		{
			args.Handled(TryGoBack());
		}
	}

	void MainPage::System_BackRequested(
		Windows::Foundation::IInspectable const& /* sender */,
		Windows::UI::Core::BackRequestedEventArgs const& args)
	{
		if (!args.Handled())
		{
			args.Handled(TryGoBack());
		}
	}
	void MainPage::ContentFrame_NavigationFailed(
		Windows::Foundation::IInspectable const& /* sender */,
		Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& args)
	{
		throw winrt::hresult_error(
			E_FAIL, winrt::hstring(L"Failed to load Page ") + args.SourcePageType().Name);
	}
	bool MainPage::TryGoBack()
	{
		if (!ContentFrame().CanGoBack())
			return false;
		// Don't go back if the nav pane is overlayed.
		if (NavView().IsPaneOpen() &&
			(NavView().DisplayMode() == muxc::NavigationViewDisplayMode::Compact ||
				NavView().DisplayMode() == muxc::NavigationViewDisplayMode::Minimal))
			return false;
		ContentFrame().GoBack();
		return true;
	}

	void MainPage::On_Navigated(
		Windows::Foundation::IInspectable const& /* sender */,
		Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
	{
		NavView().IsBackEnabled(ContentFrame().CanGoBack());

		if (ContentFrame().SourcePageType().Name ==
			winrt::xaml_typename<bikabika::SettingsPage>().Name)
		{
			// SettingsItem is not part of NavView.MenuItems, and doesn't have a Tag.
			NavView().SelectedItem(NavView().SettingsItem().as<muxc::NavigationViewItem>());
			NavView().Header(winrt::box_value(L"Settings"));
		}
		else if (ContentFrame().SourcePageType().Name != L"")
		{
			for (auto&& eachPage : m_pages)
			{
				if (eachPage.second.Name == args.SourcePageType().Name)
				{
					for (auto&& eachMenuItem : NavView().MenuItems())
					{
						auto navigationViewItem =
							eachMenuItem.try_as<muxc::NavigationViewItem>();
						{
							if (navigationViewItem)
							{
								winrt::hstring hstringValue =
									winrt::unbox_value_or<winrt::hstring>(
										navigationViewItem.Tag(), L"");
								if (hstringValue == eachPage.first)
								{
									NavView().SelectedItem(navigationViewItem);
									NavView().Header(navigationViewItem.Content());
								}
							}
						}
					}
					break;
				}
			}
		}
	}


	Windows::Foundation::IAsyncAction MainPage::CreateLoginPage(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
	{

		auto Views = CoreApplication::Views();
		if (Views.Size() == 2)
			return;
		CoreDispatcher MainDispatcher =
			CoreApplication::GetCurrentView().Dispatcher();
		int32_t  ViewId = 0;
		// Create a new window.
		
		CoreApplicationView View = CoreApplication::CreateNewView();
		co_await resume_foreground(View.Dispatcher());

		// Show the "Loading..." screen.
		Windows::UI::Xaml::Controls::Frame f;
		f.Navigate(xaml_typename<bikabika::Login>(), nullptr);
		Window::Current().Content(f);
		Window::Current().Activate();

		//ApplicationView::PreferredLaunchViewSize();
		//ApplicationView::PreferredLaunchWindowingMode(ApplicationViewWindowingMode::Auto);
		//Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TryResizeView(Size(600, 400));
		
		ViewId = ApplicationView::GetForCurrentView().Id();
		
		// Activate the new window.
		co_await resume_foreground(MainDispatcher);
		
		co_await ApplicationViewSwitcher::TryShowAsStandaloneAsync(ViewId);
		
		// Start the emulation in the new window.
		co_await resume_foreground(View.Dispatcher());
		co_await ApplicationViewSwitcher::SwitchAsync(ViewId);

		//ApplicationView::GetForCurrentView().ExitFullScreenMode();
	}
}
