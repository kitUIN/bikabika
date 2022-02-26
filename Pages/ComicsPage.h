#pragma once

#include "Generated Files/ComicsPage.g.h"
#include "Utils/Blocks/ComicBlock.h"
#include "Utils/Blocks/PageNumBox.h"
namespace winrt::bikabika::implementation
{
    struct ComicsPage : ComicsPageT<ComicsPage>
    {
        ComicsPage();

        
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> ComicBlocks();
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> TypeBlocks();
        Windows::Foundation::IAsyncAction  ContentDialogShow(hstring const& mode, hstring const& message);
        Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        Windows::Foundation::IAsyncAction PipsPager_SelectedIndexChanged(winrt::Microsoft::UI::Xaml::Controls::PipsPager const& sender, winrt::Microsoft::UI::Xaml::Controls::PipsPagerSelectedIndexChangedEventArgs const& args);
        Windows::Foundation::IAsyncAction ComicsPage::Goto(int32_t const& index, hstring const& title, hstring const& mode);
        Windows::Foundation::IAsyncAction GotoSearch(hstring const& keywords, hstring const& mode, Windows::Data::Json::JsonArray const& categories, int32_t const& index);
        Windows::Foundation::IAsyncAction GotoFavourite(hstring const& mode, int32_t const& index);
        void Pips_Loading(winrt::Windows::UI::Xaml::FrameworkElement const& sender, winrt::Windows::Foundation::IInspectable const& args);
        Windows::Foundation::IAsyncAction TypeCombo_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        bikabika::PageNumBox MyPageNumBox();
        void  NumberBox1_ValueChanged(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& sender, winrt::Microsoft::UI::Xaml::Controls::NumberBoxValueChangedEventArgs const& args);
        void GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);

    private:
        bikabika::FileCheckTool m_fileCheckTool;
        bikabika::BikaHttp m_bikaHttp;
        bool m_numberBoxFlag = true;
        bool m_flag1 = false;
        bool m_flag2 = false;
        bool m_flag3 = false;
        hstring m_beforeSort = L"ua";
        ComicsType m_GoType = ComicsType::COMIC;
        winrt::Windows::Foundation::Collections::IObservableVector<bikabika::ComicBlock> m_comicBlocks = winrt::single_threaded_observable_vector<bikabika::ComicBlock>();
        hstring m_sortMode = L"ua";
        int32_t m_total;
        int32_t m_limit;
        int32_t m_sortType = 0;
        Windows::Data::Json::JsonArray m_categories;
        bikabika::PageNumBox m_pageNumBox{ 1,1 ,L"" };
        winrt::Windows::UI::Xaml::Controls::Image m_img;
        };
}

namespace winrt::bikabika::factory_implementation
{
    struct ComicsPage : ComicsPageT<ComicsPage, implementation::ComicsPage>
    {
    };
}
