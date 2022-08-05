#include "pch.h"
#include "PicPage.h"
#if __has_include("PicPage.g.cpp")
#include "PicPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    PicPage::PicPage()
    {
        InitializeComponent();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<BikaClient::Blocks::ImageBlock> PicPage::PicturesBlocks()
    {
        return m_picturesBlocks;
    }

    Windows::Foundation::IAsyncAction PicPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        m_params = winrt::unbox_value<bikabika::PicArgs>(e.Parameter());
        m_bookId = m_params.BookId();
        m_order = m_params.Order();
        m_epsTotal = m_params.Total();
        co_await Goto(m_order, 1);
    }

    Windows::Foundation::IAsyncAction PicPage::Goto(int32_t const& order, int32_t const& page)
    {
        BikaClient::Responses::PicturesResponse res = co_await rootPage.HttpClient().Pictures(m_bookId, order, page);
        if (res.Code() == -1)
        {
            rootPage.ContentDialogShow(BikaHttpStatus::TIMEOUT, L"");
        }
        else if (res.Code() == 200)
        {

            for (auto x : res.Pictures())
            {
                x.Order(m_pageOrder++);
                m_picturesBlocks.Append(x);
            }
            if (res.Page() < res.Pages())
            {
                co_await Goto(m_order, res.Page() + 1);
            }
        }
        else if (res.Code() == 401 && res.Error() == L"1005")
        {
            rootPage.ContentDialogShow(BikaHttpStatus::NOAUTH, res.Message());
        }
        else
        {
            rootPage.ContentDialogShow(BikaHttpStatus::UNKNOWN, res.Message());
        }
    }

    void PicPage::ScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e)
    {
        auto sv = sender.as<winrt::Windows::UI::Xaml::Controls::ScrollViewer>();
        if (sv.VerticalOffset() + sv.ActualHeight() + 2 >= sv.ExtentHeight()) {
            if (m_order < m_epsTotal)
            {
                DownEps().IsOpen(true);
            }
        }
    }
    void winrt::bikabika::implementation::PicPage::DownEps_ActionButtonClick(winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& sender, winrt::Windows::Foundation::IInspectable const& args)
    {
        Windows::Storage::ApplicationDataContainer historys = Windows::Storage::ApplicationData::Current().LocalSettings().CreateContainer(L"Historys", Windows::Storage::ApplicationDataCreateDisposition::Always);
        m_params.Order(m_order + 1);
        for (auto x : m_params.Episodes())
        {
            if (x.Order() == m_params.Order())
            {
                m_params.Episode(x);
                break;
            }
        }
        DownEps().IsOpen(false);
        winrt::Microsoft::UI::Xaml::Controls::SymbolIconSource symbol;
        winrt::Windows::UI::Xaml::Controls::Frame frame;
        symbol.Symbol(Windows::UI::Xaml::Controls::Symbol::Pictures);
        frame.Navigate(winrt::xaml_typename<bikabika::PicPage>(), box_value(m_params));
        rootPage.CreateNewTab(frame, m_params.Episode().Title(), symbol);
    }
}
