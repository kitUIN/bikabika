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
	void winrt::bikabika::implementation::ComicsPage::TypeCombo_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		TypeCombo().SelectedIndex(m_index);
	}
	int32_t ComicsPage::Pages()
	{
		return m_total;
	}
	int32_t ComicsPage::PageIndex()
	{
		return m_page;
	}
	Windows::Foundation::IAsyncAction ComicsPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
		auto params = winrt::unbox_value<winrt::Windows::Foundation::Collections::IVector<hstring>>(e.Parameter());
		//Progressing().IsActive(true);
		hstring res{ co_await m_bikaHttp.Comics(1,params.GetAt(0),params.GetAt(1)) };
		m_title = params.GetAt(0);
		m_sortMode = params.GetAt(1);
		if (m_sortMode == L"ua") m_index = 0;
		else if (m_sortMode == L"dd") m_index = 1;
		else if (m_sortMode == L"da") m_index = 2;
		else if (m_sortMode == L"ld") m_index = 3;
		else if (m_sortMode == L"vd") m_index = 4;
		//Progressing().IsActive(false);
		if (res[1] == 'T') {
			//auto show{ PicErrorDialog().ShowAsync() };
		}
		else if (res[1] == 'E') {
			/*auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
			LoginContentDialog().Content(box_value(res));
			LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
			auto show{ co_await LoginContentDialog().ShowAsync() };*/
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
				m_page = jsonObject.GetNamedNumber(L"page");
				m_pages = jsonObject.GetNamedNumber(L"pages");
				m_comicBlocks.Clear();
				for (auto x : jsonObject.GetNamedArray(L"docs"))
				{
					m_comicBlocks.Append(winrt::make<ComicBlock>(x.GetObject()));
				}

			}
			else if (code == (double)401 && resp.GetNamedString(L"error") == L"1005")
			{	//缺少鉴权
				/*auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
				LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginAuthFail/Content")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ co_await LoginContentDialog().ShowAsync() };
				if (show == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::None) Frame().Navigate(winrt::xaml_typename<bikabika::Login>());
			*/}
			else
			{
				//未知
				/*auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
				LoginContentDialog().Content(box_value(to_hstring(code) + L":" + resp.GetNamedString(L"message")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ co_await LoginContentDialog().ShowAsync() };
			*/}
		}
        
        
        __super::OnNavigatedTo(e);
    }
	Windows::Foundation::IAsyncAction ComicsPage::Goto(int32_t const& index, hstring const& title, hstring const& mode) {
		if (index != m_pages) {
			//Progressing().IsActive(true);
			hstring res{ co_await m_bikaHttp.Comics(index,title,mode) };

			if (m_sortMode == L"ua") m_index = 0;
			else if (m_sortMode == L"dd") m_index = 1;
			else if (m_sortMode == L"da") m_index = 2;
			else if (m_sortMode == L"ld") m_index = 3;
			else if (m_sortMode == L"vd") m_index = 4;
			//Progressing().IsActive(false);
			if (res[1] == 'T') {
				//auto show{ PicErrorDialog().ShowAsync() };
			}
			else if (res[1] == 'E') {
				/*auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
				LoginContentDialog().Content(box_value(res));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ co_await LoginContentDialog().ShowAsync() };*/
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
					m_page = jsonObject.GetNamedNumber(L"page");
					m_pages = jsonObject.GetNamedNumber(L"pages");
					m_comicBlocks.Clear();
					for (auto x : jsonObject.GetNamedArray(L"docs"))
					{
						m_comicBlocks.Append(winrt::make<ComicBlock>(x.GetObject()));
					}

				}
				else if (code == (double)401 && resp.GetNamedString(L"error") == L"1005")
				{	//缺少鉴权
					/*auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
					LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
					LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginAuthFail/Content")));
					LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
					auto show{ co_await LoginContentDialog().ShowAsync() };
					if (show == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::None) Frame().Navigate(winrt::xaml_typename<bikabika::Login>());
					*/
				}
				else
				{
					//未知
					/*auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
					LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
					LoginContentDialog().Content(box_value(to_hstring(code) + L":" + resp.GetNamedString(L"message")));
					LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
					auto show{ co_await LoginContentDialog().ShowAsync() };
					*/
				}
			}

		}
	}




	Windows::Foundation::IAsyncAction winrt::bikabika::implementation::ComicsPage::PipsPager_SelectedIndexChanged(winrt::Microsoft::UI::Xaml::Controls::PipsPager const& sender, winrt::Microsoft::UI::Xaml::Controls::PipsPagerSelectedIndexChangedEventArgs const& args)
	{
		auto index = sender.SelectedPageIndex();
		if(m_title!=L"") co_await Goto(index + 1, m_title, m_sortMode);


	}


	void winrt::bikabika::implementation::ComicsPage::Pips_Loading(winrt::Windows::UI::Xaml::FrameworkElement const& sender, winrt::Windows::Foundation::IInspectable const& args)
	{

	}
	Windows::Foundation::IAsyncAction winrt::bikabika::implementation::ComicsPage::TypeCombo_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		m_index = TypeCombo().SelectedIndex();
		OutputDebugStringW(to_hstring(TypeCombo().SelectedIndex()).c_str());
		if (m_index == 0) m_sortMode = L"ua";
		else if (m_index == 1) m_sortMode = L"dd";
		else if (m_index == 2) m_sortMode = L"da";
		else if (m_index == 3) m_sortMode = L"ld";
		else if (m_index == 4) m_sortMode = L"vd";
		if (m_title != L"") co_await Goto(m_page, m_title, m_sortMode);
	}
}




