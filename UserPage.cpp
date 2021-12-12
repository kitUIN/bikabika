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
	void UserPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
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
	}
	
}
