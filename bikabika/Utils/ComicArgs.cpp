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
