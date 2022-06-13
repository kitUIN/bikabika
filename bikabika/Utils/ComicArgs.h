#pragma once
#include "ComicArgs.g.h"

namespace winrt::bikabika::implementation
{

    struct ComicArgs : ComicArgsT<ComicArgs>
    {
        ComicArgs() = default;
        ComicArgs(winrt::bikabika::ComicsType const& comicType,hstring const& title, BikaClient::Utils::BikaSort const& sortMode);
        ComicArgs(hstring const& bookId,int32_t eps,int32_t pageIndex, int32_t page, BikaClient::Utils::BikaSort const& sortMode);
        winrt::bikabika::ComicsType ComicType();
        void ComicType(winrt::bikabika::ComicsType const& value);
        hstring Title();
        void Title(hstring const& value);
        hstring BookId();
        void BookId(hstring const& value);
        int32_t Eps();
        void Eps(int32_t const& value);
        int32_t Page();
        void Page(int32_t const& value);
        int32_t PageIndex();
        void PageIndex(int32_t const& value);
        BikaClient::Utils::BikaSort SortMode();
        void SortMode(BikaClient::Utils::BikaSort const& value);
        hstring SortModeString();
        bool IsAnime();
        void IsAnime(bool value);

    private:
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
        winrt::bikabika::ComicsType m_comicType = winrt::bikabika::ComicsType::BOOK;
        hstring m_title = L"";
        hstring m_bookId = L"";
        int32_t m_eps = 1;
        int32_t m_pageIndex = 1;
        int32_t m_page = 1;
        BikaClient::Utils::BikaSort m_bikaSort{ BikaClient::Utils::SortMode::DD };
        bool m_isAnime = true;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct ComicArgs : ComicArgsT<ComicArgs, implementation::ComicArgs>
    {
    };
}
