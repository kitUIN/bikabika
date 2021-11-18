#pragma once

#include "ClassificationPage.g.h"
#include "ClassBlockViewModel.h"

namespace winrt::bikabika::implementation
{
    struct ClassificationPage : ClassificationPageT<ClassificationPage>
    {
        ClassificationPage();
        bikabika::ClassBlockViewModel ClassBlockView();
        Windows::Foundation::IAsyncAction ReadAuthJson();
        Windows::Foundation::IAsyncAction Init();
        Windows::Foundation::IAsyncOperation<boolean> CheckFile(hstring fileName);
        void HttpLogOut(hstring s1, hstring s2);
        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        bikabika::BikaHttp BikaHttpAPI();
    private:
        bikabika::ClassBlockViewModel m_classBlockView{ nullptr };
        bikabika::BikaHttp m_bikaHttp;
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct ClassificationPage : ClassificationPageT<ClassificationPage, implementation::ClassificationPage>
    {
    };
}
