#include "pch.h"
#include "UserPage.h"
#if __has_include("UserPage.g.cpp")
#include "UserPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    UserPage::UserPage()
    {
        InitializeComponent();
		NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled);
    }

    bikabika::UserViewModel UserPage::MainUserViewModel()
    {
        return m_userViewModel;
    }
	int32_t UserPage::GetEXP(int32_t const& level)
	{
		int32_t temp = (level + 1) * 2 - 1;
		return (temp * temp - 1) * 25;
	}
	Windows::Foundation::IAsyncAction UserPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
		__super::OnNavigatedTo(e);
		auto serversSettings = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Servers", Windows::Storage::ApplicationDataCreateDisposition::Always);
		auto userData = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"User", Windows::Storage::ApplicationDataCreateDisposition::Always);
		if (userData.Values().HasKey(L"personInfo"))
		{
			Windows::Data::Json::JsonObject personInfo = winrt::Windows::Data::Json::JsonObject::Parse(unbox_value<winrt::hstring>(userData.Values().TryLookup(L"personInfo")));
			hstring name = personInfo.GetNamedString(L"name");
			if (name != m_userViewModel.User().Name()) m_userViewModel.User().Name(name);
			hstring level = L"Lv." + to_hstring(personInfo.GetNamedNumber(L"level"));
			if (level != m_userViewModel.User().Level()) m_userViewModel.User().Level(level);
			hstring title = to_hstring(personInfo.GetNamedString(L"title"));
			//OutputDebugStringW(title.c_str());
			if (title != m_userViewModel.User().Title()) m_userViewModel.User().Title(title);
			//OutputDebugStringW(m_userViewModel.User().Title().c_str());
			hstring slogan = L"\"" +to_hstring(personInfo.GetNamedString(L"slogan"))+ L"\"";
			if (slogan != m_userViewModel.User().Slogan()) m_userViewModel.User().Slogan(slogan);
			hstring levelExp = L"("+to_hstring(personInfo.GetNamedNumber(L"exp"))+L" / "+to_hstring(GetEXP(personInfo.GetNamedNumber(L"level")))+L")";
			if (levelExp != m_userViewModel.User().LevelExp()) m_userViewModel.User().LevelExp(levelExp);
			hstring img = unbox_value<winrt::hstring>(serversSettings.Values().Lookup(L"picServerCurrent")) + L"/static/" + personInfo.GetNamedObject(L"avatar").GetNamedString(L"path");
			//OutputDebugStringW(title.c_str());
			if (img != m_userViewModel.User().Img().UriSource().ToString()) m_userViewModel.User().Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{ img} });
		}
		if (!m_firstArrive)
		{
			co_await GetFavourite(L"dd", 1);
			m_firstArrive = true;
		}
		co_await GetHistory();
	}
	Windows::Foundation::IAsyncAction UserPage::GetHistory()
	{
		auto history = co_await m_fileCheckTool.GetHistory();
		UserLookCounts().Value(history.Size());
		for (auto s : history)
		{
			m_lookComicBlocks.Append(winrt::make<ComicBlock>(s.GetObject()));
		}
	}
	void UserPage::ContentDialogShow(hstring const& mode, hstring const& message)
	{
		Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		if (mode == L"Timeout") {
			auto show{ PicErrorDialog().ShowAsync() };
		}
		else {
			HttpContentDialog().Title(box_value(resourceLoader.GetString(L"FailHttpTitle")));
			HttpContentDialog().CloseButtonText(resourceLoader.GetString(L"FailCloseButtonText"));
			if (mode == L"Error")
			{
				HttpContentDialog().Content(box_value(message));
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
			auto show{ HttpContentDialog().ShowAsync() };
		}
	}
	Windows::Foundation::IAsyncAction UserPage::GetFavourite(hstring const& sort,int32_t const& page)
	{
		auto res = co_await m_bikaHttp.PersonFavourite(page);
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
				Windows::Data::Json::JsonObject ca = resp.GetNamedObject(L"data");
				Windows::Data::Json::JsonObject jsonObject = ca.GetNamedObject(L"comics");
				m_limit = jsonObject.GetNamedNumber(L"limit");
				m_total = jsonObject.GetNamedNumber(L"total");
				UserFavouriteCounts().Value(m_total);
				for (auto x : jsonObject.GetNamedArray(L"docs"))
				{
					m_favComicBlocks.Append(winrt::make<ComicBlock>(x.GetObject()));
				}

			}
			//缺少鉴权
			else if (code == (double)401 && resp.GetNamedString(L"error") == L"1005")
			{	
				ContentDialogShow(L"1005", L"");
			}
			//未知
			else
			{
				ContentDialogShow(L"Unknown",res);
			}
		}
	}
	winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> UserPage::FavComicBlocks()
	{
		return m_favComicBlocks;
	}
	winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> UserPage::LookComicBlocks()
	{
		return m_lookComicBlocks;
	}
}
