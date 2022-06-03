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
        BikaClient::Utils::BikaSort SortMode();
        void SortMode(BikaClient::Utils::BikaSort const& value);
        hstring ComicArgs::SortModeString();
        bool IsAnime();
        void IsAnime(bool value);

    private:
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
        winrt::bikabika::ComicsType m_comicType;
        hstring m_content;
        BikaClient::Utils::BikaSort m_bikaSort{ BikaClient::Utils::SortMode::DD };
        bool m_isAnime=true;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct ComicArgs : ComicArgsT<ComicArgs, implementation::ComicArgs>
    {
    };
}
