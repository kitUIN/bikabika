#pragma once
#include "PicArgs.g.h"


namespace winrt::bikabika::implementation
{
    struct PicArgs : PicArgsT<PicArgs>
    {
        PicArgs() = default;

        PicArgs(hstring const& bookId, int32_t total, winrt::BikaClient::Blocks::EpisodeBlock const& ep, int32_t order, winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::EpisodeBlock> const& eps);
        PicArgs(hstring const& bookId, int32_t total, winrt::BikaClient::Blocks::EpisodeBlock const& ep, winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::EpisodeBlock> const& eps);
        hstring BookId();
        void BookId(hstring const& value);
        int32_t Total();
        void Total(int32_t value);
        int32_t Order();
        void Order(int32_t value);
        winrt::BikaClient::Blocks::EpisodeBlock Episode();
        void Episode(winrt::BikaClient::Blocks::EpisodeBlock const& value);
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::EpisodeBlock> Episodes();
        void Episodes(winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::EpisodeBlock> const& value);
    private:
        hstring m_bookId = L"";
        int32_t m_total = 0;
        int32_t m_order = 0;
        winrt::BikaClient::Blocks::EpisodeBlock m_ep;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::EpisodeBlock> m_eps = winrt::single_threaded_observable_vector<BikaClient::Blocks::EpisodeBlock>();
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct PicArgs : PicArgsT<PicArgs, implementation::PicArgs>
    {
    };
}
