#include "pch.h"
#include "ComicArgs.h"
#include "ComicArgs.g.cpp"

namespace winrt::bikabika::implementation
{
    winrt::bikabika::ComicsType ComicArgs::ComicType()
    {
        return m_comicType;
    }
    void ComicArgs::ComicType(winrt::bikabika::ComicsType const& value)
    {
        if (value != m_comicType)
        {
            m_comicType = value;
        }
    }
    hstring ComicArgs::Content()
    {
        return m_content;
    }
    void ComicArgs::Content(hstring const& value)
    {
        if (value != m_content)
        {
            m_content = value;
        }
    }
    winrt::bikabika::SearchSortMode ComicArgs::SortMode()
    {
        return m_sortMode;
    }
    void ComicArgs::SortMode(winrt::bikabika::SearchSortMode const& value)
    {
        if (value != m_sortMode)
        {
            m_sortMode = value;
        }
    }
    hstring ComicArgs::SortModeString()
    {
        if (m_sortMode == winrt::bikabika::SearchSortMode::UA) return L"ua";
        else if (m_sortMode == winrt::bikabika::SearchSortMode::DD) return L"dd";
        else if (m_sortMode == winrt::bikabika::SearchSortMode::DA)return L"da";
        else if (m_sortMode == winrt::bikabika::SearchSortMode::LD) return L"ld";
        else if (m_sortMode == winrt::bikabika::SearchSortMode::VD) return L"vd";
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
