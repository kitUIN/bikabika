#include "pch.h"
#include "InfoPage.h"
#if __has_include("InfoPage.g.cpp")
#include "InfoPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    InfoPage::InfoPage()
    {
        InitializeComponent();
    }
    winrt::Windows::Foundation::Collections::IObservableVector<BikaClient::Blocks::EpisodeBlock> InfoPage::Episodes()
    {
        return m_eps;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<BikaClient::Blocks::ComicBlock> InfoPage::Comics()
    {
        return m_comics;
    }
    Windows::Foundation::IAsyncOperation<uint32_t> InfoPage::Eps(int32_t const& page)
    {
        auto res = co_await rootPage.HttpClient().Episodes(m_id, page);
        if (res.Code() == -1)
        {
            rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
        }
        else if (res.Code() == 200)
        {
            for (auto x : res.Episodes())
            {
                m_eps.Append(x);
            }
            co_return res.Pages();
        }
        else if (res.Code() == 401 && res.Error() == L"1005")
        {
            rootPage.ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());
        }
        else
        {
            rootPage.ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
        }
        co_return 0;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<BikaClient::Blocks::TagBlock> InfoPage::Tags()
    {
        return m_tags;
    }
    winrt::event_token InfoPage::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void InfoPage::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
    BikaClient::Blocks::BookBlock InfoPage::Book()
    {
        return m_book;
    }
    void InfoPage::Book(BikaClient::Blocks::BookBlock const& value)
    {
        m_book = value;
        m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Book" });
    }
    Windows::Foundation::IAsyncAction InfoPage::Recommend()
    {
        auto res = co_await rootPage.HttpClient().Recommend(m_id);
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
    Windows::Foundation::IAsyncAction InfoPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        auto params = winrt::unbox_value<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>(e.Parameter());
        auto img = winrt::unbox_value<winrt::Windows::UI::Xaml::Media::ImageSource>(params.GetAt(0));
        m_id = winrt::unbox_value<ComicArgs>(params.GetAt(1)).BookId();
        __super::OnNavigatedTo(e);
        auto anim = winrt::Windows::UI::Xaml::Media::Animation::ConnectedAnimationService::GetForCurrentView().GetAnimation(L"ForwardConnectedAnimation");
        if (anim)
        {
            Img().Source(img);
            anim.TryStart(Img());
        }
        auto res = co_await rootPage.HttpClient().BookInfo(m_id);
        if (res.Code() == -1)
        {
            rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
        }
        else if (res.Code() == 200)
        {
            auto book = res.BookInfos();
            Book(book);
            for (auto x : book.Tags())
            {
                m_tags.Append(x);
            }
            auto pages = co_await Eps(1);
            for (uint32_t i = 2; i <= pages; i++)
            {
                co_await Eps(i);
            }
            co_await Recommend();
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

}
void winrt::bikabika::implementation::InfoPage::Like_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::Favourite_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::TagButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::Author_Drop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::Title_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::UsersName_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::CommentFlyout_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
{

}
void winrt::bikabika::implementation::InfoPage::CommentSubmit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::MainGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::CreaterBorder_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{

}
void winrt::bikabika::implementation::InfoPage::ListV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
{

}
