#pragma once
#include "InfoBlock.g.h"
#include "CreaterBlock.h"
#include "TagBlock.h"
namespace winrt::bikabika::implementation
{
    struct InfoBlock : InfoBlockT<InfoBlock>
    {
        InfoBlock(winrt::Windows::Data::Json::JsonObject const& json);
        hstring ID();
        void ID(hstring const& value);
        hstring Title();
        void Title(hstring const& value);
        winrt::bikabika::CreaterBlock Creater();
        void Creater(winrt::bikabika::CreaterBlock const& value);
        hstring Description();
        void Description(hstring const& value);
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Thumb();
        void Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);
        hstring Author();
        void Author(hstring const& value);
        hstring ChineseTeam();
        void ChineseTeam(hstring const& value);
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::TagBlock> Categories();
        void Categories(winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::TagBlock> const& value);
        hstring CategoriesString();
        void CategoriesString(hstring const& value);
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::TagBlock> Tages();
        void Tages(winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::TagBlock> const& value);
        hstring TagsString();
        void TagsString(hstring const& value);
        int32_t PagesCount();
        void PagesCount(int32_t value);
        int32_t EpsCount();
        void EpsCount(int32_t value);
        winrt::Windows::UI::Xaml::Visibility Finished();
        void Finished(winrt::Windows::UI::Xaml::Visibility const& value);
        hstring UpdatedAt();
        void UpdatedAt(hstring const& value);
        hstring CreatedAt();
        void CreatedAt(hstring const& value);
        bool AllowDownload();
        void AllowDownload(bool value);
        bool AllowComment();
        void AllowComment(bool value);
        int32_t TotalLikes();
        void TotalLikes(int32_t value);
        int32_t TotalViews();
        void TotalViews(int32_t value);
        int32_t ViewsCount();
        void ViewsCount(int32_t value);
        int32_t LikesCount();
        void LikesCount(int32_t value);
        bool IsFavourite();
        void IsFavourite(bool value);
        bool IsLiked();
        void IsLiked(bool value);
        int32_t CommentsCount();
        void CommentsCount(int32_t value);
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring m_id;
        hstring m_title;
        bikabika::CreaterBlock m_creater{nullptr};
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
        Windows::UI::Xaml::Visibility m_finished= Windows::UI::Xaml::Visibility::Collapsed;
        bool m_allowDownload;
        bool m_allowComment;
        int32_t m_totalLikes;
        int32_t m_totalViews;
        int32_t m_viewsCount;
        int32_t m_likesCount;
        bool m_isFavourite;
        bool m_isLiked;
        int32_t m_commentsCount;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct InfoBlock : InfoBlockT<InfoBlock, implementation::InfoBlock>
    {
    };
}
