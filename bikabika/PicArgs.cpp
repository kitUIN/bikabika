#include "pch.h"
#include "PicArgs.h"
#include "PicArgs.g.cpp"


namespace winrt::bikabika::implementation
{
    PicArgs::PicArgs(hstring const& bookId, int32_t total, winrt::BikaClient::Blocks::EpisodeBlock const& ep, int32_t order, winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::EpisodeBlock> const& eps)
    {
        m_bookId = bookId;
        m_total = total;
        m_order = order;
        m_ep = ep;
        m_eps = eps;
    }
    PicArgs::PicArgs(hstring const& bookId, int32_t total, winrt::BikaClient::Blocks::EpisodeBlock const& ep, winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::EpisodeBlock> const& eps)
    {
        m_bookId = bookId;
        m_total = total;
        m_order = ep.Order();
        m_ep = ep;
        m_eps = eps;
    }
    hstring PicArgs::BookId()
    {
        return m_bookId;
    }
    void PicArgs::BookId(hstring const& value)
    {
        m_bookId = value;
    }
    int32_t PicArgs::Total()
    {
        return m_total;
    }
    void PicArgs::Total(int32_t value)
    {
        m_total = value;
    }
    int32_t PicArgs::Order()
    {
        return m_order;
    }
    void PicArgs::Order(int32_t value)
    {
        m_order = value;
    }
    winrt::BikaClient::Blocks::EpisodeBlock PicArgs::Episode()
    {
        return m_ep;
    }
    void PicArgs::Episode(winrt::BikaClient::Blocks::EpisodeBlock const& value)
    {
        m_ep = value;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::EpisodeBlock> PicArgs::Episodes()
    {
        return m_eps;
    }
    void PicArgs::Episodes(winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::EpisodeBlock> const& value)
    {
        m_eps = value;
    }
}
