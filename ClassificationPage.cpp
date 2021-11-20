#include "pch.h"
#include "ClassificationPage.h"
#if __has_include("ClassificationPage.g.cpp")
#include "ClassificationPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
	ClassificationPage::ClassificationPage()
	{
		InitializeComponent();
		NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled);
		m_classBlockView = winrt::make<ClassBlockViewModel>();
		auto ccc{ Init() };
	}
	bikabika::BikaHttp ClassificationPage::BikaHttpAPI()
	{
		return m_bikaHttp;
	}
	bikabika::ClassBlockViewModel ClassificationPage::ClassBlockView()
	{
		return m_classBlockView;
	}

	
	Windows::Foundation::IAsyncAction ClassificationPage::ReadAuthJson()
	{	// 自动登陆载入数据
		try
		{
			bool f{ co_await m_fileCheckTool.CheckFileAccount() };
			Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
			Windows::Storage::StorageFolder folder{ co_await localFolder.CreateFolderAsync(L"bikabikadb", Windows::Storage::CreationCollisionOption::OpenIfExists) };
			auto accountFile{ co_await folder.CreateFileAsync(L"account.json", Windows::Storage::CreationCollisionOption::OpenIfExists) };
			auto accountData{ co_await Windows::Storage::FileIO::ReadTextAsync(accountFile) };
			Windows::Data::Json::JsonObject account = Windows::Data::Json::JsonObject::Parse(accountData);
			// Auth
			hstring token = account.GetNamedString(L"token");
			if (token == L"") {
				Windows::Storage::StorageFolder localFolder{ Windows::Storage::ApplicationData::Current().LocalFolder() };
				OutputDebugStringW(L"\n[Error] account file is not exist -> back to login\n\n");
				Frame().Navigate(winrt::xaml_typename<bikabika::Login>());
			}
			//OutputDebugStringW(L"\n[Auth] \n");
			//OutputDebugStringW(token.c_str());
		}
		catch (winrt::hresult_error const& ex)
		{
			OutputDebugStringW(L"\n[Error] ClassificationPage::ReadAuthJson()");
			OutputDebugStringW(ex.message().c_str());
		}
	}
	
	Windows::Foundation::IAsyncAction ClassificationPage::Init()
	{
		co_await ReadAuthJson();
		hstring res{ co_await m_bikaHttp.Categories() };
		Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(res);
		double code = resp.GetNamedNumber(L"code");
		
		if (code == (double)200)
		{
			Windows::Data::Json::JsonObject ca = resp.GetNamedObject(L"data");
			Windows::Data::Json::JsonArray jsonArray = ca.GetNamedArray(L"categories");
			for (auto e : jsonArray)
			{
				Windows::Data::Json::JsonObject categories = e.GetObject();
				hstring title = categories.GetNamedString(L"title");
				Windows::Data::Json::JsonObject thumb = categories.GetNamedObject(L"thumb");
				hstring path = thumb.GetNamedString(L"path");
				hstring fileServer = thumb.GetNamedString(L"fileServer");
				auto block = winrt::make<bikabika::implementation::ClassBlock>(title,L"https://storage1.picacomic.com/static/" + path);
				ClassBlockView().ClassBlocks().Append(block);
			}
			
		}
		else if (code == (double)401)
		{
			OutputDebugStringW(L"\n[Error]" );
			OutputDebugStringW(to_hstring(code).c_str());
			OutputDebugStringW(L"\n\n");
			
		}
		

	}
	void ClassificationPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
		
		
		__super::OnNavigatedTo(e);
	}
	
}
