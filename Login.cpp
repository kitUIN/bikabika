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
			Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
			Windows::Storage::StorageFolder folderDB{ co_await localFolder.GetFolderAsync(L"bikabikadb") };
			auto accountFile{ co_await folderDB.GetFileAsync(L"account.json") };
			Windows::Storage::Streams::IRandomAccessStream stream{ co_await accountFile.OpenAsync(Windows::Storage::FileAccessMode::Read) };
			uint64_t size{ stream.Size() };
			Windows::Storage::Streams::IInputStream inputStream{ stream.GetInputStreamAt(0) };
			Windows::Storage::Streams::DataReader dataReader{ inputStream };
			unsigned int cBytesLoaded{ co_await dataReader.LoadAsync(size) };
			winrt::hstring streamText{ dataReader.ReadString(cBytesLoaded) };


			Windows::Data::Json::JsonObject account = Windows::Data::Json::JsonObject::Parse(streamText);
			//OutputDebugStringW(account.ToString().c_str());
			//OutputDebugStringW(L"\n");
			Email().Text(account.GetNamedString(L"email"));
			Password().Password(account.GetNamedString(L"password"));
			RememberCheckBox().IsChecked(account.GetNamedBoolean(L"isChecked"));

		}
		catch (winrt::hresult_error const& ex) 
		{
		}
	}
	Windows::Foundation::IAsyncAction Login::WriteAccountJson(hstring email,hstring password,hstring token,boolean isCheck)
	{
		// 读入用户配置文件
		Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
		Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };
		auto accountFile{co_await folder.CreateFileAsync(L"account.json", Windows::Storage::CreationCollisionOption::OpenIfExists)};
		auto accountData{co_await Windows::Storage::FileIO::ReadTextAsync(accountFile)};
		// 序列化json
		Windows::Data::Json::JsonObject account = Windows::Data::Json::JsonObject::Parse(accountData);
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

		hstring ress = co_await m_bikaHttp.Login(Email().Text(), Password().Password());
		Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(ress);
		
		double code = resp.GetNamedNumber(L"code");
		if (code == (double)400)
		{	//账号或密码错误
			auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoginPasswordFail/Title")));
			LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginPasswordFail/Content")));
			LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"LoginPasswordFail/CloseButtonText"));
			Progressing().IsActive(false);
			auto show{ LoginContentDialog().ShowAsync() };
			Password().Password(L"");
		}
		else if (code == (double)200)
		{	//登陆成功

			auto processOp{ WriteAccountJson(Email().Text(),Password().Password(), resp.GetNamedObject(L"data").GetNamedString(L"token"),RememberCheckBox().IsChecked().GetBoolean()) };
			co_await SetPerson();
			
			Progressing().IsActive(false);
			
			Frame().Navigate(winrt::xaml_typename<bikabika::HomePage>(), winrt::box_value(L"HELLO WORLD!"));

		}
	}
	Windows::Foundation::IAsyncAction Login::SetPerson()
	{
		hstring personInfo = co_await m_bikaHttp.PersonInfo();
		Windows::Data::Json::JsonObject personData = Windows::Data::Json::JsonObject::Parse(personInfo);
		double code = personData.GetNamedNumber(L"code");
		if (code == (double)400)
		{
			
			auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoginPasswordFail/Title")));
			LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginPasswordFail/Content")));
			LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"LoginPasswordFail/CloseButtonText"));
			auto show{ LoginContentDialog().ShowAsync() };

		}
		else if (code == (double)200)
		{
			auto personInfo = personData.GetNamedObject(L"data").GetNamedObject(L"user");
			//Frame().Navigate(winrt::xaml_typename<bikabika::MainPage>(), winrt::box_value(personData.GetNamedObject(L"data").GetNamedObject(L"user").Stringify()));
			extern winrt::hstring userName;
			extern winrt::hstring userLevel;
			extern winrt::hstring userImage;
			extern winrt::hstring serverStream;
			userName = personInfo.GetNamedString(L"name");
			userLevel = L"Lv." + to_hstring(personInfo.GetNamedNumber(L"level"));
			userImage = serverStream+L"/static/"+personInfo.GetNamedObject(L"avatar").GetNamedString(L"path");

		}
	}
	//登录按钮
	void Login::LoginClickHandler(IInspectable const&, RoutedEventArgs const&)
	{
		
		if (Email().Text() == L""|| Password().Password() == L"")
		{
			// 账号密码为空
			auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoginBlankFail/Title")));
			LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginBlankFail/Content")));
			LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"LoginBlankFail/CloseButtonText"));
			auto show{ LoginContentDialog().ShowAsync() };
			//Email().Text(L"");
			//Password().Password(L"");
		}
		else 
		{	
			//auto client = winrt::make<BikaHttpClient>();
			Progressing().IsActive(true);
			try
			{
				auto login{ LoginAccount() };
			}
			catch (winrt::hresult_error const& ex)
			{
				winrt::hresult hr = ex.code(); // HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND).
				winrt::hstring message = ex.message(); // The system cannot find the file specified.
				Progressing().IsActive(false);
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoginPasswordFail/Title")));
				LoginContentDialog().Content(box_value(message));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"LoginPasswordFail/CloseButtonText"));
				Progressing().IsActive(false);
				auto show{ LoginContentDialog().ShowAsync() };
			}
			
			
			
			
			
		}
	}
	void winrt::bikabika::implementation::Login::Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		//OutputDebugStringW(L"\n\n?????\n\n");
		auto acc{ ReadAccountJson() };

	}
}



