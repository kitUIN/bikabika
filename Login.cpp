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

	int32_t Login::MyProperty()
	{
		throw hresult_not_implemented();
	}

	void Login::MyProperty(int32_t /* value */)
	{
		throw hresult_not_implemented();
	}
	Windows::Foundation::IAsyncAction Login::ReadAccountJson()
	{
		try 
		{
			boolean f = false;
			co_await winrt::resume_background();
			Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
			for (auto const& folder : co_await localFolder.GetFoldersAsync())
			{
				if (folder.Name() == L"bikabikadb")
				{
					f = true;
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
				CreateAccountJson(L"", L"", false);
				OutputDebugStringW(L"\n[Error] account file is not exist -> passed\n\n");
			}
		}
		catch (winrt::hresult_error const& ex) 
		{
		}
	}
	Windows::Foundation::IAsyncAction Login::CreateAccountJson(hstring email,hstring password,boolean isCheck)
	{
		// 创建用户配置文件
		Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
		Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };
		auto accountFile{co_await folder.CreateFileAsync(L"account.json", Windows::Storage::CreationCollisionOption::OpenIfExists)};
		// 序列化json
		
		Windows::Data::Json::JsonObject account;
		account.SetNamedValue(L"email", Windows::Data::Json::JsonValue::CreateStringValue(email));
		account.SetNamedValue(L"password", Windows::Data::Json::JsonValue::CreateStringValue(password));
		account.SetNamedValue(L"isChecked", Windows::Data::Json::JsonValue::CreateBooleanValue(isCheck));
		hstring data = account.Stringify();
		co_await Windows::Storage::FileIO::WriteTextAsync(accountFile, data);
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
			auto processOp{ CreateAccountJson(Email().Text(),Password().Password(),RememberCheckBox().IsChecked().GetBoolean()) };
		}
	}
}


void winrt::bikabika::implementation::Login::Password_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	auto acc{ ReadAccountJson() };

	
}
