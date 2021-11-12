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
		
	}
	bikabika::BikaHttp Login::BikaHttpAPI()
	{
		return m_bikaHttp;
	}
	
	Windows::Foundation::IAsyncAction CheckFile(hstring fileName)
	{   // 检测数据文件
		boolean f = false;
		Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
		for (auto const& folder : co_await localFolder.GetFoldersAsync())
		{
			if (folder.Name() == L"bikabikadb")
			{
				f = true;
				break;
			}
		}
		for (auto const& file : co_await localFolder.GetFilesAsync())
		{
			if (file.Name() == fileName)
			{
				f = true;
				break;
			}
		}

		
	}
	Windows::Foundation::IAsyncAction Login::ReadAccountJson()
	{	// 自动登陆载入数据
		try 
		{
			boolean f = false;
			co_await winrt::resume_background();
			Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
			for (auto const& folder : co_await localFolder.GetFoldersAsync())
			{
				if (folder.Name() == L"bikabikadb")
				{
					Windows::Storage::StorageFolder folder{ co_await localFolder.GetFolderAsync(L"bikabikadb") };

					for (auto const& file : co_await folder.GetFilesAsync())
					{
						if (file.Name() == L"account.json")
						{
							f = true;
							break;
						}
					}
					break;
				}
			}
			
			if (f)
			{
				Windows::Storage::StorageFolder folder{ co_await localFolder.GetFolderAsync(L"bikabikadb") };
				auto accountFile{ co_await folder.GetFileAsync(L"account.json") };
				Windows::Storage::Streams::IRandomAccessStream stream{ co_await accountFile.OpenAsync(Windows::Storage::FileAccessMode::Read) };
				uint64_t size{ stream.Size() };
				Windows::Storage::Streams::IInputStream inputStream{ stream.GetInputStreamAt(0) };
				Windows::Storage::Streams::DataReader dataReader{ inputStream };
				unsigned int cBytesLoaded{ co_await dataReader.LoadAsync(size) };
				winrt::hstring streamText{ dataReader.ReadString(cBytesLoaded) };
				winrt::apartment_context ui_thread;
				co_await winrt::resume_background();
				co_await ui_thread;

				Windows::Data::Json::JsonObject account = Windows::Data::Json::JsonObject::Parse(streamText);
				//OutputDebugStringW(account.ToString().c_str());
				//OutputDebugStringW(L"\n");
				co_await winrt::resume_foreground(Email().Dispatcher());
				Email().Text(account.GetNamedString(L"email"));
				co_await winrt::resume_foreground(Password().Dispatcher());
				Password().Password(account.GetNamedString(L"password"));
				co_await winrt::resume_foreground(RememberCheckBox().Dispatcher());
				RememberCheckBox().IsChecked(account.GetNamedBoolean(L"isChecked"));
			}
			else
			{
				OutputDebugStringW(L"\n[Error] account file is not exist -> passed\n\n");
				Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };
				auto accountFile{ co_await folder.CreateFileAsync(L"account.json", Windows::Storage::CreationCollisionOption::OpenIfExists) };
				Windows::Data::Json::JsonObject account;
				account.SetNamedValue(L"email", Windows::Data::Json::JsonValue::CreateStringValue(L""));
				account.SetNamedValue(L"password", Windows::Data::Json::JsonValue::CreateStringValue(L""));
				account.SetNamedValue(L"isChecked", Windows::Data::Json::JsonValue::CreateBooleanValue(false));
				account.SetNamedValue(L"token", Windows::Data::Json::JsonValue::CreateStringValue(L""));
				hstring data = account.Stringify();
				co_await Windows::Storage::FileIO::WriteTextAsync(accountFile, data);
			}
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
		if (account.GetNamedBoolean(L"isChecked") != isCheck)
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
		//winrt::apartment_context ui_thread; // Capture calling context.

		//co_await winrt::resume_background();
		// Do compute-bound work here.
		hstring ress = co_await m_bikaHttp.Login(Email().Text(), Password().Password());
		Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(ress);
		OutputDebugStringW(resp.ToString().c_str());
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
			Windows::Data::Json::JsonObject data = resp.GetNamedObject(L"data");
			hstring token = data.GetNamedString(L"token");
			auto processOp{ WriteAccountJson(Email().Text(),Password().Password(), token,RememberCheckBox().IsChecked().GetBoolean()) };
			Progressing().IsActive(false);
			Frame().Navigate(winrt::xaml_typename<bikabika::Home>());
		}

	}
	void Login::ClickHandler(IInspectable const&, RoutedEventArgs const&)
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
			}
			
			
			
			
			
		}
	}
}


void winrt::bikabika::implementation::Login::Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	auto acc{ ReadAccountJson() };

	
}
