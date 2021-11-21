#include "pch.h"
#include "ComicBlock.h"
#include "ComicBlock.g.cpp"


namespace winrt::bikabika::implementation
{
    ComicBlock::ComicBlock(hstring const& _id, hstring const& title, hstring const& author, int32_t pageCount, int32_t epsCount, bool finished, winrt::Windows::Data::Json::JsonArray const& categories, winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& thumb, int32_t likesCount)
    {
        m_id = _id;
        m_title = title;
        m_author = author;
        m_pageCount = pageCount;
        m_epsCount = epsCount;
        m_finished = finished;
        m_categories = categories;
        m_thumb = thumb;
        m_likesCount = likesCount;

    }
    hstring ComicBlock::ID()
    {
        return m_id;
    }
    void ComicBlock::ID(hstring const& value)
    {
        if (value != m_id) m_id = value;
    }
    hstring ComicBlock::Title()
    {
        return m_title;
    }
    void ComicBlock::Title(hstring const& value)
    {
        if (value != m_title) m_title = value;
    }
    hstring ComicBlock::Author()
    {
        return m_author;
    }
    void ComicBlock::Author(hstring const& value)
    {
        if (value != m_author) m_author = value;
    }
    int32_t ComicBlock::PageCount()
    {
        return m_pageCount;
    }
    void ComicBlock::PageCount(int32_t value)
    {
        if (value != m_pageCount) m_pageCount = value;
    }
    int32_t ComicBlock::EpsCount()
    {
        return m_epsCount;
    }
    void ComicBlock::EpsCount(int32_t value)
    {
        if (value != m_epsCount) m_epsCount = value;
    }
    bool ComicBlock::Finished()
    {
        return m_finished;
    }
    void ComicBlock::Finished(bool value)
    {
        if (value != m_finished) m_finished = value;
    }
    winrt::Windows::Data::Json::JsonArray ComicBlock::Categories()
    {
        return m_categories;
    }
    void ComicBlock::Categories(winrt::Windows::Data::Json::JsonArray const& value)
    {
        if (value != m_categories) m_categories = value;
    }
    winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage ComicBlock::Thumb()
    {
        return m_thumb;
    }
    void ComicBlock::Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value)
    {
        if (value != m_thumb) m_thumb = value;
    }
    int32_t ComicBlock::LikesCount()
    {
        return m_likesCount;
    }
    void ComicBlock::LikesCount(int32_t value)
    {
        if (value != m_likesCount) m_likesCount = value;
    }
    winrt::event_token ComicBlock::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void ComicBlock::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
