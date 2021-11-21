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

	Windows::Foundation::IAsyncAction ClassificationPage::Init()
	{
		Progressing().IsActive(true);
		hstring res{ co_await m_bikaHttp.Categories() };
		Progressing().IsActive(false);
		if (res[1] == 'T') {
			auto show{ PicErrorDialog().ShowAsync() };
		}
		else if (res[1] == 'E') {
			auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
			LoginContentDialog().Content(box_value(res));
			LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
			auto show{ co_await LoginContentDialog().ShowAsync() };
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
			else if (code == (double)401 && resp.GetNamedString(L"error") == L"1005")
			{	//缺少鉴权
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
				LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginAuthFail/Content")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ co_await LoginContentDialog().ShowAsync() };
				if(show == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::None) Frame().Navigate(winrt::xaml_typename<bikabika::Login>());
			}
			else
			{
				//未知
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
				LoginContentDialog().Content(box_value(to_hstring(code) + L":" + resp.GetNamedString(L"message")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ co_await LoginContentDialog().ShowAsync() };
			}
		}
		

	}
	void ClassificationPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
		
		
		__super::OnNavigatedTo(e);
	}
	
}


Windows::Foundation::IAsyncAction  winrt::bikabika::implementation::ClassificationPage::GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
{
	OutputDebugStringW(L"\n\n------\n\n");
	auto classBlack = e.ClickedItem().as<bikabika::ClassBlock>();
	if (classBlack.ClassType() == L"2") {
		Progressing().IsActive(true);
		hstring res{ co_await m_bikaHttp.Comics(1,classBlack.ClassName(),L"ua")};
		Progressing().IsActive(false);
		if (res[1] == 'T') {
			auto show{ PicErrorDialog().ShowAsync() };
		}
		else if (res[1] == 'E') {
			auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
			LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
			LoginContentDialog().Content(box_value(res));
			LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
			auto show{ co_await LoginContentDialog().ShowAsync() };
		}
		else
		{
			Windows::Data::Json::JsonObject resp = Windows::Data::Json::JsonObject::Parse(res);
			double code = resp.GetNamedNumber(L"code");
			if (code == (double)200)
			{
				Windows::Data::Json::JsonObject ca = resp.GetNamedObject(L"data");
				Windows::Data::Json::JsonObject jsonObject = ca.GetNamedObject(L"comics");
				Frame().Navigate(winrt::xaml_typename<bikabika::ComicsPage>(), box_value(jsonObject));

			}
			else if (code == (double)401 && resp.GetNamedString(L"error") == L"1005")
			{	//缺少鉴权
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
				LoginContentDialog().Content(box_value(resourceLoader.GetString(L"LoginAuthFail/Content")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ co_await LoginContentDialog().ShowAsync() };
				if (show == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::None) Frame().Navigate(winrt::xaml_typename<bikabika::Login>());
			}
			else
			{
				//未知
				auto resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
				LoginContentDialog().Title(box_value(resourceLoader.GetString(L"LoadFail/Title")));
				LoginContentDialog().Content(box_value(to_hstring(code) + L":" + resp.GetNamedString(L"message")));
				LoginContentDialog().CloseButtonText(resourceLoader.GetString(L"Fail/CloseButtonText"));
				auto show{ co_await LoginContentDialog().ShowAsync() };
			}
		}
	}

}
