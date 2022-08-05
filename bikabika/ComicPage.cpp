/*****************************************************************//**
 * \file   ComicPage.cpp
 * \brief  分区页面
 *
 * \author kulujun
 * \date   June 2022
 *********************************************************************/
#include "pch.h"
#include "ComicPage.h"
#if __has_include("ComicPage.g.cpp")
#include "ComicPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace  Windows::UI::Xaml::Controls;
namespace winrt::bikabika::implementation
{
    ComicPage::ComicPage()
    {
        InitializeComponent();
    }
	Windows::Foundation::IAsyncAction ComicPage::Goto(int32_t const& index, hstring const& title, BikaClient::Utils::SortMode const& mode)
	{
		if (!TypeCombo().IsEnabled() || !Pips().IsEnabled())
		{
			TypeCombo().IsEnabled(true);
			Pips().IsEnabled(true);
		}
		BikaClient::Responses::ComicsResponse res{ nullptr };
		if (m_comicType == ComicsType::SEARCH)
		{
			res = co_await rootPage.HttpClient().Search(index, title, mode);
		}
		else if (m_comicType == ComicsType::FACOURITE)
		{
			//auto res = co_await rootPage.HttpClient().Search(index, title, mode);
		}
		else if (m_comicType == ComicsType::RECENTLY_UPDATE)
		{
			res = co_await rootPage.HttpClient().Comics(index, mode);
		}
		else if (m_comicType == ComicsType::HISTORY)
		{

		}
		else if (m_comicType == ComicsType::RANDOM)
		{
			TypeCombo().IsEnabled(false);
			Pips().IsEnabled(false);
			res = co_await rootPage.HttpClient().Random();
		}
		else
		{
			res = co_await rootPage.HttpClient().Comics(index, title, mode);
		}
		if (res.Code() == -1)
		{
			rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200)
		{
			for (auto x : res.Comics())
			{
				m_comics.Append(x);
			}
			if (m_comicType != ComicsType::RANDOM)
			{
				Index(res.Page() - 1);
				AllPage(res.Pages());
			}
		}
		else if (res.Code() == 401 && res.Error() == L"1005")
		{
			rootPage.ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());
		}
		else
		{
			rootPage.ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
		}
	}
	void ComicPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
		TypeCombo().ItemsSource(m_typeBlocks);

		auto params = winrt::unbox_value<ComicArgs>(e.Parameter());
		m_sort = params.SortMode().SortMode();
		for (uint32_t i = 0; i < 4; i++)
		{
			if (m_typeBlocks.GetAt(i) == params.SortModeString())
			{
				TypeCombo().SelectedIndex(i);
			}
		}
		ComicTitle().Text(params.Title());
		m_comicType = params.ComicType();
	}

	winrt::event_token ComicPage::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}
	void ComicPage::PropertyChanged(winrt::event_token const& token) noexcept
	{
		m_propertyChanged.remove(token);
	}
	winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::ComicBlock> ComicPage::Comics()
	{
		return m_comics;
	}
	int32_t ComicPage::Index()
	{
		return m_index;
	}
	int32_t ComicPage::PipIndex()
	{
		return m_index + 1;
	}
	int32_t ComicPage::AllPage()
	{
		return m_pages;
	}
	void ComicPage::AllPage(int32_t const& value)
	{
		m_pages = value;
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"AllPage" });
	}
	void ComicPage::Index(int32_t const& value)
	{
		m_index = value;
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Index" });
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"PipIndex" });
	}
}





Windows::Foundation::IAsyncAction winrt::bikabika::implementation::ComicPage::TypeCombo_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
	if (m_firstArrive)
	{
		hstring s = sender.as<ComboBox>().SelectedItem().as<hstring>();
		if (s == resourceLoader.GetString(L"sort/dd")) m_sort = BikaClient::Utils::SortMode::DD;
		else if (s == resourceLoader.GetString(L"sort/da"))m_sort = BikaClient::Utils::SortMode::DA;
		else if (s == resourceLoader.GetString(L"sort/ld")) m_sort = BikaClient::Utils::SortMode::LD;
		else if (s == resourceLoader.GetString(L"sort/vd")) m_sort = BikaClient::Utils::SortMode::VD;
		else m_sort = BikaClient::Utils::SortMode::UA;
		if (m_index == 0)
		{
			m_comics.Clear();
			co_await Goto(1, ComicTitle().Text(), m_sort);
		}
		else
		{
			Index(0);
		}
	}
	else m_firstArrive = true;
}


void winrt::bikabika::implementation::ComicPage::Index_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
{
	if (e.Key() == Windows::System::VirtualKey::Enter)
	{
		auto box = sender.as<TextBox>();
		hstring s = box.Text();
		for (auto x : s)
		{
			if (!(x >= L'0' && x <= L'9'))
			{
				box.Text(to_hstring(m_index+1));
				return;
			}
		}
		int32_t index = std::stoi(to_string(s));
		if (index <= m_pages)
		{
			Index(index - 1);
		}
		else box.Text(to_hstring(m_index + 1));
	}
}


Windows::Foundation::IAsyncAction winrt::bikabika::implementation::ComicPage::PipsPager_SelectedIndexChanged(winrt::Microsoft::UI::Xaml::Controls::PipsPager const& sender, winrt::Microsoft::UI::Xaml::Controls::PipsPagerSelectedIndexChangedEventArgs const& args)
{
	if (m_index < m_pages)
	{
		auto index = sender.SelectedPageIndex();
		m_comics.Clear();
		co_await Goto(index + 1, ComicTitle().Text(), m_sort);
	}
}


Windows::Foundation::IAsyncAction winrt::bikabika::implementation::ComicPage::RefreshButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	m_comics.Clear();
	co_await Goto(m_index + 1, ComicTitle().Text(), m_sort);
}

void winrt::bikabika::implementation::ComicPage::GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
{
	auto comicBlock = e.ClickedItem().as<BikaClient::Blocks::ComicBlock>();
	auto container = GridV().ContainerFromItem(e.ClickedItem()).as<winrt::Windows::UI::Xaml::Controls::GridViewItem>();
	FrameworkElement root = container.ContentTemplateRoot().as<FrameworkElement>();
	bikabika::BikaImage bikaImg = root.FindName(L"ConnectedElement2").as<bikabika::BikaImage>();
	if(bikaImg.ImageLoaded()) winrt::Windows::UI::Xaml::Media::Animation::ConnectedAnimationService::GetForCurrentView().PrepareToAnimate(L"ForwardConnectedAnimation", bikaImg.as<UIElement>());
	winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
	winrt::Windows::UI::Xaml::Controls::Frame frame;
	symbol.Symbol(Windows::UI::Xaml::Controls::Symbol::PreviewLink);
	frame.Navigate(winrt::xaml_typename<bikabika::InfoPage>(), box_value(single_threaded_vector<winrt::Windows::Foundation::IInspectable>({ box_value(bikaImg.ImgSource()), box_value(bikabika::ComicArgs(comicBlock.ID(),1,1,1)) })), winrt::Windows::UI::Xaml::Media::Animation::SuppressNavigationTransitionInfo());
	rootPage.CreateNewTab(frame, comicBlock.Title(), symbol);
}