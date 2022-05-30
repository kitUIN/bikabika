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
using namespace Windows::Data::Json;
using namespace Windows::Foundation;

using namespace winrt::Windows::UI::Xaml::Media;
using namespace Windows::Foundation::Numerics;
using namespace Windows::Foundation::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;


namespace winrt::bikabika::implementation
{
	bikabika::MainPage MainPage::current{ nullptr };

	MainPage::MainPage()
	{

		InitializeComponent();
		MainPage::current = *this;
		// 隐藏标题栏
		auto coreTitleBar = CoreApplication::GetCurrentView().TitleBar();
		coreTitleBar.ExtendViewIntoTitleBar(true);
		Window::Current().SetTitleBar(CustomDragRegion());

		// 登录初始化
		LoginTeachingTip().IsOpen(true);
		NavHome().IsEnabled(false);
		NavClassification().IsEnabled(false);
		NavAccount().IsEnabled(false);

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
			//dialog.PrimaryButtonClick({this,&MainPage:: });
			dialog.DefaultButton(ContentDialogButton::Primary);
			dialog.IsPrimaryButtonEnabled(true);
		}
		else
		{
			title.Text(resourceLoader.GetString(L"FailMessage/Title/Unknown"));
			img.Source(BitmapImage{ Uri{ L"ms-appx:///Assets//Picacgs//icon_exclamation_error.png" } });
			dialog.Content(box_value(message));
		}
		grid.Children().Append(img);
		grid.Children().Append(title);
		dialog.Title(box_value(grid));
		dialog.ShowAsync();
	}

	void MainPage::LayoutMessageShow(hstring const& message, bool const& isOpen)
	{
		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [message, isOpen, this]()
			{
				LayoutMessage().Title(message);
				LayoutMessage().IsOpen(isOpen);
			});
	}
	winrt::event_token MainPage::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}
	void MainPage::PropertyChanged(winrt::event_token const& token) noexcept
	{
		m_propertyChanged.remove(token);
	}
	Windows::Foundation::IAsyncAction MainPage::Login()
	{

		auto res = co_await m_bikaClient.Login(Email().Text(), Password().Password());
		if (res.Code()== -1)
		{
			ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200) {
			Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
			JsonObject tokens;
			if (loginData.Values().HasKey(L"AutoLogin") && loginData.Values().Lookup(L"AutoLogin").as<bool>())
			{
				if (loginData.Values().HasKey(L"tokens"))
				{
					tokens = JsonObject::Parse(loginData.Values().Lookup(L"tokens").as<hstring>());
				}
				tokens.Insert(Email().Text(), JsonValue::CreateStringValue(res.Token()));
				loginData.Values().Insert(L"tokens", box_value(tokens.Stringify()));
			}

			JsonObject emails;
			JsonObject passwords;
			JsonArray emailArray;
			emails.Insert(L"Last", JsonValue::CreateStringValue(Email().Text()));
			if (loginData.Values().HasKey(L"emails"))
			{
				emails = JsonObject::Parse(loginData.Values().Lookup(L"emails").as<hstring>());
				emailArray = emails.GetNamedArray(L"emailArry");
			}
			emailArray.Append(JsonValue::CreateStringValue(Email().Text()));
			emails.Insert(L"emailArry", emailArray);
			loginData.Values().Insert(L"emails", box_value(emails.Stringify()));

			if (loginData.Values().HasKey(L"RememberMe") && loginData.Values().Lookup(L"RememberMe").as<bool>())
			{
				if (loginData.Values().HasKey(L"passwords"))
				{
					passwords = JsonObject::Parse(loginData.Values().Lookup(L"passwords").as<hstring>());
				}
				passwords.Insert(Email().Text(), JsonValue::CreateStringValue(Password().Password()));
				loginData.Values().Insert(L"passwords", box_value(passwords.Stringify()));
			}


			co_await SetPerson();
			/*if (m_user.IsPunched()) {
				PunchIn();
				SetPerson();
			}*/
			LayoutMessageShow(L"", false);
		}
		else if(res.Code()==401&&res.Error()==L"1005")
		{
			ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());

		}
		else if (res.Code() == 400)
		{
			ContentDialogShow(BikaHttpStatus::UNKNOWN, resourceLoader.GetString(L"FailMessage/Message/Login/Error"));
			Password().Password(L"");
		}
		else
		{
			ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
			Password().Password(L"");
		}
	}

	Windows::Foundation::IAsyncAction MainPage::PunchIn()
	{
		return Windows::Foundation::IAsyncAction();
	}


	void MainPage::LoginClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
	{
		// 账号密码为空
		if (Email().Text() == L"" || Password().Password() == L"")
		{
			ContentDialogShow(BikaHttpStatus::UNKNOWN, resourceLoader.GetString(L"FailMessage/Message/Login/Blank"));
		}
		else
		{
			LayoutMessageShow(resourceLoader.GetString(L"Logining"),true);
			auto login{ Login() };
		}
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
		if (sender.as<CheckBox>().IsChecked().GetBoolean())
		{
			RememberCheckBox().IsChecked(true);
		}
		Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
		loginData.Values().Insert(L"AutoLogin", box_value(AutoCheckBox().IsChecked().GetBoolean()));
	}
	void MainPage::RememberCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		if (!sender.as<CheckBox>().IsChecked().GetBoolean())
		{
			AutoCheckBox().IsChecked(false);
		}
		Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
		loginData.Values().Insert(L"RememberMe", box_value(RememberCheckBox().IsChecked().GetBoolean()));
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
		if (e.Key() == Windows::System::VirtualKey::Enter)
		{
			LoginClickHandler(sender, Windows::UI::Xaml::RoutedEventArgs{ nullptr });
		}
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
	BikaClient::Blocks::UserBlock MainPage::User()
	{
		return m_user;
	}
	void MainPage::User(BikaClient::Blocks::UserBlock const& value)
	{
		m_user = value;
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"User" });
	}
	Windows::Foundation::IAsyncAction MainPage::SetPerson()
	{
		auto res = co_await m_bikaClient.PersonInfo();
		if (res.Code() == -1)
		{
			ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200) {
			NavHome().IsEnabled(true);
			NavClassification().IsEnabled(true);
			NavAccount().IsEnabled(true);
			User(res.User());
			if (m_firstArrive) {
				winrt::Microsoft::UI::Xaml::Controls::TabViewItem newItem;
				newItem.Header(box_value(resourceLoader.GetString(L"NavHome/Content")));
				winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
				symbol.Symbol(Symbol::Home);
				newItem.IconSource(symbol);
				winrt::Windows::UI::Xaml::Controls::Frame frame;
				frame.Navigate(winrt::xaml_typename<bikabika::HomePage>());
				newItem.Content(frame);
				ContentTabView().TabItems().Append(newItem);
				ContentTabView().SelectedItem(newItem);
				m_firstArrive = false;
				m_login = true;
				//co_await GetKeywords();
			}
		}
		else if (res.Code() == 401 && res.Error() == L"1005")
		{
			ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());

		}
		else
		{
			ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
			Password().Password(L"");
		}
		LayoutMessageShow(L"", false);
		LoginTeachingTip().IsOpen(false);
	}
	Windows::Foundation::IAsyncAction MainPage::AutoLogin()
	{
		m_login = false;
		return Windows::Foundation::IAsyncAction();
	}
}
