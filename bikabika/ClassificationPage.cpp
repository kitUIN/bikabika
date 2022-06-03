#include "pch.h"
#include "ClassificationPage.h"
#if __has_include("ClassificationPage.g.cpp")
#include "ClassificationPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
namespace winrt::bikabika::implementation
{
    ClassificationPage::ClassificationPage()
    {
        InitializeComponent();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::CategoriesBlock> ClassificationPage::Categories()
    {
		return m_categories;
    }

    void ClassificationPage::Categories(winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::CategoriesBlock> const& value)
    {
		m_categories = value;
		m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Categories" });
    }
	Windows::Foundation::IAsyncAction ClassificationPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{
		__super::OnNavigatedTo(e);
		auto res = co_await rootPage.HttpClient().Categories();
		rootPage.LayoutMessageShow(false);
		if (res.Code() == -1)
		{
			rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200)
		{
			Categories(res.Categories());
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
	winrt::event_token ClassificationPage::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}
	void ClassificationPage::PropertyChanged(winrt::event_token const& token) noexcept
	{
		m_propertyChanged.remove(token);
	}
}

//选择
void  winrt::bikabika::implementation::ClassificationPage::GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
{
	auto categoriesBlack = e.ClickedItem().as<BikaClient::Blocks::CategoriesBlock>();

	if (!categoriesBlack.IsWeb()&& categoriesBlack.Active()) {
		bikabika::ComicArgs args;
		args.ComicType(bikabika::ComicsType::COMIC);
		args.Content(categoriesBlack.Title());
		args.SortMode(winrt::BikaClient::Utils::BikaSort{ winrt::BikaClient::Utils::SortMode::UA });
		winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
		winrt::Windows::UI::Xaml::Controls::Frame frame;
		symbol.Symbol(Windows::UI::Xaml::Controls::Symbol::List);
		//frame.Navigate(winrt::xaml_typename<bikabika::ComicsPage>(), box_value(args));
		//rootPage.CreateNewTab(frame, categoriesBlack.Title(), symbol);
	}

}


void winrt::bikabika::implementation::ClassificationPage::Image_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& /*e*/)
{
	auto grid = sender.as<Grid>();
	auto border = grid.Children().GetAt(0).as<Border>();
	auto image = border.Child().as<Image>();
	border.Margin(Thickness{ 0,0,0,0 });
	border.Width(145);
	border.Height(145);
	image.Width(145);
	image.Height(145);
}


void winrt::bikabika::implementation::ClassificationPage::Image_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& /*e*/)
{
	auto grid= sender.as<Grid>();
	auto border = grid.Children().GetAt(0).as<Border>();
	auto image = border.Child().as<Image>();
	border.Margin(Thickness{ 0,5,0,0 });
	border.Width(140);
	border.Height(140);
	image.Width(140);
	image.Height(140);
}
