#include "pch.h"
#include "ComicArgs.h"
#include "ComicArgs.g.cpp"

namespace winrt::bikabika::implementation
{
    ComicArgs::ComicArgs(winrt::bikabika::ComicsType const& comicType, hstring const& title, BikaClient::Utils::BikaSort const& sortMode)
    {
        ComicType(comicType);
        Title(title);
        SortMode(sortMode);
    }
    winrt::bikabika::ComicsType ComicArgs::ComicType()
    {
        return m_comicType;
    }
    ComicArgs::ComicArgs(hstring const& bookId, int32_t eps, int32_t pageIndex, int32_t page, BikaClient::Utils::BikaSort const& sortMode)
    {
    }
    void ComicArgs::ComicType(winrt::bikabika::ComicsType const& value)
    {
        if (value != m_comicType)
        {
            m_comicType = value;
        }
    }
    hstring ComicArgs::Title()
    {
        return m_title;
    }
    void ComicArgs::Title(hstring const& value)
    {
        if (value != m_title)
        {
            m_title = value;
        }
    }
    hstring ComicArgs::BookId()
    {
        return m_bookId;
    }
    void ComicArgs::BookId(hstring const& value)
    {
        if (value != m_bookId)
        {
            m_bookId = value;
        }
    }
    int32_t ComicArgs::Eps()
    {
        return m_eps;
    }
    void ComicArgs::Eps(int32_t const& value)
    {
        if (value != m_eps)
        {
            m_eps = value;
        }
    }
    int32_t ComicArgs::Page()
    {
        return m_page;
    }
    void ComicArgs::Page(int32_t const& value)
    {
        if (value != m_page)
        {
            m_page = value;
        }
    }
    int32_t ComicArgs::PageIndex()
    {
        return m_pageIndex;
    }
    void ComicArgs::PageIndex(int32_t const& value)
    {
        if (value != m_pageIndex)
        {
            m_pageIndex = value;
        }
    }
    BikaClient::Utils::BikaSort ComicArgs::SortMode()
    {
        return m_bikaSort;
    }
    void ComicArgs::SortMode(BikaClient::Utils::BikaSort const& value)
    {
        m_bikaSort = value;
    }
    hstring ComicArgs::SortModeString()
    {
        return m_bikaSort.SortName(resourceLoader);
    }

    bool ComicArgs::IsAnime()
    {
        return m_isAnime;
    }
    void ComicArgs::IsAnime(bool value)
    {
        if (value != m_isAnime)
        {
            m_isAnime = value;
        }
    }
}
