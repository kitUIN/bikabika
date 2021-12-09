#pragma once
#include "Utils/API/BikaHttp.h"
#include "PicPage.g.h"
#include "Utils/Blocks/PicturesBlock.h"
#include "Utils/Blocks/EpisodeBlock.h"
namespace winrt::bikabika::implementation
{
    struct PicPage : PicPageT<PicPage>
    {
        PicPage();
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::PicturesBlock> PicturesBlocks();
        Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        Windows::Foundation::IAsyncAction Goto(int32_t const& order, int32_t const& page);
        void ScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e);
        Windows::Foundation::IAsyncAction DownEps_ActionButtonClick(winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& sender, winrt::Windows::Foundation::IInspectable const& args);

    private:
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::PicturesBlock> m_picturesBlocks= winrt::single_threaded_observable_vector<bikabika::PicturesBlock>();
        hstring m_id;
        int32_t m_order;
        bikabika::BikaHttp m_bikaHttp;
        hstring m_bookId;
        int32_t m_epsTotal;
        int32_t m_pageOrder = 1;
        int32_t m_page;
        int32_t m_pages;
        int32_t m_pageTotal;
        int32_t m_pageLimit;

    };
}

namespace winrt::bikabika::factory_implementation
{
    struct PicPage : PicPageT<PicPage, implementation::PicPage>
    {
    };
}
