#include "pch.h"
#include "ComicsPage.h"
#if __has_include("ComicsPage.g.cpp")
#include "ComicsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    ComicsPage::ComicsPage()
    {
        InitializeComponent();
        NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled);
    }

    
    
    winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> ComicsPage::ComicBlocks()
    {
        return m_comicBlocks;
    }

	winrt::Windows::Foundation::Collections::IObservableVector<hstring> ComicsPage::TypeBlocks()
	{
		auto m_typeBlocks = winrt::single_threaded_observable_vector<hstring>();
		auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		m_typeBlocks.Append(resourceLoader.GetString(L"SortMode/UA"));
		m_typeBlocks.Append(resourceLoader.GetString(L"SortMode/DD"));
		m_typeBlocks.Append(resourceLoader.GetString(L"SortMode/DA"));
		m_typeBlocks.Append(resourceLoader.GetString(L"SortMode/LD"));
		m_typeBlocks.Append(resourceLoader.GetString(L"SortMode/VD"));
		return m_typeBlocks;
	}

	void ComicsPage::ContentDialogShow(hstring const& mode, hstring const& message)
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
	Windows::Foundation::IAsyncAction ComicsPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
		extern bool loadComicFlag;
		extern bool animeFlag;
		animeFlag = true;
		auto params = winrt::unbox_value<winrt::Windows::Foundation::Collections::IVector<hstring>>(e.Parameter());
		if (!Pips().IsEnabled())
		{
			Pips().IsEnabled(true);
			TypeCombo().IsEnabled(true);
			NumberBox1().IsEnabled(true);
		}
		m_GoType = params.GetAt(0);
		if (m_GoType == L"Comic")
		{
			if (m_pageNumBox.Title() != params.GetAt(1)|| loadComicFlag)
			{
				co_await Goto(1, params.GetAt(1), params.GetAt(2));
				m_sortMode = params.GetAt(2);
			}
			m_pageNumBox.Title(params.GetAt(1));
		}
		else if (m_GoType == L"Search")
		{
			if (m_pageNumBox.Title() != params.GetAt(1) || loadComicFlag)
			{
				co_await GotoSearch(params.GetAt(1), params.GetAt(2), m_categories, 1);
				m_sortMode = params.GetAt(2);
			}
			m_pageNumBox.Title(params.GetAt(1));

		}
		else if (m_GoType == L"History"  )
		{
			auto history = co_await m_fileCheckTool.GetHistory();
			for (auto x : history)
			{
				m_comicBlocks.Append(winrt::make<ComicBlock>(x.GetObject()));
			}
			m_pageNumBox.Title(params.GetAt(1));
			Pips().IsEnabled(false);
			TypeCombo().IsEnabled(false);
			NumberBox1().IsEnabled(false);
		}
		else if (m_GoType == L"Favourite" )
		{
			if (m_pageNumBox.Title() != params.GetAt(1) || loadComicFlag)
			{
				co_await GotoFavourite(params.GetAt(2), 1);
				m_sortMode = params.GetAt(2);
			}
			m_pageNumBox.Title(params.GetAt(1));
			
		}
		loadComicFlag = false;
        __super::OnNavigatedTo(e);
		if (m_sortMode == L"ua") m_sortType = 0;
		else if (m_sortMode == L"dd") m_sortType = 1;
		else if (m_sortMode == L"da") m_sortType = 2;
		else if (m_sortMode == L"ld") m_sortType = 3;
		else if (m_sortMode == L"vd") m_sortType = 4;
		TypeCombo().SelectedIndex(m_sortType);
		
    }
	Windows::Foundation::IAsyncAction ComicsPage::Goto(int32_t const& index, hstring const& title, hstring const& mode) {
		if (index <= m_pageNumBox.Pages()) {
			//Progressing().IsActive(true);
			m_comicBlocks.Clear();
			hstring res{ co_await m_bikaHttp.Comics(index,title,mode) };
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
					m_pageNumBox.PageIndex(jsonObject.GetNamedNumber(L"page"));
					auto pages = jsonObject.GetNamedNumber(L"pages");
					m_pageNumBox.Pages(pages);
					Pips().NumberOfPages(pages);
					for (auto x : jsonObject.GetNamedArray(L"docs"))
					{
						m_comicBlocks.Append(winrt::make<ComicBlock>(x.GetObject()));
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
					ContentDialogShow(L"Unknown", res);
				}
			}

		}
	}

	Windows::Foundation::IAsyncAction ComicsPage::GotoSearch(hstring const& keywords, hstring  const& mode, Windows::Data::Json::JsonArray const& categories, int32_t const& index) {
		if (index <= m_pageNumBox.Pages()) {
			//Progressing().IsActive(true);
			m_comicBlocks.Clear();
			hstring res{ co_await m_bikaHttp.Search(keywords, mode, categories, index) };
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
					m_pageNumBox.PageIndex(jsonObject.GetNamedNumber(L"page"));
					auto pages = jsonObject.GetNamedNumber(L"pages");
					m_pageNumBox.Pages(pages);
					Pips().NumberOfPages(pages);
					for (auto x : jsonObject.GetNamedArray(L"docs"))
					{
						m_comicBlocks.Append(winrt::make<ComicBlock>(x.GetObject()));
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
					ContentDialogShow(L"Unknown", res);
				}
			}
		}
	}
	Windows::Foundation::IAsyncAction ComicsPage::GotoFavourite(hstring  const& mode, int32_t const& index) {
		if (index <= m_pageNumBox.Pages()) {
			//Progressing().IsActive(true);
			m_comicBlocks.Clear();
			hstring res{ co_await m_bikaHttp.PersonFavourite(mode,index) };
			
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
					m_pageNumBox.PageIndex(jsonObject.GetNamedNumber(L"page"));
					auto pages = jsonObject.GetNamedNumber(L"pages");
					m_pageNumBox.Pages(pages);
					Pips().NumberOfPages(pages);
					for (auto x : jsonObject.GetNamedArray(L"docs"))
					{
						m_comicBlocks.Append(winrt::make<ComicBlock>(x.GetObject()));
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
					ContentDialogShow(L"Unknown", res);
				}
			}
		}
	}


	Windows::Foundation::IAsyncAction winrt::bikabika::implementation::ComicsPage::PipsPager_SelectedIndexChanged(winrt::Microsoft::UI::Xaml::Controls::PipsPager const& sender, winrt::Microsoft::UI::Xaml::Controls::PipsPagerSelectedIndexChangedEventArgs const& args)
	{
		
		auto index = sender.SelectedPageIndex();
		OutputDebugStringW(L"this ");
		OutputDebugStringW(L"PipsPager_SelectedIndexChanged ");
		OutputDebugStringW(to_hstring(index).c_str());
		OutputDebugStringW(L"\n");
		if (m_pageNumBox.Title() != L"")
		{
			if (m_GoType == L"Comic")
			{
				co_await Goto(index + 1, m_pageNumBox.Title(), m_sortMode);
			}
			else if (m_GoType == L"Search")
			{
				co_await GotoSearch(m_pageNumBox.Title(), m_sortMode, m_categories, index + 1);
			}
			else if (m_GoType == L"Favourite")
			{
				co_await GotoFavourite(m_sortMode, index + 1);
			}
		}

	}


	void winrt::bikabika::implementation::ComicsPage::Pips_Loading(winrt::Windows::UI::Xaml::FrameworkElement const& sender, winrt::Windows::Foundation::IInspectable const& args)
	{

	}
	Windows::Foundation::IAsyncAction winrt::bikabika::implementation::ComicsPage::TypeCombo_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{

		m_sortType = TypeCombo().SelectedIndex();
		
		
		if (m_sortType == 0) m_sortMode = L"ua";
		else if (m_sortType == 1) m_sortMode = L"dd";
		else if (m_sortType == 2) m_sortMode = L"da";
		else if (m_sortType == 3) m_sortMode = L"ld";
		else if (m_sortType == 4) m_sortMode = L"vd";

		if (m_pageNumBox.Title() != L"")
		{
			OutputDebugStringW(L"this ");
			OutputDebugStringW(L"TypeCombo_SelectionChanged ");
			OutputDebugStringW(to_hstring(TypeCombo().SelectedIndex()).c_str());
			OutputDebugStringW(L"\n");
			//co_await Goto(1, m_pageNumBox.Title(), m_sortMode);
			if (m_pageNumBox.Title() != L""&& m_pageNumBox.PageIndex() == 1)
			{
				if (m_GoType == L"Comic")
				{
					co_await Goto(1, m_pageNumBox.Title(), m_sortMode);
				}
				else if (m_GoType == L"Search")
				{
					co_await GotoSearch(m_pageNumBox.Title(), m_sortMode, m_categories,1);
				}
				else if (m_GoType == L"Favourite")
				{
					co_await GotoFavourite(m_sortMode, 1);
				}
			}
			else {
				Pips().SelectedPageIndex(0);
			}
			
		}

	}
	bikabika::PageNumBox ComicsPage::MyPageNumBox()
	{
		return m_pageNumBox;
	}

	void winrt::bikabika::implementation::ComicsPage::NumberBox1_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args)
	{
		
		
		int32_t index = sender.Value();
		if (index >= 1 && index <= m_pageNumBox.Pages())

		{
			OutputDebugStringW(L"this ");
			OutputDebugStringW(L"NumberBox1_ValueChanged ");
			OutputDebugStringW(to_hstring(sender.Value()).c_str());
			OutputDebugStringW(L"\n");
			
			Pips().SelectedPageIndex(index - 1);
		}
		else
		{
			sender.Value(m_pageNumBox.PageIndex());
		}

	}
	void winrt::bikabika::implementation::ComicsPage::GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
	{
		auto comicBlock = e.ClickedItem().as<bikabika::ComicBlock>();
		m_fileCheckTool.SetHistory(comicBlock.GetJsonObject());
		auto container = GridV().ContainerFromItem(e.ClickedItem()).as<winrt::Windows::UI::Xaml::Controls::GridViewItem>();
		auto root = container.ContentTemplateRoot().as<FrameworkElement>();
		auto image =  root.FindName(L"ConnectedElement2").as<UIElement>();
		winrt::Windows::UI::Xaml::Media::Animation::ConnectedAnimationService::GetForCurrentView().PrepareToAnimate(L"ForwardConnectedAnimation", image);
		Frame().Navigate(winrt::xaml_typename<bikabika::InfoPage>(),box_value(single_threaded_vector<winrt::Windows::Foundation::IInspectable>({ box_value(root.FindName(L"ConnectedElement2").as<winrt::Windows::UI::Xaml::Controls::Image>().Source()), box_value(comicBlock.ID()) })) , winrt::Windows::UI::Xaml::Media::Animation::SuppressNavigationTransitionInfo());

	}
}









