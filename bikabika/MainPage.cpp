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
using namespace winrt::Windows::UI::Xaml::Media::Animation;
using namespace winrt::Windows::UI::Input;


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

		auto titleBar = ApplicationView::GetForCurrentView().TitleBar();
		titleBar.ButtonBackgroundColor(Colors::Transparent());

		// 登录初始化
		LogOut();

		NavHome().IsEnabled(false);
		NavClassification().IsEnabled(false);
		NavAccount().IsEnabled(false);
	}
	void MainPage::LoginViewShow(bool const& isOpen)
	{
		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [isOpen, this]()
			{
				LoginTeachingTip().IsOpen(isOpen);
			});
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
			});

	}

	void  MainPage::ContentDialogShow(bikabika::BikaHttpStatus const& mode, hstring const& message)
	{
		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [mode, message, this]()
			{
				LayoutMessage().IsOpen(false);
				auto color = Application::Current().Resources().Lookup(box_value(L"SystemAccentColorLight3")).as<Color>();
				ContentDialog dialog;
				dialog.CloseButtonText(resourceLoader.GetString(L"FailMessage/CloseButton/Normal"));
				dialog.IsTextScaleFactorEnabled(true);
				dialog.Background(SolidColorBrush{ color });
				StackPanel grid;
				grid.Orientation(Orientation::Vertical);
				Border boder;
				boder.Background(SolidColorBrush{ color });
				boder.CornerRadius(Windows::UI::Xaml::CornerRadius{ 10,10,10,10 });
				boder.Padding(Thickness{ 10,5,10,5 });
				boder.VerticalAlignment(VerticalAlignment::Top);
				boder.HorizontalAlignment(HorizontalAlignment::Left);
				TextBlock title;
				Image img;
				img.Height(270);
				img.Width(270);
				img.VerticalAlignment(VerticalAlignment::Center);
				img.HorizontalAlignment(HorizontalAlignment::Center);
				title.FontWeight(Text::FontWeights::Bold());
				if (mode == bikabika::BikaHttpStatus::TIMEOUT) {
					title.Text(resourceLoader.GetString(L"FailMessage/Title/TimeOut"));
					img.Source(BitmapImage{ Uri{ L"ms-appx:///Assets//Picacgs//icon_unknown_error.png" } });
					StackPanel stackPanel;
					stackPanel.Orientation(Orientation::Vertical);
					stackPanel.HorizontalAlignment(HorizontalAlignment::Center);
					TextBlock content1, content2, content3, content4;
					content1.FontWeight(Text::FontWeights::Bold());
					content1.HorizontalAlignment(HorizontalAlignment::Center);
					content2.FontWeight(Text::FontWeights::Bold());
					content2.HorizontalAlignment(HorizontalAlignment::Center);
					content3.FontWeight(Text::FontWeights::Bold());
					content3.HorizontalAlignment(HorizontalAlignment::Center);
					content4.FontWeight(Text::FontWeights::Bold());
					content4.HorizontalAlignment(HorizontalAlignment::Center);
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
					dialog.PrimaryButtonClick({ [this](ContentDialog const&, ContentDialogButtonClickEventArgs const&) {LoginViewShow(true); } });
					dialog.DefaultButton(ContentDialogButton::Primary);
					dialog.IsPrimaryButtonEnabled(true);
				}
				else
				{
					title.Text(resourceLoader.GetString(L"FailMessage/Title/Unknown"));
					img.Source(BitmapImage{ Uri{ L"ms-appx:///Assets//Picacgs//icon_exclamation_error.png" } });
					dialog.Content(box_value(message));
				}
				boder.Child(title);
				grid.Children().Append(boder);
				grid.Children().Append(img);
				dialog.Title(box_value(grid));
				dialog.ShowAsync();
			});
	}

	void MainPage::LayoutMessageShow(hstring const& message, bool const& isOpen)
	{
		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [message, isOpen, this]()
			{
				LayoutMessage().Title(message);
				LayoutMessage().IsOpen(isOpen);
			});
	}
	void MainPage::LayoutMessageShow(bool const& isOpen)
	{
		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [isOpen, this]()
			{
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
	bool MainPage::IsLogin()
	{
		return m_login;
	}
	void MainPage::IsLogin(bool const& value)
	{
		m_login = value;
	}

	Windows::Foundation::IAsyncAction MainPage::Login()
	{
		m_login = false;
		auto res = co_await m_bikaClient.Login(Email().Text(), Password().Password());

		if (res.Code()== -1)
		{
			ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200)
		{
			Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
			/*JsonObject tokens;
			if (loginData.Values().HasKey(L"AutoLogin") && loginData.Values().Lookup(L"AutoLogin").as<bool>())
			{
				if (loginData.Values().HasKey(L"tokens"))
				{
					tokens = JsonObject::Parse(loginData.Values().Lookup(L"tokens").as<hstring>());
				}
				tokens.Insert(Email().Text(), JsonValue::CreateStringValue(res.Token()));
				loginData.Values().Insert(L"tokens", box_value(tokens.Stringify()));
			}*/

			JsonObject emails;
			JsonObject passwords;
			JsonArray emailArray;
			if (loginData.Values().HasKey(L"emails"))
			{
				emails = JsonObject::Parse(loginData.Values().Lookup(L"emails").as<hstring>());
				emailArray = emails.GetNamedArray(L"emailArry");
			}
			emails.Insert(L"Last", JsonValue::CreateStringValue(Email().Text()));
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
			if(!m_user.IsPunched()) {
				co_await PunchIn();
				co_await SetPerson();
			}
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
		auto res = co_await m_bikaClient.PunchIn();
		auto action = res.Action();

		if (action == BikaClient::Responses::Actions::OK)
		{
			InfoBarMessageShow(resourceLoader.GetString(L"Message/AutoPunchIn"), resourceLoader.GetString(L"Message/PunchIned"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success);
		}
		else if (action == BikaClient::Responses::Actions::Fail)
		{
			InfoBarMessageShow(resourceLoader.GetString(L"Message/AutoPunchIn"), resourceLoader.GetString(L"Message/PunchIned"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Informational);
		}
		else
		{
			InfoBarMessageShow(resourceLoader.GetString(L"Message/AutoPunchIn"), res.Message(), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Error);
		}
	}


	void MainPage::StartInfoBar()
	{
		timer.Interval(std::chrono::milliseconds{ 100 });
		auto registrationtoken = timer.Tick({ this, &MainPage::OnTick });
		timer.Start();
	}

	void MainPage::ChangePassword(bool const& isOpen)
	{
		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [isOpen,this]()
			{
				OldPasswrod().Text(L"");
				NewPasswrod().Text(L"");
				ChangePasswordTip().IsOpen(isOpen);

			});
	}

	void MainPage::ChangeSignature(bool const& isOpen)
	{
		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [isOpen, this]()
			{
				NewSignature().Text(L"");
				ChangeSignatureTip().IsOpen(isOpen);
			});
	}

	void MainPage::OnTick(Windows::Foundation::IInspectable const& /* sender */,Windows::Foundation::IInspectable const& /* e */)
	{

		if (Info().Opacity() >= 0.1)
		{
			Info().Opacity(Info().Opacity() - 0.02);
		}
		else
		{
			Info().IsOpen(false);
			timer.Stop();
		}
	}

	void MainPage::InfoBarMessageShow(hstring const& title, hstring const& message, winrt::Microsoft::UI::Xaml::Controls::InfoBarSeverity const& severity)
	{

		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [title, message, severity, this]()
			{
				if (timer.IsEnabled()) timer.Stop();
				timer = Windows::UI::Xaml::DispatcherTimer();
				Info().IsOpen(false);
				Info().Opacity(1.0);
				Info().Message(message);
				Info().Title(title);
				Info().Severity(severity);
				Info().IsOpen(true);
				StartInfoBar();
				LayoutMessage().IsOpen(false);
			});
	}
	void MainPage::LogOut()
	{

		Dispatcher().RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, [this]()
			{
				m_login = false;
				m_user = BikaClient::Blocks::UserBlock{ nullptr };
				BigUserImg().ProfilePicture(BitmapImage{ Uri{ L"ms-appx:///Assets//Picacgs//placeholder_avatar_2.png" } });
				SmallUserImg().ProfilePicture(BitmapImage{ Uri{ L"ms-appx:///Assets//Picacgs//placeholder_avatar_2.png" } });
				UserName().Text(resourceLoader.GetString(L"Keyword/Default/Name"));
				UserLevel().Text(resourceLoader.GetString(L"Keyword/Default/Level"));
				UserSlogan().Text(resourceLoader.GetString(L"Keyword/Default/Slogan"));
				LoginViewShow(true);
			});

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
		LayoutMessageShow(false);
		LoginViewShow(false);
		if (res.Code() == -1)
		{
			ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200)
		{
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
				co_await GetKeywords();
			}
		}
		else if (res.Code() == 401 && res.Error() == L"1005")
		{
			ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());

		}
		else
		{
			ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());

		}

	}
	Windows::Foundation::IAsyncAction MainPage::GetKeywords()
	{
		auto res =  co_await m_bikaClient.Keywords() ;
		if (res.Code() == -1)
		{
			ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200)
		{
			Windows::Storage::ApplicationDataContainer historys = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Historys", Windows::Storage::ApplicationDataCreateDisposition::Always);
			if (historys.Values().HasKey(L"Search"))
			{
				auto y = Windows::Data::Json::JsonArray::Parse(historys.Values().Lookup(L"Search").as<hstring>());

				for (auto z : y)
				{
					m_suggestions.Append(winrt::make<KeywordBox>(z.GetString(), resourceLoader.GetString(L"Keyword/SearchHistory"), L"\xE81C"));
				}
			}
			for (auto x : res.Keywords())
			{
				m_suggestions.Append(winrt::make<bikabika::implementation::KeywordBox>(x.Tag(), resourceLoader.GetString(L"Keyword/Keywords"), L"\xE8EC"));
			}
		}
		else if (res.Code() == 401 && res.Error() == L"1005")
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

	BikaClient::BikaHttpClient MainPage::HttpClient()
	{
		return m_bikaClient;
	}

}

void winrt::bikabika::implementation::MainPage::LoginClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
{
	// 账号密码为空
	if (Email().Text() == L"" || Password().Password() == L"")
	{
		ContentDialogShow(BikaHttpStatus::UNKNOWN, resourceLoader.GetString(L"FailMessage/Message/Login/Blank"));
	}
	else
	{
		LayoutMessageShow(resourceLoader.GetString(L"Message/Logining"), true);
		auto login{ Login() };
	}
}
void winrt::bikabika::implementation::MainPage::ContentFrame_NavigationFailed(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& args)
{
}
void winrt::bikabika::implementation::MainPage::NavView_ItemInvoked(Windows::Foundation::IInspectable const&, muxc::NavigationViewItemInvokedEventArgs const& args)
{
	if (args.IsSettingsInvoked())
	{
		NavView_Navigate(L"settings", args.RecommendedNavigationTransitionInfo());
	}
	else if (args.InvokedItemContainer())
	{
		NavView_Navigate(winrt::unbox_value_or<winrt::hstring>(args.InvokedItemContainer().Tag(), L"").c_str(), args.RecommendedNavigationTransitionInfo());
	}
}
void winrt::bikabika::implementation::MainPage::NavView_Navigate(std::wstring navItemTag, Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& transitionInfo)
{
	winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
	winrt::Windows::UI::Xaml::Controls::Frame frame;
	for (auto item : ContentTabView().TabItems())
	{
		if (winrt::unbox_value_or<winrt::hstring>(item.as<winrt::Microsoft::UI::Xaml::Controls::TabViewItem>().Header(), L"") == resourceLoader.GetString(hstring{L"Header/" + navItemTag}))
		{
			ContentTabView().SelectedItem(item);
			return;
		}
	}
	if (navItemTag == L"settings")
	{

		symbol.Symbol(Symbol::Setting);
		frame.Navigate(winrt::xaml_typename<bikabika::SettingsPage>());
	}
	else if (navItemTag == L"Home")
	{
		frame.Navigate(winrt::xaml_typename<bikabika::HomePage>());
		symbol.Symbol(Symbol::Home);
	}
	else if (navItemTag == L"Classification")
	{
		symbol.Symbol(Symbol::AllApps);
		frame.Navigate(winrt::xaml_typename<bikabika::ClassificationPage>());
	}
	else if (navItemTag == L"User")
	{
		frame.Navigate(winrt::xaml_typename<bikabika::UserPage>());
		symbol.Symbol(Symbol::Contact);
	}
	else if (navItemTag == L"Download")
	{
		frame.Navigate(winrt::xaml_typename<bikabika::DownloadPage>());
		symbol.Symbol(Symbol::Download);
	}
	else return;
	CreateNewTab(frame, resourceLoader.GetString(hstring{ L"Header/" + navItemTag }) , symbol);
}
void winrt::bikabika::implementation::MainPage::UsersPic_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	PointerPoint currentPoint = e.GetCurrentPoint(NULL);
	PointerPointProperties props = currentPoint.Properties();
	if (m_login) {
		if (props.IsRightButtonPressed()) {
			Menu().ShowAt(sender.as<FrameworkElement>());
		}
		else if (props.IsLeftButtonPressed())
		{
			NavView_Navigate(L"User", Windows::UI::Xaml::Media::Animation::EntranceNavigationTransitionInfo());
		}
	}
	else {
		LoginTeachingTip().IsOpen(true);
	}
}
void winrt::bikabika::implementation::MainPage::AutoCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	if (sender.as<CheckBox>().IsChecked().GetBoolean())
	{
		RememberCheckBox().IsChecked(true);
	}
	Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
	loginData.Values().Insert(L"AutoLogin", box_value(AutoCheckBox().IsChecked().GetBoolean()));
}
void winrt::bikabika::implementation::MainPage::RememberCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	if (!sender.as<CheckBox>().IsChecked().GetBoolean())
	{
		AutoCheckBox().IsChecked(false);
	}
	Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
	loginData.Values().Insert(L"RememberMe", box_value(RememberCheckBox().IsChecked().GetBoolean()));
}

void winrt::bikabika::implementation::MainPage::ContentTabView_TabCloseRequested(winrt::Microsoft::UI::Xaml::Controls::TabView const& sender, winrt::Microsoft::UI::Xaml::Controls::TabViewTabCloseRequestedEventArgs const& args)
{
	uint32_t tabIndexFromControl;
	if (sender.TabItems().IndexOf(args.Tab(), tabIndexFromControl))
	{
		sender.TabItems().RemoveAt(tabIndexFromControl);
	}

}
void winrt::bikabika::implementation::MainPage::Grid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e)
{
	ContentTabView().Width(sender.as<Controls::Frame>().ActualWidth());
}
void winrt::bikabika::implementation::MainPage::NavView_PaneClosed(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args)
{
	ContentFrame().Margin(Thickness{ 47,0,0,0 });
	APPTitle().Visibility(Visibility::Collapsed);
	NavSmallImg().Visibility(Visibility::Visible);
	NavBigImg().Visibility(Visibility::Collapsed);
}
void winrt::bikabika::implementation::MainPage::NavView_PaneOpened(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Windows::Foundation::IInspectable const& args)
{
	ContentFrame().Margin(Thickness{ 179,0,0,0 });
	APPTitle().Visibility(Visibility::Visible);
	NavSmallImg().Visibility(Visibility::Collapsed);
	NavBigImg().Visibility(Visibility::Visible);
}
void winrt::bikabika::implementation::MainPage::Flyout_Opened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
{
	CatSearch().Text(L" ");
	CatSearch().ItemsSource(box_value(m_suggestions));
	CatSearch().Text(L"");
}
void winrt::bikabika::implementation::MainPage::LogOut_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	ContentDialog dialog = ContentDialog();
	StackPanel stack;
	stack.Orientation(Orientation::Horizontal);
	stack.Children().Append(SymbolIcon{ Symbol::LeaveChat });
	TextBlock text;
	text.Text(resourceLoader.GetString(L"Keyword/Tip/Tip"));
	stack.Children().Append(text);
	dialog.Title(stack);
	dialog.Content(box_value(resourceLoader.GetString(L"Keyword/Tip/LogOut")));
	dialog.PrimaryButtonText(resourceLoader.GetString(L"Keyword/Sure"));
	dialog.SecondaryButtonText(resourceLoader.GetString(L"Keyword/Cancel"));
	dialog.DefaultButton(ContentDialogButton::Secondary);
	dialog.IsPrimaryButtonEnabled(true);
	dialog.IsSecondaryButtonEnabled(true);
	dialog.PrimaryButtonClick([this](ContentDialog const&, ContentDialogButtonClickEventArgs const&) {
		Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
		if (loginData.Values().HasKey(L"AutoLogin") && loginData.Values().Lookup(L"AutoLogin").as<bool>())
		{
			loginData.Values().Insert(L"AutoLogin", box_value(false));
		}
		LogOut();
		});
	dialog.SecondaryButtonClick([](ContentDialog const&, ContentDialogButtonClickEventArgs const&) {
		return;
		});
	dialog.ShowAsync();
}
void winrt::bikabika::implementation::MainPage::ChangeSignature_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	ChangeSignature(true);
}
Windows::Foundation::IAsyncAction winrt::bikabika::implementation::MainPage::SetPassword_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	return Windows::Foundation::IAsyncAction();
}
/// <summary>
/// 菜单栏中修改密码按钮
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::MainPage::ChangePassword_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	ChangePassword(true);
}
/// <summary>
/// 密码框按回车响应
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::MainPage::LoginButton_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
{
	if (e.Key() == Windows::System::VirtualKey::Enter)
	{
		LoginClickHandler(sender, Windows::UI::Xaml::RoutedEventArgs{ nullptr });
	}
}
/// <summary>
/// 修改签名框按回车响应
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::MainPage::ChangePasswordButton_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
{
	if (e.Key() == Windows::System::VirtualKey::Enter)
	{
		ChangePasswordButton_Click(sender, Windows::UI::Xaml::RoutedEventArgs{ nullptr });
	}
}
/// <summary>
/// 检测搜索框内容更改
/// </summary>
/// <param name="sender"></param>
/// <param name="args"></param>
void winrt::bikabika::implementation::MainPage::CatSearch_TextChanged(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
{
	if (sender.Text() != L"" && (args.Reason() == AutoSuggestionBoxTextChangeReason::UserInput || (args.Reason() == AutoSuggestionBoxTextChangeReason::ProgrammaticChange && sender.Text() == L" ")))
	{
		if (!m_suggestIsChosen)
		{
			sender.ItemsSource(box_value(m_suggestions));
		}
		m_suggestIsChosen = false;
	}
}
/// <summary>
/// 搜索框提交
/// </summary>
/// <param name="sender"></param>
/// <param name="args"></param>
void winrt::bikabika::implementation::MainPage::CatSearch_QuerySubmitted(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args)
{

	Windows::Storage::ApplicationDataContainer historys = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Historys", Windows::Storage::ApplicationDataCreateDisposition::Always);
	hstring text = sender.Text();
	if (text == L"") return;
	if (historys.Values().HasKey(L"Search"))
	{
		int i;
		bool f = false;
		JsonArray searchHistorys = Windows::Data::Json::JsonArray::Parse(historys.Values().Lookup(L"Search").as<hstring>());
		for (i = 0; i < searchHistorys.Size(); i++)
		{
			if (text == searchHistorys.GetStringAt(i))
			{
				f = true;
				break;
			}
		}
		if (f)
		{
			searchHistorys.RemoveAt(i);
			m_suggestions.RemoveAt(i);
		}
		searchHistorys.InsertAt(0, Windows::Data::Json::JsonValue::CreateStringValue(text));
		historys.Values().Insert(L"Search", box_value(searchHistorys.Stringify()));
		m_suggestions.InsertAt(0, winrt::make<KeywordBox>(text, resourceLoader.GetString(L"Keyword/SearchHistory"), L"\xE81C"));
	}
	else {
		Windows::Data::Json::JsonArray json;
		json.InsertAt(0, Windows::Data::Json::JsonValue::CreateStringValue(text));
		historys.Values().Insert(L"Search", box_value(json.Stringify()));
		m_suggestions.InsertAt(0, winrt::make<KeywordBox>(text, resourceLoader.GetString(L"Keyword/SearchHistory"), L"\xE81C"));
	}
}
/// <summary>
/// 搜索框建议选择
/// </summary>
/// <param name="sender"></param>
/// <param name="args"></param>
void winrt::bikabika::implementation::MainPage::CatSearch_SuggestionChosen(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args)
{
	m_suggestIsChosen = true;
	hstring s = args.SelectedItem().as<bikabika::KeywordBox>().Keyword();
	sender.Text(s);
}
/// <summary>
/// 邮箱与密码与自动登录控制
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::MainPage::Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
	if (loginData.Values().HasKey(L"emails"))
	{
		JsonObject emails = JsonObject::Parse(loginData.Values().Lookup(L"emails").as<hstring>());
		if (emails.HasKey(L"Last"))
		{
			Email().Text(emails.GetNamedString(L"Last"));
		}
	}
	if (loginData.Values().HasKey(L"RememberMe") && loginData.Values().Lookup(L"RememberMe").as<bool>())
	{
		if (loginData.Values().HasKey(L"passwords"))
		{
			JsonObject passwords = JsonObject::Parse(loginData.Values().Lookup(L"passwords").as<hstring>());
			if (passwords.HasKey(Email().Text()))
			{
				Password().Password(passwords.GetNamedString(Email().Text()));
				AutoCheckBox().IsChecked(true);
			}
		}
	}
	if (loginData.Values().HasKey(L"AutoLogin") && loginData.Values().Lookup(L"AutoLogin").as<bool>())
	{
		LayoutMessageShow(resourceLoader.GetString(L"Message/Logining"), true);
		auto login{ Login() };
	}

}
/// <summary>
/// 删除搜索记录
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::MainPage::KeywordClose_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	auto border = sender.as<AppBarButton>().Parent().as<Grid>().Children().GetAt(0).as<Border>();
	auto grid = border.Child().as<Grid>();
	hstring keyword = ToolTipService::GetToolTip(border).as<ToolTip>().Content().as<hstring>();
	hstring keywordType = grid.Children().GetAt(1).as<TextBlock>().Text();
	for (uint32_t kIndex = 0; kIndex < m_suggestions.Size(); kIndex++)
	{
		auto x = m_suggestions.GetAt(kIndex);
		if (x.Keyword() == keyword && x.KeywordType() == keywordType)
		{
			m_suggestions.RemoveAt(kIndex);
			if (keywordType == resourceLoader.GetString(L"Keyword/SearchHistory"))
			{
				Windows::Storage::ApplicationDataContainer historys = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Historys", Windows::Storage::ApplicationDataCreateDisposition::Always);
				JsonArray searchHistorys = Windows::Data::Json::JsonArray::Parse(historys.Values().Lookup(L"Search").as<hstring>());
				searchHistorys.RemoveAt(kIndex);
				historys.Values().Insert(L"Search", box_value(searchHistorys.Stringify()));
			}
		}
	}
	CatSearch().ItemsSource(box_value(m_suggestions));
}
/// <summary>
/// 自动转换省略号
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::MainPage::Omit_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	TextBlock block = sender.as<TextBlock>();
	if (block.ActualWidth() > block.Width())
	{
		wstring text;
		int32_t i = 0;
		for (auto a:block.Text())
		{
			if (i == 6)break;
			text += a;
			i++;
		}
		block.Text(hstring{text+L" ..."});
	}
}




/// <summary>
/// 修改签名回车响应
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
void winrt::bikabika::implementation::MainPage::ChangeSignatureBox_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
{
	if (e.Key() == Windows::System::VirtualKey::Enter)
	{
		ChangeSignatureButton_Click(sender, Windows::UI::Xaml::RoutedEventArgs{ nullptr });
	}
}


/// <summary>
/// 修改密码按钮响应
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
/// <returns></returns>
Windows::Foundation::IAsyncAction winrt::bikabika::implementation::MainPage::ChangePasswordButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	if (OldPasswrod().Text() != L"" && NewPasswrod().Text() != L"")
	{
		LayoutMessageShow(resourceLoader.GetString(L"Message/Change"), true);
		auto res = co_await m_bikaClient.SetPassword(OldPasswrod().Text(), NewPasswrod().Text());

		if (res.Code() == -1)
		{
			ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200)
		{

			InfoBarMessageShow(resourceLoader.GetString(L"ChangePasswordButton/Content"), resourceLoader.GetString(L"Message/ChangeSuccess"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success);
			Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
			if (loginData.Values().HasKey(L"passwords"))
			{
				JsonObject passwords = JsonObject::Parse(loginData.Values().Lookup(L"passwords").as<hstring>());
				passwords.Insert(m_user.Email(), JsonValue::CreateStringValue(NewPasswrod().Text()));
				loginData.Values().Insert(L"passwords", box_value(passwords.Stringify()));
			}
			ChangePassword(false);
		}
		else if (res.Code() == 401 && res.Error() == L"1005")
		{
			ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());
		}
		else
		{
			ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
		}
		LayoutMessageShow(false);
	}
}

/// <summary>
/// 修改签名按钮响应
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
/// <returns></returns>
Windows::Foundation::IAsyncAction winrt::bikabika::implementation::MainPage::ChangeSignatureButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	if (NewSignature().Text() != L"")
	{
		LayoutMessageShow(resourceLoader.GetString(L"Message/Change"), true);
		auto res = co_await m_bikaClient.SetSlogan(NewSignature().Text());

		if (res.Code() == -1)
		{
			ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200)
		{
			ChangeSignature(false);
			InfoBarMessageShow(resourceLoader.GetString(L"ChangeSignatureButton/Content"), resourceLoader.GetString(L"Message/ChangeSuccess"), Microsoft::UI::Xaml::Controls::InfoBarSeverity::Success);
			co_await SetPerson();
		}
		else if (res.Code() == 401 && res.Error() == L"1005")
		{
			ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());
		}
		else
		{
			ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
		}
		LayoutMessageShow(false);
	}
}
