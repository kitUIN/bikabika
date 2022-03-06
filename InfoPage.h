#pragma once

#include "InfoPage.g.h"
#include "Utils/API/BikaHttp.h"
#include "Utils/Blocks/FileCheckTool.h"
#include "Utils/Blocks/TagBlock.h"
#include "Utils/Blocks/CreaterBlock.h"
#include "Utils/Blocks/EpisodeBlock.h"
#include "Utils/Blocks/CommetsViewModel.h"
#include "MainPage.h"
namespace winrt::bikabika::implementation
{
    struct InfoPage : InfoPageT<InfoPage>
    {
        InfoPage();
        Windows::Foundation::IAsyncAction ContentDialogShow(hstring const& mode, hstring const& message);
        Windows::Foundation::IAsyncAction Eps(int32_t const& page);
        Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> Tags();
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::EpisodeBlock> Episodes();
        bikabika::CommetsViewModel CommentBlocks();
        void CommentsFormat(winrt::Windows::Data::Json::JsonObject const& json);
        Windows::Foundation::IAsyncAction CommentsRequest(int32_t const& page);
        void MainGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);
        void CreaterBorder_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void ListV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);
        Windows::Foundation::IAsyncAction  Comments_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void CommentsView_PaneClosed(winrt::Windows::UI::Xaml::Controls::SplitView const& sender, winrt::Windows::Foundation::IInspectable const& args);
        Windows::Foundation::IAsyncAction Like_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction Favourite_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction ScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e);


    private:
        bikabika::MainPage rootPage{ MainPage::Current() };
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
        bikabika::FileCheckTool m_fileCheckTool;
        bikabika::BikaHttp m_bikaHttp;
        bool m_commentsFirstLoad = false;
        bool m_commentsContinue = false;
        hstring m_id;
        hstring m_title;
        bikabika::CreaterBlock m_creater{ nullptr };
        hstring m_description;
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_thumb;
        hstring m_author;
        hstring m_chineseTeam;
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> m_categories = winrt::single_threaded_observable_vector<bikabika::TagBlock>();
        hstring m_categoriesString;
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> m_tags = winrt::single_threaded_observable_vector<bikabika::TagBlock>();
        hstring m_tagsString;
        hstring m_updatedAt;
        hstring m_createdAt;
        int32_t m_pagesCount;
        int32_t m_epsCount;
        Windows::UI::Xaml::Visibility m_finished = Windows::UI::Xaml::Visibility::Collapsed;
        bool m_allowDownload;
        bool m_allowComment;
        int32_t m_totalLikes;
        int32_t m_totalViews;
        int32_t m_viewsCount;
        int32_t m_likesCount;
        bool m_isFavourite;
        bool m_isLiked;
        int32_t m_commentsCount;
        int32_t m_epsTotal;
        int32_t m_epsLimit;
        int32_t m_epsPage;
        int32_t m_epsPages;
        int32_t m_commentsTotal;
        int32_t m_commentsLimit;
        int32_t m_commentsPage;
        int32_t m_commentsPages;
        bikabika::CommetsViewModel m_comments;
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::EpisodeBlock> m_eps = winrt::single_threaded_observable_vector<bikabika::EpisodeBlock>();


    public:
        void Like_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Favourite_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void TagButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Author_Drop(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void Title_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void UsersName_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void CommentFlyout_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);
        Windows::Foundation::IAsyncAction   CommentSubmit_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct InfoPage : InfoPageT<InfoPage, implementation::InfoPage>
    {
    };
}
