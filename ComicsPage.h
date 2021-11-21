#pragma once

#include "ComicsPage.g.h"
#include "ComicBlock.h"
namespace winrt::bikabika::implementation
{
    struct ComicsPage : ComicsPageT<ComicsPage>
    {
        ComicsPage();

        
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> ComicBlocks();

        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

    private:
        bikabika::FileCheckTool m_fileCheckTool;
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> m_comicBlocks = winrt::single_threaded_observable_vector<bikabika::ComicBlock>();
        int32_t m_total;
        int32_t m_limit;
        int32_t m_page;
        int32_t m_pages;

    };
}

namespace winrt::bikabika::factory_implementation
{
    struct ComicsPage : ComicsPageT<ComicsPage, implementation::ComicsPage>
    {
    };
}
