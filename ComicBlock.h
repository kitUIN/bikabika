#pragma once
#include "ComicBlock.g.h"
#include "TagBlock.h"

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
        winrt::Windows::UI::Xaml::Visibility Finished();
        void Finished(winrt::Windows::UI::Xaml::Visibility value);
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> Categories();
        void Categories(winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> const& value);
        hstring Category();
        void Category(hstring const& value);
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
        winrt::Windows::UI::Xaml::Visibility m_finished = winrt::Windows::UI::Xaml::Visibility::Collapsed;
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::TagBlock> m_categories = winrt::single_threaded_observable_vector<bikabika::TagBlock>();
        hstring m_category;
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_thumb = winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ Windows::Foundation::Uri{L"ms-appx:///gray.png"} } ;
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
