#pragma once

#include "ComicsPage.g.h"
#include "ComicBlock.h"
namespace winrt::bikabika::implementation
{
    struct ComicsPage : ComicsPageT<ComicsPage>
    {
        ComicsPage();

        void MyProperty(int32_t value);
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> ComicBlocks();
        
    private:
        bikabika::FileCheckTool m_fileCheckTool;
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> m_comicBlocks = winrt::single_threaded_observable_vector<bikabika::ComicBlock>();

    };
}

namespace winrt::bikabika::factory_implementation
{
    struct ComicsPage : ComicsPageT<ComicsPage, implementation::ComicsPage>
    {
    };
}
