#pragma once
#include "ClassBlockViewModel.g.h"
#include "ClassBlock.h"
namespace winrt::bikabika::implementation
{
    struct ClassBlockViewModel : ClassBlockViewModelT<ClassBlockViewModel>
    {
        ClassBlockViewModel();
        ClassBlockViewModel(Windows::Data::Json::JsonArray jsonArray);

        winrt::bikabika::ClassBlock DefaultClassBlock();
        Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> ClassBlocks();

    private:
        winrt::bikabika::ClassBlock m_defaultClassBlock{ nullptr };
        Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> m_classBlocks;
    };
}
namespace winrt::bikabika::factory_implementation
{
    struct ClassBlockViewModel : ClassBlockViewModelT<ClassBlockViewModel, implementation::ClassBlockViewModel>
    {
    };
}
