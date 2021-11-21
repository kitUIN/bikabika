#pragma once
#include "SuggestBlockViewModel.g.h"
#include <SuggestBlock.h>

namespace winrt::bikabika::implementation
{
    struct SuggestBlockViewModel : SuggestBlockViewModelT<SuggestBlockViewModel>
    {
        SuggestBlockViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::bikabika::SuggestBlock> SuggestBlocks();
    private:
       Windows::Foundation::Collections::IObservableVector<bikabika::SuggestBlock> m_suggestBlocks;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct SuggestBlockViewModel : SuggestBlockViewModelT<SuggestBlockViewModel, implementation::SuggestBlockViewModel>
    {
    };
}
