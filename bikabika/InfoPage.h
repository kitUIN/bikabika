#pragma once

#include "InfoPage.g.h"
#include "CommentView.h"
namespace winrt::bikabika::implementation
{
    struct InfoPage : InfoPageT<InfoPage>
    {
        InfoPage();
        bikabika::CommentView GetCommentView();

        Windows::Foundation::IAsyncAction Comment(int32_t const& page);
        Windows::Foundation::IAsyncAction Recommend();
        BikaClient::Blocks::BookBlock Book();
        Windows::Foundation::IAsyncOperation<uint32_t> Eps(int32_t const& page);
        void Book(BikaClient::Blocks::BookBlock const& value);
        void CommentsFormat(winrt::Windows::Data::Json::JsonObject const& json);
        Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
        bikabika::MainPage rootPage{ MainPage::Current() };
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
        BikaClient::Blocks::BookBlock m_book;
        hstring m_id=L"";
        hstring m_reply =L"";
        bool m_isTop = false;
        int32_t m_commentsPage = 1;
        int32_t m_commentsPages = 1;
        int32_t m_total = 1;
        bool m_commentsContinue = false;
        winrt::Windows::Foundation::Collections::IObservableVector<BikaClient::Blocks::TagBlock> m_tags = winrt::single_threaded_observable_vector<BikaClient::Blocks::TagBlock>();
        winrt::Windows::Foundation::Collections::IObservableVector<BikaClient::Blocks::EpisodeBlock> m_eps = winrt::single_threaded_observable_vector<BikaClient::Blocks::EpisodeBlock>();
        winrt::Windows::Foundation::Collections::IObservableVector<BikaClient::Blocks::ComicBlock> m_comics = winrt::single_threaded_observable_vector<BikaClient::Blocks::ComicBlock>();
        bikabika::CommentView m_commentView;

    public:
        Windows::Foundation::IAsyncAction Like_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction Favourite_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void TagButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Author_Drop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void Title_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void UsersName_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void CommentFlyout_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);
        void CommentSubmit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void MainGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);
        void CreaterBorder_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void ListV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);

        void GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);
        Windows::Foundation::IAsyncAction  winrt::bikabika::implementation::InfoPage::ScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void CommentLike_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void CommentLike_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction CommentComment_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction  CommentLike_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void PersonPicture_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction ButtonSend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct InfoPage : InfoPageT<InfoPage, implementation::InfoPage>
    {
    };
}
