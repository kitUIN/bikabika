#pragma once

#include "ClassificationPage.g.h"
#include "Utils/Blocks/ClassBlockViewModel.h"

namespace winrt::bikabika::implementation
{
    struct ClassificationPage : ClassificationPageT<ClassificationPage>
    {
        ClassificationPage();
        bikabika::ClassBlockViewModel ClassBlockView();
        Windows::Foundation::IAsyncAction ContentDialogShow(hstring const& mode, hstring const& message);
        Windows::Foundation::IAsyncAction Init();
        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        bikabika::BikaHttp BikaHttpAPI();
        void  GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);

    private:
        bikabika::ClassBlockViewModel m_classBlockView{ nullptr };
        bikabika::BikaHttp m_bikaHttp;
        bikabika::FileCheckTool m_fileCheckTool;
        };
}

namespace winrt::bikabika::factory_implementation
{
    struct ClassificationPage : ClassificationPageT<ClassificationPage, implementation::ClassificationPage>
    {
    };
}
