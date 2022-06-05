#include "pch.h"
#include "ClassificationPage.h"
#if __has_include("ClassificationPage.g.cpp")
#include "ClassificationPage.g.cpp"
#endif
using namespace winrt::BikaClient::Blocks;

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Data::Json;
using namespace Windows::Foundation;
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
	CategoriesBlock ClassificationPage::CreateCategoriesBlock(hstring const& title, hstring const& uri)
	{
		ImageBlock imageBlock;
		imageBlock.Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Uri{ uri } });
		CategoriesBlock categoriesBlock;
		categoriesBlock.Thumb(imageBlock);
		categoriesBlock.Title(title);
		categoriesBlock.IsAuto(true);
		return categoriesBlock;
	}
	Windows::Foundation::IAsyncAction ClassificationPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
	{

		m_categories.Append(CreateCategoriesBlock(resourceLoader.GetString(L"Categories/Support"),L"ms-appx:///Assets//Picacgs//cat_support.jpg"));
		m_categories.Append(CreateCategoriesBlock(resourceLoader.GetString(L"Categories/Leaderboard"),L"ms-appx:///Assets//Picacgs//cat_leaderboard.jpg"));
		m_categories.Append(CreateCategoriesBlock(resourceLoader.GetString(L"Categories/Game"),L"ms-appx:///Assets//Picacgs//cat_game.jpg"));

		m_categories.Append(CreateCategoriesBlock(resourceLoader.GetString(L"Categories/Smalltool"),L"ms-appx:///Assets//Picacgs//cat_smalltool.jpg"));
		m_categories.Append(CreateCategoriesBlock(resourceLoader.GetString(L"Categories/Forum"),L"ms-appx:///Assets//Picacgs//cat_forum.jpg"));
		m_categories.Append(CreateCategoriesBlock(resourceLoader.GetString(L"Categories/Latest"),L"ms-appx:///Assets//Picacgs//cat_latest.jpg"));
		m_categories.Append(CreateCategoriesBlock(resourceLoader.GetString(L"Categories/Random"),L"ms-appx:///Assets//Picacgs//cat_random.jpg"));
		__super::OnNavigatedTo(e);
		auto res = co_await rootPage.HttpClient().Categories();
		rootPage.LayoutMessageShow(false);
		if (res.Code() == -1)
		{
			rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
		}
		else if (res.Code() == 200)
		{
			for (auto x : res.Categories())
			{
				m_categories.Append(x);
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
Windows::Foundation::IAsyncAction  winrt::bikabika::implementation::ClassificationPage::GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
{
	auto categoriesBlack = e.ClickedItem().as<BikaClient::Blocks::CategoriesBlock>();
	bikabika::ComicArgs args;
	if (!categoriesBlack.IsWeb()) {

		if (categoriesBlack.IsAuto())
		{
			if (categoriesBlack.Title()== resourceLoader.GetString(L"Categories/Latest"))
			{
				args.ComicType(bikabika::ComicsType::RECENTLY_UPDATE);
			}
			else if (categoriesBlack.Title() == resourceLoader.GetString(L"Categories/Leaderboard"))
			{
				co_return;
			}
			else if (categoriesBlack.Title() == resourceLoader.GetString(L"Categories/Game"))
			{
				co_return;
			}
			else if (categoriesBlack.Title() == resourceLoader.GetString(L"Categories/Smalltool"))
			{
				co_return;
			}
			else if (categoriesBlack.Title() == resourceLoader.GetString(L"Categories/Forum"))
			{
				co_return;
			}
			else if (categoriesBlack.Title() == resourceLoader.GetString(L"Categories/Random"))
			{
				args.ComicType(bikabika::ComicsType::RANDOM);
			}
			else if (categoriesBlack.Title() == resourceLoader.GetString(L"Categories/Support"))
			{
				Windows::System::LauncherOptions launcherOptions;
				launcherOptions.TreatAsUntrusted(true);
				co_await Windows::System::Launcher::LaunchUriAsync(Uri{ L"https://donate.wikawika.xyz" });
				co_return;
			}

		}
		else
		{

			args.ComicType(bikabika::ComicsType::COMIC);
		}

	}
	else
	{
		if (categoriesBlack.Title() == resourceLoader.GetString(L"Categories/Help"))
		{
			Windows::System::LauncherOptions launcherOptions;
			launcherOptions.TreatAsUntrusted(true);
			co_await Windows::System::Launcher::LaunchUriAsync(Uri{ L"https://donate.wikawika.xyz" });
		}
		co_return;
	}
	args.Title(categoriesBlack.Title());
	args.SortMode(winrt::BikaClient::Utils::BikaSort{ winrt::BikaClient::Utils::SortMode::UA });
	winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
	winrt::Windows::UI::Xaml::Controls::Frame frame;
	symbol.Symbol(Windows::UI::Xaml::Controls::Symbol::List);
	frame.Navigate(winrt::xaml_typename<bikabika::ComicPage>(), box_value(args));
	rootPage.CreateNewTab(frame, categoriesBlack.Title(), symbol);
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
