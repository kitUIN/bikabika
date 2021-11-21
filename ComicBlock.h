#pragma once
#include "ComicBlock.g.h"


namespace winrt::bikabika::implementation
{
    struct ComicBlock : ComicBlockT<ComicBlock>
    {
       
        ComicBlock(winrt::Windows::Data::Json::JsonObject const& json);
        hstring ID();
        void ID(hstring const& value);
        hstring Title();
        void Title(hstring const& value);
        hstring Author();
        void Author(hstring const& value);
        int32_t TotalViews();
        void TotalViews(int32_t value);
        int32_t TotalLikes();
        void TotalLikes(int32_t value);
        int32_t PageCount();
        void PageCount(int32_t value);
        int32_t EpsCount();
        void EpsCount(int32_t value);
        bool Finished();
        void Finished(bool value);
        winrt::Windows::Data::Json::JsonArray Categories();
        void Categories(winrt::Windows::Data::Json::JsonArray const& value);
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Thumb();
        void Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);
        int32_t LikesCount();
        void LikesCount(int32_t value);
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring m_id;
        hstring m_title;
        hstring m_author;
        int32_t m_totalViews;
        int32_t m_totalLikes;
        int32_t m_pageCount;
        int32_t m_epsCount;
        bool m_finished;
        winrt::Windows::Data::Json::JsonArray m_categories;
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_thumb;
        int32_t m_likesCount;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

    };
}
namespace winrt::bikabika::factory_implementation
{
    struct ComicBlock : ComicBlockT<ComicBlock, implementation::ComicBlock>
    {
    };
}
