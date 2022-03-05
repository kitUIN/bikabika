#pragma once
#include "ComicArgs.g.h"

namespace winrt::bikabika::implementation
{
    
    struct ComicArgs : ComicArgsT<ComicArgs>
    {
        ComicArgs() = default;

        winrt::bikabika::ComicsType ComicArgs::ComicType();
        void ComicType(winrt::bikabika::ComicsType const& value);
        hstring Content();
        void Content(hstring const& value);
        winrt::bikabika::SearchSortMode SortMode();
        void SortMode(winrt::bikabika::SearchSortMode const& value);
        hstring ComicArgs::SortModeString();
        bool IsAnime();
        void IsAnime(bool value);

    private:
        winrt::bikabika::ComicsType m_comicType;
        hstring m_content;
        winrt::bikabika::SearchSortMode m_sortMode= winrt::bikabika::SearchSortMode::DD;
        bool m_isAnime=true;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct ComicArgs : ComicArgsT<ComicArgs, implementation::ComicArgs>
    {
    };
}
