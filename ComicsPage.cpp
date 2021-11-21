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

        NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled);
    }

    
    
    winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> ComicsPage::ComicBlocks()
    {
        return m_comicBlocks;
    }

    void ComicsPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        winrt::Windows::Data::Json::JsonObject jsonObject = winrt::unbox_value<winrt::Windows::Data::Json::JsonObject>(e.Parameter());
        m_limit = jsonObject.GetNamedNumber(L"limit");
        m_total = jsonObject.GetNamedNumber(L"total");
        m_page = jsonObject.GetNamedNumber(L"page");
        m_pages = jsonObject.GetNamedNumber(L"pages");
        for (auto x : jsonObject.GetNamedArray(L"docs"))
        {
            m_comicBlocks.Append(winrt::make<ComicBlock>(x.GetObject()));
        }
        
        
        __super::OnNavigatedTo(e);
    }
    
}
