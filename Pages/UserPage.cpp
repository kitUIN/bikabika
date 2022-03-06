#include "pch.h"
#include "UserPage.h"
#if __has_include("UserPage.g.cpp")
#include "UserPage.g.cpp"
#endif
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Controls::Primitives;

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
        return rootPage.MainUserViewModel();
    }
	// 检测打卡情况
	void UserPage::CheckPunchIn()
	{
		if (MainUserViewModel().User().IsPunched())
		{
			hstring punch = resourceLoader.GetString(L"PunchIned");
			Punch().IsChecked(true);
			Punch().Label(punch);
			PunchTip().Content(box_value(punch));
		}
	}
	Windows::Foundation::IAsyncAction UserPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
		__super::OnNavigatedTo(e);
		extern bool loadComicFlag;
		CheckPunchIn();
		loadComicFlag = true;
		auto anim = winrt::Windows::UI::Xaml::Media::Animation::ConnectedAnimationService::GetForCurrentView().GetAnimation(L"ForwardConnectedAnimation");
		if (anim)
		{
			if (m_img)
			{
				anim.TryStart(m_img);
			}
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
		m_lookComicBlocks.Clear();
		for (auto s : history)
		{
			m_lookComicBlocks.Append(winrt::make<ComicBlock>(s.GetObject()));
			if (m_lookComicBlocks.Size() == 20) break;
		}
		
		
	}
	
	Windows::Foundation::IAsyncAction UserPage::GetFavourite(hstring const& sort,int32_t const& page)
	{
		auto res = co_await m_bikaHttp.PersonFavourite(sort,page);
		if (res[1] == 'T')
		{
			rootPage.ContentDialogShow(L"Timeout", L"");
		}
		else if (res[1] == 'E') {
			rootPage.ContentDialogShow(L"Error", res);
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
				rootPage.ContentDialogShow(L"1005", L"");
			}
			//未知
			else
			{
				rootPage.ContentDialogShow(L"Unknown",res);
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


void winrt::bikabika::implementation::UserPage::GotoLook_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	ComicArgs args;
	args.ComicType(ComicsType::HISTORY);
	args.Content(L"History");
	args.SortMode(winrt::bikabika::SearchSortMode::DD);
	Frame().Navigate(winrt::xaml_typename<bikabika::ComicsPage>(), box_value(args));
}


void winrt::bikabika::implementation::UserPage::GotoFav_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	ComicArgs args;
	args.ComicType(ComicsType::FACOURITE);
	args.Content(L"Favourite");
	args.SortMode(winrt::bikabika::SearchSortMode::DD);
	winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
	winrt::Windows::UI::Xaml::Controls::Frame frame;
	symbol.Symbol(Windows::UI::Xaml::Controls::Symbol::List);
	frame.Navigate(winrt::xaml_typename<bikabika::ComicsPage>(), box_value(args));
	rootPage.CreateNewTab(frame, L"Favourite", symbol);
}


void winrt::bikabika::implementation::UserPage::Grid_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
	extern bool animeFlag;
	animeFlag = true;
	//OutputDebugStringW(L"\nisokkkkkkk\n");
	auto it = sender.as<winrt::Windows::UI::Xaml::Controls::Grid>().Children().GetAt(0).as<winrt::Windows::UI::Xaml::Controls::Border>().Child().as<winrt::Windows::UI::Xaml::Controls::Grid>();
	auto title = it.Children().GetAt(2).as<winrt::Windows::UI::Xaml::Controls::Border>().Child().as<winrt::Windows::UI::Xaml::Controls::TextBlock>().Text();
	auto bookId = it.Children().GetAt(0).as<winrt::Windows::UI::Xaml::Controls::TextBlock>().Text();
	auto image = it.Children().GetAt(1).as<UIElement>();
	m_img = it.Children().GetAt(1).as<winrt::Windows::UI::Xaml::Controls::Image>();
	winrt::Windows::UI::Xaml::Media::Animation::ConnectedAnimationService::GetForCurrentView().PrepareToAnimate(L"ForwardConnectedAnimation", image);
	winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
	winrt::Windows::UI::Xaml::Controls::Frame frame;
	symbol.Symbol(Windows::UI::Xaml::Controls::Symbol::PreviewLink);
	frame.Navigate(winrt::xaml_typename<bikabika::InfoPage>(), box_value(single_threaded_vector<winrt::Windows::Foundation::IInspectable>({ box_value(it.Children().GetAt(1).as<winrt::Windows::UI::Xaml::Controls::Image>().Source()), box_value(bookId) })), winrt::Windows::UI::Xaml::Media::Animation::SuppressNavigationTransitionInfo());
	rootPage.CreateNewTab(frame, title, symbol);

}


void winrt::bikabika::implementation::UserPage::Punch_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{

	if (!Punch().IsChecked().GetBoolean() && !MainUserViewModel().User().IsPunched()) {
		
	}
	CheckPunchIn();
}


void winrt::bikabika::implementation::UserPage::UserLogOut_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	sender.as<AppBarToggleButton>().IsChecked(false);
	rootPage.LogOut();
}


void winrt::bikabika::implementation::UserPage::UserSettings_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	FlyoutBase::ShowAttachedFlyout(sender.as<FrameworkElement>());
}


void winrt::bikabika::implementation::UserPage::Flyout_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
{
	UserSettings().IsChecked(false);

}


void winrt::bikabika::implementation::UserPage::FlyoutPasswordButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	rootPage.ChangePassword();
}


void winrt::bikabika::implementation::UserPage::FlyoutSloganButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	rootPage.ChangeSignature();
}
