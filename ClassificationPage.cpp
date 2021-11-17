#include "pch.h"
#include "ClassificationPage.h"
#if __has_include("ClassificationPage.g.cpp")
#include "ClassificationPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    ClassificationPage::ClassificationPage()
    {
        InitializeComponent();
        NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled);
        m_classBlockView = winrt::make<ClassBlockViewModel>();
    }

    bikabika::ClassBlockViewModel ClassificationPage::ClassBlockView()
    {
        return m_classBlockView;
    }

    
}
