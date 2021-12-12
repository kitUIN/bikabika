#include "pch.h"
#include "LoginPage.h"
#if __has_include("LoginPage.g.cpp")
#include "LoginPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::ViewManagement;
using namespace Windows::Foundation;
namespace winrt::bikabika::implementation
{
	LoginPage::LoginPage()
	{
		InitializeComponent();
		//NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled);
	}

	Windows::Foundation::IAsyncAction LoginPage::ReadAccountJson()
	{	// 自动登陆载入数据
		try
		{
			bool f{ co_await m_fileCheckTool.CheckFileAccount() };
			Windows::Data::Json::JsonObject account{ co_await m_fileCheckTool.GetAccount() };
			Email().Text(account.GetNamedString(L"email"));
			bool flag = account.GetNamedBoolean(L"isChecked");
			RememberCheckBox().IsChecked(flag);
			if (flag) Password().Password(account.GetNamedString(L"password"));
			//else Password().Password(L"");
		}
		catch (winrt::hresult_error const& ex)
		{
		}
	}
	Windows::Foundation::IAsyncAction LoginPage::WriteAccountJson(hstring email, hstring password, hstring token, boolean isCheck)
	{
		// 读入用户配置文件
		bool f{ co_await m_fileCheckTool.CheckFileAccount() };
		Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
		Windows::Storage::StorageFolder folderDB{ co_await localFolder.GetFolderAsync(L"bikabikadb") };
		auto accountFile{ co_await folderDB.GetFileAsync(L"account.json") };
		Windows::Data::Json::JsonObject account{ co_await m_fileCheckTool.GetAccount() };
		if (account.GetNamedString(L"email") != email)
		{
			account.SetNamedValue(L"email", Windows::Data::Json::JsonValue::CreateStringValue(email));
		}
		if (account.GetNamedString(L"password") != password)
		{
			account.SetNamedValue(L"password", Windows::Data::Json::JsonValue::CreateStringValue(password));
		}
		if (isCheck != (boolean)account.GetNamedBoolean(L"isChecked"))
		{
			account.SetNamedValue(L"isChecked", Windows::Data::Json::JsonValue::CreateBooleanValue(isCheck));
		}
		if (account.GetNamedString(L"token") != password)
		{
			account.SetNamedValue(L"token", Windows::Data::Json::JsonValue::CreateStringValue(token));
		}
		hstring data = account.Stringify();
		co_await Windows::Storage::FileIO::WriteTextAsync(accountFile, data);
	}
	void LoginPage::ContentDialogShow(hstring const& mode, hstring const& message)
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
			}
			else if (mode == L"LoginError")
			{
				HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailLoginPassword")));
			}
			else if (mode == L"Unknown")
			{
				Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(message);
				HttpContentDialog().Content(box_value(to_hstring(resp.GetNamedNumber(L"code")) + L":" + resp.GetNamedString(L"message")));
			}
			else if (mode == L"1005")
			{
				HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailAuth")));
			}
			else if (mode == L"Blank")
			{
				HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailLoginBlank")));
			}
			auto show{ HttpContentDialog().ShowAsync() };
		}
	}
	Windows::Foundation::IAsyncAction LoginPage::LoginAccount()
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
				extern winrt::hstring token;
				token = resp.GetNamedObject(L"data").GetNamedString(L"token");
				auto processOp{ WriteAccountJson(Email().Text(),Password().Password(), token,RememberCheckBox().IsChecked().GetBoolean()) };
				Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LayoutMessage().Title(resourceLoader.GetString(L"Logining"));
				LayoutMessage().IsOpen(true);
				co_await SetPerson();
				
			}
			//未知
			else
			{
				ContentDialogShow(L"Unknown", ress);
			}
		}

	}
	Windows::Foundation::IAsyncAction LoginPage::SetPerson()
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
				ContentDialogShow(L"1005", L"");
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
				//auto nav = Frame().Parent().as<winrt::Microsoft::UI::Xaml::Controls::NavigationView>();
				//nav.SelectedItem(nav.MenuItems().GetAt(3));

				//Frame().Navigate(winrt::xaml_typename<bikabika::ClassificationPage>());
			}
			//未知
			else 
			{
				ContentDialogShow(L"Unknown", personInfo);
			}
		}

	}
	//登录按钮
	void LoginPage::LoginClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		// 账号密码为空
		if (Email().Text() == L"" || Password().Password() == L"")
		{
			ContentDialogShow(L"Blank", L"");
		}
		else
		{
			auto login{ LoginAccount() };
		}
	}
	void winrt::bikabika::implementation::LoginPage::Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		
		auto acc{ ReadAccountJson() };
		auto bcc{ AutoLogin() };

	}
	//自动登录
	Windows::Foundation::IAsyncAction LoginPage::AutoLogin()
	{
		Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };

		LayoutMessage().Title(resourceLoader.GetString(L"AutoLogining"));
		LayoutMessage().IsOpen(true);
		bool f{ co_await m_fileCheckTool.CheckFileAccount() };
		if (f) {
			Windows::Data::Json::JsonObject account{ co_await m_fileCheckTool.GetAccount() };
			if (account.GetNamedBoolean(L"isChecked")) co_await SetPerson();
		}
	}
}



