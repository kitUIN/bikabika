#pragma once

#include "InfoPage.g.h"
#include "BikaHttp.h"
#include "FileCheckTool.h"
#include "TagBlock.h"
#include "CreaterBlock.h"
namespace winrt::bikabika::implementation
{
    struct InfoPage : InfoPageT<InfoPage>
    {
        InfoPage();
        Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        
        
        
    private:
        bikabika::FileCheckTool m_fileCheckTool;
        bikabika::BikaHttp m_bikaHttp;
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
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct InfoPage : InfoPageT<InfoPage, implementation::InfoPage>
    {
    };
}
