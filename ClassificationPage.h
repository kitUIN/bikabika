#pragma once

#include "ClassificationPage.g.h"
#include "ClassBlockViewModel.h"

namespace winrt::bikabika::implementation
{
    struct ClassificationPage : ClassificationPageT<ClassificationPage>
    {
        ClassificationPage();
        bikabika::ClassBlockViewModel ClassBlockView();
    private:
        bikabika::ClassBlockViewModel m_classBlockView{ nullptr };
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct ClassificationPage : ClassificationPageT<ClassificationPage, implementation::ClassificationPage>
    {
    };
}
