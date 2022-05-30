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

	void  MainPage::ContentDialogShow(bikabika::BikaHttpStatus const& mode, hstring const& message)
	{
		Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		ContentDialog dialog;
		dialog.CloseButtonText(resourceLoader.GetString(L"FailMessage/CloseButton/Normal"));
		dialog.IsTextScaleFactorEnabled(true);
		Grid grid;
		TextBlock title;
		Image img;
		img.Height(270);
		img.Width(270);
		img.VerticalAlignment(VerticalAlignment::Center);
		img.HorizontalAlignment(HorizontalAlignment::Center);
		title.VerticalAlignment(VerticalAlignment::Top);
		title.HorizontalAlignment(HorizontalAlignment::Left);
		if (mode == bikabika::BikaHttpStatus::TIMEOUT) {
			title.Text(resourceLoader.GetString(L"FailMessage/Title/TimeOut"));
			img.Source(BitmapImage{Uri{ L"ms-appx:///Assets//Picacgs//icon_unknown_error.png" }});
			StackPanel stackPanel;
			stackPanel.Orientation(Orientation::Vertical);
			stackPanel.HorizontalAlignment(HorizontalAlignment::Center);
			TextBlock content1, content2, content3, content4;
			content1.Text(resourceLoader.GetString(L"FailMessage/Message/TimeOut/One"));
			content3.Text(resourceLoader.GetString(L"FailMessage/Message/TimeOut/Two"));
			content4.Text(resourceLoader.GetString(L"FailMessage/Message/TimeOut/Three"));
			stackPanel.Children().Append(content1);
			stackPanel.Children().Append(content2);
			stackPanel.Children().Append(content3);
			stackPanel.Children().Append(content4);
			dialog.Content(box_value(stackPanel));
		}
		else if (mode == bikabika::BikaHttpStatus::NOAUTH)
		{
			title.Text(resourceLoader.GetString(L"FailMessage/Message/NoAuth"));
			img.Source(BitmapImage{ Uri{ L"ms-appx:///Assets//Picacgs//icon_exclamation_error.png" } });
			dialog.PrimaryButtonText(resourceLoader.GetString(L"FailMessage/PrimaryButton/NoAuth"));
			//dialog.PrimaryButtonClick({this,&MainPage::AutoLogin });
			dialog.DefaultButton(ContentDialogButton::Primary);
			dialog.IsPrimaryButtonEnabled(true);
		}
		else
		{
			title.Text(resourceLoader.GetString(L"FailMessage/Title/Unknown"));
			dialog.Content(box_value(message));
		}
		grid.Children().Append(img);
		grid.Children().Append(title);
		dialog.Content(box_value(grid));
		dialog.ShowAsync();
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
	Windows::Foundation::IAsyncAction MainPage::AutoLogin()
	{
		m_login = false;
		return Windows::Foundation::IAsyncAction();
	}
}
