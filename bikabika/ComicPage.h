#pragma once

#include "ComicPage.g.h"

namespace winrt::bikabika::implementation
{
    struct ComicPage : ComicPageT<ComicPage>
    {
        ComicPage();
        Windows::Foundation::IAsyncAction Goto(int32_t const& index, hstring const& title, BikaClient::Utils::SortMode const& mode);
        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::ComicBlock> Comics();
        int32_t Index();
        int32_t PipIndex();
        int32_t AllPage();
		void AllPage(int32_t const& value);
		void Index(int32_t const& value);

    private:
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
        bikabika::MainPage rootPage{ MainPage::Current() };
        int32_t m_index = 0;
        int32_t m_pages = 1;
        bool m_firstArrive = false;
        bikabika::ComicsType m_comicType = bikabika::ComicsType::COMIC;
        BikaClient::Utils::SortMode m_sort = BikaClient::Utils::SortMode::UA;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::ComicBlock> m_comics = winrt::single_threaded_observable_vector<winrt::BikaClient::Blocks::ComicBlock>();
        winrt::Windows::Foundation::Collections::IObservableVector<hstring> m_typeBlocks = winrt::single_threaded_observable_vector<hstring>({ resourceLoader.GetString(L"sort/ua"),resourceLoader.GetString(L"sort/dd"),resourceLoader.GetString(L"sort/da"),resourceLoader.GetString(L"sort/ld"),resourceLoader.GetString(L"sort/vd") });
    public:
        Windows::Foundation::IAsyncAction TypeCombo_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void Index_KeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction PipsPager_SelectedIndexChanged(winrt::Microsoft::UI::Xaml::Controls::PipsPager const& sender, winrt::Microsoft::UI::Xaml::Controls::PipsPagerSelectedIndexChangedEventArgs const& args);
        Windows::Foundation::IAsyncAction RefreshButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct ComicPage : ComicPageT<ComicPage, implementation::ComicPage>
    {
    };
}
