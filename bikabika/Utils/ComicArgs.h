#pragma once
#include "ComicArgs.g.h"

namespace winrt::bikabika::implementation
{

    struct ComicArgs : ComicArgsT<ComicArgs>
    {
        ComicArgs() = default;
        ComicArgs(winrt::bikabika::ComicsType const& comicType,hstring const& title, BikaClient::Utils::BikaSort const& sortMode);
        winrt::bikabika::ComicsType ComicType();
        void ComicType(winrt::bikabika::ComicsType const& value);
        hstring Title();
        void Title(hstring const& value);
        BikaClient::Utils::BikaSort SortMode();
        void SortMode(BikaClient::Utils::BikaSort const& value);
        hstring SortModeString();
        bool IsAnime();
        void IsAnime(bool value);

    private:
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
        winrt::bikabika::ComicsType m_comicType;
        hstring m_title;
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
