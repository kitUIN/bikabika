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

namespace winrt::bikabika::implementation
{

	
	MainPage::MainPage()
	{
		
		InitializeComponent();
		Windows::Storage::ApplicationDataContainer serversSettings = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Servers", Windows::Storage::ApplicationDataCreateDisposition::Always);
		Windows::Storage::ApplicationDataContainer userData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"User", Windows::Storage::ApplicationDataCreateDisposition::Always);
		if (!serversSettings.Values().HasKey(L"picServer1")) serversSettings.Values().Insert(L"picServer1", box_value(L"https://storage1.picacomic.com"));
		if (!serversSettings.Values().HasKey(L"picServer2")) serversSettings.Values().Insert(L"picServer2", box_value(L"https://s2.picacomic.com"));
		if (!serversSettings.Values().HasKey(L"picServer3")) serversSettings.Values().Insert(L"picServer3", box_value(L"https://s3.picacomic.com"));
		if (!serversSettings.Values().HasKey(L"picServersCurrent")) serversSettings.Values().Insert(L"picServersCurrent", box_value(L"https://storage1.picacomic.com"));
		
		m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
			(L"home", winrt::xaml_typename<bikabika::HomePage>()));
		m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
			(L"classification", winrt::xaml_typename<bikabika::ClassificationPage>()));
		m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
			(L"account", winrt::xaml_typename<bikabika::UserPage>()));
		m_pages.push_back(std::make_pair<std::wstring, Windows::UI::Xaml::Interop::TypeName>
			(L"settings", winrt::xaml_typename<bikabika::SettingsPage>()));
		Window::Current().SetTitleBar(AppTitleBar());
		Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		LoginTeachingTip().Title(resourceLoader.GetString(L"LoginButton/Content"));
		LoginTeachingTip().IsOpen(true);
		NavHome().IsEnabled(false);
		NavClassification().IsEnabled(false);
		NavAccount().IsEnabled(false);
	}





	
	void MainPage::NavView_Loaded(
		Windows::Foundation::IInspectable const& /* sender */,
		Windows::UI::Xaml::RoutedEventArgs const& /* args */)
	{
		//NavView_Navigate(L"login",Windows::UI::Xaml::Media::Animation::EntranceNavigationTransitionInfo());
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
			//m_userViewModel.User().Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ L"https://storage1.picacomic.com/static/0788a77a-81e4-46a5-9206-c424226bed07.jpg" } });
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

	bikabika::UserViewModel MainPage::MainUserViewModel()
	{
		return m_userViewModel;
	}

	

	/*
	* void MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
		auto propertyValue{ e.Parameter().as<Windows::Foundation::IPropertyValue>() };
		if (propertyValue.Type() == Windows::Foundation::PropertyType::String)
		{
			auto ss = winrt::unbox_value<winrt::hstring>(e.Parameter());
			Windows::Data::Json::JsonObject personData = Windows::Data::Json::JsonObject::Parse(ss);
			Uri url(L"https://storage1.picacomic.com/static/" + personData.GetNamedObject(L"avatar").GetNamedString(L"path"));
			Windows::UI::Xaml::Media::Imaging::BitmapImage source(url);
			UsersPic().ProfilePicture(source);
		}
		else
		{
			__super::OnNavigatedTo(e);
		}

	}
	Windows::Foundation::IAsyncAction MainPage::CreateLoginPage(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
	{	// 新建页面

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
		f.Navigate(xaml_typename<bikabika::LoginPage>(), nullptr);
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
	}*/

	
	void  winrt::bikabika::implementation::MainPage::CatSearch_TextChanged(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
	{
		OutputDebugStringW(L"\n\n\n666\n\n\n");
		if (!m_suggestIsChosen)
		{
			sender.ItemsSource(box_value(m_suggestions));
		}
		m_suggestIsChosen = false;
	}
	void winrt::bikabika::implementation::MainPage::CatSearch_QuerySubmitted(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args)
	{
		extern bool loadComicFlag;
		loadComicFlag = true;
		ContentFrame().Navigate(winrt::xaml_typename<bikabika::ComicsPage>(), box_value(single_threaded_vector<hstring>({ L"Search",sender.Text(), to_hstring("dd") })));
		sender.Text(L"");
	}


	void winrt::bikabika::implementation::MainPage::CatSearch_SuggestionChosen(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args)
	{
		m_suggestIsChosen = true;
		hstring s = args.SelectedItem().as<bikabika::KeywordsBox>().GetKeywords();
		OutputDebugStringW(s.c_str());
		sender.Text(s);
	}
	void MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
		__super::OnNavigatedTo(e);
	}
	
	Windows::Foundation::IAsyncAction  MainPage::ContentDialogShow(hstring const& mode, hstring const& message)
	{
		Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };

		if (mode == L"Timeout") {

			auto show{ PicErrorDialog().ShowAsync() };
		}
		else {
			HttpContentDialog().Title(box_value(resourceLoader.GetString(L"FailLoginTitle")));
			HttpContentDialog().CloseButtonText(resourceLoader.GetString(L"FailCloseButtonText"));
			if (mode == L"Error")
			{
				HttpContentDialog().Content(box_value(message));
				auto show{ co_await HttpContentDialog().ShowAsync() };
			}
			else if (mode == L"LoginError")
			{
				HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailLoginPassword")));
				auto show{ HttpContentDialog().ShowAsync() };
			}
			else if (mode == L"Unknown")
			{
				Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(message);
				HttpContentDialog().Content(box_value(to_hstring(resp.GetNamedNumber(L"code")) + L":" + resp.GetNamedString(L"message")));
				auto show{ co_await HttpContentDialog().ShowAsync() };

			}
			else if (mode == L"1005")
			{
				HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailAuth")));
				extern bool m_login;
				m_login = false;
				auto show{ co_await HttpContentDialog().ShowAsync() };
				if (show == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::None)
				{
					Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
					LoginTeachingTip().Title(resourceLoader.GetString(L"LoginButton/Content"));
					LoginTeachingTip().IsOpen(true);
				}
			}
			else if (mode == L"Blank")
			{
				HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailLoginBlank")));
				auto show{ HttpContentDialog().ShowAsync() };
			}
			
		}
	}
	Windows::Foundation::IAsyncAction MainPage::Login()
	{
		
		auto ress = co_await m_bikaHttp.Login(Email().Text(), Password().Password());
		LayoutMessage().IsOpen(false);
		if (ress[1] == 'T')
		{
			ContentDialogShow(L"Timeout", L"");
		}
		else if (ress[1] == 'E') {
			ContentDialogShow(L"Error", ress);
		}
		else
		{
			Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(ress);
			double code = resp.GetNamedNumber(L"code");
			//账号或密码错误
			if (code == (double)400)
			{
				ContentDialogShow(L"LoginError", L"");
				Password().Password(L"");
			}
			//登陆成功
			else if (code == (double)200)
			{
				Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
				loginData.Values().Insert(L"token", box_value(resp.GetNamedObject(L"data").GetNamedString(L"token")));
				loginData.Values().Insert(L"email", box_value(Email().Text()));
				loginData.Values().Insert(L"password", box_value(Password().Password()));
				Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LayoutMessage().Title(resourceLoader.GetString(L"Logining"));
				LayoutMessage().IsOpen(true);
				NavHome().IsEnabled(true);
				NavClassification().IsEnabled(true);
				NavAccount().IsEnabled(true);
				co_await SetPerson();
				
			}
			//未知
			else
			{
				ContentDialogShow(L"Unknown", ress);
			}
		}

	}
	Windows::Foundation::IAsyncAction MainPage::SetPerson()
	{
		auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		hstring personInfo = co_await m_bikaHttp.PersonInfo();
		LayoutMessage().IsOpen(false);
		if (personInfo[1] == 'T') {
			ContentDialogShow(L"Timeout", L"");
		}
		else if (personInfo[1] == 'E') {
			ContentDialogShow(L"Error", personInfo);
		}
		else {
			Windows::Data::Json::JsonObject personData = Windows::Data::Json::JsonObject::Parse(personInfo);
			double code = personData.GetNamedNumber(L"code");
			//缺少鉴权
			if (code == (double)401 && personData.GetNamedString(L"error") == L"1005")
			{
				co_await Login();
				//ContentDialogShow(L"1005", L"");
			}
			//请求无效
			else if (code == (double)400)
			{
				ContentDialogShow(L"Error", personInfo);
			}
			else if (code == (double)200)
			{
				Windows::Storage::ApplicationDataContainer userData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"User", Windows::Storage::ApplicationDataCreateDisposition::Always);
				auto personInfo = personData.GetNamedObject(L"data").GetNamedObject(L"user");
				userData.Values().Insert(L"personInfo", box_value(personInfo.Stringify()));
				LoginTeachingTip().IsOpen(false);
				extern bool m_login;
				m_login = true;
				Windows::Storage::ApplicationDataContainer serversSettings = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Servers", Windows::Storage::ApplicationDataCreateDisposition::Always);
				if (userData.Values().HasKey(L"personInfo"))
				{
					Windows::Data::Json::JsonObject personInfo = winrt::Windows::Data::Json::JsonObject::Parse(unbox_value<winrt::hstring>(userData.Values().TryLookup(L"personInfo")));
					hstring name = personInfo.GetNamedString(L"name");
					hstring slogan = L"\"" + to_hstring(personInfo.GetNamedString(L"slogan")) + L"\"";
					UserInfomation().Text(slogan);
					if (name != m_userViewModel.User().Name()) m_userViewModel.User().Name(name);
					hstring level = L"Lv." + to_hstring(personInfo.GetNamedNumber(L"level"));
					if (level != m_userViewModel.User().Level()) m_userViewModel.User().Level(level);
					hstring img = unbox_value<winrt::hstring>(serversSettings.Values().Lookup(L"picServersCurrent")) + L"/static/" + personInfo.GetNamedObject(L"avatar").GetNamedString(L"path");
					if (img != m_userViewModel.User().Img().UriSource().ToString()) {
						m_userViewModel.User().Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ img} });
					}
				}
				
				NavHome().IsEnabled(true);
				NavClassification().IsEnabled(true);
				NavAccount().IsEnabled(true);
				if (m_firstArrive) {
					NavView().SelectedItem(NavView().MenuItems().GetAt(1));
					ContentFrame().Navigate(winrt::xaml_typename<bikabika::HomePage>());
					m_firstArrive = false;
					co_await GetKeywords();
				}
				
			}
			//未知
			else
			{
				ContentDialogShow(L"Unknown", personInfo);
			}
		}

	}
	//登录按钮
	void MainPage::LoginClickHandler(Windows::Foundation::IInspectable const& /*sender*/ , Windows::UI::Xaml::RoutedEventArgs const& /*args*/)
	{
		// 账号密码为空
		if (Email().Text() == L"" || Password().Password() == L"")
		{
			ContentDialogShow(L"Blank", L"");
		}
		else
		{
			Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LayoutMessage().Title(resourceLoader.GetString(L"Logining"));
			LayoutMessage().IsOpen(true);
			auto login{ Login() };
		}
	}
	Windows::Foundation::IAsyncAction MainPage::GetKeywords()
	{
		hstring res{ co_await m_bikaHttp.Keywords() };
		if (res[1] == 'T')
		{
			ContentDialogShow(L"Timeout", L"");
		}
		else if (res[1] == 'E') {
			ContentDialogShow(L"Error", res);
		}
		else
		{
			Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(res);
			double code = resp.GetNamedNumber(L"code");
			if (code == (double)200)
			{
				Windows::Storage::ApplicationDataContainer userData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"User", Windows::Storage::ApplicationDataCreateDisposition::Always);
				auto keywords = resp.GetNamedObject(L"data").GetNamedArray(L"keywords");
				userData.Values().Insert(L"keywords", box_value(keywords.Stringify()));
				for (auto x : keywords)
				{
					m_suggestions.Append(winrt::make<KeywordsBox>(x.GetString(), L"大家都在搜", L"[TAG]", winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage(winrt::Windows::Foundation::Uri(L"ms-appx:///Assets//Picacgs//tag.png"))));
				}
			}
			//未知
			else
			{
				ContentDialogShow(L"Unknown", res);
			}
		}
	}
	void winrt::bikabika::implementation::MainPage::Password_Loaded(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
	{

		Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
		if (auto x = loginData.Values().TryLookup(L"email"))
		{
			Email().Text(unbox_value<hstring>(x));
		}
		
		if (auto y = loginData.Values().TryLookup(L"rememberMe"))
		{
			if (unbox_value<bool>(y))
			{
				RememberCheckBox().IsChecked(unbox_value<bool>(y));
				if (auto z = loginData.Values().TryLookup(L"password"))
				{
					Password().Password(unbox_value<hstring>(z));
				}
				if (auto s = loginData.Values().TryLookup(L"autoLogin"))
				{
					OutputDebugStringW(to_hstring(unbox_value<bool>(s)).c_str());
					AutoCheckBox().IsChecked(unbox_value<bool>(s));

				}
			}
			else
			{
				Password().Password(L"");
			}
			
		}
		
		auto bcc{ AutoLogin() };
	}
	hstring MainPage::PicPath()
	{
		return m_picPath;
	}
	//自动登录
	Windows::Foundation::IAsyncAction MainPage::AutoLogin()
	{
		Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
		if (auto x = loginData.Values().TryLookup(L"autoLogin"))
		{
			if (unbox_value<bool>(x))
			{
				Windows::Data::Json::JsonObject account{ co_await m_fileCheckTool.GetAccount() };
				if (auto s = loginData.Values().TryLookup(L"rememberMe"))
				{
					if (unbox_value<bool>(s))
					{
						Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
						LayoutMessage().Title(resourceLoader.GetString(L"AutoLogining"));
						LayoutMessage().IsOpen(true);
						co_await SetPerson();
					}
				}

			}
		}
	}
	void winrt::bikabika::implementation::MainPage::UsersPic_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
	{
		extern bool m_login;
		if (m_login)
		{
			NavView().SelectedItem(NavView().MenuItems().GetAt(4));
			ContentFrame().Navigate(xaml_typename<UserPage>());
		}
		else
		{
			Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginTeachingTip().Title(resourceLoader.GetString(L"LoginButton/Content"));
			LoginTeachingTip().IsOpen(true);
		}
		
	}
}













void winrt::bikabika::implementation::MainPage::AutoCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	if (AutoCheckBox().IsChecked().GetBoolean())
	{
		RememberCheckBox().IsChecked(true);
	}
	Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
	loginData.Values().Insert(L"autoLogin", box_value(RememberCheckBox().IsChecked().GetBoolean()));
}


void winrt::bikabika::implementation::MainPage::RememberCheckBox_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	
	Windows::Storage::ApplicationDataContainer loginData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"LoginData", Windows::Storage::ApplicationDataCreateDisposition::Always);
	loginData.Values().Insert(L"rememberMe", box_value(RememberCheckBox().IsChecked().GetBoolean()));
}
