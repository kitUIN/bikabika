#include "pch.h"
#include "Login.h"
#if __has_include("Login.g.cpp")
#include "Login.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::ViewManagement;
using namespace Windows::Foundation;
namespace winrt::bikabika::implementation
{
	Login::Login()
	{
		InitializeComponent();
		NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled);
	}
	bikabika::BikaHttp Login::BikaHttpAPI()
	{
		return m_bikaHttp;
	}
	
	
	Windows::Foundation::IAsyncAction Login::ReadAccountJson()
	{	// 自动登陆载入数据
		try 
		{
			bool f{ co_await m_fileCheckTool.CheckFileAccount() };
			Windows::Data::Json::JsonObject account{ co_await m_fileCheckTool.GetAccount() };
			Email().Text(account.GetNamedString(L"email"));
			bool flag = account.GetNamedBoolean(L"isChecked");
			RememberCheckBox().IsChecked(flag);
			if(flag) Password().Password(account.GetNamedString(L"password"));
			//else Password().Password(L"");
		}
		catch (winrt::hresult_error const& ex) 
		{
		}
	}
	Windows::Foundation::IAsyncAction Login::WriteAccountJson(hstring email,hstring password,hstring token,boolean isCheck)
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
		if (isCheck !=	(boolean)account.GetNamedBoolean(L"isChecked") )
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
	Windows::Foundation::IAsyncAction Login::LoginAccount()
	{	

		auto ress = co_await m_bikaHttp.Login(Email().Text(), Password().Password());
		Progressing().IsActive(false);
		if (ress[1] == 'T') {
			
			auto show{ PicErrorDialog().ShowAsync() };
		}
		else if (ress[1] == 'E') {
			auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
			LoginContentDialog().Content(box_value(ress));
			LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
			auto show{ LoginContentDialog().ShowAsync() };
		}
		else 
		{
			Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(ress);
			double code = resp.GetNamedNumber(L"code");
			if (code == (double)400)
			{	//账号或密码错误
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
				LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginPasswordFail/Content")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				
				auto show{ LoginContentDialog().ShowAsync() };
				Password().Password(L"");
			}
			else if (code == (double)200)
			{	//登陆成功
				extern winrt::hstring token;
				token = resp.GetNamedObject(L"data").GetNamedString(L"token");
				auto processOp{ WriteAccountJson(Email().Text(),Password().Password(), token,RememberCheckBox().IsChecked().GetBoolean()) };
				co_await SetPerson();
				Frame().Navigate(winrt::xaml_typename<bikabika::HomePage>());

			}
			else
			{
				//未知
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
				LoginContentDialog().Content(box_value(to_hstring(code) + L":" + resp.GetNamedString(L"message")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ LoginContentDialog().ShowAsync() };
			}
		}
		
	}
	Windows::Foundation::IAsyncAction Login::SetPerson()
	{
		Progressing().IsActive(true);
		hstring personInfo = co_await m_bikaHttp.PersonInfo();
		Progressing().IsActive(false);
		if (personInfo[1] == 'T') {
			
			auto show{ PicErrorDialog().ShowAsync() };
		}
		else if(personInfo[1] == 'E'){
			auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
			LoginContentDialog().Content(box_value(personInfo));
			LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
			auto show{ LoginContentDialog().ShowAsync() };
		}
		else {
			Windows::Data::Json::JsonObject personData = Windows::Data::Json::JsonObject::Parse(personInfo);
			double code = personData.GetNamedNumber(L"code");
			if (code == (double)401 && personData.GetNamedString(L"error") == L"1005")
			{	//缺少鉴权
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
				LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginAuthFail/Content")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ LoginContentDialog().ShowAsync() };
			}
			else if (code == (double)400)
			{
				//请求无效
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
				LoginContentDialog().Content(box_value(personData.GetNamedString(L"message")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ LoginContentDialog().ShowAsync() };

			}
			else if (code == (double)200)
			{
				auto personInfo = personData.GetNamedObject(L"data").GetNamedObject(L"user");
				extern winrt::hstring userName;
				extern winrt::hstring userLevel;
				extern winrt::hstring userImage;
				extern winrt::hstring serverStream;
				userName = personInfo.GetNamedString(L"name");
				userLevel = L"Lv." + to_hstring(personInfo.GetNamedNumber(L"level"));
				userImage = serverStream + L"/static/" + personInfo.GetNamedObject(L"avatar").GetNamedString(L"path");
			}
			else
			{
				//未知
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
				LoginContentDialog().Content(box_value(to_hstring(code) + L":" + personData.GetNamedString(L"message")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ LoginContentDialog().ShowAsync() };
			}
		}
		
	}
	//登录按钮
	void Login::LoginClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		
		if (Email().Text() == L""|| Password().Password() == L"")
		{
			// 账号密码为空
			auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
			LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginBlankFail/Content")));
			LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
			auto show{ LoginContentDialog().ShowAsync() };
			//Email().Text(L"");
			//Password().Password(L"");
		}
		else 
		{	
			//auto client = winrt::make<BikaHttpClient>();
			Progressing().IsActive(true);
			auto login{ LoginAccount() };
		}
	}
	void winrt::bikabika::implementation::Login::Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		//OutputDebugStringW(L"\n\n?????\n\n");
		auto acc{ ReadAccountJson() };
		auto bcc{ AutoLogin() };
		
	}
	Windows::Foundation::IAsyncAction Login::AutoLogin()
	{
		Progressing().IsActive(true);
		bool f{ co_await m_fileCheckTool.CheckFileAccount() };
		Progressing().IsActive(false);
		if (f) {
			Windows::Data::Json::JsonObject account{ co_await m_fileCheckTool.GetAccount() };
			if (account.GetNamedBoolean(L"isChecked")) {
				hstring personInfo = co_await m_bikaHttp.PersonInfo();
				
				if (personInfo[1] == 'T') {
					auto show{ PicErrorDialog().ShowAsync() };
				}
				else if (personInfo[1] == 'E') {
					auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
					LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
					LoginContentDialog().Content(box_value(personInfo));
					LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
					auto show{ LoginContentDialog().ShowAsync() };
				}
				else
				{
					Windows::Data::Json::JsonObject personData = Windows::Data::Json::JsonObject::Parse(personInfo);
					double code = personData.GetNamedNumber(L"code");
					if (code == (double)401 && personData.GetNamedString(L"error") == L"1005")
					{
						auto login{ LoginAccount() };
					}
					else if (code == (double)200)
					{
						auto personInfo = personData.GetNamedObject(L"data").GetNamedObject(L"user");
						extern winrt::hstring userName;
						extern winrt::hstring userLevel;
						extern winrt::hstring userImage;
						extern winrt::hstring serverStream;
						userName = personInfo.GetNamedString(L"name");
						userLevel = L"Lv." + to_hstring(personInfo.GetNamedNumber(L"level"));
						userImage = serverStream + L"/static/" + personInfo.GetNamedObject(L"avatar").GetNamedString(L"path");
						Frame().Navigate(winrt::xaml_typename<bikabika::HomePage>());

					}
					else
					{
						//未知
						auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
						LoginContentDialog().Title(box_value(resourceLoader.GetString(L"Fail/Title")));
						LoginContentDialog().Content(box_value(to_hstring(code) + L":" + personData.GetNamedString(L"message")));
						LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
						auto show{ LoginContentDialog().ShowAsync() };
					}
				}
			}
		}
	}
}



