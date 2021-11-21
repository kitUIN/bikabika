#include "pch.h"
#include "ComicsPage.h"
#if __has_include("ComicsPage.g.cpp")
#include "ComicsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::bikabika::implementation
{
    ComicsPage::ComicsPage()
    {
        InitializeComponent();
    }

    
    
    winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> ComicsPage::ComicBlocks()
    {
        return m_comicBlocks;
    }

    
}
