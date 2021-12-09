#pragma once
#include "ClassBlockViewModel.g.h"
#include "ClassBlock.h"
namespace winrt::bikabika::implementation
{
    struct ClassBlockViewModel : ClassBlockViewModelT<ClassBlockViewModel>
    {
       
        ClassBlockViewModel();

        winrt::bikabika::ClassBlock DefaultClassBlock();
        Windows::Foundation::Collections::IObservableVector<bikabika::ClassBlock> ClassBlocks();

    private:
        winrt::bikabika::ClassBlock m_defaultClassBlock{ nullptr };
        Windows::Foundation::Collections::IObservableVector<bikabika::ClassBlock> m_classBlocks;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct ClassBlockViewModel : ClassBlockViewModelT<ClassBlockViewModel, implementation::ClassBlockViewModel>
    {
    };
}
