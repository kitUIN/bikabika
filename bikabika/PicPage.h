#pragma once

#include "PicPage.g.h"

namespace winrt::bikabika::implementation
{
    struct PicPage : PicPageT<PicPage>
    {
        PicPage();

        winrt::Windows::Foundation::Collections::IObservableVector<BikaClient::Blocks::ImageBlock> PicturesBlocks();
        Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        Windows::Foundation::IAsyncAction Goto(int32_t const& order, int32_t const& page);
        void ScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e);
        void DownEps_ActionButtonClick(winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& sender, winrt::Windows::Foundation::IInspectable const& args);

    private:
        bikabika::MainPage rootPage{ MainPage::Current() };
        bikabika::PicArgs m_params;
        winrt::Windows::Foundation::Collections::IObservableVector<BikaClient::Blocks::ImageBlock> m_picturesBlocks = winrt::single_threaded_observable_vector<BikaClient::Blocks::ImageBlock>();
        BikaClient::Responses::PicturesResponse m_picRes{ nullptr };
        int32_t m_order;
        int32_t m_epsTotal;
        hstring m_bookId;
        int32_t m_pageOrder = 1;
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct PicPage : PicPageT<PicPage, implementation::PicPage>
    {
    };
}
