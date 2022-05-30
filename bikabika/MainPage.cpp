/*****************************************************************//**
 * \file   MainPage.cpp
 * \brief  主页面
 *
 * \author kulujun
 * \date   March 2022
 *********************************************************************/
#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

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
using namespace winrt::Windows::UI::Xaml::Media;

namespace winrt::bikabika::implementation
{
	bikabika::MainPage MainPage::current{ nullptr };

	MainPage::MainPage()
	{

		InitializeComponent();
		MainPage::current = *this;

		auto coreTitleBar = CoreApplication::GetCurrentView().TitleBar();
		coreTitleBar.ExtendViewIntoTitleBar(true);
		Window::Current().SetTitleBar(CustomDragRegion());
		/*Windows::Storage::ApplicationDataContainer serversSettings = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Servers", Windows::Storage::ApplicationDataCreateDisposition::Always);
		Windows::Storage::ApplicationDataContainer userData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"User", Windows::Storage::ApplicationDataCreateDisposition::Always);
		Windows::Storage::ApplicationDataContainer settingsData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Settings", Windows::Storage::ApplicationDataCreateDisposition::Always);


		// 隐藏标题栏

		/*LoginTeachingTip().IsOpen(true);
		NavHome().IsEnabled(false);
		NavClassification().IsEnabled(false);
		NavAccount().IsEnabled(false);*/

	}
	void MainPage::CreateNewTab(Windows::UI::Xaml::Controls::Frame const& frame, hstring const& title, Microsoft::UI::Xaml::Controls::SymbolIconSource const& symbol)
	{

		winrt::Microsoft::UI::Xaml::Controls::TabViewItem newItem;
		newItem.Header(box_value(title));
		newItem.IconSource(symbol);
		newItem.Content(frame);
		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [newItem, this]()
			{
				ContentTabView().TabItems().Append(newItem);
				ContentTabView().SelectedItem(newItem);
				NavView().SelectedItem(NavView().MenuItems().GetAt(1));
			});

	}
	void  MainPage::ContentDialogShow(hstring const& mode, hstring const& message)
	{

		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [mode, message, this]()->winrt::fire_and_forget
			{
				Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				if (mode == L"Timeout") {
					auto show{ PicErrorDialog().ShowAsync() };
				}
				else {
					HttpContentDialog().Title(box_value(resourceLoader.GetString(L"FailHttpTitle")));
					HttpContentDialog().CloseButtonText(resourceLoader.GetString(L"FailCloseButtonText"));
					if (mode == L"Error")
					{
						HttpContentDialog().Content(box_value(message));
						HttpContentDialog().IsTextScaleFactorEnabled(true);
						auto show{ HttpContentDialog().ShowAsync() };

					}
					else if (mode == L"Unknown")
					{
						Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(message);
						HttpContentDialog().Content(box_value(to_hstring(resp.GetNamedNumber(L"code")) + L":" + resp.GetNamedString(L"message")));
						HttpContentDialog().IsTextScaleFactorEnabled(true);
						auto show{ HttpContentDialog().ShowAsync() };

					}
					else if (mode == L"1005")
					{
						HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailAuth")));
						HttpContentDialog().IsTextScaleFactorEnabled(true);
						m_login = false;
						auto show{ co_await HttpContentDialog().ShowAsync() };
						if (show == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::None)
						{
							LoginTeachingTip().Title(resourceLoader.GetString(L"LoginButton/Content"));
							LoginTeachingTip().IsOpen(true);
						}
					}
					else if (mode == L"Blank")
					{
						HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailLoginBlank")));
						HttpContentDialog().IsTextScaleFactorEnabled(true);
						auto show{ HttpContentDialog().ShowAsync() };
					}
					else if (mode == L"Customize") {
						HttpContentDialog().Content(box_value(message));
						HttpContentDialog().IsTextScaleFactorEnabled(true);
						auto show{ HttpContentDialog().ShowAsync() };
					}
				}
			});

	}


	void MainPage::LoginClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
	{
	}
	void MainPage::ContentFrame_NavigationFailed(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& args)
	{
	}
	void MainPage::NavView_ItemInvoked(Windows::Foundation::IInspectable const&, muxc::NavigationViewItemInvokedEventArgs const& args)
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
	void MainPage::NavView_Navigate(std::wstring navItemTag, Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo)
	{
		winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
		winrt::Windows::UI::Xaml::Controls::Frame frame;
		hstring title;
		if (navItemTag == L"settings")
		{
			/*title = resourceLoader.GetString(L"NavSettings/Content");
			symbol.Symbol(Symbol::Setting);
			frame.Navigate(winrt::xaml_typename<bikabika::SettingsPage>());*/
		}
		else if (navItemTag == L"home")
		{
			/*frame.Navigate(winrt::xaml_typename<bikabika::HomePage>());
			title = resourceLoader.GetString(L"NavHome/Content");
			symbol.Symbol(Symbol::Home);*/
		}
		else if (navItemTag == L"classification")
		{
			//frame.Navigate(winrt::xaml_typename<bikabika::ClassificationPage>());
			title = resourceLoader.GetString(L"NavClassification/Content");
			symbol.Symbol(Symbol::AllApps);
		}
		else if (navItemTag == L"account")
		{
			/*frame.Navigate(winrt::xaml_typename<bikabika::UserPage>());
			title = resourceLoader.GetString(L"NavAccount/Content");
			symbol.Symbol(Symbol::Contact);*/
		}
		else if (navItemTag == L"download")
		{
			/*frame.Navigate(winrt::xaml_typename<bikabika::DownloadPage>());
			title = resourceLoader.GetString(L"NavDownload/Content");
			symbol.Symbol(Symbol::Home);*/
		}
		else return;
		CreateNewTab(frame, title, symbol);
	}
	void MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
	}
	void MainPage::UsersPic_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
	{
	}
	void MainPage::AutoCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
	}
	void MainPage::RememberCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
	}
	void MainPage::ClearCatSearchHistory_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
	}
	void MainPage::ContentTabView_TabCloseRequested(winrt::Microsoft::UI::Xaml::Controls::TabView const& sender, winrt::Microsoft::UI::Xaml::Controls::TabViewTabCloseRequestedEventArgs const& args)
	{
	}
	void MainPage::Grid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e)
	{
	}
	void MainPage::NavView_PaneClosed(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args)
	{
	}
	void MainPage::NavView_PaneOpened(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args)
	{
	}
	void MainPage::Flyout_Opened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
	{
	}
	void MainPage::LogOut_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
	}
	void MainPage::ChangeSignature_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
	}
	Windows::Foundation::IAsyncAction MainPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		return Windows::Foundation::IAsyncAction();
	}
	void MainPage::ChangePassword_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
	}
	void MainPage::LoginButton_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{
	}
	void MainPage::SubmitButton_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{
	}
	void MainPage::CatSearch_TextChanged(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
	{
	}
	void MainPage::CatSearch_QuerySubmitted(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args)
	{
	}
	void MainPage::CatSearch_SuggestionChosen(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args)
	{
	}
	void MainPage::Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
	}
}
