#pragma once

#include "ClassificationPage.g.h"

namespace winrt::bikabika::implementation
{
    struct ClassificationPage : ClassificationPageT<ClassificationPage>
    {
        ClassificationPage();
        Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::CategoriesBlock> Categories();
		void Categories(winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::CategoriesBlock> const& value);
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
        bikabika::MainPage rootPage{ MainPage::Current() };
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::BikaClient::Blocks::CategoriesBlock> m_categories = winrt::single_threaded_observable_vector<winrt::BikaClient::Blocks::CategoriesBlock>();


    public:
        void GridV_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);
        void Image_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void Image_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct ClassificationPage : ClassificationPageT<ClassificationPage, implementation::ClassificationPage>
    {
    };
}
