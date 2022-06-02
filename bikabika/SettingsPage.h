#pragma once

#include "SettingsPage.g.h"

namespace winrt::bikabika::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage();

        double SettingWidth();
        double SettingConentWidth();

        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);

        void PropertyChanged(winrt::event_token const& token) noexcept;

    private:
        Windows::ApplicationModel::Resources::ResourceLoader resourceLoader{ Windows::ApplicationModel::Resources::ResourceLoader::GetForCurrentView() };
        Windows::Foundation::Collections::IObservableVector<hstring> m_flows = winrt::single_threaded_observable_vector<hstring>();
        bikabika::MainPage rootPage{ MainPage::Current() };
        double m_settingWidth = 600;
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;

    public:
        void BackGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);
        void SettingBikaClientFlow_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void SettingBikaClientFlow_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::bikabika::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
