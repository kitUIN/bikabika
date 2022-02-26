#include "pch.h"
#include "ClassificationPage.h"
#if __has_include("ClassificationPage.g.cpp")
#include "ClassificationPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
//todo 分区封印
namespace winrt::bikabika::implementation
{
	ClassificationPage::ClassificationPage()
	{
		InitializeComponent();
		NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled);
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
	Windows::Foundation::IAsyncAction ClassificationPage::ContentDialogShow(hstring const& mode, hstring const& message)
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
                
                auto show{ co_await HttpContentDialog().ShowAsync() };

            }
            else if (mode == L"Unknown")
            {
                Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(message);
                HttpContentDialog().Content(box_value(to_hstring(resp.GetNamedNumber(L"code")) + L":" + resp.GetNamedString(L"message")));
                HttpContentDialog().IsTextScaleFactorEnabled(true);
                auto show{ co_await HttpContentDialog().ShowAsync() };

            }
            else if (mode == L"1005")
            {
                HttpContentDialog().Content(box_value(resourceLoader.GetString(L"FailAuth")));
                HttpContentDialog().IsTextScaleFactorEnabled(true);
                extern bool m_login;
                m_login = false;
                auto show{ co_await HttpContentDialog().ShowAsync() };
                if (show == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::None)
                {
                    auto loginTeachingTip = Frame().Parent().as<Microsoft::UI::Xaml::Controls::NavigationView>().Parent().as<Windows::UI::Xaml::Controls::Grid>().Children().GetAt(3).as<Microsoft::UI::Xaml::Controls::TeachingTip>();
                    loginTeachingTip.Title(resourceLoader.GetString(L"LoginButton/Content"));
                    loginTeachingTip.IsOpen(true);
                }
            }
        }
		ErrorTip().IsOpen(true);
	}
	Windows::Foundation::IAsyncAction ClassificationPage::Init()
	{
		Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
		LayoutMessage().Title(resourceLoader.GetString(L"Loading"));
		LayoutMessage().IsOpen(true);
		hstring res{ co_await m_bikaHttp.Categories() };
		LayoutMessage().IsOpen(false);
		if (res[1] == 'T')
		{
			co_await ContentDialogShow(L"Timeout", L"");
		}
		else if (res[1] == 'E') {
			co_await ContentDialogShow(L"Error", res);
		}
		else
		{
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
					auto block = winrt::make<bikabika::implementation::ClassBlock>(title, L"https://storage1.picacomic.com/static/" + path, L"2");
					ClassBlockView().ClassBlocks().Append(block);
				}

			}
			//缺少鉴权
			else if (code == (double)401 && resp.GetNamedString(L"error") == L"1005")
			{
				co_await ContentDialogShow(L"1005", L"");
			}
			//未知
			else
			{
				co_await ContentDialogShow(L"Unknown", res);
			}
		}
		

	}
	void ClassificationPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
		
		extern bool loadComicFlag;
		loadComicFlag = true;
		__super::OnNavigatedTo(e);
		m_classBlockView = winrt::make<ClassBlockViewModel>();
		
	}
	
}

//选择
void  winrt::bikabika::implementation::ClassificationPage::GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
{
	auto classBlack = e.ClickedItem().as<bikabika::ClassBlock>();
	
	if (classBlack.ClassType() == L"2") {
		ComicArgs args;
		args.ComicType(ComicsType::COMIC);
		args.Content(classBlack.ClassName());
		args.SortMode(winrt::bikabika::SearchSortMode::UA);
		Frame().Navigate(winrt::xaml_typename<bikabika::ComicsPage>(), box_value(args));
	}

}


void winrt::bikabika::implementation::ClassificationPage::ErrorTip_ActionButtonClick(winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& sender, winrt::Windows::Foundation::IInspectable const& args)
{
	auto ccc{ Init() };
	ErrorTip().IsOpen(false);
}
